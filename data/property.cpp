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
#include "../typeerror.h"

using namespace data;
using namespace std;

Property::Property()
{
    mEnum = false;
    mConfig = false;
}

Property::Property(const Data& data)
{
    mEnum = true;
    mConfig = true;
    factor = shared_ptr<PropertyFactor>(new DataPropertyFactor(data, true, this));
}

Data Property::getValue(Object* obj)
{
    return factor->getValue(obj);
}

void Property::putValue(const Data& data, Object* obj)
{
    factor->putValue(data, obj);
}

void Property::define(Object* desc)
{
    if (desc->hasProperty("enumerable"))
    {
        Data val = desc->getValue("enumerable");
        bool b = val.toBoolean();
        if (!mConfig && mEnum != b) 
            throw Reject();
        mEnum = b;
    }
    if (desc->hasProperty("configurable"))
    {
        Data val = desc->getValue("configurable");
        bool b = val.toBoolean();
        if (!mConfig && b)
            throw Reject();
        mConfig = b;
    }
    
    Type type = factor->type();
    if ( (type != data::DATA_PROPERTY && isDataDesc(desc)) ||
        (type != data::ACCESSOR_PROPERTY && isAccessorDesc(desc)) )
    {
        factor = createFactor(this, desc);
    }
    else
    {
        factor->define(desc);
    }
}

Type Property::type()
{
    return factor->type();
}

PropertyPtr Property::create(Object* desc)
{
    Property* prop = new Property();
    if (desc->hasProperty("enumerable"))
    {
        Data val = desc->getValue("enumerable");
        prop->mEnum = val.toBoolean();
    }
    if (desc->hasProperty("configurable"))
    {
        Data val = desc->getValue("configurable");
        prop->mConfig =  val.toBoolean();
    }
    prop->factor = createFactor(prop, desc);
    return PropertyPtr(prop);
}

shared_ptr< PropertyFactor > Property::createFactor(Property* prop, Object* desc)
{
    PropertyFactor* factor;
    if (isDataDesc(desc))
    {
        bool writable = false;
        Data value;
        
        if (desc->hasProperty("writable")) 
        {
            Data val = desc->getValue("writable");
            writable = val.toBoolean();
        }
        if (desc->hasProperty("value"))
        {
            value = desc->getValue("value");
        }
        factor = new DataPropertyFactor(value, writable, prop);
    }
    else if (isAccessorDesc(desc))
    {
        Function *get, *set;
        if (desc->hasProperty("get"))
        {
            auto val = desc->getValue("get");
            if (val != Data::OBJECT) {
                auto obj = val.object();
                auto func = dynamic_cast<Function*>(obj);
                if (func == nullptr)
                    throw Reject();
                get = func;
            }
        }
        
        if (desc->hasProperty("set"))
        {
            auto val = desc->getValue("set");
            if (val != Data::OBJECT) {
                auto obj = val.object();
                auto func = dynamic_cast<Function*>(obj);
                if (func == nullptr)
                    throw Reject();
                set = func;
            }
        }
        factor = new AccessorPropertyFactor(get, set, prop);
    }
    else 
    {
        factor = new DataPropertyFactor(Data(), false, prop);
    }
    
    return shared_ptr<PropertyFactor>(factor);
}


bool Property::isDataDesc(Object* desc)
{
    return desc->hasProperty("writable") || desc->hasProperty("value");
}

bool Property::isAccessorDesc(Object* desc)
{
    return desc->hasProperty("get") || desc->hasProperty("set");
}

DataPropertyFactor::DataPropertyFactor(const Data value, bool writable, Property* prop)
: PropertyFactor(prop), mValue(value), mWritable(writable)
{
}

Data DataPropertyFactor::getValue(Object* obj)
{
    return mValue;
}
void DataPropertyFactor::putValue(const Data& data, Object* obj)
{
    mValue = data;
}

void DataPropertyFactor::define(Object* desc)
{
    if (desc->hasProperty("value"))
    {
        auto val = desc->getValue("value");
        if (!mWritable && mValue != val) 
            throw Reject();
        mValue = val;
    }
    if (desc->hasProperty("writable")) 
    {
        auto val = desc->getValue("writable");
        bool b = val.toBoolean();
        if (!mWritable && !mProp->mConfig && b)
            throw Reject();
        mWritable = b;
    }
}


AccessorPropertyFactor::AccessorPropertyFactor(Function* getter, Function* setter, Property* prop)
: PropertyFactor(prop), mGetter(getter), mSetter(setter)
{

}

Data AccessorPropertyFactor::getValue(Object* obj)
{
    if (mGetter == nullptr)
        return Data::newUndefined();
    return mGetter->call(obj);
}

void AccessorPropertyFactor::putValue(const Data& data, Object* obj)
{
    if (mSetter == nullptr)
    {
        throw Reject();
    }
    else
    {
        std::list<Data> param = { data };
        mSetter->call(obj, param);
    }
}


void AccessorPropertyFactor::define(Object* desc)
{
    if (desc->hasProperty("get"))
    {
        auto val = desc->getValue("get");
        if (val.type() != Data::OBJECT)
            throw Reject();
        auto obj = val.object();
        auto func = dynamic_cast<Function*>(obj);
        if (func == nullptr)
            throw Reject();
        mGetter = func;
    }
    if (desc->hasProperty("set"))
    {
        auto val = desc->getValue("set");
        if (val.type() != Data::OBJECT)
            throw Reject();
        auto obj = val.object();
        auto func = dynamic_cast<Function*>(obj);
        if (func == nullptr)
            throw Reject();
        mSetter = func;
    }
}
