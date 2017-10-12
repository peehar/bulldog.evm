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

DataProperty::DataProperty(PropertyDescPtr desc)
{
    mValue = Data::newUndefined();
    mWritable = false;
    mEnum = desc->enumrable.get(false);
    mConfig = desc->configurable.get(false);
}

DataProperty::DataProperty(DataPropertyDescPtr desc)
{
    mValue = desc->value.get(Data::newUndefined());
    mWritable = desc->writable.get(false);
    mEnum = desc->enumrable.get(false);
    mConfig = desc->configurable.get(false);
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

void DataProperty::define(DataPropertyDescPtr& desc, bool t)
{
    if (!desc->configurable.isNull())
    {
        if (!mConfig && desc->configurable)
            reject(t);
        else
            mConfig = desc->configurable;
    }

    if (!desc->enumrable.isNull())
    {
        if (!mConfig && mEnum != desc->enumrable)
            reject(t);
        else
            mEnum = desc->enumrable;
    }

    if (!desc->writable.isNull())
    {
        if (!mConfig && mWritable != desc->writable)
            reject(t);
        else
            mWritable = desc->writable;
    }

    if (!desc->value.isNull())
    {
        mValue = desc->value;
    }
    
}

data::AccessorProperty::AccessorProperty(AccessorPropertyDescPtr desc)
{
    mGetter = desc->getter;
    mSetter = desc->setter;
    mEnum = desc->enumrable.get(false);
    mConfig = desc->configurable.get(false);
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

void AccessorProperty::define(AccessorPropertyDescPtr& desc, bool t)
{
    if (!desc->configurable.isNull())
    {
        if (!mConfig && desc->configurable)
            reject(t);
        else
            mConfig = desc->configurable;
    }

    if (!desc->enumrable.isNull())
    {
        if (!mConfig && desc->enumrable)
            reject(t);
        else
            mEnum = desc->enumrable;
    }

    if (desc->getter != nullptr)
    {
        if (!mConfig && mGetter != desc->getter)
            reject(t);
        else
            mGetter = desc->getter;
    }

    if (desc->setter != nullptr)
    {
        if (!mConfig && mSetter != desc->setter)
            reject(t);
        else
            mSetter = desc->setter;
    }
}
