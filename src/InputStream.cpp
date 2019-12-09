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

#include "InputStream.h"

namespace Mezzanine
{
    InputStream::InputStream(std::streambuf* Buf) :
        std::istream(Buf)
        {  }

    ///////////////////////////////////////////////////////////////////////////////
    // Stream Base Operations

    Boole InputStream::EoF() const
        { return this->eof(); }

    Boole InputStream::Bad() const
        { return this->bad(); }

    Boole InputStream::Fail() const
        { return this->fail(); }

    Boole InputStream::IsValid() const
        { return this->good(); }

    void InputStream::ClearErrors()
        { this->clear(); }

    ///////////////////////////////////////////////////////////////////////////////
    // Input methods

    size_t InputStream::Read(void* Buffer, StreamSize Size)
    {
        this->read(static_cast<char*>(Buffer),Size);
        return static_cast<size_t>( this->gcount() );
    }

    size_t InputStream::ReadLine(Char8* Buffer, const StreamSize Size, const Char8 Delim)
    {
        this->getline(Buffer,Size,Delim);
        return static_cast<size_t>( this->gcount() );
    }

    void InputStream::SetReadPosition(StreamPos Position)
        { this->seekg(Position); }

    void InputStream::SetReadPosition(StreamOff Offset, SeekOrigin Origin)
        { this->seekg(Offset,static_cast<std::ios_base::seekdir>(Origin)); }

    StreamPos InputStream::GetReadPosition()
        { return this->tellg(); }

    Boole InputStream::Sync()
        { return ( this->sync() == 0 ); }
}
