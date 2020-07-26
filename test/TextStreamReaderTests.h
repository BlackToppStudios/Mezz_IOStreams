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
#ifndef Mezz_IOStreams_TextStreamReaderTests_h
#define Mezz_IOStreams_TextStreamReaderTests_h

/// @file
/// @brief This file tests the functionality of the TextStreamReader class.

#include "MezzTest.h"
#include "MezzException.h"

#include "TextStreamReader.h"

AUTOMATIC_TEST_GROUP(TextStreamReaderTests,TextStreamReader)
{
    using namespace Mezzanine;

    // Set everything up for our test.
    // Poem from: https://www.poetrysoup.com/poem/will_you_slumber_on_823149
    String TestBuffer = "When the moon retires its gleam,\n"  //33
                        "And sunlight shines upon the dew,\n" //34
                        "Do you rise from bed anew?\n"        //27
                        "Or slumber on in a waking dream..."; //34
    StdInputStreamPtr TestStream = std::make_shared<std::istringstream>(TestBuffer);
    TextStreamReader TestReader(TestStream);

    TEST_EQUAL("AtEnd()_const-Begin",
               false,TestReader.AtEnd())

    TEST_EQUAL("GetAsString()",
               TestBuffer,TestReader.GetAsString())
    TEST_THROW("GetAsString()-MissingFileStream",
               Mezzanine::Exception::StreamReadError,
               [](){
                    Mezzanine::TextStreamReader Reader(
                        std::make_shared<std::ifstream>("ZZZ_NoSuchFile.txt.bad", std::ios::in)
                    );
                    std::cerr << Reader.GetAsString();

    })


    String FirstReadResult = TestReader.Read(14);
    TEST_EQUAL("Read(const_StreamSize)-First",
               String("When the moon "),FirstReadResult)
    String SecondReadResult = TestReader.Read(19);
    TEST_EQUAL("Read(const_StreamSize)-Second",
               String("retires its gleam,\n"),SecondReadResult)

    String DefaultDelimLineResult = TestReader.ReadLine();
    TEST_EQUAL("ReadLine(const_Char8)-DefaultDelim",
               String("And sunlight shines upon the dew,"),DefaultDelimLineResult)
    String FDelimLineResult = TestReader.ReadLine('f');
    TEST_EQUAL("ReadLine(const_Char8)-FDelim",
               String("Do you rise "),FDelimLineResult)
    String QuestionMarkDelimLineResult = TestReader.ReadLine('?');
    TEST_EQUAL("ReadLine(const_Char8)-QuestionMarkDelim",
               String("rom bed anew"),QuestionMarkDelimLineResult)

    TEST_EQUAL("ReadCharacter()-First",
               '\n',TestReader.ReadCharacter())
    TEST_EQUAL("ReadCharacter()-Second",
               'O',TestReader.ReadCharacter())
    TEST_EQUAL("ReadCharacter()-Third",
               'r',TestReader.ReadCharacter())

    TEST_EQUAL("Skip(const_StreamSize)",
               32,TestReader.Skip(32))

    TEST_EQUAL("AtEnd()_const-End",
               true,TestReader.AtEnd())
}

#endif // Mezz_IOStreams_TextStreamReaderTests_h
