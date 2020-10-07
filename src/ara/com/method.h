#pragma once

#include "response_handler.h"

namespace ara::com
{
    class Service; // Class prototype for Service

    template<typename A, typename R>
    class Method {
    // Typedefines:

    // Constructor:

    // Methods:
    public:

        /**
         * Calls the method and expects respone if handler is not nullptr.
         */
        virtual void Call(A argument, ResponseHandler<R>* handler) = 0;

        /**
         * Calls the method synchronously and expects return value.
         */
        virtual R Call(A argument) = 0;

    // Statics:

    // Members:

    };

    template<typename A>
    class Method<A, void> {
    // Typedefines:

    // Constructor:

    // Methods:
    public:

        /**
         * Calls the method synchronously.
         */
        virtual void Call(A argument) = 0;

    // Statics:

    // Members:

    };
} // namespace ara::com
