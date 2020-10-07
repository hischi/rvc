#pragma once

namespace ara::com
{
    template <typename T>
    class NotifyHandler {

    public:
        /**
         * Handles a notification.
         */
        virtual void HandleNotify(T& newValue) = 0;

    };
} // namespace ara::com
