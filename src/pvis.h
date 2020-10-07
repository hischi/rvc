#pragma once

#include "ara/com/service.h"

using namespace ara::com;

class PVisRenderingControl : public Service {

public:
    struct Availability {
        bool rear, front, left, right;
        bool pvis;

        bool operator!=(Availability& other) {
            return (rear != other.rear) || (front != other.front) || (left != other.left) || (right != other.right) || (pvis != other.pvis);
        }
    };

    struct View {
        uint8_t app, mode;
        uint16_t variant;

        bool operator!=(View& other) {
            return (app != other.app) || (mode != other.mode) || (variant != other.variant);
        }
    };

    class RequestPVis : public Method<const View*, bool> {
    public:
        RequestPVis(PVisRenderingControl* service) : Method<const View*, bool>(), service(service) { }

        void Call(const View* argument, ResponseHandler<bool>* handler);

        bool Call(const View* argument);
    
    private:
        PVisRenderingControl* service;
    };

public:
    PVisRenderingControl() : Service(0x3054, 0x0001, {1,0}), requestPVis(RequestPVis(this)) {
        // empty
    }

    bool ChangeView(const View* newView) {
        if(newView->app < 5) {
            transitionActive.Trigger(true);
            currentView.Set(*newView);
            transitionActive.Trigger(false);
            return true;
        }
        return false;
    }

public:
    Field<Availability> availability;
    Field<View> currentView;
    Event<bool> transitionActive;
    RequestPVis requestPVis;
};