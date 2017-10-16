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
#include "function.h"
#include "../wraper.h"

namespace data {
    
using namespace std;

Data Object::getValue(const string& pname)
{
    auto prop = getProperty(pname);
    if (!prop)
        return Data::newUndefined();
    return prop->getValue();
}

void Object::putValue(const string& pname, const Data& data)
{
    auto prop = getOwnProperty(pname);
    if (prop && prop->type() == DATA_PROPERTY) 
    {
        prop->putValue(data);
    }
    else 
    {
        prop = getProperty(pname);
        if (!prop) 
        {
            properties[pname] = PropertyPtr(new Property(data));
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

void Object::defineDataProperty(const string& pname, Object* desc)
{
    if (properties.find(pname) == properties.end())
    {
        if (!extensible) 
            throw Reject();
        auto prop = Property::create(desc);
        properties[pname] = prop;
    }
    else 
    {
        properties[pname]->define(desc);
    }
}


}// namespace data
