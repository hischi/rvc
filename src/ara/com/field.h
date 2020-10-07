#pragma once

#include "notifier.h"

namespace ara::com
{
    template<typename T>
    class Field : public Notifier<T> {
    // Typedefines:

    // Constructor:
    public:
        /**
         * Constructor.
         */
        Field(T value = T()) : Notifier<T>(), value(value) {
            // empty on purpose
        }

        /**
         * Copy constructor.
         */
        Field(Field const& other) : Notifier<T>(other), value(other.value) {
            // empty on purpose
        }

        /**
         * Move constructor.
         */
        Field(Field && other) : Notifier<T>(other), value(other.value) {
            // empty on purpose
        }

        /**
         * Destructor.
         */
        virtual ~Field() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy assignment.
         */
        Field& operator=(const Field& other) {
            Notifier<T>::operator=(other);
            value = other.value;
            return *this;
        }

        /**
         * Move assign.
         */
        Field& operator=(Field&& other) {
            Notifier<T>::operator=(other);
            value = other.value;
            return *this;
        }

        /**
         * Set value. On changed value, this will issue notifies.
         * Returns the new value.
         */
        T Set(T newValue) {
            bool notify = (value != newValue);
            value = newValue;
            if(notify) {
                this->Notify(value);
            }
            return value;
        }

        /**
         * Returns the value.
         */
        T Get() const {
            return value;
        }

    // Statics:

    // Members:
    private:
        T value;
    };
} // namespace ara::com
