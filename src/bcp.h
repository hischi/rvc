#pragma once

#include "ara/com/service.h"
#include "ara/com/service_consumer.h"
#include "pvis.h"
#include <iostream>

using namespace ara::com;

class Bcp : public Service {

public:
    class PVisConsumer : public ServiceConsumer {
    public:
        PVisConsumer(Bcp* service) : ServiceConsumer(0x3054, 0x0001, {ServiceVersionDontCare, ServiceVersionDontCare}), service(service) { }

        void HandleServiceStateChange(ServiceState state) {
            if(state == ServiceState::Up) {
                service->pvisRef = (PVisRenderingControl*) ServiceRegistry::Get().GetService(this);
                if(service->pvisRef) {
                    service->pvisRef->availability.Subscribe(&service->availHandler);
                    service->pvisRef->currentView.Subscribe(&service->viewHandler);
                    service->pvisRef->transitionActive.Subscribe(&service->transHandler);
                }
            } else {
                if(service->pvisRef) {
                    service->pvisRef->availability.StopSubscribe(&service->availHandler);
                    service->pvisRef->currentView.StopSubscribe(&service->viewHandler);
                    service->pvisRef->transitionActive.StopSubscribe(&service->transHandler);
                }
                service->pvisRef = nullptr;
            }
        }

    private:
        Bcp* service;
    };

    class PVisAvailHandler : public NotifyHandler<PVisRenderingControl::Availability> {
    public:
        PVisAvailHandler(Bcp* service) : service(service) { }

        void HandleNotify(PVisRenderingControl::Availability& newValue) {
            std::cout << "PVis availability changed: " << newValue.rear << ", " << newValue.front << ", " << newValue.left << ", " << newValue.right << ", " << newValue.pvis << std::endl;
            if(newValue.pvis) {
                if(service->pvisRef) {
                    PVisRenderingControl::View view = {10, 1, 5};
                    bool success = service->pvisRef->requestPVis.Call(&view);
                    std::cout << "View change was successfull? " << success << std::endl;
                }
            }
        }
    private:
    Bcp* service;
    };

    class PVisViewHandler : public NotifyHandler<PVisRenderingControl::View> {
    public:
        PVisViewHandler(Bcp* service) : service(service) { }

        void HandleNotify(PVisRenderingControl::View& newValue) {
            std::cout << "PVis view changed: " << (int) newValue.app << ", " << (int) newValue.mode << ", " << (int) newValue.variant << std::endl;
        }
    private:
    Bcp* service;
    };

    class PVisTransHandler : public NotifyHandler<bool> {
    public:
        PVisTransHandler(Bcp* service) : service(service) { }

        void HandleNotify(bool& newValue) {
            std::cout << "Transition active? " << newValue << std::endl;
        }
    private:
    Bcp* service;
    };

public:
    Bcp() : Service(0x1000, 0x0001, {1,0}), pvisRef(nullptr), availHandler(this), viewHandler(this), transHandler(this), consumer(this) { }

    void OnStart() {
        ServiceRegistry::Get().Consume(&consumer);
    }

    void OnStop() {
        ServiceRegistry::Get().StopConsume(&consumer);
    }

public:
    PVisRenderingControl* pvisRef;
    PVisAvailHandler availHandler;
    PVisViewHandler viewHandler;
    PVisTransHandler transHandler;
    PVisConsumer consumer;
};
