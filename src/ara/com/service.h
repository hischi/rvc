#pragma once

#include "../core/result.h"

namespace ara::com
{
    /**
     * This abstract class provides a basic implementation of common service functions.
     */
    class Service {

    // Type definitions:
    public:
        /**
         * Unique id of the service in the network.
         */ 
        using ServiceIdType = uint16_t;

        /**
         * Unique id of the instantiation of the service in the network.
         */
        using InstanceIdType = uint16_t;

        /**
         * Service version.
         */
        struct ServiceVersionType {
            uint8_t major;
            uint8_t minor;
        };

        /**
         * Value which indicates a "don't care" for the version elements.
         */
        static const uint8_t ServiceVersionDontCare = 0xFFU;

        /**
         * Unique id of methods (and events).
         */
        using MethodIdType = uint16_t;

        /**
         * Server state.
         */
        enum class ServiceStateType : uint8_t {
            Down    = 0x00U,
            Up      = 0x01U,
            Unknown = 0xFFU
        };

    // Constructors:
    public:
        /**
         * Constructs a new service object.
         */
        Service(ServiceIdType serviceId, InstanceIdType instanceId, ServiceVersionType serviceVersion) :
            serviceId(serviceId), instanceId(instanceId), serviceVersion(serviceVersion), serviceState(ServiceStateType::Unknown) {
            // empty on purpose
        }

        /**
         * Copy constructor.
         */
        Service(const Service& other) : 
            serviceId(other.serviceId), instanceId(other.instanceId), serviceVersion(other.serviceVersion), serviceState(other.serviceState){
            // empty on purpose
        }

        /**
         * Move constructor.
         */
        Service(Service&& other) : 
            serviceId(other.serviceId), instanceId(other.instanceId), serviceVersion(other.serviceVersion), serviceState(other.serviceState){
            // empty on purpose
        }

        /**
         * Default destructor.
         */
        virtual ~Service() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy assign.
         */
        Service& operator=(const Service& other) {
            serviceId = other.serviceId;
            instanceId = other.instanceId;
            serviceVersion = other.serviceVersion;
            serviceState = other.serviceState;
            return *this;
        }

        /**
         * Move assign.
         */
        Service& operator=(Service&& other) {
            serviceId = other.serviceId;
            instanceId = other.instanceId;
            serviceVersion = other.serviceVersion;
            serviceState = other.serviceState;
            return *this;
        }

        /**
         * Returns the service id.
         */
        ServiceIdType ServiceId() const {
            return serviceId;
        }

        /**
         * Returns the instance-id of the service.
         */
        InstanceIdType InstanceId() const {
            return instanceId;
        }

        /**
         * Returns the version of the service.
         */
        ServiceVersionType ServiceVersion() const {
            return serviceVersion;
        }

        /**
         * Tests the service-version for compatibility.
         * A version is compatible if the version is equal or uses the "don't care" value. 
         */
        bool TestServiceVersion(ServiceVersionType other) {
            if(other.major == ServiceVersionDontCare || serviceVersion.major == other.major) {
                return (other.minor == ServiceVersionDontCare) || (serviceVersion.minor == other.minor);
            } else {
                return false;
            }
        }

        /**
         * Returns the service-state.
         */
        ServiceStateType ServiceState() const {
            return serviceState;
        }

        /** 
         * Returns true if service is up.
         */
        bool IsServiceUp() const {
            return (serviceState == ServiceStateType::Up);
        }

        /**
         * Return true if service is down.
         */
        bool IsServiceDown() const {
            return (serviceState == ServiceStateType::Down);
        }


    protected:
        /**
         * Starts the service.
         * This function calls OnStartService method which needs to be implemented by derived classes.
         */
        void StartService() {
            OnStartService();
            serviceState = ServiceStateType::Up;
        }

        /**
         * Stops the service.
         * This function calls OnStopService method which needs to be implemented by derived classes.
         */
        void StopService() {
            serviceState = ServiceStateType::Down;
            OnStopService();
        }

        /**
         * Is called when service is started.
         * Override this method to handle startup-sequence of service in derived classes.
         */
        virtual void OnStartService() {
            // empty on purpose
        }

        /**
         * Is called when service is stopped.
         * Override this method to handle stop-sequence of service in derived classes.
         */
        virtual void OnStopService() {
            // empty on purpose
        }

    // Statics:

    // Members:
    protected:
        ServiceIdType serviceId;
        InstanceIdType instanceId;
        ServiceVersionType serviceVersion;
        ServiceStateType serviceState;
    };


} // namespace ara::com
