// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/ncm/ncm.h"

namespace Service::NCM {

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

NCM::NCM() : ServiceFramework("ncm") {
    static const FunctionInfo functions[] = {
        {6, nullptr, "TurnOnBacklight"},
        {7, nullptr, "TurnOffBacklight"},
        {8, nullptr, "GetBacklightStatus"},
        {16, nullptr, "ReadRawLightSensor"},
    };
    RegisterHandlers(functions);
}

void InstallInterfaces(SM::ServiceManager& service_manager) {
    std::make_shared<NCM>()->InstallAsService(service_manager);
}

} // namespace Service::NCM
