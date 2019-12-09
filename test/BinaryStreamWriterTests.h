// © Copyright 2010 - 2019 BlackTopp Studios Inc.
/* This file is part of The Mezzanine Engine.

    The Mezzanine Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The Mezzanine Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Mezzanine Engine.  If not, see <http://www.gnu.org/licenses/>.
*/
/* The original authors have included a copy of the license specified above in the
   'Docs' folder. See 'gpl.txt'
*/
/* We welcome the use of the Mezzanine engine to anyone, including companies who wish to
   Build professional software and charge for their product.

   However there are some practical restrictions, so if your project involves
   any of the following you should contact us and we will try to work something
   out:
    - DRM or Copy Protection of any kind(except Copyrights)
    - Software Patents You Do Not Wish to Freely License
    - Any Kind of Linking to Non-GPL licensed Works
    - Are Currently In Violation of Another Copyright Holder's GPL License
    - If You want to change our code and not add a few hundred MB of stuff to
        your distribution

   These and other limitations could cause serious legal problems if you ignore
   them, so it is best to simply contact us or the Free Software Foundation, if
   you have any questions.

   Joseph Toppi - toppij@gmail.com
   John Blackwood - makoenergy02@gmail.com
*/
#ifndef Mezz_IOStreams_BinaryStreamWriterTests_h
#define Mezz_IOStreams_BinaryStreamWriterTests_h

/// @file
/// @brief This file tests the functionality of the BinaryStreamWriter class.

#include "MezzTest.h"

#include "BinaryStreamWriter.h"

/// @brief A struct of values to use with the BinaryStreamReader tests.
struct BinaryStreamWriterStruct
{
    double DoubleVar = 0;
    float FloatVar1 = 0;
    float FloatVar2 = 0;
    Mezzanine::UInt32 UIntVar1 = 0;
    Mezzanine::UInt32 UIntVar2 = 0;
    Mezzanine::UInt32 UIntVar3 = 0;
    Mezzanine::UInt32 UIntVar4 = 0;
    short ShortVar1 = 0;
    short ShortVar2 = 0;
    char CharVar1 = 0;
    char CharVar2 = 0;
    char CharVar3 = 0;
    char CharVar4 = 0;
};//BinaryStreamWriterStruct

/// @brief A simple streambuf implementation that allows access to the test struct from a Stream.
class BinaryStreamWriterBuffer : public std::streambuf
{
public:
    /// @brief Class constructor.
    /// @param Struct A pointer to the test struct being streamed to.
    BinaryStreamWriterBuffer(BinaryStreamWriterStruct* Struct)
    {
        char* CastedStruct = reinterpret_cast<char*>(Struct);
        this->setp(CastedStruct,CastedStruct + sizeof(BinaryStreamWriterStruct));
    }
    ~BinaryStreamWriterBuffer() = default;
};//BinaryStreamWriterBuffer

