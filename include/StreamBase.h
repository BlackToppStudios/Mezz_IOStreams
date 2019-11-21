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
#ifndef Mezz_IOStreams_StreamBase_h
#define Mezz_IOStreams_StreamBase_h

/// @file
/// @brief This file contains the interfaces used by the various Stream classes.

#ifndef SWIG
    #include "DataTypes.h"
#endif

namespace Mezzanine
{
    /// @brief Convenience define for the Stream position data type.
    using StreamPos = std::streampos;
    /// @brief Convenience define for the Stream offset data type.
    using StreamOff = std::streamoff;
    /// @brief Convenience define for the Stream size data type.
    using StreamSize = std::streamsize;

    /// @brief This enum describes the flags that control certain behaviors of a Stream.
    /// @details It is important to note that not all of these flags are used by all Streams.
    enum StreamFlags
    {
        // Standard Flags
        SF_None         = 0,                     ///< Error/no special initialization.
        SF_Read         = std::ios_base::in,     ///< Permit read operations on the Stream.
        SF_Write        = std::ios_base::out,    ///< Permit write operations on the Stream.
        SF_Append       = std::ios_base::app,    ///< All write operations on the Stream are done at the end of the Stream.
        SF_AtEnd        = std::ios_base::ate,    ///< Moves the starting position of the Stream to the end upon initialization.
        SF_Binary       = std::ios_base::binary, ///< Tell the Stream that the file in question is Binary.
        SF_Truncate     = std::ios_base::trunc,  ///< Clear the contents of the file when opening.  Note that this will also create the file if it's not found.
        // Convenience Flags
        SF_Create       = SF_Truncate,
        SF_ReadWrite    = SF_Read | SF_Write
    };

    /// @brief An enum describing which position should be considered the origin for changing the current position in a Stream.
    enum class SeekOrigin
    {
        Beginning = std::ios_base::beg,  ///< The beginning of the Stream.
        Current   = std::ios_base::cur,  ///< The current position for read/write operations in the Stream.
        End       = std::ios_base::end   ///< The end of the Stream.
    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The base interface for I/O Streams.
    ///////////////////////////////////////
    class iStreamBase
    {
    public:
        /// @brief Class constructor.
        iStreamBase() = default;
        /// @brief Class destructor.
        virtual ~iStreamBase() = default;

        /// @brief Gets the identifier for this Stream.
        /// @remarks Typically the identifier will uniquely identify the source of the Stream such
        /// as a file name or URI.  This is meant to be more flexible than that though as it may
        /// need to be used to identify a memory buffer in some cases.
        /// @return Returns a String containing the identifier for the Stream.
        [[nodiscard]] virtual String GetIdentifier() const = 0;
        /// @brief Gets the name of the AssetGroup this Stream is streaming to/from.
        /// @remarks The returned Stream can be empty, which usually means it wasn't created by the Resource system.
        /// @return Returns a String containing the identifier this Stream was grouped with.
        [[nodiscard]] virtual String GetGroup() const = 0;

        /// @brief Gets the size of the Stream.
        /// @return Returns the size of this Stream in bytes.
        [[nodiscard]] virtual StreamSize GetSize() const = 0;
        /// @brief Gets whether or not this Stream supports seeking.
        /// @return Returns true if this Stream supports seeking to any point in the Stream, false otherwise.
        [[nodiscard]] virtual Boole CanSeek() const = 0;
        /// @brief Gets whether or not the source of this Stream is encrypted.
        /// @return Returns true if the original data being streamed is encrypted, false otherwise.
        [[nodiscard]] virtual Boole IsEncrypted() const = 0;
        /// @brief Gets whether or not this Stream is decompressing/decrypting the source data.
        /// @remarks A Raw Stream is fairly common for file system and memory streams.  Even with Zip or other
        /// similar archive streams it can be useful if custom operations are desired, but less common.
        /// @return Returns true if the source data is being streamed without being altered, false otherwise.
        [[nodiscard]] virtual Boole IsRaw() const = 0;

