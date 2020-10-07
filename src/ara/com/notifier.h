#pragma once

#include <list>
#include "notify_handler.h"

namespace ara::com
{
    template<typename T>
    class Notifier {
    // Typedefines:

    // Constructor:
    public:
        /**
         * Constructor.
         */
        Notifier() : subscribers() {
            // empty on purpose
        }

        /**
         * Copy constructor.
         */
        Notifier(Notifier const& other) : subscribers(other.subscribers) {
            // empty on purpose
        }

        /**
         * Move constructor.
         */
        Notifier(Notifier && other) : subscribers(other.subscribers) {
            // empty on purpose
        }

        /**
         * Destructor.
         */
        virtual ~Notifier() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy assignment.
         */
        Notifier& operator=(const Notifier& other) {
            subscribers = other.subscribers;
            return *this;
        }

        /**
         * Move assign.
         */
        Notifier& operator=(Notifier&& other) {
            subscribers = other.subscribers;
            return *this;
        }

        /**
         * Subscribe to notifications.
         */
        void Subscribe(NotifyHandler<T>* handler) {
            subscribers.push_back(handler);
        }

        /**
         * Stop Subscribe to notifications.
         */
        void StopSubscribe(NotifyHandler<T>* handler) {
            subscribers.remove(handler);
        }

    protected:
        /**
         * Sends the notify to all subscribers.
         */
        void Notify(T value) const {
            for (NotifyHandler<T>* handler : subscribers) {
                handler->HandleNotify(value);
            }
        }

    // Statics:

    // Members:
    private:
        std::list<NotifyHandler<T>*> subscribers;
    };
} // namespace ara::com
