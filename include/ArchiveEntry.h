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
#ifndef Mezz_IOStreams_ArchiveEntry_h
#define Mezz_IOStreams_ArchiveEntry_h

/// @file
/// @brief This file contains the ArchiveEntry data struct used by other I/O utilities.

#ifndef SWIG
    #include "DataTypes.h"
    #include "ArchiveEnumerations.h"
#endif

namespace Mezzanine
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief A base class for conveying information on a specific entry in an archive.
    /// @details An archive can be the intuitive compressed archive, the filesystem, a space in memory, or something
    /// over the network. Any place a collection of files can be stored, really. An entry is single collection
    /// of metadata relating to that one file. This class specifically contains abstract methods for the query
    /// of the most common/basic information that is common between data in most or all of these places. Not
    /// every archive will support all of the information covered here, but they should contain most of it.
    ///////////////////////////////////////
    struct MEZZ_LIB ArchiveEntry
    {
        ///////////////////////////////////////////////////////////////////////////////
        // Construction and Destruction

        /// @brief Class constructor.
        ArchiveEntry() = default;
        /// @brief Copy constructor.
        /// @param Other The other entry to be copied.
        ArchiveEntry(const ArchiveEntry& Other) = default;
        /// @brief Move constructor.
        /// @param Other The other entry to be moved.
        ArchiveEntry(ArchiveEntry&& Other) = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Operators

        /// @brief Copy assignment operator.
        /// @param Other The other entry to be copied.
        /// @return Returns a reference to this.
        ArchiveEntry& operator=(const ArchiveEntry& Other) = default;
        /// @brief Move assignment operator.
        /// @param Other The other entry to be moved.
        /// @return Returns a reference to this.
        ArchiveEntry& operator=(ArchiveEntry&& Other) = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Type Information

        /// @brief Gets the type of archive this entry belongs to.
        /// @remarks Generally archives will each have their own Entry type, so this enum can be used to determine
        /// what this entry can be safely casted to in order to get more detailed metadata about the file.
        ArchiveType Archive = ArchiveType::Invalid;
        /// @brief Gets the type of entry this is in the Archive.
        /// @remarks See the EntryType enum for more detailed description of entry types.
        EntryType Entry = EntryType::Unknown;
        /// @brief Gets the method used to compress the file referenced by the entry.
        CompressionMethod Compression = CompressionMethod::Unknown;
        /// @brief The algorithm used to encrypt the file referenced by the entry.
        EncryptionMethod Encryption = EncryptionMethod::Unknown;

        ///////////////////////////////////////////////////////////////////////////////
        // Basic Metadata

        /// @brief The full path to and name of the file.
        String Name;
        /// @brief A short description of the file.
        String Comment;
        /// @brief The size of the file.
        /// @remarks Usually in compressed Archives, this will be the uncompressed size of the file.
        UInt64 Size = 0;
        /// @brief The compressed size of the file (if applicable).
        UInt64 CompressedSize = 0;
        /// @brief The time the file was created.
        UInt64 CreateTime = 0;
        /// @brief The last time the file was accessed.
        UInt64 AccessTime = 0;
        /// @brief The last time the file was modified.
        UInt64 ModifyTime = 0;
        /// @brief The 32-bit Cyclic Redundancy Check (CRC) of the file (if applicable).
        UInt32 CRC = 0;
        /// @brief A bitmask describing the attributes given to the file in the archive.
        FilePermissions Permissions = FilePermissions::None;

        ///////////////////////////////////////////////////////////////////////////////
        // Simple Queries

        /// @brief Gets the compression ratio of this entry.
        /// @remarks The "Compression" member should be checked to see if it is compressed at all. This may or may
        /// not result in a value of "1.0" due to floating point imprecision. Values returned ought to be in the
        /// range of 0.0-1.0, but no checks are performed to force this.
        /// @return Returns a PreciseReal containing the ratio of compression applied to this entry.
        PreciseReal GetCompressionRatio() const noexcept
            { return static_cast<PreciseReal>( this->CompressedSize ) / static_cast<PreciseReal>( this->Size ); }
    };//ArchiveEntry

    /// @brief Convenience pointer type for ArchiveEntry.
    using ArchiveEntryPtr = std::unique_ptr<ArchiveEntry>;
    /// @brief Convenience vector type for ArchiveEntry.
    using ArchiveEntryVector = std::vector<ArchiveEntry>;
}//Mezzanine

#endif
