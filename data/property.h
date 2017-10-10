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

#ifndef DATA_PROPERTY_H
#define DATA_PROPERTY_H

#include "../wraper.h"
#include "data.h"
#include <memory>

namespace data {

enum Type { GENERIC_PROPERTY, DATA_PROPERTY, ACCESSOR_PROPERTY };    
    
class Object;
class Function;

struct PropertyDesc
{
    Wraper<bool> configurable;
    Wraper<bool> enumrable;
    virtual Type getType() { return GENERIC_PROPERTY; }
    virtual ~PropertyDesc() {}
};

struct DataPropertyDesc : public PropertyDesc
{
    Wraper<Data> value;
    Wraper<bool> writable;
    virtual Type getType() { return DATA_PROPERTY; }
};

struct AccessorPropertyDesc : public PropertyDesc
{
    Function* getter = nullptr;
    Function* setter = nullptr;
    virtual Type getType() { return ACCESSOR_PROPERTY; }
};

typedef std::shared_ptr<PropertyDesc> PropertyDescPtr;
typedef std::shared_ptr<DataPropertyDesc> DataPropertyDescPtr;
typedef std::shared_ptr<AccessorPropertyDesc> AccessorPropertyDescPtr;

class Property
{
public:

    virtual ~Property() {}
    virtual Data getValue(Object* obj = nullptr) = 0;
    virtual void putValue(const Data& data, Object* obj = nullptr, bool t = false) = 0;    
    virtual Type type() = 0;
};

class DataProperty : public Property
{
public:
    DataProperty(PropertyDescPtr desc);
    DataProperty(DataPropertyDescPtr desc);
    DataProperty(Data value, bool writable, bool enumerable, bool configurable)
    : mValue(value), mWritable(writable), mEnum(enumerable), mConfig(configurable)
    {}
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, Object* obj = nullptr, bool t = false);
    virtual Type type()     { return DATA_PROPERTY; }
    void define(DataPropertyDescPtr& desc, bool t = false);
    
private:
    Data mValue;
    bool mWritable;
    bool mEnum;
    bool mConfig;
};

class AccessorProperty : public Property
{
public:
    AccessorProperty(AccessorPropertyDescPtr desc);
    AccessorProperty(Function* getter, Function* setter, bool enumerable, bool configurable)
    : mGetter(getter), mSetter(setter), mEnum(enumerable), mConfig(configurable)
    {}    
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, Object* obj = nullptr, bool t = false);
    virtual Type type()     { return ACCESSOR_PROPERTY; }
    virtual void define(AccessorPropertyDescPtr& desc, bool t = false);
    
private:
    Function* mGetter;
    Function* mSetter;
    bool mEnum;
    bool mConfig;
};

typedef std::shared_ptr<Property> PropertyPtr;


}

#endif // DATA_PROPERTY_H
