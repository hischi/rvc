#pragma once

#include "notifier.h"

namespace ara::com
{
    template<typename T>
    class Event : public Notifier<T> {
    // Typedefines:

    // Constructor:
    public:
        /**
         * Constructor.
         */
        Event() : Notifier<T>() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Triggers the event to be sent to all subscribers.
         */
        void Trigger(T value) const {
            this->Notify(value);
        }

    // Statics:

    // Members:
    };
} // namespace ara::com
