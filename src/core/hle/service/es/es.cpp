// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/es/es.h"

namespace Service::ES {

/*
void PSM::GetBatteryChargePercentage(Kernel::HLERequestContext& ctx) {
    IPC::ResponseBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(99);
    NGLOG_DEBUG(Service_PSM, "called");
}

void PSM::OpenSession(Kernel::HLERequestContext& ctx) {
    IPC::ResponseBuilder rb{ctx, 2, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.PushIpcInterface<IPsmSession>();
    NGLOG_DEBUG(Service_PSM, "called");
}
*/

ES::ES() : ServiceFramework("es") {
    static const FunctionInfo functions[] = {
        {0, nullptr, "UNKNOWN"},
    };
    RegisterHandlers(functions);
}

void InstallInterfaces(SM::ServiceManager& service_manager) {
    std::make_shared<ES>()->InstallAsService(service_manager);
}

} // namespace Service::ES
