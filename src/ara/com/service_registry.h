#pragma once



namespace ara::com
{
    class ServiceRegistry final {

    // Type definitions:

    // Constructors:
    private:
        /**
         * Default constructor.
         * Private because of singleton pattern.
         */
        ServiceRegistry() {
            // empty on purpose
        }

    public:
        /**
         * Default desctructor.
         */
        ~ServiceRegistry() {
            // empty on purpose
        }

    // Methods:

    // Statics:
    public:
        /**
         * Returns the (singleton) instance of ServiceRegistry. 
         */
        static ServiceRegistry& Instance() {
            static ServiceRegistry singleton;
            return singleton;
        }

    // Members:

    }; 
} // namespace ara::com
