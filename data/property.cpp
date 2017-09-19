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

#include "property.h"

using namespace data;

Property::Property(Object* desc)
{
    
}

void Property::defineOwnProperty(Object* desc)
{

}

Data Property::get()
{
    return method->get();
}

void Property::set(const Data& data)
{
    method->set(data);
}

Data Property::DataProperty::get()
{
    return Value;
}

void Property::DataProperty::set(const Data& data)
{

}

Data Property::AccessorProperty::get()
{
    if (Get == Data::UNDEFINED) {
        return Data::newUndefined();
    }
}

void Property::AccessorProperty::set(const Data& data)
{

}
