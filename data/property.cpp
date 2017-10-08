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
#include "object.h"

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

void DataProperty::define(DataPropertyDesc& desc)
{
    if (!mConfig) 
    {
        if (!desc.configurable.isNull()) 
        {
            mConfig = desc.configurable;
        }
        
        if (!desc.enumrable.isNull()) 
        {
            mEnum = desc.enumrable;
        }
        
        if (!desc.writable.isNull())
        {
            mWritable = desc.writable;
        }
    }

    if (!desc.value.isNull())
    {
        mValue = desc.value;
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

void AccessorProperty::define(AccessorPropertyDesc& desc)
{
    if (!mConfig) 
    {
        if (!desc.configurable.isNull()) 
        {
            mConfig = desc.configurable;
        }
        
        if (!desc.enumrable.isNull()) 
        {
            mEnum = desc.enumrable;
        }
                
        if (!desc.getter.isNull())
        {
            mGetter = desc.getter;
        }
        
        if (!desc.setter.isNull())
        {
            mSetter = desc.setter;
        }
    }
}
