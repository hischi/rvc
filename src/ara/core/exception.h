#pragma once

#include "error_code.h"

namespace ara::core
{
    /**
     * Base type for all AUTOSAR exception types
     */
    class Exception : public std::exception {

    // Type definitions:

    // Constructors:
    public:
        /**
         * Construct a new Exception object with a specific ErrorCode.
         */
        explicit Exception (ErrorCode err) noexcept : err(err) {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Return the explanatory string.
         * This function overrides the virtual function std::exception::what. All guarantees about the
         * lifetime of the returned pointer that are given for std::exception::what are preserved.
         */
        char const* what () const noexcept override {
            return err.Message();
        }

        /**
         * Return the embedded ErrorCode that was given to the constructor.
         */
        ErrorCode const& Error () const noexcept {
            return err;
        }

    // Members:
    protected:
        ErrorCode err;
    };
} // namespace ara::core
