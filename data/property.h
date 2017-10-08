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

#include "data.h"
#include <memory>

namespace data {
    
class Object;
class Function;

class Property
{
public:
    enum Type { DATA_PROPERTY, ACCESSOR_PROPERTY };
    virtual Data getValue(Object* obj = nullptr) = 0;
    virtual void putValue(const Data& data, bool t = false, Object* obj = nullptr) = 0;    
    virtual void defineDataProperty(Obejct* desc) = 0;
    virtual Type type() = 0;
    
private:
    bool mEnum;
    bool mConfig;
};

class DataProperty : public Property
{
public:
    DataProperty(Data value, bool writable, bool enumerable, bool configurable)
    : mValue(value), mWritable(writable), mEnum(enumerable), mConfig(configurable)
    {}
    
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, bool t = false, Object* obj = nullptr);
    virtual void defineDataProperty(Obejct* desc);
    virtual Type type()     { return DATA_PROPERTY; }
    
private:
    Data mValue;
    bool mWritable;
    bool mEnum;
    bool mConfig;
};

class AccessorProperty : public Property
{
public:
    AccessorProperty(Function* getter, Function* setter, bool enumerable, bool configurable)
    : mGetter(getter), mSetter(setter), mEnum(enumerable), mConfig(configurable)
    {}
    
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, bool t = false, Object* obj = nullptr);
    virtual void defineDataProperty(Obejct* desc);
    virtual Type type()     { return ACCESSOR_PROPERTY; }
    
private:
    Function* mGetter;
    Function* mSetter;
    bool mEnum;
    bool mConfig;
};


class PropertyPtr : public std::shared_ptr<Property>
{
public:
    PropertyPtr() {}
    PropertyPtr(Property* ptr) : shared_ptr< data::Property >(ptr) {}
    PropertyPtr(Obejct* desc);    
    virtual void defineDataProperty(Obejct* desc);
    
private:
    bool isDataDesc(Object* desc);
    bool isAccessorDesc(Object* desc);
};

}

#endif // DATA_PROPERTY_H
