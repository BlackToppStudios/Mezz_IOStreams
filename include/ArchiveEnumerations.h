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
#ifndef Mezz_IOStreams_ArchiveEnumerations_h
#define Mezz_IOStreams_ArchiveEnumerations_h

#ifndef SWIG
    #include "BitFieldTools.h"
#endif

namespace Mezzanine
{
    /// @brief Used to indicate what kind of resources the Entresol should look for
    enum class ArchiveType
    {
        Invalid    = 0,  ///< Uninitialized or Indicates an error condition of some kind.
        FileSystem,      ///< No archive format, raw binary on disk.
        Zip,             ///< Archive abiding by the PKWARE Zip format.
        SevenZ           ///< Archive abiding by the 7zip format.
    };

    /// @brief Used to indicate an algorithm of compression.
    enum class CompressionMethod
    {
        Unknown   = 0,   ///< Uninitialized or Indicates an error condition of some kind.
        None,            ///< No compression is applied.
        Deflate,         ///< Common DEFLATE compression.
        Deflate64,       ///< A 64-bit variant of Deflate.
        BZip2,           ///< A compression method that is slow to compress, but fast to decompress.
        ZPAQ,            ///< A compression method that uses a combination of LZ77 and BWT.
        Brotli,          ///< A google compression method based on LZ77 offering denser compression than DEFLATE.
        LZMA,            ///< The compression method used by 7zip offering dense compression.
        LZ4              ///< A compression method focused on compression and decompression speed.
    };

    /// @brief Used to indicate an algorithm of encryption.
    enum class EncryptionMethod
    {
        Unknown  = 0,    ///< Uninitialized or Indicates an error condition of some kind.
        None,            ///< No encryption is applied.
        PKWARE,          ///< Proprietary encryption used by PKWARE in Zip/Zip64 files.
        AES_128,         ///< A symmetric encryption with a 128-bit key size.
        AES_192,         ///< A symmetric encryption with a 192-bit key size.
        AES_256,         ///< A symmetric encryption with a 256-bit key size.
        RSA_128,         ///< An asymmetric encryption with a 128-bit key size.
        RSA_192,         ///< An asymmetric encryption with a 192-bit key size.
        RSA_256,         ///< An asymmetric encryption with a 256-bit key size.
        TDES_112,        ///< Also 3TES. A symmetric encryption with a 112-bit key size.
        TDES_168         ///< Also 3TES. A symmetric encryption with a 168-bit key size.
    };

    /// @brief Used to differentiate entries in some archive systems.
    enum class EntryType
    {
        Unknown   = 0,   ///< Uninitialized or Indicates an error condition of some kind.
        File,            ///< Indicates the entry is a file.
        Directory,       ///< Indicates the entry is a directory.
        Hardlink,        ///< Indicates the entry is a name-file association to data on disk.
        Symlink          ///< Indicates the entry is a symbolic link (shortcut) to a file or directory entry.
    };

    /// @brief Used to identify the permissions a file has in an archive.
    /// @remarks These permissions are based on posix/std::filesystem permissions.
    enum class FilePermissions : UInt32
    {
        None          = 0,           ///< File has no permissions, which is an invalid state.
        Other_Execute = EnumBit(1),  ///< Other users can execute the file.
        Other_Write   = EnumBit(2),  ///< Other users can write to the file.
        Other_Read    = EnumBit(3),  ///< Other users can read from the file.
        Group_Execute = EnumBit(4),  ///< Users in the owning group can execute the file.
        Group_Write   = EnumBit(5),  ///< Users in the owning group can write to the file.
        Group_Read    = EnumBit(6),  ///< Users in the owning group can read from the file.
        Owner_Execute = EnumBit(7),  ///< The owner can execute the file.
        Owner_Write   = EnumBit(8),  ///< The owner can write to the file.
        Owner_Read    = EnumBit(9),  ///< The owner can read from the file.
        // Permission helper values
        Read = Owner_Read | Group_Read | Other_Read,              ///< Everyone can read from the file.
        Write = Owner_Write | Group_Write | Other_Write,          ///< Everyone can write to the file.
        Execute = Owner_Execute | Group_Execute | Other_Execute,  ///< Everyone can execute the file.
        // User helper values
        Other = Other_Read | Other_Write | Other_Execute,  ///< Other users have full file permissions.
        Group = Group_Read | Group_Write | Group_Execute,  ///< Users in the owning group have full file permissions.
        Owner = Owner_Read | Owner_Write | Owner_Execute   ///< The owner has full file permissions.
    };
    ENABLE_BITMASK_OPERATORS_INSIDE_MEZZANINE(FilePermissions)
}//Mezzanine

#endif
