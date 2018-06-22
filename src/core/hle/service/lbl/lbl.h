// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::LBL {

class LBL final : public ServiceFramework<LBL> {
public:
    explicit LBL();
    ~LBL() = default;

private:
    void GetBatteryChargePercentage(Kernel::HLERequestContext& ctx);
    void OpenSession(Kernel::HLERequestContext& ctx);
};

/// Registers all LBL services with the specified service manager.
void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace Service::LBL
