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
#ifndef Mezz_IOStreams_OutputStream_h
#define Mezz_IOStreams_OutputStream_h

#ifndef SWIG
    #include "StreamBase.h"
#endif

namespace Mezzanine
{
    SAVE_WARNING_STATE
    SUPPRESS_CLANG_WARNING("-Wpadded")

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for output (write) streams with minimal implementation.
    ///////////////////////////////////////
    class OutputStream : public OutputStreamBase, public std::ostream
    {
    public:
        /// @brief Class constructor.
        /// @param Buf A pointer to the buffer that will be streamed.
        OutputStream(std::streambuf* Buf);
        /// @brief Class destructor.
        virtual ~OutputStream() = default;

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
        // Output methods

        /// @copydoc OutputStreamBase::Write(const void*, StreamSize)
        virtual Boole Write(const void* Buffer, StreamSize Size);

        /// @copydoc OutputStreamBase::SetWritePosition(StreamPos)
        virtual void SetWritePosition(StreamPos Position);
        /// @copydoc OutputStreamBase::SetWritePosition(StreamOff, SeekOrigin)
        virtual void SetWritePosition(StreamOff Offset, SeekOrigin Origin);
        /// @copydoc OutputStreamBase::GetWritePosition()
        [[nodiscard]] virtual StreamPos GetWritePosition();

        /// @copydoc OutputStreamBase::Flush()
        virtual Boole Flush();
    };//OutputStream

    RESTORE_WARNING_STATE

    /// @brief Convenience type for a standard output stream in a shared_ptr.
    using StdOutputStreamPtr = std::shared_ptr<std::ostream>;
    /// @brief Convenience type for a Mezzanine output stream in a shared_ptr.
    using OutputStreamPtr = std::shared_ptr<OutputStream>;
}//Mezzanine

#endif
