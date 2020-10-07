#pragma once

#include <cstdint>

namespace ara::com
{
    /**
         * Unique id of the service in the network.
         */ 
        using ServiceId = uint16_t;

        /**
         * Unique id of the instantiation of the service in the network.
         */
        using InstId = uint16_t;

        /**
         * Don't care for instance ids.
         */
        static const InstId InstIdDontCare = 0xFFFFU;

        /**
         * Service version.
         */
        struct ServiceVersion {
            uint8_t major;
            uint8_t minor;
        };

        /**
         * Value which indicates a "don't care" for the version elements.
         */
        static const uint8_t ServiceVersionDontCare = 0xFFU;

        /**
         * Server state.
         */
        enum class ServiceState : uint8_t {
            Down    = 0x00U,
            Up      = 0x01U,
            Unknown = 0xFFU
        };
} // namespace ara::com
