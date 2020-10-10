#include "service_registry.h"
#include "service.h"
#include "service_consumer.h"
#include "service_interface.h"

using namespace ara::com;

ServiceInterface* ServiceRegistry::GetService(ServiceConsumer* consumer) {
    for(Service* service : services) {
        if(consumer->Id() != service->Id()) {
            continue;
        }
        
        if(!service->TestInstanceId(consumer->InstanceId())) {
            continue;
        }

        if(!service->TestServiceVersion(consumer->Version())) {
            continue;
        }

        return service->Interface();
    }
    return nullptr;
}

void ServiceRegistry::NotifyConsumers(Service* service) {
    for(ServiceConsumer* consumer : consumers) {
        if(consumer->Id() != service->Id()) {
            continue;
        }
        
        if(!service->TestInstanceId(consumer->InstanceId())) {
            continue;
        }

        if(!service->TestServiceVersion(consumer->Version())) {
            continue;
        }

        consumer->HandleServiceStateChange(service->State());
    }
}