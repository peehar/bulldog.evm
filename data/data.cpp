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

#include <cstring>

using namespace data;

Data::Data(double num)
{
    data.number = num;
    mtype = NUMBER;
}

Data::Data(bool boolean)
{
    data.boolean = boolean;
    mtype = BOOLEAN;
}

Data::Data(char* string)
{
    data.string.c_str = string;
    data.string.counter = new int;
    *(data.string.counter) = 1;
    mtype = STRING;
}

Data::Data(Object* obj)
{
    data.object = obj;
    mtype = OBJECT;
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
   