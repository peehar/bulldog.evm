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

#include <memory>
#include <string>
#include "dataexception.h"

namespace data {

class Object;

class Data
{
public:
    enum Type { NUMBER, BOOLEAN, STRING, OBJECT };
    
    Data(double num);
    Data(bool boolean);
    Data(char* string);
    Data(Object* obj);  
    Data(const Data& data);
    ~Data();
    
    double number() throw(DataException);
    bool boolean() throw(DataException);
    const char* string() throw(DataException);
    Object* object() throw(DataException);
    
    Type type() { return mtype; }
    
    void operator=(const Data& data); 
    
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