AUTOMATIC_TEST_GROUP(BinaryStreamWriterTests,BinaryStreamWriter)
{
    using namespace Mezzanine;

    // Set everything up for our test.
    BinaryStreamWriterStruct TestStruct;
    BinaryStreamWriterBuffer TestBuffer(&TestStruct);
    StdOutputStreamPtr TestStream = std::make_shared<std::ostream>(&TestBuffer);
    BinaryStreamWriter TestWriter(TestStream);

    double DoubleVar = 0.5772156649015328606065120; // Euler's Constant
    float FloatVar1 = 3.1415926f; // Archimedes' Constant (Pi)
    float FloatVar2 = 1.411421f; // Pythagoras' Constant
    Mezzanine::UInt32 UIntVar1 = 42;
    Mezzanine::UInt32 UIntVar2 = 115;
    Mezzanine::UInt32 UIntVar3 = 975454;
    Mezzanine::UInt32 UIntVar4 = 602214076;
    short ShortVar1 = 7;
    short ShortVar2 = -49;
    char CharVar1 = 'c';
    char CharVar2 = '0';
    char CharVar3 = '\t';
    char CharVar4 = '\r';

    BinaryBuffer ReusableBuffer;

    // DoubleVar
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&DoubleVar);
    ReusableBuffer.Size = sizeof(double);
    TEST_EQUAL("Write(const_BinaryBuffer&)-DoubleVar-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL_EPSILON("Write(const_BinaryBuffer&)-DoubleVar-Value",
                       DoubleVar,TestStruct.DoubleVar);
    // FloatVar1
    TEST_EQUAL("Write(T)-FloatVar1-Valid",
               true,TestWriter.Write(FloatVar1));
    TEST_EQUAL_EPSILON("Write(T)-FloatVar1-Value",
                       FloatVar1,TestStruct.FloatVar1);
    // FloatVar2
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&FloatVar2);
    ReusableBuffer.Size = sizeof(float);
    TEST_EQUAL("Write(const_BinaryBuffer&)-FloatVar2-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL_EPSILON("Write(const_BinaryBuffer&)-FloatVar2-Value",
                       FloatVar2,TestStruct.FloatVar2);
    // UIntVar1
    TEST_EQUAL("Write(T)-UIntVar1-Valid",
               true,TestWriter.Write(UIntVar1));
    TEST_EQUAL("Write(T)-UIntVar1-Value",
               UIntVar1,TestStruct.UIntVar1);
    // UIntVar2
    TEST_EQUAL("Write(T)-UIntVar2-Valid",
               true,TestWriter.Write(UIntVar2));
    TEST_EQUAL("Write(T)-UIntVar2-Value",
               UIntVar2,TestStruct.UIntVar2);
    // UIntVar3
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&UIntVar3);
    ReusableBuffer.Size = sizeof(UInt32);
    TEST_EQUAL("Write(const_BinaryBuffer&)-UIntVar3-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(const_BinaryBuffer&)-UIntVar3-Value",
               UIntVar3,TestStruct.UIntVar3);
    // UIntVar4
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&UIntVar4);
    ReusableBuffer.Size = sizeof(UInt32);
    TEST_EQUAL("Write(const_BinaryBuffer&)-UIntVar4-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(const_BinaryBuffer&)-UIntVar4-Value",
               UIntVar4,TestStruct.UIntVar4);
    // ShortVar1
    TEST_EQUAL("Write(T)-ShortVar1-Valid",
               true,TestWriter.Write(ShortVar1));
    TEST_EQUAL("Write(T)-ShortVar1-Value",
               ShortVar1,TestStruct.ShortVar1);
    // ShortVar2
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&ShortVar2);
    ReusableBuffer.Size = sizeof(short);
    TEST_EQUAL("Write(const_BinaryBuffer&)-ShortVar2-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(const_BinaryBuffer&)-ShortVar2-Value",
               ShortVar2,TestStruct.ShortVar2);
    // CharVar1
    TEST_EQUAL("Write(T)-CharVar1-Valid",
               true,TestWriter.Write(CharVar1));
    TEST_EQUAL("Write(T)-CharVar1-Value",
               CharVar1,TestStruct.CharVar1);
    // CharVar2
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&CharVar2);
    ReusableBuffer.Size = sizeof(char);
    TEST_EQUAL("Write(const_BinaryBuffer&)-CharVar2-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(const_BinaryBuffer&)-CharVar2-Value",
               CharVar2,TestStruct.CharVar2);
    // CharVar3
    TEST_EQUAL("Write(T)-CharVar3-Valid",
               true,TestWriter.Write(CharVar3));
    TEST_EQUAL("Write(T)-CharVar3-Value",
               CharVar3,TestStruct.CharVar3);
    // CharVar4
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&CharVar4);
    ReusableBuffer.Size = sizeof(char);
    TEST_EQUAL("Write(const_BinaryBuffer&)-CharVar4-Valid",
               true,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(const_BinaryBuffer&)-CharVar4-Value",
               CharVar4,TestStruct.CharVar4);

    // EoF
    ReusableBuffer.Binary = reinterpret_cast<BinaryBuffer::Byte*>(&DoubleVar);
    ReusableBuffer.Size = sizeof(double);
    TEST_EQUAL("Write(const_BinaryBuffer&)-EoF",
               false,TestWriter.Write(ReusableBuffer));
    TEST_EQUAL("Write(T)-EoF",
               false,TestWriter.Write(DoubleVar));

    // Throw
    ReusableBuffer.Binary = nullptr;
    ReusableBuffer.Size = std::numeric_limits<SizeType>::max();
    TEST_THROW("Write(const_BinaryBuffer&)-Throw",
               std::runtime_error,
               [&](){ TestWriter.Write(ReusableBuffer); });
}

#endif // Mezz_IOStreams_BinaryStreamWriterTests_h
