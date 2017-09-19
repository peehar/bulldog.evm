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

namespace data {
    
using namespace std;

Data Object::Get(const string& pname)
{
    return properties[pname]->get();
}

void Object::Put(const string& pname, Data& data, bool s)
{
    properties[pname]->set(data);
}

} // namespace data
