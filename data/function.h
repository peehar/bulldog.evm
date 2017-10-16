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

#ifndef DATA_FUNCTION_H
#define DATA_FUNCTION_H

#include "data.h"
#include "object.h"
#include <list>

namespace data {

class Function : public Object
{
public:
    virtual Data call(Object* thisptr, std::list<Data> param = std::list<Data>()) = 0;
};

class NativeFucntion : public Function
{
};

class JSFunction : public Function
{
};

}

#endif // DATA_FUNCTION_H
