// /*
//  * Copyright 2017 <copyright holder> <email>
//  * 
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * you may not use this file except in compliance with the License.
//  * You may obtain a copy of the License at
//  * 
//  *     http://www.apache.org/licenses/LICENSE-2.0
//  * 
//  * Unless required by applicable law or agreed to in writing, software
//  * distributed under the License is distributed on an "AS IS" BASIS,
//  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  * See the License for the specific language governing permissions and
//  * limitations under the License.
//  * 
//  */
// 
// #include "propertyptr.h"
// #include "object.h"
// #include "function.h"
// #include "../typeerror.h"
// 
// #include <string>
// 
// using namespace data;
// using namespace std;
// 
// PropertyPtr::PropertyPtr(Object* desc)
// {
// //     if (isAccessorDesc(desc))
// //     {
// //         bool configurable_bool = false;
// //         bool enumerable_bool = false;
// //         Function* get_func = nullptr;
// //         Function* set_func = nullptr;
// //         string configurable_str("configurable");
// //         if (desc->hasProperty(configurable_str))
// //         {
// //             Data configurable_data = desc->getValue(configurable_str);
// //             configurable_bool = configurable_data.toBoolean();
// //         }
// //                 
// //         string enumerable_str("enumerable");
// //         if (desc->hasProperty(enumerable_str))
// //         {
// //             Data enumerable_data = desc->getValue(enumerable_str);
// //             enumerable_bool = enumerable_data.toBoolean();
// //         }
// //         
// //         string get_str("get");
// //         if (desc->hasProperty(get_str))
// //         {
// //             Data get_data = desc->getValue(get_str);
// //             get_func = dynamic_cast<Function*>(get_data.object());
// //             if (get_func == nullptr)
// //                 throw TypeError();
// //         }
// //         
// //         string set_str("set");
// //         if (desc->hasProperty(set_str))
// //         {
// //             Data set_data = desc->getValue(set_str);
// //             set_func = dynamic_cast<Function*>(set_data.object());
// //             if (set_func == nullptr)
// //                 throw TypeError();
// //         }
// //         
// //         reset(new AccessorProperty(get_func, set_func, enumerable_bool, configurable_bool));
// //     }
// //     else 
// //     {
// //         bool configurable_bool = false;
// //         bool enumerable_bool = false;
// //         bool writable_bool = false;
// //         Data value = Data::newUndefined();
// //         
// //         string configurable_str("configurable");
// //         if (desc->hasProperty(configurable_str))
// //         {
// //             Data configurable_data = desc->getValue(configurable_str);
// //             configurable_bool = configurable_data.toBoolean();
// //         }
// //                 
// //         string enumerable_str("enumerable");
// //         if (desc->hasProperty(enumerable_str))
// //         {
// //             Data enumerable_data = desc->getValue(enumerable_str);
// //             enumerable_bool = enumerable_data.toBoolean();
// //         }
// //         
// //         string writable_str("writable");
// //         if (desc->hasProperty(writable_str))
// //         {
// //             Data writable_data = desc->getValue(writable_str);
// //             writable_bool = writable_data.toBoolean();
// //         }
// //         
// //         string value_str("value");
// //         if (desc->hasProperty(value_str))
// //         {
// //             value = desc->getValue(value_str);
// //         }
// //         
// //         reset(new DataProperty(value, writable_bool, enumerable_bool, configurable_bool));
// //     }
//     
// }
// 
// void PropertyPtr::defineDataProperty(Object* desc)
// {
//     
// }
// 
// shared_ptr< DataProperty > PropertyPtr::toPropertyDesc(Object* desc)
// {
// }
