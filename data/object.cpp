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

#include "object.h"
#include "data.h"
#include "property.h"
#include "../typeerror.h"

namespace data {
    
using namespace std;

Data Object::get(const string& pname)
{
    auto prop = getProperty(pname);
    if (!prop)
        return Data::newUndefined();
    return prop->get();
}

void Object::put(const string& pname, Data& data, bool t)
{
    auto prop = getOwnProperty(pname);
    if (prop && prop->type() == Property::DATA_PROPERTY) 
    {
        prop->put(data);
    }
    else 
    {
        prop = getProperty(pname);
        if (!prop) 
        {
            addDataProperty(pname, t, data, true, true, true);
        }
        else 
        {
            prop->put(data, this);
        }
    }
}

std::shared_ptr<Property> Object::getOwnProperty(const std::string& pname) 
{
    if (properties.find(pname) == properties.end())
        return shared_ptr<Property>();
    return properties[pname];
}

std::shared_ptr<Property> Object::getProperty(const std::string& pname) 
{
    auto prop = getOwnProperty(pname);
    if (prototype != nullptr)
        prop = prototype->getProperty(pname);
    return prop;
}

bool Object::addDataProperty(const std::string& pname, bool t, Data& value, bool writable, bool enumerable, bool configurable)
{
    if (!extensible) 
    {
        if (t)
            throw TypeError();
        return false;
    }
    properties[pname] = shared_ptr<Property>(new Property (value, writable, enumerable, configurable));
    return true;
}

}// namespace data
