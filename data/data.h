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

#ifndef DATA_DATA_H
#define DATA_DATA_H

#include <string>
#include "dataexception.h"

namespace data {

class Object;

class Data
{
public:
    enum Type { UNDEFINED, NUL, NUMBER, BOOLEAN, STRING, OBJECT };
    
    static Data newUndefined();
    static Data newNull();
    static Data newNumber(double num);
    static Data newBoolean(bool boolean);
    static Data newString(char* string);
    static Data newObject(Object* obj);  
    
public:
    Data();
    Data(const Data& data);
    ~Data();
    
public:
    double number() throw(DataException);
    bool boolean() throw(DataException);
    const char* string() throw(DataException);
    Object* object() throw(DataException);
    
    Type type() { return mtype; }
    
    void operator =(const Data& data); 
    bool operator ==(Type type);
    bool operator ==(const Data& type);
    bool operator !=(Type type);
    bool operator !=(const Data& type);
    
public:
    bool toBoolean();
    
private:
    union _data 
    {
        double number;
        bool boolean;
        struct {
            char* c_str;
            int* counter;
        } string;
        Object* object;
    };
    _data data;
    Type mtype;
};



}

#endif // DATA_DATA_H
