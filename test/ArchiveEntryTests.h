// © Copyright 2010 - 2019 BlackTopp Studios Inc.
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
#ifndef Mezz_IOStreams_ArchiveEntryTests_h
#define Mezz_IOStreams_ArchiveEntryTests_h

/// @file
/// @brief This file tests the functionality of the ArchiveEntry struct.

#include "MezzTest.h"

#include "ArchiveEntry.h"

DEFAULT_TEST_GROUP(ArchiveEntryTests,ArchiveEntry)
{
    using namespace Mezzanine;

    ArchiveEntry First;
    First.Permissions = FilePermissions::None;
    First.Size = 100;
    First.CompressedSize = 25;

    ArchiveEntry Second;
    Second.Permissions = FilePermissions::Read | FilePermissions::Owner;
    Second.Size = 1000;
    Second.CompressedSize = 10;

    ArchiveEntry Third;
    Third.Permissions = FilePermissions::Read | FilePermissions::Owner | FilePermissions::Group_Write;
    Third.Size = 10000;
    Third.CompressedSize = 550;

    ArchiveEntry Fourth;
    Fourth.Permissions = FilePermissions::Owner_Read;
    Fourth.Size = 16000;
    Fourth.CompressedSize = 12424;

    {//GetCompressionRatio
        TEST_EQUAL_EPSILON("GetCompressionRatio()_const-First",0.25,First.GetCompressionRatio());
        TEST_EQUAL_EPSILON("GetCompressionRatio()_const-Second",0.01,Second.GetCompressionRatio());
        TEST_EQUAL_EPSILON("GetCompressionRatio()_const-Third",0.055,Third.GetCompressionRatio());
        TEST_EQUAL_EPSILON("GetCompressionRatio()_const-Fourth",0.7765,Fourth.GetCompressionRatio());
    }//GetCompressionRatio
}

#endif // Mezz_Foundation_ArchiveEntryTests_h
