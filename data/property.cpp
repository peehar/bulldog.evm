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
#include "function.h"
#include "object.h"

using namespace data;
using namespace std;


BaseProperty::BaseProperty(bool enumerable, bool configurable)
: mEnum(enumerable), mConfig(configurable)
{
}

void BaseProperty::define(Object* desc, bool t)
{
    if (desc->hasProperty("enumerable"))
    {
        Data val = desc->getValue("enumerable");
        bool b = val.toBoolean();
        if (!mConfig && mEnum != b)
            reject(t);
        else
            mEnum = b;
    }
    if (desc->hasProperty("configurable"))
    {
        Data val = desc->getValue("configurable");
        bool b = val.toBoolean();
        if (!mConfig && b)
            reject(t);
        else
            mConfig = b;
    }
}

DataProperty::DataProperty(Data value, bool writable, bool enumerable, bool configurable)
: Property(enumerable, configurable), mValue(value), mWritable(writable)
{
}

Data DataProperty::getValue(Object* obj)
{
    return mValue;
}

void DataProperty::putValue(const Data& data, Object* obj, bool t)
{
    if (!this->mWritable)
        reject(t);
    else
        mValue = data;
}

void DataProperty::define(Object* desc, bool t)
{
    if (desc->hasProperty("writable"))
    {
        Data val = desc->getValue("writable");
        bool b = val.toBoolean();
        if (!mConfig && !mWritable && b)
            reject(t);
        else
            mEnum = b;
    }
    if (desc->hasProperty("value"))
    {
        Data val = desc->getValue("value");
        if (!mWritable && mValue != val)
            reject(t);
        else
            mValue = val;
    }
    BaseProperty::define(desc, t);
}

AccessorProperty::AccessorProperty(Function* getter, Function* setter, bool enumerable, bool configurable)
: Property(enumerable, configurable), mGetter(getter), mSetter(setter)
{
}

Data AccessorProperty::getValue(Object* obj)
{
    if (mGetter == nullptr)
        return Data::newUndefined();
    return mGetter->call(obj);
}

void AccessorProperty::putValue(const Data& data, Object* obj, bool t)
{
    if (mSetter == nullptr)
    {
        reject(t);
    }
    else
    {
        std::list<Data> param = { data };
        mSetter->call(obj, param);
    }
}

void AccessorProperty::define(Object* desc, bool t)
{
    if (desc->hasProperty("get"))
    {
        Data val = desc->getValue("get");
        if (val != Data::OBJECT)
        {
            Function* func = dynamic_cast<Function*>(val.object());
            if (func == nullptr)
                reject(t);
            else
                mGetter = func;
        }
    }
    if (desc->hasProperty("set"))
    {
        Data val = desc->getValue("get");
        if (val != Data::OBJECT)
        {
            Function* func = dynamic_cast<Function*>(val.object());
            if (func == nullptr)
                reject(t);
            else
                mSetter = func;
        }
    }
    BaseProperty::define(desc, t);
}

Data PropertyProxy::getValue(Object* obj)
{
    return prop->getValue(obj);
}

void PropertyProxy::putValue(const Data& data, Object* obj, bool t)
{
    prop->putValue(data, obj, t);
}

Type PropertyProxy::type()
{
    return prop->type();
}

void PropertyProxy::define(Object* desc, bool t)
{
    if (desc->hasProperty("writable") || desc->hasProperty("value"))
    {
        if (prop != nullptr)
        {
            Data::Type type = prop->type();
            if (type == DATA_PROPERTY)
            {
                prop->define(desc, t);
            }
            else
            {
            }
        }
        else
        {
        }
    }
    else if (desc->hasProperty("get") || desc->hasProperty("set"))
    {
        if (prop != nullptr) 
        {
            if (type == ACCESSOR_PROPERTY)
            {
                prop->define(desc, t);
            }
            else 
            {
            }
        }
        else
        {
        }
    }
    else 
    {
        if (prop != nullptr) 
        {
            prop->define(desc, t);
        }
        else
        {
        }
    }
}

