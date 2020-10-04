#pragma once
#include "error_domain.h"

namespace ara::core
{
    /**
     * Encapsulation of an error code.
     * An ErrorCode contains a raw error code value and an error domain. The raw error code value is
     * specific to this error domain.
     */
    class ErrorCode final {

    // Type definitions:
    struct NoDomainException : std::exception {
        const char* what() const noexcept { return "No Domain specified for Error Code"; }
    };
    
    // Constructors:
    public:
        /**
         * Construct an empty ErrorCode.
         */
        constexpr ErrorCode () noexcept : 
            value(ErrorDomain::CodeType()), domain(nullptr), data(ErrorDomain::SupportDataType()) {
            // empty on purpose
        }

        /**
         * Construct a new ErrorCode instance with parameters.
         * This constructor does not participate in overload resolution unless EnumT is an enum type.
         */
        template <typename EnumT>
        constexpr ErrorCode (EnumT e, ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType()) noexcept : 
            value(ErrorDomain::CodeType(e)), data(data), domain(nullptr) {
            // empty on purpose        
        }

        /**
         * Construct a new ErrorCode instance with parameters.
         */
        constexpr ErrorCode (ErrorDomain::CodeType value, ErrorDomain const& domain, 
            ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType()) noexcept : 
            value(value), domain(&domain), data(data) {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Return the raw error code value.
         */
        constexpr ErrorDomain::CodeType Value () const noexcept {
            return value;
        }

        /**
         * Return the domain with which this ErrorCode is associated.
         */
        constexpr ErrorDomain const& Domain () const noexcept {
            return *domain;
        }

        /**
         * Return the supplementary error context data.
         * The underlying type and the meaning of the returned value are implementation-defined.
         */
        constexpr ErrorDomain::SupportDataType SupportData () const noexcept {
            return data;
        }

        /**
         * Return a textual representation of this ErrorCode.
         */
        char const* Message () const noexcept {
            if(domain) {
                return domain->Message(value);
            } else {
                return "";
            }
        }

        /**
         * Throw this error as exception.
         * This function will determine the appropriate exception type for this ErrorCode and throw it. The
         * thrown exception will contain this ErrorCode.
         */
        void ThrowAsException () const {
            if(domain) {
                domain->ThrowAsException(*this);
            } else {
                throw NoDomainException();
            }
        }

        

    // Members:
    private:
        ErrorDomain::CodeType value;
        ErrorDomain::SupportDataType data;
        const ErrorDomain* domain;
    };

    // Globals:
    /**
     * Global operator== for ErrorCode.
     * Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
     * are equal. The result of SupportData() is not considered for equality.
     */
    constexpr bool operator== (ErrorCode const &lhs, ErrorCode const &rhs) noexcept {
        return (lhs.Domain() == rhs.Domain()) && (lhs.Value() == rhs.Value());
    }

    /**
     * Global operator!= for ErrorCode.
     * Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
     * are equal. The result of SupportData() is not considered for equality
     */
    constexpr bool operator!= (ErrorCode const &lhs, ErrorCode const &rhs) noexcept {
        return (lhs.Value() != rhs.Value()) || (lhs.Domain() != rhs.Domain());
    }

} // namespace ara::core

