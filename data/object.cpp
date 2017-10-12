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

void Object::putValue(const string& pname, const Data& data, bool t)
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
    auto d = createPropertyDesc(desc);
    if (properties.find(pname) == properties.end())
    {
        if (!extensible) {
            reject(t);
        }
        else 
        {
            Property* prop;
            switch (d->getType()) 
            {
                case GENERIC_PROPERTY:
                    prop = new DataProperty(d);
                    break;
                case DATA_PROPERTY:
                    prop = new DataProperty(dynamic_pointer_cast<DataPropertyDesc>(d));
                    break;
                case ACCESSOR_PROPERTY:
                    prop = new AccessorProperty(dynamic_pointer_cast<AccessorPropertyDesc>(d));
                    break;
            }
            properties[pname] = PropertyPtr(prop);
        }
    }
    else 
    {
        Property* prop;
        switch (d->getType()) 
        {
            case GENERIC_PROPERTY:
                break;
            case DATA_PROPERTY:
                break;
            case ACCESSOR_PROPERTY:
                break;
        }
        
        auto accPtr = dynamic_pointer_cast<AccessorPropertyDesc>(d);
        if (accPtr) 
        {
            
        }
        else 
        {
            auto dataPtr = dynamic_pointer_cast<DataPropertyDesc>(d);
            if (dataPtr) 
            {
                prop = new DataProperty(dataPtr);
            }
            else 
            {
                prop = new DataProperty(d);
            }
        }
    }
    return true;
}


PropertyDescPtr Object::createPropertyDesc(Object* desc) 
{
    Wraper<bool> configurable_bool;
    Wraper<bool> enumerable_bool;
    Wraper<bool> writable_bool;
    Data value = Data::newUndefined();
    Function* get_func = nullptr;
    Function* set_func = nullptr;
    
    string configurable_str("configurable");
    if (desc->hasProperty(configurable_str))
    {
        Data configurable_data = desc->getValue(configurable_str);
        configurable_bool = configurable_data.toBoolean();
    }
            
    string enumerable_str("enumerable");
    if (desc->hasProperty(enumerable_str))
    {
        Data enumerable_data = desc->getValue(enumerable_str);
        enumerable_bool = enumerable_data.toBoolean();
    }
    
    string writable_str("writable");
    if (desc->hasProperty(writable_str))
    {
        Data writable_data = desc->getValue(writable_str);
        writable_bool = writable_data.toBoolean();
    }
    
    string value_str("value");
    if (desc->hasProperty(value_str))
    {
        value = desc->getValue(value_str);
    }
    
    string get_str("get");
    if (desc->hasProperty(get_str))
    {
        Data get_data = desc->getValue(get_str);
        get_func = dynamic_cast<Function*>(get_data.object());
        if (get_func == nullptr)
            throw TypeError();
    }
    
    string set_str("set");
    if (desc->hasProperty(set_str))
    {
        Data set_data = desc->getValue(set_str);
        set_func = dynamic_cast<Function*>(set_data.object());
        if (set_func == nullptr)
            throw TypeError();
    }
    
    if (!writable_bool.isNull() || value != Data::UNDEFINED) 
    {
        DataPropertyDesc *desc = new DataPropertyDesc();;
        desc->value = value;
        desc->writable = writable_bool;
        desc->enumrable = enumerable_bool;
        desc->configurable = configurable_bool;
        return std::shared_ptr<PropertyDesc>(desc);
    } 
    else if (get_func != nullptr || set_func != nullptr) 
    {
        AccessorPropertyDesc *desc = new AccessorPropertyDesc();
        desc->getter = get_func;
        desc->setter = set_func;
        desc->enumrable = enumerable_bool;
        desc->configurable = configurable_bool;
        return std::shared_ptr<PropertyDesc>(desc);
    }
    else 
    {
        PropertyDesc *desc = new PropertyDesc();
        desc->configurable = configurable_bool;
        desc->enumrable = enumerable_bool;
        return std::shared_ptr<PropertyDesc>(desc);
    }
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
