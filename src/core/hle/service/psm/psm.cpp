// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/psm/psm.h"

namespace Service::PSM {

class IPsmSession final : public ServiceFramework<IPsmSession> {
public:
    IPsmSession() : ServiceFramework("IPsmSession") {
        static const FunctionInfo functions[] = {
            {0, nullptr, "BindStateChangeEvent"},
            {1, nullptr, "UnbindStateChangeEvent"},
            {2, nullptr, "SetChargerTypeChangeEventEnabled"},
            {3, nullptr, "SetPowerSupplyChangeEventEnabled"},
            {4, nullptr, "SetBatteryVoltageStateChangeEventEnabled"},
        };
        RegisterHandlers(functions);
    }
};

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

PSM::PSM() : ServiceFramework("psm") {
    static const FunctionInfo functions[] = {
        {0, &PSM::GetBatteryChargePercentage, "GetBatteryChargePercentage"},
        {1, nullptr, "GetChargerType"},
        {2, nullptr, "EnableBatteryCharging"},
        {3, nullptr, "DisableBatteryCharging"},
        {4, nullptr, "IsBatteryChargingEnabled"},
        {5, nullptr, "AcquireControllerPowerSupply"},
        {6, nullptr, "ReleaseControllerPowerSupply"},
        {7, &PSM::OpenSession, "OpenSession"},
        {8, nullptr, "EnableEnoughPowerChargeEmulation"},
        {9, nullptr, "DisableEnoughPowerChargeEmulation"},
        {10, nullptr, "EnableFastBatteryCharging"},
        {11, nullptr, "DisableFastBatteryCharging"},
        {12, nullptr, "GetBatteryVoltageState"},
        {13, nullptr, "GetRawBatteryChargePercentage"},
        {14, nullptr, "IsEnoughPowerSupplied"},
        {15, nullptr, "GetBatteryAgePercentage"},
        {16, nullptr, "GetBatteryChargeInfoEvent"},
        {17, nullptr, "GetBatteryChargeInfoFields"},
    };
    RegisterHandlers(functions);
}

void InstallInterfaces(SM::ServiceManager& service_manager) {
    std::make_shared<PSM>()->InstallAsService(service_manager);
}

} // namespace Service::PSM
