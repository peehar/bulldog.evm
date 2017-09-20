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

#ifndef DATA_PROPERTYMETHOD_H
#define DATA_PROPERTYMETHOD_H

#include "data.h"

namespace data {
    
class Function;

class PropertyMethod 
{
public:
    virtual ~PropertyMethod() {}
    virtual Data get(Object* obj = nullptr) = 0;
    virtual void put(const Data& data, bool t = false, Object* obj = nullptr) = 0;
};

class DataProperty : public PropertyMethod
{
public:
    Data Value;
    bool Writable;
    virtual Data get(Object* obj = nullptr);
    virtual void put(const Data& data, bool t = false, Object* obj = nullptr);
};

class AccessorProperty : public PropertyMethod
{
public:
    Function* getter;
    Function* setter;
    virtual Data get(Object* obj = nullptr);
    virtual void put(const Data& data, bool t = false, Object* obj = nullptr);
};

}

#endif // DATA_PROPERTYMETHOD_H
