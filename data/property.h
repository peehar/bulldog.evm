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

enum Type { DATA_PROPERTY, ACCESSOR_PROPERTY };

class Object;
class Function;
class Property;
class PropertyFactor;
typedef std::shared_ptr<Property> PropertyPtr;
typedef std::shared_ptr<PropertyFactor> FactorPtr;

class Property
{
    friend class DataPropertyFactor;
    friend class AccessorPropertyFactor;
private:
    Property();
public:
    Property(const Data& data);
    Data getValue(Object* obj = nullptr);
    void putValue(const Data& data, Object* obj = nullptr);
    void define(Object* desc);
    Type type();
    static PropertyPtr create(Object* desc);
    
private:
    static bool isDataDesc(Object* desc);
    static bool isAccessorDesc(Object* desc);
    static FactorPtr createFactor(Property* prop, Object* desc);
    
private:
    bool mEnum;
    bool mConfig;
    FactorPtr factor;
};

class PropertyFactor
{
public:
    PropertyFactor(Property* prop) : mProp(prop) {}
    virtual ~PropertyFactor()   {}
    virtual Data getValue(Object* obj = nullptr) = 0;
    virtual void putValue(const Data& data, Object* obj = nullptr) = 0;
    virtual Type type() = 0;
    virtual void define(Object* desc) = 0;
protected:
    Property* mProp;
};

class DataPropertyFactor : public PropertyFactor
{
public:
    DataPropertyFactor(const Data value, bool writable, Property* prop);
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, Object* obj = nullptr);  
    virtual Type type()     { return DATA_PROPERTY; }
    virtual void define(Object* desc);
private:
    Data mValue;
    bool mWritable;
};

class AccessorPropertyFactor : public PropertyFactor
{
public:
    AccessorPropertyFactor(Function* getter, Function* setter, Property* prop);
    virtual Data getValue(Object* obj = nullptr);
    virtual void putValue(const Data& data, Object* obj = nullptr);
    virtual Type type()     { return ACCESSOR_PROPERTY; }
    virtual void define(Object* desc);
private:
    Function* mGetter;
    Function* mSetter;
};

}

#endif // DATA_PROPERTY_H
