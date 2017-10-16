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

#ifndef DATA_OBJECT_H
#define DATA_OBJECT_H

#include <map>
#include <string>
#include "data.h"
#include "property.h"

namespace data {

class Object
{
public:
    Object(Object* parent = nullptr) : prototype(parent), extensible(true) {}
    virtual ~Object() {}
    Data getValue(const std::string& pname);
    void putValue(const std::string& pname, const Data& data);
    
    bool hasProperty(const std::string& pname);
    
private:
    PropertyPtr getOwnProperty(const std::string& pname);
    PropertyPtr getProperty(const std::string& pname);
    void defineDataProperty(const std::string& pname, Object* desc);
    
private:
    std::map<std::string, PropertyPtr> properties;
    Object* prototype;
    bool extensible;
};

} // namespace data

#endif // DATA_OBJECT_H
