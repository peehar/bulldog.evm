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

namespace data {

class Property
{
public:
    bool Enumerable;
    bool Configurable;
    virtual Data get() = 0;
    virtual void set(const Data& data) = 0;
};

class DataProperty : public Property 
{
public:
    Data Value;
    bool Configurable;
    virtual Data get();
    virtual void set(const Data& data);
};


class AccessorProperty : public Property 
{
public:
    Data Get;
    Data Set;
    virtual Data get();
    virtual void set(const Data& data);
};

}

#endif // DATA_PROPERTY_H
