#pragma once

#include "error_code.h"

namespace ara::core
{
    /**
     * This class is a type that contains either a value or an error.
     */
    template <typename T, typename E = ErrorCode>
    class Result final {

    // Type definitions:
    public:
        /**
         * Type alias for the type T of values .
         */
        using value_type = T;

        /**
         * Type alias for the type E of errors .
         */
        using error_type = E;

    // Constructors:
    public:
        /**
         * Construct a new Result from the specified value (given as lvalue).
         */
        Result (T const &t) : 
            value(t), hasValue(true) {
            // empty on purpose
        }

        /**
         * Construct a new Result from the specified value (given as rvalue).
         */
        Result (T &&t) :
            value(t), hasValue(true) {
            // empty on purpose
        }

        /**
         * Construct a new Result from the specified error (given as lvalue)
         */
        explicit Result (E const &e) : 
            error(e), hasValue(false) {
            // empty on purpose
        }

        /**
         * Construct a new Result from the specified error (given as rvalue)
         */
        explicit Result (E &&e) : 
            error(e), hasValue(false) {
            // empty on purpose
        }

        /**
         * Copy-construct a new Result from another instance.
         */
        Result (Result const &other) : 
            value(other.value), error(other.error), hasValue(other.hasValue) {
            // empty on purpose
        }

        /**
         * Move-construct a new Result from another instance.
         */
        Result (Result &&other) 
            noexcept(std::is_nothrow_move_constructible< T >::value && std::is_nothrow_move_constructible< E >::value) : 
            value(other.value), error(other.error), hasValue(other.hasValue) {
            // empty on purpose
        }

