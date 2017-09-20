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
#include "propertymethod.h"

using namespace data;

Property::Property(Data& value, bool writable, bool enumerable, bool configurable)
{
    enumerable = enumerable;
    configurable = configurable;
    auto dp = new DataProperty();
    dp->Value = value;
    dp->Writable = writable;
    method = std::shared_ptr<PropertyMethod>(dp);
    mtype = DATA_PROPERTY;
}

Data Property::get(Object* obj)
{
    return method->get(obj);
}

void Property::put(const Data& data, Object* obj)
{
    method->put(data, obj);
}

Property::Type Property::type()
{
    return mtype;
}

