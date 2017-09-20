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

#ifndef DATA_PROPERTY_H
#define DATA_PROPERTY_H

#include "data.h"
#include "propertymethod.h"

#include <memory>

namespace data {
    
class Object;

class Property
{
public:
    enum Type { DATA_PROPERTY, ACCESSOR_PROPERTY };

    Property(Data& value, bool writable, bool enumerable, bool configurable);
    Data get(Object* obj = nullptr);
    void put(const Data& data, Object* obj = nullptr);
    Type type();
    
private:
    bool enumerable;
    bool configurable;
    Type mtype;
    std::shared_ptr<PropertyMethod> method;
};


}

#endif // DATA_PROPERTY_H
