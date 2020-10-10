#pragma once

#include <list>
#include <algorithm>

namespace ara::com
{
    class Service;
    class ServiceInterface;
    class ServiceConsumer;
    class ServiceRegistry final {

    // Type definitions:

    // Constructors:
    private:
        /**
         * Default constructor.
         * Private because of singleton pattern.
         */
        ServiceRegistry() : services(), consumers() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Provides the given service in the system.
         * Consumers which want to consume the service will be notified.
         */
        void Provide(Service* service) {
            if(std::find(services.begin(), services.end(), service) == services.end()) {
                services.push_back(service);
            }
            NotifyConsumers(service);
        }

        /**
         * Stops providing the service in the system.
         * Consumers which want to consume the service will be notified.
         */
        void StopProvide(Service* service) {
            std::remove(services.begin(), services.end(), service);
            NotifyConsumers(service);
        }

        /**
         * Consume a service.
         * As soon as service is available, the consumer is notified.
         */
        ServiceInterface* Consume(ServiceConsumer* consumer) {
            if(std::find(consumers.begin(), consumers.end(), consumer) == consumers.end()) {
                consumers.push_back(consumer);
            }

            return GetService(consumer);
        }

        /**
         * Stop consuming a service.
         */
        void StopConsume(ServiceConsumer* consumer) {
            std::remove(consumers.begin(), consumers.end(), consumer);
        }

        /**
         * Returns the service-interface if it is provided at the moment. 
         * Otherwise a nullptr is returned.
         */
        ServiceInterface* GetService(ServiceConsumer* consumer);

    private:
        void NotifyConsumers(Service* service);        

    // Statics:
    public:
        /**
         * Returns the (singleton) instance of ServiceRegistry. 
         */
        static ServiceRegistry& Get() {
            static ServiceRegistry singleton;
            return singleton;
        }

    // Members:
    private:
        std::list<Service*> services;
        std::list<ServiceConsumer*> consumers;
    }; 
} // namespace ara::com
