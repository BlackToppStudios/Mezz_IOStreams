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
#ifndef Mezz_IOStreams_InputStream_h
#define Mezz_IOStreams_InputStream_h

#ifndef SWIG
    #include "StreamBase.h"
#endif

namespace Mezzanine
{
    SAVE_WARNING_STATE
    SUPPRESS_CLANG_WARNING("-Wpadded")

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for input (read) streams with minimal implementation.
    ///////////////////////////////////////
    class InputStream : public InputStreamBase, public std::istream
    {
    public:
        /// @brief Class constructor.
        /// @param Buf A pointer to the buffer that will be streamed.
        InputStream(std::streambuf* Buf);
        /// @brief Class destructor.
        virtual ~InputStream() = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Stream Base Operations

        /// @copydoc StreamBase::EoF() const
        [[nodiscard]] virtual Boole EoF() const;
        /// @copydoc StreamBase::Bad() const
        [[nodiscard]] virtual Boole Bad() const;
        /// @copydoc StreamBase::Fail() const
        [[nodiscard]] virtual Boole Fail() const;
        /// @copydoc StreamBase::IsValid() const
        [[nodiscard]] virtual Boole IsValid() const;
        /// @copydoc StreamBase::ClearErrors()
        virtual void ClearErrors();

        ///////////////////////////////////////////////////////////////////////////////
        // Input Functions

        /// @copydoc InputStreamBase::Read(void*, const StreamSize)
        virtual size_t Read(void* Buffer, const StreamSize Size);
        /// @copydoc InputStreamBase::ReadLine(Char8*, const StreamSize, const Char8)
        virtual size_t ReadLine(Char8* Buffer, const StreamSize Size, const Char8 Delim = '\n');

        /// @copydoc InputStreamBase::SetReadPosition(StreamPos)
        virtual void SetReadPosition(StreamPos Position);
        /// @copydoc InputStreamBase::SetReadPosition(StreamOff, SeekOrigin)
        virtual void SetReadPosition(StreamOff Offset, SeekOrigin Origin);
        /// @copydoc InputStreamBase::GetReadPosition()
        [[nodiscard]] virtual StreamPos GetReadPosition();

        /// @copydoc InputStreamBase::Sync()
        virtual Boole Sync();
    };//InputStream

    RESTORE_WARNING_STATE

    /// @brief Convenience type for a standard input stream in a shared_ptr.
    using StdInputStreamPtr = std::shared_ptr<std::istream>;
    /// @brief Convenience type for a Mezzanine input stream in a shared_ptr.
    using InputStreamPtr = std::shared_ptr<InputStream>;
}//Mezzanine

#endif
