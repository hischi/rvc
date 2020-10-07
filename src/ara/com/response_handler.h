#pragma once

namespace ara::com
{
    template<typename R>
    class ResponseHandler {

    public:
        /**
         * Handles a response.
         */
        virtual void HandleResponse(R response) = 0;

    };
} // namespace ara::com
