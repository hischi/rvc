#pragma once

#include <cstdint>
#include <exception>
#include "error_code.h"

namespace ara::core
{
    class ErrorCode;

    /**
     * Encapsulation of an error domain.
     * An error domain is the controlling entity for ErrorCode’s error code values, and defines the
     * mapping of such error code values to textual representations.
     * This class is a literal type, and subclasses are strongly advised to be literal types as well.
     */
    class ErrorDomain {

    // Type definitions:
    public:
        /**
         * Alias type for a unique ErrorDomain identifier type .
         */
        using IdType = std::uint64_t; 

        /**
         * Alias type for a domain-specific error code value .
         */
        using CodeType = std::int32_t;

        /**
         * Alias type for vendor-specific supplementary data .
         */
        using SupportDataType = std::uint64_t;

    // Constructors:
    public:
        ErrorDomain (ErrorDomain const &)=delete; // Copy construction shall be disabled.
        ErrorDomain (ErrorDomain &&)=delete; // Move construction shall be disabled. .

    protected:
        /**
         * Construct a new instance with the given identifier.
         * Identifiers are expected to be system-wide unique
         */
        explicit constexpr ErrorDomain (IdType id) noexcept : id(id) {
            // empty on purpose
        }

        /**
         * Destructor.
         * This dtor is non-virtual (and trivial) so that this class can be a literal type. While this class has
         * virtual functions, no polymorphic destruction is needed.
         */
        ~ErrorDomain ()=default;
    
    // Methods:
    public:
        ErrorDomain& operator= (ErrorDomain const &)=delete; // Copy assignment shall be disabled. .
        ErrorDomain& operator= (ErrorDomain &&)=delete; // Move assignment shall be disabled. .

        /**
         * Compare for equality with another ErrorDomain instance.
         * Two ErrorDomain instances compare equal when their identifiers (returned by Id()) are equal.
         */
        constexpr bool operator== (ErrorDomain const &other) const noexcept {
            return (id == other.id);
        }

        /**
         * Compare for non-equality with another ErrorDomain instance.
         */
        constexpr bool operator!= (ErrorDomain const &other) const noexcept {
            return (id != other.id);
        }

        /**
         * Return the unique domain identifier.
         */
        constexpr IdType Id () const noexcept {
            return id;
        }

        /**
         * Return the name of this error domain.
         * The returned pointer remains owned by class ErrorDomain and shall not be freed by clients.
         */
        virtual char const* Name () const noexcept=0;

        /**
         * Return a textual representation of the given error code.
         * It is a Violation if the errorCode did not originate from this error domain, and thus be subject to
         * SWS_CORE_00003.
         * The returned pointer remains owned by the ErrorDomain subclass and shall not be freed by
         * clients.
         */
        virtual char const* Message (CodeType errorCode) const noexcept=0;

        /**
         * Throw the given error as exception.
         * This function will determine the appropriate exception type for the given ErrorCode and throw it.
         * The thrown exception will contain the given ErrorCode.
         */
        virtual void ThrowAsException (ErrorCode const &errorCode) const noexcept(false)=0;

    // Members:
    protected:
        IdType id;
    };
} // namespace ara::core
