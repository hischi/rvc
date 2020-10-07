#include <iostream>
#include "ara/core/result.h"
#include "ara/core/core_error_domain.h"
#include "pvis.h"
#include "bcp.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    PVisRenderingControl pvis;
    Bcp bcp;

    bcp.StartService();
    pvis.StartService();
    pvis.availability.Set({true, true, false, true, true});
    pvis.StopService();
    bcp.StopService();
}
