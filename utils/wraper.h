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

#ifndef WRAPER_H
#define WRAPER_H

template<typename T>
class Wraper
{
public:
    Wraper() : mNull(true) {}
    Wraper(T val) : mNull(false), mValue(val) {}
    operator T() { return mValue; }
    bool isNull() { return mNull; }
    T operator =(const T val) 
    { 
        mValue = val; 
        return mValue;
    }
    
    T get(T defval)
    {
        return mNull ? defval : mValue;
    }
private:
    bool mNull;
    T mValue;
};

#endif // WRAPER_H
