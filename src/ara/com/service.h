#pragma once

#include "service_types.h"
#include "service_interface.h"
#include "service_registry.h"

namespace ara::com
{
    /**
     * This abstract class provides a basic implementation of common service functions.
     */
    class Service {

    // Type definitions:

    // Constructors:
    public:
        /**
         * Constructs a new service object.
         */
        Service(ServiceId id, InstId instId, ServiceVersion version, ServiceInterface* intf = nullptr, bool isRemote = false) :
            id(id), instId(instId), version(version), intf(intf), isRemote(isRemote), state(ServiceState::Unknown) {
            // empty on purpose
        }

        /**
         * Copy constructor.
         */
        Service(const Service& other) : 
            id(other.id), instId(other.instId), version(other.version), intf(other.intf), isRemote(other.isRemote), state(other.state) {
            // empty on purpose
        }

        /**
         * Move constructor.
         */
        Service(Service&& other) : 
            id(other.id), instId(other.instId), version(other.version), intf(other.intf), isRemote(other.isRemote), state(other.state) {
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
            id = other.id;
            instId = other.instId;
            version = other.version;
            intf = other.intf;
            isRemote = other.isRemote;
            state = other.state;
            return *this;
        }

        /**
         * Move assign.
         */
        Service& operator=(Service&& other) {
            id = other.id;
            instId = other.instId;
            version = other.version;
            intf = other.intf;
            isRemote = other.isRemote;
            state = other.state;
            return *this;
        }

        /**
         * Returns the service id.
         */
        ServiceId Id() const {
            return id;
        }

        /**
         * Returns the instance-id of the service.
         */
        InstId InstanceId() const {
            return instId;
        }

        /**
         * Tests the instance-id for equality or don't care.
         */
        bool TestInstanceId(InstId other) const {
            return (other == InstIdDontCare) || (other == instId);
        }

        /**
         * Returns the version of the service.
         */
        ServiceVersion Version() const {
            return version;
        }

        /**
         * Tests the service-version for compatibility.
         * A version is compatible if the version is equal or uses the "don't care" value. 
         */
        bool TestServiceVersion(ServiceVersion other) {
            if(other.major == ServiceVersionDontCare || version.major == other.major) {
                return (other.minor == ServiceVersionDontCare) || (version.minor == other.minor);
            } else {
                return false;
            }
        }

        /** 
         * Returns the pointer to the service-interface.
         */
        ServiceInterface* Interface() const {
            return intf;
        }

        /**
         * Returns the service-state.
         */
        ServiceState State() const {
            return state;
        }

        /** 
         * Returns true if service is up.
         */
        bool IsServiceUp() const {
            return (state == ServiceState::Up);
        }

        /**
         * Return true if service is down.
         */
        bool IsServiceDown() const {
            return (state == ServiceState::Down);
        }

        /**
         * Returns true if the consumer is remote.
         */
        bool IsRemote() const {
            return isRemote;
        }


    public:
        /**
         * Starts the service.
         * This function calls OnStartService method which needs to be implemented by derived classes.
         */
        void StartService() {
            OnStart();
            state = ServiceState::Up;
            ServiceRegistry::Get().Provide(this);
        }

        /**
         * Stops the service.
         * This function calls OnStopService method which needs to be implemented by derived classes.
         */
        void StopService() {
            state = ServiceState::Down;
            ServiceRegistry::Get().StopProvide(this);
            OnStop();
        }

    protected:
        /**
         * Is called when service is started.
         * Override this method to handle startup-sequence of service in derived classes.
         */
        virtual void OnStart() {
            // empty on purpose
        }

        /**
         * Is called when service is stopped.
         * Override this method to handle stop-sequence of service in derived classes.
         */
        virtual void OnStop() {
            // empty on purpose
        }

    // Statics:

    // Members:
    protected:
        ServiceId id;
        InstId instId;
        ServiceVersion version;
        ServiceInterface* intf;
        bool isRemote;
        ServiceState state;
    };


} // namespace ara::com
