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
#ifndef Mezz_IOStreams_BinaryStreamReaderTests_h
#define Mezz_IOStreams_BinaryStreamReaderTests_h

/// @file
/// @brief This file tests the functionality of the BinaryStreamReader class.

#include "MezzTest.h"

#include "BinaryStreamReader.h"

/// @brief A struct of values to use with the BinaryStreamReader tests.
struct BinaryStreamReaderStruct
{
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
    char CharVar4 = '\0';
};//BinaryStreamReaderStruct

SAVE_WARNING_STATE
SUPPRESS_CLANG_WARNING("-Wweak-vtables")
/// @brief A simple streambuf implementation that allows access to the test struct from a Stream.
class BinaryStreamReaderBuffer : public std::streambuf
{
public:
    /// @brief Class constructor.
    /// @param Struct A pointer to the test struct being streamed from.
    BinaryStreamReaderBuffer(BinaryStreamReaderStruct* Struct)
    {
        char* CastedStruct = reinterpret_cast<char*>(Struct);
        this->setg(CastedStruct,CastedStruct,CastedStruct + sizeof(BinaryStreamReaderStruct));
    }
    ~BinaryStreamReaderBuffer() = default;
};//BinaryStreamReaderBuffer
RESTORE_WARNING_STATE

SAVE_WARNING_STATE
SUPPRESS_GCC_WARNING("-Wcast-align")
AUTOMATIC_TEST_GROUP(BinaryStreamReaderTests,BinaryStreamReader)
{
    using namespace Mezzanine;

    // Set everything up for our test.
    BinaryStreamReaderStruct TestStruct;
    BinaryStreamReaderBuffer TestBuffer(&TestStruct);
    StdInputStreamPtr TestStream = std::make_shared<std::istream>(&TestBuffer);
    BinaryStreamReader TestReader(TestStream);

    TEST_EQUAL("AtEnd()_const-Begin",
               false,TestReader.AtEnd());

    // DoubleVar
    TEST_EQUAL_EPSILON("Read(T)-DoubleVar",
                       TestStruct.DoubleVar,TestReader.Read<double>());
    // FloatVar1
    TEST_EQUAL("Skip(const_StreamSize)-FloatVar1",
               StreamSize( sizeof(float) ),TestReader.Skip( StreamSize( sizeof(float) ) ));
    // FloatVar2
    BinaryBuffer FloatBuffer = TestReader.Read( sizeof(float) );
    TEST_EQUAL("Read(const_StreamSize)-FloatVar2-BufferSize",
               sizeof(float),FloatBuffer.Size);
    TEST_EQUAL_EPSILON("Read(const_StreamSize)-FloatVar2-Value",
                       TestStruct.FloatVar2,*reinterpret_cast<float*>(FloatBuffer.Binary));
    // UIntVar1
    TEST_EQUAL("Read(T)-UIntVar1",
               TestStruct.UIntVar1,TestReader.Read<UInt32>());
    // UIntVar2
    BinaryBuffer UInt32Buffer = TestReader.Read( sizeof(UInt32) );
    TEST_EQUAL("Read(const_StreamSize)-UIntVar2-BufferSize",
               sizeof(UInt32),UInt32Buffer.Size);
    TEST_EQUAL("Read(const_StreamSize)-UIntVar2-Value",
               TestStruct.UIntVar2,*reinterpret_cast<UInt32*>(UInt32Buffer.Binary));
    // UIntVar3 & UIntVar4
    TEST_EQUAL("Skip(const_StreamSize)-UIntVar3-UIntVar4",
               StreamSize( sizeof(UInt32) ) * 2,TestReader.Skip( StreamSize( sizeof(UInt32) ) * 2 ));
    // ShortVar1
    TEST_EQUAL("Read(T)-ShortVar1",
               TestStruct.ShortVar1,TestReader.Read<short>());
    // ShortVar2
    BinaryBuffer ShortBuffer = TestReader.Read( sizeof(short) );
    TEST_EQUAL("Read(const_StreamSize)-ShortVar2-BufferSize",
               sizeof(short),ShortBuffer.Size);
    TEST_EQUAL("Read(const_StreamSize)-ShortVar2-Value",
               TestStruct.ShortVar2,*reinterpret_cast<short*>(ShortBuffer.Binary));
    // CharVar1
    TEST_EQUAL("Read(T)-CharVar1",
               TestStruct.CharVar1,TestReader.Read<char>());
    // CharVar2 & CharVar3
    TEST_EQUAL("Skip(const_StreamSize)-CharVar2-CharVar3",
               StreamSize( sizeof(char) ) * 2,TestReader.Skip( StreamSize( sizeof(char) ) * 2 ));
    // CharVar4
    BinaryBuffer CharBuffer = TestReader.Read( sizeof(char) );
    TEST_EQUAL("Read(const_StreamSize)-CharVar4-BufferSize",
               sizeof(char),CharBuffer.Size);
    TEST_EQUAL("Read(const_StreamSize)-CharVar4-Value",
               TestStruct.CharVar4,*reinterpret_cast<char*>(CharBuffer.Binary));

    TEST_EQUAL("AtEnd()_const-End",
               true,TestReader.AtEnd());
}
RESTORE_WARNING_STATE

#endif // Mezz_IOStreams_BinaryStreamReaderTests_h