        /// @brief Gets whether or not the current position is at the end of the Stream.
        /// @return Returns true if the current position has reached the end of the Stream, false otherwise.
        [[nodiscard]] virtual Boole EoF() const = 0;
        /// @brief Gets whether or not a critical error was detected in a previous operation in the Stream.
        /// @return Returns true if a critical error has occurred and the Stream integrity may be invalid, false otherwise.
        [[nodiscard]] virtual Boole Bad() const = 0;
        /// @brief Gets whether or not an otherwise silent and recoverable error was detected in a previous operation in the Stream.
        /// @return Returns true if a non-critical operation failed (such as seek), false otherwise.
        [[nodiscard]] virtual Boole Fail() const = 0;
        /// @brief Gets whether or not this Stream is intact and ready for operations.
        /// @return Returns true if no failures have been detected, false otherwise.
        [[nodiscard]] virtual Boole IsValid() const = 0;

        /// @brief Clears any stored error state on the Stream.
        /// @remarks This is useful for non-critical errors such as ones that cause "EoF()" or "Fail()" to return true but not
        /// "Bad()".  Using this to clear critical errors is not advised.
        virtual void ClearErrors() = 0;
    };//iStreamBase

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Interface class for input (read) Streams.
    ///////////////////////////////////////
    class iInStream : virtual public iStreamBase
    {
    public:
        /// @brief Class constructor.
        iInStream() = default;
        /// @brief Class destructor.
        virtual ~iInStream() = default;

        /// @brief Reads from the Stream and copies that data to a buffer.
        /// @param Buffer The buffer to be populated with the read data.
        /// @param Size The number of bytes to read from the Stream.
        /// @return Returns the number of bytes successfully read.
        virtual size_t Read(void* Buffer, StreamSize Size) = 0;
        /// @brief Reads a single line from a String.
        /// @param Buffer Pointer to the buffer to copy to.
        /// @param BufferSize The size of the Buffer parameter.
        /// @param Delim The character that marks the end of a line.
        /// @return Returns the number of bytes actually read, not including the Delimiter.
        virtual size_t ReadLine(Char8* Buffer, const size_t BufferSize, const Char8 Delim = '\n') = 0;

        /// @brief Sets the position of the read cursor explicitly.
        /// @param Position The position to be set.Stream
        virtual void SetReadPosition(StreamPos Position) = 0;
        /// @brief Sets the position of the read cursor.
        /// @param Offset The number of bytes to move the read cursor back(if negative) or forward(if positive).
        /// @param Origin The starting point to be considered for the offset.
        virtual void SetReadPosition(StreamOff Offset, SeekOrigin Origin) = 0;
        /// @brief Gets the current read position in this Stream.
        /// @return Returns a StreamPos representing the current read position.
        [[nodiscard]] virtual StreamPos GetReadPosition() = 0;

        /// @brief Synchronizes the internal Stream buffer with data from the Stream source.
        /// @return Returns true if the sync was successful and the Stream is usable, false otherwise.
        virtual Boole Sync() = 0;
        /// @brief Gets the contents of the Stream as a String.
        /// @warning This function may produce a VERY large String as it gets the entire Stream contents.
        /// @return Returns a String with the contents of the Stream.
        [[nodiscard]] virtual String GetAsString() = 0;
    };//iInStream

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Interface class for output (write) Streams.
    ///////////////////////////////////////
    class iOutStream : virtual public iStreamBase
    {
    public:
        /// @brief Class constructor.
        iOutStream() = default;
        /// @brief Class destructor.
        virtual ~iOutStream() = default;

        /// @brief Writes data to the Stream.
        /// @param Buffer The memory buffer to write to this Stream.
        /// @param Size The size of the buffer being passed in.
        /// @return Returns the number of bytes successfully written.
        virtual size_t Write(const void* Buffer, StreamSize Size) = 0;

        /// @brief Sets the position of the write cursor explicitly.
        /// @param Position The position to be set.
        virtual void SetWritePosition(StreamPos Position) = 0;
        /// @brief Sets the position of the write cursor.
        /// @param Offset The number of bytes to move the write cursor back(if negative) or forward(if positive).
        /// @param Origin The starting point to be considered for the offset.
        virtual void SetWritePosition(StreamOff Offset, SeekOrigin Origin) = 0;
        /// @brief Gets the current write position in this Stream.
        /// @return Returns a StreamPos representing the current write position.
        [[nodiscard]] virtual StreamPos GetWritePosition() = 0;

        /// @brief Flushes all writes to the Streams internal buffer to the Stream destination.
        /// @return Returns true if the flush was successful and the Stream is usable, false otherwise.
        virtual Boole Flush() = 0;
    };//iOutStream
}//Mezzanine

#endif
