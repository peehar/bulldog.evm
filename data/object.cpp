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

Data Object::getValue(const string& pname)
{
    auto prop = getProperty(pname);
    if (!prop)
        return Data::newUndefined();
    return prop->getValue();
}

void Object::putValue(const string& pname, const Data& data, bool t)
{
    auto prop = getOwnProperty(pname);
    if (prop && prop->type() == Property::DATA_PROPERTY) 
    {
        prop->putValue(data);
    }
    else 
    {
        prop = getProperty(pname);
        if (!prop) 
        {
            properties[pname] = PropertyPtr(new DataProperty(data, true, true, true));
        }
        else 
        {
            prop->putValue(data, this);
        }
    }
}

bool Object::hasProperty(const string& pname)
{
    return properties.find(pname) != properties.end();
}

PropertyPtr Object::getOwnProperty(const std::string& pname) 
{
    if (properties.find(pname) == properties.end())
        return PropertyPtr();
    return properties[pname];
}

PropertyPtr Object::getProperty(const std::string& pname) 
{
    auto prop = getOwnProperty(pname);
    if (prototype != nullptr)
        prop = prototype->getProperty(pname);
    return prop;
}

bool Object::defineDataProperty(const string& pname, Object* desc, bool t)
{
    if (properties.find(pname) == properties.end())
    {
        if (!extensible) {
            if (t)
                throw TypeError();
        }
        else 
        {
            PropertyPtr pp(desc);
            properties[pname] = pp;
        }
    }
    else 
    {
        if (!desc->properties.empty()) 
            properties[pname].defineDataProperty(desc);
    }
    return true;
}


/*
bool Object::addDataProperty(const std::string& pname, bool t, Data& value, bool writable, bool enumerable, bool configurable)
{
    return defineDataProperty(pname, t, &value, &writable, &enumerable, &configurable);
}

bool Object::defineDataProperty(const std::string& pname, bool t, Data* value, bool* writable, bool* enumerable, bool* configurable)
{
    if (properties.find(pname) == properties.end()) 
    {
        if (!extensible) 
        {
            if (t)
                throw TypeError();
            return false;
        }
        properties[pname] = shared_ptr<Property>(new DataProperty(*value, *writable, *enumerable, *configurable));
    }
    else
    {
        auto prop = properties[pname];
        if (!prop->configurable()) 
        {
            
        }
    }
    
    return true;
}

bool Object::addAccessorProperty(const std::string& pname, bool t, Function* getter, Function* setter, bool enumerable, bool configurable)
{
    return defineAccessorProperty(pname, t, getter, setter, &enumerable, &configurable);
}

bool Object::defineAccessorProperty(const std::string& pname, bool t, Function* getter, Function* setter, bool* enumerable, bool* configurable)
{
    if (!extensible) 
    {
        if (t)
            throw TypeError();
        return false;
    }
    properties[pname] = shared_ptr<Property>(new AccessorProperty(getter, setter, enumerable, configurable));
    return true;
}*/

}// namespace data
