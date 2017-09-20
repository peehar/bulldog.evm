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
#include <memory>
#include "data.h"

namespace data {

class Property;
    
class Object
{
public:
    Object(Object* parent = nullptr) : prototype(parent), extensible(true) {}
    Data get(const std::string& pname);
    void put(const std::string& pname, Data& data, bool t);
    
private:
    std::shared_ptr<Property> getOwnProperty(const std::string& pname);
    std::shared_ptr<Property> getProperty(const std::string& pname);
    bool addDataProperty(const std::string& pname, bool t, Data& value, bool writable, bool enumerable, bool configurable);
//     void addAccessorProperty();
    
private:
    std::map<std::string, std::shared_ptr<Property>> properties;
    Object* prototype;
    bool extensible;
};

} // namespace data

#endif // DATA_OBJECT_H
