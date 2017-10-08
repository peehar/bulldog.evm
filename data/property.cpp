/*
 * Copyright 2017 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "property.h"
#include "../typeerror.h"
#include "function.h"
#include "cast.h"

using namespace data;
using namespace std;

Data DataProperty::getValue(Object* obj)
{
    return mValue;
}

void DataProperty::putValue(const Data& data, bool t, Object* obj)
{
    if (!this->mWritable)
    {
        if (t)
            throw TypeError();
    }
    else
    {
        mValue = data;
    }
}

void DataProperty::defineDataProperty(Obejct* desc)
{
    bool configurable_bool = mConfig;
    bool enumerable_bool = mEnum;
    bool writable_bool = mWritable;
    if (!mConfig) 
    {
        string configurable_str("configurable");
        if (desc->hasProperty(configurable_str))
        {
            Data configurable_data = desc->getValue(configurable_str);
            configurable_bool = (configurable_data);
            if (configurable_bool)
                throw TypeError();
        }
                
        string enumerable_str("enumerable");
        if (desc->hasProperty(enumerable_str))
        {
            Data enumerable_data = desc->getValue(enumerable_str);
            enumerable_bool = ToBoolean(enumerable_data);
            if (enumerable_bool != mEnum)
                throw TypeError();
        }
        
        string writable_str("writable");
        if (desc->hasProperty(writable_str))
        {
            Data writable_data = desc->getValue(writable_str);
            writable_bool = ToBoolean(writable_data);
            if (writable_bool != mWritable)
                throw TypeError();
        }
    }
    mConfig = configurable_bool;
    mEnum = enumerable_bool;
    mWritable = writable_bool;
    
    string value_str("value");
    if (desc->hasProperty(value_str))
    {
        mValue = desc->getValue(value_str);
    }
}

Data AccessorProperty::getValue(Object* obj)
{
    if (mGetter == nullptr)
        return Data::newUndefined();
    return mGetter->call(obj);
}

void AccessorProperty::putValue(const Data& data, bool t, Object* obj)
{
    if (mSetter == nullptr)
    {
        if (t)
            throw TypeError();
    }
    else
    {
        std::list<Data> param = { data };
        mSetter->call(obj, param);
    }
}

void AccessorProperty::defineDataProperty(Obejct* desc)
{
    bool configurable_bool = mConfig;
    bool enumerable_bool = mEnum;
    Data get_data = mGetter;
    Data set_data = mSetter;
    if (!mConfig) 
    {
        string configurable_str("configurable");
        if (desc->hasProperty(configurable_str))
        {
            Data configurable_data = desc->getValue(configurable_str);
            configurable_bool = ToBoolean(configurable_data);
            if (configurable_bool)
                throw TypeError();
        }
                
        string enumerable_str("enumerable");
        if (desc->hasProperty(enumerable_str))
        {
            Data enumerable_data = desc->getValue(enumerable_str);
            enumerable_bool = ToBoolean(enumerable_data);
            if (enumerable_bool != mEnum)
                throw TypeError();
        }
        
        string get_str("get");
        if (desc->hasProperty(get_str))
        {
            Data get_data = desc->getValue(get_str);
            if (get_data != mGetter)
                throw TypeError();
        }
        
        string set_str("set");
        if (desc->hasProperty(set_str))
        {
            Data set_data = desc->getValue(set_str);
            if (set_data != mSetter)
                throw TypeError();
        }
    }
    mConfig = configurable_bool;
    mEnum = enumerable_bool;
    mGetter = get_data;
    mSetter = set_data;
}

PropertyPtr::PropertyPtr(Obejct* desc)
{
    if (isAccessorDesc(desc))
    {
        bool configurable_bool = false;
        bool enumerable_bool = false;
        Function* get_func = nullptr;
        Function* set_func = nullptr;
        string configurable_str("configurable");
        if (desc->hasProperty(configurable_str))
        {
            Data configurable_data = desc->getValue(configurable_str);
            configurable_bool = ToBoolean(configurable_data);
        }
                
        string enumerable_str("enumerable");
        if (desc->hasProperty(enumerable_str))
        {
            Data enumerable_data = desc->getValue(enumerable_str);
            enumerable_bool = ToBoolean(enumerable_data);
        }
        
        string get_str("get");
        if (desc->hasProperty(get_str))
        {
            Data get_data = desc->getValue(get_str);
            get_func = dynamic_cast<Function*>(get_data.object());
            if (get_func == nullptr)
                throw TypeError();
        }
        
        string set_str("set");
        if (desc->hasProperty(set_str))
        {
            Data set_data = desc->getValue(set_str);
            set_func = dynamic_cast<Function*>(set_data.object());
            if (set_func == nullptr)
                throw TypeError();
        }
        
        reset(new AccessorProperty(get_func, set_func, enumerable_bool, configurable_bool));
    }
    else 
    {
        bool configurable_bool = false;
        bool enumerable_bool = false;
        bool writable_bool = false;
        Data value = Data::newUndefined();
        
        string configurable_str("configurable");
        if (desc->hasProperty(configurable_str))
        {
            Data configurable_data = desc->getValue(configurable_str);
            configurable_bool = ToBoolean(configurable_data);
        }
                
        string enumerable_str("enumerable");
        if (desc->hasProperty(enumerable_str))
        {
            Data enumerable_data = desc->getValue(enumerable_str);
            enumerable_bool = ToBoolean(enumerable_data);
        }
        
        string writable_str("writable");
        if (desc->hasProperty(writable_str))
        {
            Data writable_data = desc->getValue(writable_str);
            writable_bool = ToBoolean(writable_data);
        }
        
        string value_str("value");
        if (desc->hasProperty(value_str))
        {
            value = desc->getValue(value_str);
        }
        
        reset(new DataProperty(value, writable_bool, enumerable_bool, configurable_bool));
    }
    
}

void PropertyPtr::defineDataProperty(Obejct* desc)
{
    
}
