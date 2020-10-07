#pragma once

#include "service_types.h"

namespace ara::com
{
    /**
     * This abstract class provides an interface to consume a service.
     */
    class ServiceConsumer {

    // Type definitions:

    // Constructors:
    public:
        /**
         * Constructs a new service object.
         */
        ServiceConsumer(ServiceId id, InstId instId = InstIdDontCare, ServiceVersion version = {ServiceVersionDontCare, ServiceVersionDontCare}) :
            id(id), instId(instId), version(version), isRemote(false) {
            // empty on purpose
        }

    protected:
        /**
         * Constructs a new service object. Only useable from derived remote classes.
         */
        ServiceConsumer(ServiceId id, InstId instId, ServiceVersion version, bool isRemote) :
            id(id), instId(instId), version(version), isRemote(isRemote) {
            // empty on purpose
        }

    public:
        /**
         * Copy constructor.
         */
        ServiceConsumer(const ServiceConsumer& other) : 
            id(other.id), instId(other.instId), version(other.version), isRemote(other.isRemote) {
            // empty on purpose
        }

        /**
         * Move constructor.
         */
        ServiceConsumer(ServiceConsumer&& other) : 
            id(other.id), instId(other.instId), version(other.version), isRemote(other.isRemote) {
            // empty on purpose
        }

        /**
         * Default destructor.
         */
        virtual ~ServiceConsumer() {
            // empty on purpose
        }

    // Methods:
    public:
        /**
         * Copy assign.
         */
        ServiceConsumer& operator=(const ServiceConsumer& other) {
            id = other.id;
            instId = other.instId;
            version = other.version;
            isRemote = other.isRemote;
            return *this;
        }

        /**
         * Move assign.
         */
        ServiceConsumer& operator=(ServiceConsumer&& other) {
            id = other.id;
            instId = other.instId;
            version = other.version;
            isRemote = other.isRemote;
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
        bool TestServiceVersion(ServiceVersion other) const {
            if(other.major == ServiceVersionDontCare || version.major == other.major) {
                return (other.minor == ServiceVersionDontCare) || (version.minor == other.minor);
            } else {
                return false;
            }
        }

        /**
         * Returns true if the consumer is remote.
         */
        bool IsRemote() const {
            return isRemote;
        }

        virtual void HandleServiceStateChange(ServiceState state) = 0;

    // Statics:

    // Members:
    protected:
        ServiceId id;
        InstId instId;
        ServiceVersion version;
        bool isRemote;
    };


} // namespace ara::com
