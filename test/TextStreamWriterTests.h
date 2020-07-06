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
#ifndef Mezz_IOStreams_TextStreamWriterTests_h
#define Mezz_IOStreams_TextStreamWriterTests_h

/// @file
/// @brief This file tests the functionality of the TextStreamWriter class.

#include "MezzTest.h"

#include "TextStreamWriter.h"

AUTOMATIC_TEST_GROUP(TextStreamWriterTests,TextStreamWriter)
{
    using namespace Mezzanine;

    // Set everything up for our test.
    // Poem from: https://www.poetrysoup.com/poem/will_you_slumber_on_823149
    String SourceBuffer = "When the moon retires its gleam,\n"  //33
                          "And sunlight shines upon the dew,\n" //34
                          "Do you rise from bed anew?\n"        //27
                          "Or slumber on in a waking dream..."; //34
    std::shared_ptr<std::ostringstream> TestStream = std::make_shared<std::ostringstream>();
    TextStreamWriter TestWriter(TestStream);

    TEST_EQUAL("Write(const_StringView)-FirstLine-Valid",
               true,TestWriter.Write("When the moon retires its gleam,\n"))
    TEST_EQUAL("Write(const_StringView)-FirstLine-Value",
               SourceBuffer.substr(0,33),TestStream->str())

    TEST_EQUAL("Write(const_StringView)-SecondLine-Valid",
               true,TestWriter.Write("And sunlight shines upon the dew,\n"))
    TEST_EQUAL("Write(const_StringView)-SecondLine-Value",
               SourceBuffer.substr(0,67),TestStream->str())

    TEST_EQUAL("Write(const_Char8)-ThirdLine-FirstChar-Valid",
               true,TestWriter.Write('D'))
    TEST_EQUAL("Write(const_Char8)-ThirdLine-FirstChar-Value",
               SourceBuffer.substr(0,68),TestStream->str());
    TEST_EQUAL("Write(const_Char8)-ThirdLine-SecondChar-Valid",
               true,TestWriter.Write('o'))
    TEST_EQUAL("Write(const_Char8)-ThirdLine-SecondChar-Value",
               SourceBuffer.substr(0,69),TestStream->str())
    TEST_EQUAL("Write(const_Char8)-ThirdLine-ThirdChar-Valid",
               true,TestWriter.Write(' '))
    TEST_EQUAL("Write(const_Char8)-ThirdLine-ThirdChar-Value",
               SourceBuffer.substr(0,70),TestStream->str())
    TEST_EQUAL("Write(const_Char8)-ThirdLine-FourthChar-Valid",
               true,TestWriter.Write('y'))
    TEST_EQUAL("Write(const_Char8)-ThirdLine-FourthChar-Value",
               SourceBuffer.substr(0,71),TestStream->str())

    TEST_EQUAL("Write(const_StringView)-ThirdLine-Remainder-Valid",
               true,TestWriter.Write("ou rise from bed anew?\n"))
    TEST_EQUAL("Write(const_StringView)-ThirdLine-Remainder-Value",
               SourceBuffer.substr(0,94),TestStream->str())
    TEST_EQUAL("Write(const_StringView)-FourthLine-FirstHalf-Valid",
               true,TestWriter.Write("Or slumber on in "))
    TEST_EQUAL("Write(const_StringView)-FourthLine-FirstHalf-Value",
               SourceBuffer.substr(0,111),TestStream->str())
    TEST_EQUAL("Write(const_StringView)-FourthLine-SecondHalf-Valid",
               true,TestWriter.Write("a waking dream..."))
    TEST_EQUAL("Write(const_StringView)-FourthLine-SecondHalf-Value",
               SourceBuffer,TestStream->str());

    // I don't know how to make a very large String without causing OOM issues.
    // Solution: Simple! Use PAE and Buy many PB of RAM!
    //TEST_THROW("Write(const_BinaryBuffer&)-Throw",
    //           std::runtime_error,
    //           [&](){ TestWriter.Write(String(std::numeric_limits<StreamSize>::max()+1,'\0')); });
}

#endif // Mezz_IOStreams_TextStreamWriterTests_h
