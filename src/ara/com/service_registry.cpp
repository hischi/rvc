#include "service_registry.h"
#include "service.h"
#include "service_consumer.h"

using namespace ara::com;

Service* ServiceRegistry::GetService(ServiceConsumer* consumer) {
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

        return service;
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