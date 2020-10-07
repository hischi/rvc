#pragma once

#include "service_consumer.h"

namespace ara::com
{
    class RemoteServiceConsumer : public ServiceConsumer {
    // Type defintions:

    // Constructors:
    public:
        RemoteServiceConsumer(ServiceId id, InstId instId = InstIdDontCare, ServiceVersion version = {ServiceVersionDontCare, ServiceVersionDontCare}) : 
            ServiceConsumer(id, instId, version, true) {
            // empty on purpose
        }

    // Methods:

    // Statics:

    // Members:

    };
} // namespace ara::com
