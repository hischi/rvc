#include "pvis.h"

using namespace ara::com;

void PVisRenderingControl::RequestPVis::Call(const View* argument, ResponseHandler<bool>* handler) {
    bool success = service->ChangeView(argument);
    handler->HandleResponse(success);
}

bool PVisRenderingControl::RequestPVis::Call(const View* argument) {
    return service->ChangeView(argument);
}