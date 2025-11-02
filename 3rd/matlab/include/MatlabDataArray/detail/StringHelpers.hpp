/* Copyright 2015-2024 The MathWorks, Inc. */

#ifndef STRING_HELPERS_HPP_
#define STRING_HELPERS_HPP_

#include <stdint.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <locale>
#include <codecvt>

#include "ExceptionType.hpp"
#include "ExceptionHelpers.hpp"


namespace matlab {
    namespace data {
        namespace detail {
            inline bool isAscii7(const String &str) {
                return (std::find_if(str.begin(), str.end(), [](CHAR16_T ch) {return (ch & 0xFF80) != 0; }) == str.end());
            }

            inline bool isAscii7(const std::string &str) {
                return (std::find_if(str.begin(), str.end(), [](char ch) {return (ch & 0x80) != 0; }) == str.end());
            }

            inline std::string toAsciiHelper(const char16_t* in, size_t inLen) {
                if (in == nullptr) {
                    return std::string();
                }
                std::string out;
                std::transform(in, in + inLen, std::back_inserter(out),
                               [](char16_t ch) -> char { return static_cast<char>(ch); });
                return out;
            }

            template<class Facet>
            struct deletable_facet : Facet
            {
                template<class... Args>
                deletable_facet(Args&&... args) : Facet(std::forward<Args>(args)...) {}

                ~deletable_facet() {}
            };

            inline  std::string toUTF8Helper(const char16_t* in, size_t inLen) 
            {

               deletable_facet<std::codecvt<char16_t, char, std::mbstate_t>> cvt;
               std::mbstate_t state = std::mbstate_t();

               const char16_t* nextIn = nullptr;
               const char16_t* begin = in;
               const char16_t* end = begin + inLen;

               char* nextOut = nullptr;

               std::string buffer(3 * inLen, char());
               std::codecvt_base::result r = std::codecvt_base::ok;

               char* buffStart = &buffer[0];
               char* bufferEnd = buffStart + buffer.length();
               r = cvt.out(state, begin, end, nextIn, buffStart, bufferEnd, nextOut);
               if (r != std::codecvt_base::ok) {
                   throwIfError(static_cast<int>(ExceptionType::InvalidUTF16toUTF8Conversion));
               }
               buffer.resize(nextOut - &buffer[0]);
               return buffer;
            }

            inline std::codecvt_base::result fromUTF8Helper(const char* str, size_t strLen, char16_t* out, size_t *strLenOut) {
                detail::deletable_facet<std::codecvt<char16_t, char, std::mbstate_t>> cvt;
                std::mbstate_t state = std::mbstate_t();
                const char* nextIn = nullptr;
                char16_t* nextOut = nullptr;

                char16_t* bufferStart = out;
                char16_t* bufferEnd = bufferStart + strLen;
                std::codecvt_base::result r = cvt.in(state, str, str + strLen, nextIn, static_cast<char16_t*>(bufferStart), static_cast<char16_t*>(bufferEnd),
                                                        nextOut);

                *strLenOut = (nextOut - out);

                return r;
            }

        }
    }
}


#endif