        /**
         * Destructor.
         * This destructor is trivial if std::is_trivially_destructible<T>::value && std::is_trivially_
         * destructible<E>::value is true.
         */
        ~Result () {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy-assign another Result to this instance
         */
        Result& operator= (Result const &other) {
            hasValue = other.hasValue;

            if(hasValue) {
                value = other.value;
            } else {
                error = other.error;
            }
            return *this;
        }

        /**
         * Move-assign another Result to this instance.
         */
        Result& operator= (Result &&other) 
            noexcept(std::is_nothrow_move_constructible< T >::value && std::is_nothrow_move_assignable< T >::value && std::is_nothrow_move_constructible< E >::value && std::is_nothrow_move_assignable< E >::value) {
            hasValue = other.hasValue;
            
            if(hasValue) {
                value = other.value;
            } else {
                error = other.error;
            }
            return *this;
        }

        /**
         * Put a new value into this instance, constructed in-place from the given arguments.
         */
        template <typename... Args>
        void EmplaceValue (Args &&... args) {
            value = T(args...);
            hasValue = true;
        }

        /**
         * Put a new error into this instance, constructed in-place from the given arguments.
         */
        template <typename... Args>
        void EmplaceError (Args &&... args) {
            error = E(args...);
            hasValue = false;
        }

        /**
         * Exchange the contents of this instance with those of other.
         */
        void Swap (Result &other) 
            noexcept(std::is_nothrow_move_constructible< T >::value && std::is_nothrow_move_assignable< T >::value && std::is_nothrow_move_constructible< E >::value && std::is_nothrow_move_assignable< E >::value) {
                bool hasValueCpy = hasValue;
                T valueCpy = value;
                E errorCpy = error;

                hasValue = other.hasValue;
                value = other.value;
                error = other.error;

                other.hasValue = hasValueCpy;
                other.value = valueCpy;
                other.error = errorCpy;
            }

        /**
         * Check whether *this contains a value
         */
        bool HasValue () const noexcept {
            return hasValue;
        }

        /**
         * Check whether *this contains a value.
         */
        explicit operator bool () const noexcept {
            return hasValue;
        }

        /**
         * Access the contained value.
         * This function’s behavior is undefined if *this does not contain a value.
         */
        T const& operator * () const & {
            return value;
        }

        /**
         * Access the contained value.
         * This function’s behavior is undefined if *this does not contain a value.
         */
        T&& operator * () && {
            return value;
        }

        /**
         * Access the contained value.
         * This function’s behavior is undefined if *this does not contain a value.
         */
        T const* operator-> () const {
            return &value;
        }

        /**
         * Access the contained value.
         * This function’s behavior is undefined if *this does not contain a value.
         */
        T const& Value () const & {
            return value;
        }

        /**
         * Access the contained value.
         * This function’s behavior is undefined if *this does not contain a value.
         */
        T&& Value () && {
            return value;
        }

        /**
         * Access the contained error.
         * The behavior of this function is undefined if *this does not contain an error.
         */
        E const& Error () const & {
            return error;
        }

        /**
         * Access the contained error.
         * The behavior of this function is undefined if *this does not contain an error.
         */
        E&& Error () && {
            return error;
        }

        /**
         * Return the contained value or the given default value.
         * If *this contains a value, it is returned. Otherwise, the specified default value is returned, static_
         * cast’d to T.
         */
        template <typename U>
        T ValueOr (U &&defaultValue) const & {
            if(hasValue) {
                return value;
            } else {
                return defaultValue;
            }
        }

        /**
         * Return the contained value or the given default value.
         * If *this contains a value, it is returned. Otherwise, the specified default value is returned, static_
         * cast’d to T.
         */
        template <typename U>
        T ValueOr (U &&defaultValue) && {
            if(hasValue) {
                return value;
            } else {
                return defaultValue;
            }
        }

        /**
         * Return the contained error or the given default error.
         * If *this contains an error, it is returned. Otherwise, the specified default error is returned, static_
         * cast’d to E.
         */
        template <typename G>
        E ErrorOr (G &&defaultError) const {
            if(!hasValue) {
                return error;
            } else {
                return defaultError;
            }
        }

        /**
         * Return whether this instance contains the given error.
         * This call compares the argument error, static_cast’d to E, with the return value from Error().
         */ 
        template <typename G>
        bool CheckError (G &&error) const {
            if(hasValue) {
                return false;
            } else {
                return (this.error == static_cast<E>(error));
            }
        }

        /**
         * Return the contained value or throw an exception.
         * This function does not participate in overload resolution when the compiler toolchain does not
         * support C++ exceptions.
         */
        T const& ValueOrThrow () const& noexcept(false) {
            if(hasValue) {
                return value;
            } else {
                static_cast<ErrorCode>(error).ThrowAsException();
            }
        }

        /**
         * Return the contained value or throw an exception.
         * This function does not participate in overload resolution when the compiler toolchain does not
         * support C++ exceptions.
         */
        T&& ValueOrThrow () && noexcept(false) {
            if(hasValue) {
                return value;
            } else {
                static_cast<ErrorCode>(error).ThrowAsException();
            }
        }

        /**
         * Return the contained value or return the result of a function call.
         * If *this contains a value, it is returned. Otherwise, the specified callable is invoked and its return
         * value which is to be compatible to type T is returned from this function.
         * The Callable is expected to be compatible to this interface: T f(E const&);
         */
        template <typename F>
        T Resolve (F &&f) const {
            if(hasValue) {
                return value;
            } else {
                return f(error);
            }
        }

    // Statics:
    public:
        /**
         * Build a new Result from the specified value (given as lvalue).
         */
        static Result FromValue (T const &t) {
            return Result<T,E>(t);
        }

        /**
         * Build a new Result from the specified value (given as rvalue)
         */
        static Result FromValue (T &&t)  {
            return Result<T,E>(t);
        }

        /**
         * Build a new Result from a value that is constructed in-place from the given arguments.
         * This function shall not participate in overload resolution unless: std::is_constructible<T,
         * Args&&...>::value is true, and the first type of the expanded parameter pack is not T, and the
         * first type of the expanded parameter pack is not a specialization of Result
         */
        template <typename... Args>
        static Result FromValue (Args &&... args)  {
            return Result<T,E>(T(args...));
        }

        /**
         * Build a new Result from the specified error (given as lvalue).
         */
        static Result FromError (E const &e) {
            return Result<T,E>(e);
        }

        /**
         * Build a new Result from the specified error (given as rvalue).
         */
        static Result FromError (E &&e) {
            return Result<T,E>(e);
        }

        /**
         * Build a new Result from an error that is constructed in-place from the given arguments.
         * This function shall not participate in overload resolution unless: std::is_constructible<E,
         * Args&&...>::value is true, and the first type of the expanded parameter pack is not E, and the
         * first type of the expanded parameter pack is not a specialization of Result
         */
        template <typename... Args>
        static Result FromError (Args &&... args) {
            return Result<T,E>(E(args...));
        }

    // Members:
    private:
        T value;
        E error;
        bool hasValue;
    };

    /**
     * Specialization of class Result for "void" values.
     */
    template <typename E>
    class Result< void, E > final {

    // Type definitions:
    public:
        /**
         * Type alias for the type T of values, always "void" for this specialization .
         */
        using value_type = void;

        /**
         * Type alias for the type E of errors .
         */
        using error_type = E;

    // Constructors:
    public:
        /**
         * Construct a new Result with a "void" value.
         */
        Result () : 
            hasValue(true) {
            // empty on purpose
        }

        /**
         * Construct a new Result from the specified error (given as lvalue)
         */
        explicit Result (E const &e) : 
            error(e), hasValue(false) {
            // empty on purpose
        }

        /**
         * Construct a new Result from the specified error (given as rvalue)
         */
        explicit Result (E &&e) : 
            error(e), hasValue(false) {
            // empty on purpose
        }

