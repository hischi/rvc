#pragma once

#include <cstdint>

namespace ara::com
{
    template<typename T>
    class SomeIpDataTransformer {

    // Type definitions:

    // Constructors:
    // None since abstract interface

    // Methods:
    // None since static interface
        
    // Statics:
    public:
        /**
         * Serialises the given data structure to the given buffer in the SomeIp way.
         */
        uint32_t Serialise(T& data, uint8_t* buffer, uint32_t maxLen) = 0;

        /**
         * Deserialises the given SomeIp buffer into the given data structure.
         */
        void Deserialise(const uint8_t* buffer, uint32_t len, T* data) = 0;

    // Members:
    // None since static interface
    };
} // namespace ara::com
