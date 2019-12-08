// � Copyright 2010 - 2019 BlackTopp Studios Inc.
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

#include "TextStreamReader.h"

namespace Mezzanine
{
    TextStreamReader::TextStreamReader(StdInputStreamPtr Input) :
        Stream(Input)
        {  }

    ///////////////////////////////////////////////////////////////////////////////
    // Reading

    String TextStreamReader::Read(const SizeType Bytes)
    {
        String ToReturn;
        ToReturn.resize(Bytes,'\0');
        this->Stream->read(ToReturn.data(),Bytes);
        SizeType BytesRead = this->Stream->gcount();
        if( BytesRead < Bytes ) {
            ToReturn.resize(BytesRead);
        }
        return ToReturn;
    }

    String TextStreamReader::ReadLine(const Char8 Delim)
    {
        String ToReturn;
        std::getline( *(this->Stream.get()), ToReturn, Delim );
        return ToReturn;
    }

    Char8 TextStreamReader::ReadCharacter()
    {
        Char8 ToReturn = '\0';
        this->Stream->get(ToReturn);
        return ToReturn;
    }

    SizeType TextStreamReader::Skip(const SizeType Bytes)
    {
        this->Stream->ignore(static_cast<StreamSize>(Bytes));
        return static_cast<SizeType>( this->Stream->gcount() );
    }

    String TextStreamReader::GetAsString()
    {
        String ToReturn;
        StreamPos SavedReadPos = this->Stream->tellg();
        if( SavedReadPos < 0 ) {
            return ToReturn;
        }

        this->Stream->seekg(0,std::ios::end);
        SizeType ReturnSize = static_cast<SizeType>( this->Stream->tellg() );
        if( ReturnSize > 0 ) {
            ToReturn.reserve(ReturnSize);
        }
        this->Stream->seekg(0,std::ios::beg);

        ToReturn.append(std::istreambuf_iterator<char>( *(this->Stream.get()) ),{});
        this->Stream->seekg(SavedReadPos);
        return ToReturn;
    }

    Boole TextStreamReader::AtEnd() const
    {
        // eof only checks already set bits and doesn't examine the Stream itself.
        // So we need to perform an operation that can set the bit.
        // peek can do this, with the bonus of not actually changing the Stream state.
        this->Stream->peek();
        return this->Stream->eof();
    }
}//Mezzanine
