///*
// * Copyright 2017 <copyright holder> <email>
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// * You may obtain a copy of the License at
// *
// *     http://www.apache.org/licenses/LICENSE-2.0
// *
// * Unless required by applicable law or agreed to in writing, software
// * distributed under the License is distributed on an "AS IS" BASIS,
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * See the License for the specific language governing permissions and
// * limitations under the License.
// *
// */

//#ifndef EXEC_OPERAND_H
//#define EXEC_OPERAND_H

////#include "controlcontext.h"
//#include "../data/data.h"

//#include <memory>

//namespace exec {

//class ControlContext{};

//class Operand
//{
//public:
//    virtual ~Operand() {}
//    virtual Data get(ControlContext* cc) = 0;
//    virtual void put(const Data& data);
//};

//std::shared_ptr<Operand> OperandPtr;

//class ResultOperand : public Operand
//{
//public:
//    virtual Data get(ControlContext* cc);
//};

//class DataOperand : public Operand
//{
//public:
//    DataOperand(const Data &data);
//    virtual Data get(ControlContext* cc);
//private:
//    Data mData;
//};

//class VariableOperand : public Operand
//{
//public:
//    virtual Data get(ControlContext* cc);
//    virtual void put(const Data& data);
//};

//}

//#endif // EXEC_OPERAND_H
