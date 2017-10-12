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

#include "data.h"
#include "object.h"
#include "../typeerror.h"

#include <cstring>

using namespace data;

void reject(bool t)
{
    if (t)
        throw TypeError();
}

Data Data::newUndefined()
{
    Data data;
    data.mtype = UNDEFINED;
    return data;
}

Data Data::newNull()
{
    Data data;
    data.mtype = NUL;
    return data;
}

Data Data::newNumber(double num)
{
    Data data;
    data.data.number = num;
    data.mtype = NUMBER;
    return data;
}

Data Data::newBoolean(bool boolean)
{
    Data data;
    data.data.boolean = boolean;
    data.mtype = BOOLEAN;
    return data;
}

Data Data::newString(char* string)
{
    Data data;
    data.data.string.c_str = string;
    data.data.string.counter = new int;
    *(data.data.string.counter) = 1;
    data.mtype = STRING;
    return data;
}

Data Data::newObject(Object* obj)
{
    Data data;
    data.data.object = obj;
    data.mtype = OBJECT;
    return data;
}

Data::Data()
{
    mtype = UNDEFINED;
}

Data::Data(const Data& data)
{
    ::memcpy(&this->data, &data, sizeof(Data));
    mtype = data.mtype;
    if (mtype == STRING) 
        this->data.string.counter++;
}

Data::~Data() 
{
    if (mtype == STRING) 
    {
        data.string.counter--;
        if (data.string.counter == 0) {
            delete[] data.string.c_str;
            delete data.string.counter;
        }
    }
}

void Data::operator=(const Data& data)
{
    ::memcpy(&this->data, &data, sizeof(Data));
    mtype = data.mtype;
    if (mtype == STRING) 
        this->data.string.counter++;
}

bool Data::operator==(Data::Type type)
{
    return mtype == type;
}
bool data::Data::operator!=(data::Data::Type type)
{
    return mtype != type;
}



double Data::number() throw(DataException)
{
    if (mtype != NUMBER)
        throw DataException();
    return data.number;
}

bool Data::boolean() throw(DataException)
{
    if (mtype != BOOLEAN)
        throw DataException();
    return data.boolean;
}

const char* Data::string() throw(DataException)
{
    if (mtype != STRING)
        throw DataException();
    return data.string.c_str;
}

Object* Data::object() throw(DataException)
{
    if (mtype != OBJECT)
        throw DataException();
    return data.object;
}

bool Data::toBoolean()
{
    return false;
}

