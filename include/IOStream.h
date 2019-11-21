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
#ifndef Mezz_IOStreams_IOStream_h
#define Mezz_IOStreams_IOStream_h

#ifndef SWIG
    #include "IStream.h"
    #include "OStream.h"
#endif

namespace Mezzanine
{
    SAVE_WARNING_STATE
    SUPPRESS_CLANG_WARNING("-Wpadded")

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for streams that support both read and write operations.
    ///////////////////////////////////////
    class IOStream : public iInStream, public iOutStream, public std::iostream
    {
    public:
        /// @brief Class constructor.
        /// @param Buf A pointer to the buffer that will be streamed.
        IOStream(std::streambuf* Buf);
        /// @brief Class destructor.
        virtual ~IOStream() = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Stream Base Operations

        /// @copydoc iStreamBase::EoF() const
        [[nodiscard]] virtual Boole EoF() const;
        /// @copydoc iStreamBase::Bad() const
        [[nodiscard]] virtual Boole Bad() const;
        /// @copydoc iStreamBase::Fail() const
        [[nodiscard]] virtual Boole Fail() const;
        /// @copydoc iStreamBase::IsValid() const
        [[nodiscard]] virtual Boole IsValid() const;
        /// @copydoc iStreamBase::ClearErrors()
        virtual void ClearErrors();

        ///////////////////////////////////////////////////////////////////////////////
        // Input methods

        /// @copydoc iInStream::Read(void*, StreamSize)
        virtual size_t Read(void* Buffer, StreamSize Size);

        /// @copydoc iInStream::SetReadPosition(StreamPos)
        virtual void SetReadPosition(StreamPos Position);
        /// @copydoc iInStream::SetReadPosition(StreamOff, SeekOrigin)
        virtual void SetReadPosition(StreamOff Offset, SeekOrigin Origin);
        /// @copydoc iInStream::GetReadPosition()
        [[nodiscard]] virtual StreamPos GetReadPosition();

        /// @copydoc iInStream::Sync()
        virtual Boole Sync();

        ///////////////////////////////////////////////////////////////////////////////
        // Output methods

        /// @copydoc iOutStream::Write(const void*, StreamSize)
        virtual size_t Write(const void* Buffer, StreamSize Size);

        /// @copydoc iOutStream::SetWritePosition(StreamPos)
        virtual void SetWritePosition(StreamPos Position);
        /// @copydoc iOutStream::SetWritePosition(StreamOff, SeekOrigin)
        virtual void SetWritePosition(StreamOff Offset, SeekOrigin Origin);
        /// @copydoc iOutStream::GetWritePosition()
        [[nodiscard]] virtual StreamPos GetWritePosition();

        /// @copydoc iOutStream::Flush()
        virtual Boole Flush();

        ///////////////////////////////////////////////////////////////////////////////
        // Combined Read/Write methods

        /// @brief Moves the read and write positions in the Stream.
        /// @param Count The number of bytes to move from the current position in the Stream.
        virtual void Advance(const StreamOff Count);
        /// @brief Sets the read and write positions explicitly.
        /// @param Position The position in the Stream to be set.
        virtual void SetStreamPosition(StreamPos Position);
        /// @brief Sets the read and write positions from an offset.
        /// @param Offset The number of bytes to move the cursors back(if negative) or forward(if positive).
        /// @param Origin The starting point to be considered for the offset.
        virtual void SetStreamPosition(StreamOff Offset, SeekOrigin Origin);
    };//IOStream

    RESTORE_WARNING_STATE

    /// @brief Convenience type for a standard input/output stream in a shared_ptr.
    using IOStreamPtr = std::shared_ptr<IOStream>;
}//Mezzanine

#endif
