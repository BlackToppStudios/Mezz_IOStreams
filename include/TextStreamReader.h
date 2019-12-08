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
#ifndef Mezz_IOStreams_TextStreamReader_h
#define Mezz_IOStreams_TextStreamReader_h

#ifndef SWIG
    #include "InputStream.h"
#endif

namespace Mezzanine
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief An input Stream (in text mode) helper class for safer streaming.
    ///////////////////////////////////////
    class MEZZ_LIB TextStreamReader
    {
    protected:
        /// @brief A pointer to the Stream being read from.
        StdInputStreamPtr Stream;
    public:
        /// @brief Stream constructor.
        /// @param Input The Stream to read from.
        TextStreamReader(StdInputStreamPtr Input);
        /// @brief Class destructor.
        ~TextStreamReader() = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Reading

        /// @brief Reads N bytes from the Stream.
        /// @remarks This will also advance the Stream position by the number of bytes read. The read operation
        /// may not read the amount of bytes specified. To verify, query the size on the returned String.
        /// @param Bytes The number of bytes to read from the Stream.
        /// @return Returns a String containing the data read from the Stream.
        [[nodiscard]] String Read(const SizeType Bytes);
        /// @brief Reads characters from the Stream until the delimiter is found.
        /// @remarks This will also advance the Stream position by the number of bytes read, which includes the
        /// the specified delimiter. So any further read operation will begin at the Stream position just after the
        /// delimiter. However the delimiter will not be returned as a part of the return String.
        /// @param Delim The character to stop at when reading the Stream.
        /// @return Returns a String with all characters from the read position to (but not including) the delimiter.
        [[nodiscard]] String ReadLine(const Char8 Delim = '\n');
        /// @brief Reads a single character from the Stream.
        /// @remarks This will also advance the Stream position by 1 byte.
        /// @return Returns the character at the current read position, or a null terminator if the Stream is at EoF.
        [[nodiscard]] Char8 ReadCharacter();
        /// @brief Advances the read position in the Stream.
        /// @remarks The return and Bytes will match if the operation was successful.
        /// @param Bytes The number of bytes to advance in the Stream.
        /// @return The number of bytes actually skipped in the Stream.
        SizeType Skip(const SizeType Bytes);

        /// @brief Reads the entire Stream and places it into a String.
        /// @remarks This function reads the entire Stream from start to finish. The read position will be saved,
        /// then set to the beginning of the Stream, advanced to the end, and then set back to the same read
        /// position the Stream was at when this function was called.
        /// @n @n
        /// This might produce a very large String. Be mindful of the Streams size when using this.
        /// @return Returns a String containing the entire contents of the Stream.
        [[nodiscard]] String GetAsString();
        /// @brief Gets whether or not the read position has reached the end of the Stream
        /// @return Returns true if the Stream has reached EoF, false otherwise.
        [[nodiscard]] Boole AtEnd() const;
    };//TextStreamReader
}//Mezzanine

#endif
