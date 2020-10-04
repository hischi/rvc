#pragma once

#include "exception.h"

namespace ara::core
{
    /**
     * An enumeration that defines all errors of the CORE Functional Cluster.
     */
    enum class CoreErrc : ErrorDomain::CodeType {
        kInvalidArgument            = 22,   // an invalid argument was passed to a function
        kInvalidMetaModelShortname  = 137,  // given string is not a valid model element shortname
        kInvalidMetaModelPath       = 138   // missing or invalid path to model element
    };

    /**
     * Exception type thrown for CORE errors.
     */
    class CoreException : public Exception {
    // Constructors:
    public:
        /**
         * Construct a new CoreException from an ErrorCode.
         */
        explicit CoreException (ErrorCode err) noexcept : Exception(err) {
            // empty on purpose
        }
    };

    /**
     * An error domain for errors originating from the CORE Functional Cluster .
     */
    class CoreErrorDomain final : public ErrorDomain {
    
    // Type definitions:
    public:
        static const ErrorDomain::IdType UID = 0x8000000000000014LLU;

        /**
         * Alias for the error code value enumeration
         */
        using Errc = CoreErrc;

        /**
         * Alias for the exception base class.
         */
        using Exception = CoreException;

    // Constructors:
    public:
        /**
         * Default constructor.
         */
        constexpr CoreErrorDomain () noexcept : ErrorDomain(UID) {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Return the "shortname" of this error domain.
         */
        char const* Name () const noexcept override {
            return "Core";
        }

        /**
         * Translate an error code value into a text message
         */
        char const* Message (ErrorDomain::CodeType errorCode) const noexcept override{
            switch (Errc(errorCode))
            {
            case Errc::kInvalidArgument:            return "Invalid Argument";
            case Errc::kInvalidMetaModelShortname:  return "Invalid Meta Model Shortname";
            case Errc::kInvalidMetaModelPath:       return "Invalid Meta Model Path";
            default:                                return "Unknown Error Code";
            }
        }

        /**
         * Throw the exception type corresponding to the given ErrorCode.
         */
        void ThrowAsException (ErrorCode const &errorCode) const noexcept(false) override { 
            throw CoreException(errorCode);
        }

    // Statics:
    public:
        static const CoreErrorDomain domain;
    };

    // Globals:
    /**
     * Return a reference to the global CoreErrorDomain.
     */
    constexpr ErrorDomain const& GetCoreErrorDomain () noexcept {
        return CoreErrorDomain::domain;
    }

    /**
     * Create a new ErrorCode within CoreErrorDomain.
     * This function is used internally by constructors of ErrorCode. It is usually not used directly by
     * users.
     */
    constexpr ErrorCode MakeErrorCode (CoreErrc code, ErrorDomain::SupportDataType data) noexcept {
        return ErrorCode((ErrorDomain::CodeType) code, GetCoreErrorDomain (), data);
    }

} // namespace ara::core
