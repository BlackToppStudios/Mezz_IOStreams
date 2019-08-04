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
#ifndef _Mezz_IOStreams_ArchiveEnumerations_h
#define _Mezz_IOStreams_ArchiveEnumerations_h

#ifndef SWIG
    #include "BitFieldTools.h"
#endif

namespace Mezzanine
{
    /// @brief Used to indicate what kind of resources the Entresol should look for
    enum class ArchiveType
    {
        Invalid    = 0,  ///< Indicates an error condition of some kind.
        FileSystem,      ///< No archive format, raw binary on disk.
        Zip,             ///< Archive abiding by the PKWARE Zip format.
        SevenZ           ///< Archive abiding by the 7zip format.
    };

    /// @brief Used to indicate an algorithm of compression.
    enum class CompressionMethod
    {
        Unknown   = 0,
        None,
        Deflate,
        Deflate64,
        BZip2,
        ZPAQ,
        Brotli9,
        Brotli11,
        LZMA,
        LZ4,
        LZ4F
    };

    /// @brief Used to indicate an algorithm of encryption.
    enum class EncryptionMethod
    {
        Unknown  = 0,
        PKWARE,
        AES_128,
        AES_192,
        AES_256,
        RC2,
        RC4,
        TDES_112,
        TDES_168
    };

    /// @brief Used to differentiate entries in some archive systems.
    enum class EntryType
    {
        Unknown   = 0,
        File,
        Directory,
        Hardlink,
        Symlink
    };

    /// @brief Used to identify the permissions a file has in an archive.
    /// @remarks These permissions are based on posix/std::filesystem permissions.
    enum class FilePermissions : UInt32
    {
        None          = 0,
        Other_Execute = EnumBit(1),
        Other_Write   = EnumBit(2),
        Other_Read    = EnumBit(3),
        Group_Execute = EnumBit(4),
        Group_Write   = EnumBit(5),
        Group_Read    = EnumBit(6),
        Owner_Execute = EnumBit(7),
        Owner_Write   = EnumBit(8),
        Owner_Read    = EnumBit(9),
        // Permission helper values
        Read = Owner_Read | Group_Read | Other_Read,
        Write = Owner_Write | Group_Write | Other_Write,
        Execute = Owner_Execute | Group_Execute | Other_Execute,
        // User helper values
        Other = Other_Read | Other_Write | Other_Execute,
        Group = Group_Read | Group_Write | Group_Execute,
        Owner = Owner_Read | Owner_Write | Owner_Execute
    };
    ENABLE_BITMASK_OPERATORS_INSIDE_MEZZANINE(FilePermissions)
}//Mezzanine

#endif