        /**
         * Copy-construct a new Result from another instance.
         */
        Result (Result const &other) : 
            error(other.error), hasValue(other.hasValue) {
            // empty on purpose
        }

        /**
         * Move-construct a new Result from another instance.
         */
        Result (Result &&other) 
            noexcept(std::is_nothrow_move_constructible< E >::value) : 
            error(other.error), hasValue(other.hasValue) {
            // empty on purpose
        }

        /**
         * Destructor.
         * This destructor is trivial if std::is_trivially_destructible<E>::value is true.
         */
        ~Result () {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy-assign another Result to this instance
         */
        Result& operator= (Result const &other) {
            hasValue = other.hasValue;

            if(!hasValue) {
                error = other.error;
            }
        }

        /**
         * Move-assign another Result to this instance.
         */
        Result& operator= (Result &&other) 
            noexcept(std::is_nothrow_move_constructible< E >::value && std::is_nothrow_move_assignable< E >::value) {
            hasValue = other.hasValue;
            
            if(!hasValue) {
                error = other.error;
            }
        }

        /**
         * Put a new value into this instance, constructed in-place from the given arguments.
         */
        template <typename... Args>
        void EmplaceValue (Args &&... args) {
            hasValue = true;
        }

        /**
         * Put a new error into this instance, constructed in-place from the given arguments.
         */
        template <typename... Args>
        void EmplaceError (Args &&... args) {
            error = E(args...);
            hasValue = false;
        }

        /**
         * Exchange the contents of this instance with those of other.
         */
        void Swap (Result &other) 
            noexcept(std::is_nothrow_move_constructible< E >::value && std::is_nothrow_move_assignable< E >::value) {
                bool hasValueCpy = hasValue;
                E errorCpy = error;

                hasValue = other.hasValue;
                error = other.error;

                other.hasValue = hasValueCpy;
                other.error = errorCpy;
            }

        /**
         * Check whether *this contains a value
         */
        bool HasValue () const noexcept {
            return hasValue;
        }

        /**
         * Check whether *this contains a value.
         */
        explicit operator bool () const noexcept {
            return hasValue;
        }

        /**
         * Do nothing.
         * This function only exists for helping with generic programming.
         * The behavior of this function is undefined if *this does not contain a value.
         */
        void operator * () const {
            // empty on purpose
        }

        /**
         * Do nothing.
         * This function only exists for helping with generic programming.
         * The behavior of this function is undefined if *this does not contain a value.
         */
        void Value () const {
            // empty on purpose
        }

        /**
         * Access the contained error.
         * The behavior of this function is undefined if *this does not contain an error.
         */
        E const& Error () const & {
            return error;
        }

        /**
         * Access the contained error.
         * The behavior of this function is undefined if *this does not contain an error.
         */
        E&& Error () && {
            return error;
        }

        /**
         * Do nothing.
         * This function only exists for helping with generic programming
         */
        template <typename U>
        void ValueOr (U &&defaultValue) const {
            // empty on purpose
        }

        /**
         * Return the contained error or the given default error.
         * If *this contains an error, it is returned. Otherwise, the specified default error is returned, static_
         * cast’d to E.
         */
        template <typename G>
        E ErrorOr (G &&defaultError) const {
            if(!hasValue) {
                return error;
            } else {
                return defaultError;
            }
        }

        /**
         * Return whether this instance contains the given error.
         * This call compares the argument error, static_cast’d to E, with the return value from Error().
         */ 
        template <typename G>
        bool CheckError (G &&error) const {
            if(hasValue) {
                return false;
            } else {
                return (this.error == static_cast<E>(error));
            }
        }

        /**
         * Return the contained value or throw an exception.
         * This function does not participate in overload resolution when the compiler toolchain does not
         * support C++ exceptions.
         */
        void ValueOrThrow () const& noexcept(false) {
            if(!hasValue) {
                static_cast<ErrorCode>(error).ThrowAsException();
            }
        }

        /**
         * Return the contained value or return the result of a function call.
         * If *this contains a value, it is returned. Otherwise, the specified callable is invoked and its return
         * value which is to be compatible to type T is returned from this function.
         * The Callable is expected to be compatible to this interface: void f(E const&);
         */
        template <typename F>
        void Resolve (F &&f) const {
            if(!hasValue) {
                f(error);
            }
        }

    // Statics:
    public:
        /**
         * Build a new Result with "void" as value.
         */
        static Result FromValue () {
            return Result<void,E>();
        }

        /**
         * Build a new Result from the specified error (given as lvalue).
         */
        static Result FromError (E const &e) {
            return Result<void,E>(e);
        }

        /**
         * Build a new Result from the specified error (given as rvalue).
         */
        static Result FromError (E &&e) {
            return Result<void,E>(e);
        }

        /**
         * Build a new Result from an error that is constructed in-place from the given arguments.
         * This function shall not participate in overload resolution unless: std::is_constructible<E,
         * Args&&...>::value is true, and the first type of the expanded parameter pack is not E, and the
         * first type of the expanded parameter pack is not a specialization of Result
         */
        template <typename... Args>
        static Result FromError (Args &&... args) {
            return Result<void,E>(E(args...));
        }

    // Members:
    private:
        E error;
        bool hasValue;
    };

