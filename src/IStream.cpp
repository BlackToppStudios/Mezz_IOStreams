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

#include "IStream.h"

namespace Mezzanine
{
    IStream::IStream(std::streambuf* Buf) :
        std::istream(Buf)
        {  }

    ///////////////////////////////////////////////////////////////////////////////
    // Stream Base Operations

    Boole IStream::EoF() const
        { return this->eof(); }

    Boole IStream::Bad() const
        { return this->bad(); }

    Boole IStream::Fail() const
        { return this->fail(); }

    Boole IStream::IsValid() const
        { return this->good(); }

    void IStream::ClearErrors()
        { this->clear(); }

    ///////////////////////////////////////////////////////////////////////////////
    // Input methods

    size_t IStream::Read(void* Buffer, StreamSize Size)
    {
        this->read(static_cast<char*>(Buffer),Size);
        return static_cast<size_t>( this->gcount() );
    }

    size_t IStream::ReadLine(Char8* Buffer, const StreamSize Size, const Char8 Delim)
    {
        this->getline(Buffer,Size,Delim);
        return static_cast<size_t>( this->gcount() );
    }

    void IStream::SetReadPosition(StreamPos Position)
        { this->seekg(Position); }

    void IStream::SetReadPosition(StreamOff Offset, SeekOrigin Origin)
        { this->seekg(Offset,static_cast<std::ios_base::seekdir>(Origin)); }

    StreamPos IStream::GetReadPosition()
        { return this->tellg(); }

    Boole IStream::Sync()
        { return ( this->sync() == 0 ); }

    String IStream::GetAsString()
    {
        String Ret;
        size_t RetSize = static_cast<size_t>( this->GetSize() );
        if( RetSize > 0 ) {
            Ret.reserve(RetSize);
        }

        StreamPos SavedReadPos = this->GetReadPosition();
        this->SetReadPosition(0);

        Ret.append(std::istreambuf_iterator<char>(*this),{});

        this->SetReadPosition(SavedReadPos);
        return Ret;
    }
}
