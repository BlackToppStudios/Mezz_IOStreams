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
#ifndef Mezz_IOStreams_BinaryStreamReader_h
#define Mezz_IOStreams_BinaryStreamReader_h

#ifndef SWIG
    #include "BinaryBuffer.h"
    #include "InputStream.h"
#endif

namespace Mezzanine
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief An input Stream (in binary mode) helper class for safer streaming.
    ///////////////////////////////////////
    class MEZZ_LIB BinaryStreamReader
    {
    protected:
        /// @brief A pointer to the Stream being read from.
        StdInputStreamPtr Stream;
    public:
        /// @brief Stream constructor.
        /// @param Input The Stream to read from.
        BinaryStreamReader(StdInputStreamPtr Input);
        /// @brief Class destructor.
        ~BinaryStreamReader() = default;

        ///////////////////////////////////////////////////////////////////////////////
        // Reading

        /// @brief Reads N bytes from the Stream.
        /// @remarks This will also advance the Stream position by the number of bytes read. The read operation
        /// may not read the amount of bytes specified. To verify, check the Size member on the returned
        /// BinaryBuffer.
        /// @param Bytes The number of bytes to read from the Stream.
        /// @return Returns a BinaryBuffer containing the data read from the Stream.
        [[nodiscard]] BinaryBuffer Read(const SizeType Bytes);
        /// @brief Reads the value of a standard arithmetic type from the Stream.
        /// @remarks The Stream doesn't actually know what types are where in the Stream. It is expected
        /// that the user of the Stream has taken precautions to make this coherent.
        /// @tparam Datum The standard arithmetic type to read.
        /// @return Returns a value of the type Datum that was read from the Stream.
        template<typename Datum, typename = std::enable_if_t< std::is_arithmetic_v<Datum> >>
        [[nodiscard]] Datum Read()
        {
            Datum ToReturn{};
            this->Stream->read(reinterpret_cast<char*>(&ToReturn),sizeof(Datum));
            return ToReturn;
        }
        /// @brief Advances the read position in the Stream.
        /// @remarks The return and Bytes will match if the operation was successful.
        /// @param Bytes The number of bytes to advance in the Stream.
        /// @return The number of bytes actually skipped in the Stream.
        SizeType Skip(const SizeType Bytes);

        /// @brief Gets whether or not the read position has reached the end of the Stream
        /// @return Returns true if the Stream has reached EoF, false otherwise.
        [[nodiscard]] Boole AtEnd() const;
    };//BinaryStreamReader
}//Mezzanine

#endif