    // Globals:
    /**
     * Compare two Result instances for equality.
     * A Result that contains a value is unequal to every Result containing an error. A Result is equal
     * to another Result only if both contain the same type, and the value of that type compares equal.
     */
    template <typename T, typename E>
    bool operator== (Result< T, E > const &lhs, Result< T, E > const &rhs) {
        if(lhs.HasValue()) {
            return rhs.HasValue() && (lhs.Value() == rhs.Value());
        } else {
            return !rhs.HasValue() && (lhs.Error() == rhs.Error());
        }
    }

    /**
     * Compare two Result instances for inequality.
     * A Result that contains a value is unequal to every Result containing an error. A Result is equal
     * to another Result only if both contain the same type, and the value of that type compares equal.
     */
    template <typename T, typename E>
    bool operator!= (Result< T, E > const &lhs, Result< T, E > const &rhs) {
        return !(lhs == rhs);
    }

    /**
     * Compare a Result instance for equality to a value.
     * A Result that contains no value is unequal to every value. A Result is equal to a value only if the
     * Result contains a value of the same type, and the values compare equal.
     */
    template <typename T, typename E>
    bool operator== (Result< T, E > const &lhs, T const &rhs) {
        if(lhs.HasValue()) {
            return (lhs.Value() == rhs);
        } else {
            return false;
        }
    }

    /**
     * Compare a Result instance for equality to a value.
     * A Result that contains no value is unequal to every value. A Result is equal to a value only if the
     * Result contains a value of the same type, and the values compare equal.
     */
    template <typename T, typename E>
    bool operator== (T const &lhs, Result< T, E > const &rhs) {
        if(rhs.HasValue()) {
            return (rhs.Value() == lhs);
        } else {
            return false;
        }
    }

    /**
     * Compare a Result instance for inequality to a value.
     * A Result that contains no value is unequal to every value. A Result is equal to a value only if the
     * Result contains a value of the same type, and the values compare equal.
     */
    template <typename T, typename E>
    bool operator!= (Result< T, E > const &lhs, T const &rhs) {
        return !(lhs == rhs);
    }

    /**
     * Compare a Result instance for inequality to a value.
     * A Result that contains no value is unequal to every value. A Result is equal to a value only if the
     * Result contains a value of the same type, and the values compare equal.
     */
    template <typename T, typename E>
    bool operator!= (T const &lhs, Result< T, E > const &rhs) {
        return !(lhs == rhs);
    }
    
    /**
     * Compare a Result instance for equality to an error.
     * A Result that contains no error is unequal to every error. A Result is equal to an error only if the
     * Result contains an error of the same type, and the errors compare equal.
     */
    template <typename T, typename E>
    bool operator== (Result< T, E > const &lhs, E const &rhs) {
        if(!lhs.HasValue()) {
            return (lhs.Error() == rhs);
        } else {
            return false;
        }
    }

    /**
     * Compare a Result instance for equality to an error.
     * A Result that contains no error is unequal to every error. A Result is equal to an error only if the
     * Result contains an error of the same type, and the errors compare equal.
     */
    template <typename T, typename E>
    bool operator== (E const &lhs, Result< T, E > const &rhs) {
        if(!rhs.HasValue()) {
            return (rhs.Error() == lhs);
        } else {
            return false;
        }
    }

    /**
     * Compare a Result instance for inequality to an error.
     * A Result that contains no error is unequal to every error. A Result is equal to an error only if the
     * Result contains an error of the same type, and the errors compare equal.
     */
    template <typename T, typename E>
    bool operator!= (Result< T, E > const &lhs, E const &rhs) {
        return !(lhs == rhs);
    }

    /**
     * Compare a Result instance for inequality to an error.
     * A Result that contains no error is unequal to every error. A Result is equal to an error only if the
     * Result contains an error of the same type, and the errors compare equal.
     */
    template <typename T, typename E>
    bool operator!= (E const &lhs, Result< T, E > const &rhs) {
        return !(lhs == rhs);
    }

    /**
     * Swap the contents of the two given arguments.
     */
    template <typename T, typename E>
    void swap (Result< T, E > &lhs, Result< T, E > &rhs) noexcept {
        lhs.Swap(rhs);
    }

} // namespace ara::core
