// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::PSM {

class PSM final : public ServiceFramework<PSM> {
public:
    explicit PSM();
    ~PSM() = default;

private:
    void GetBatteryChargePercentage(Kernel::HLERequestContext& ctx);
    void OpenSession(Kernel::HLERequestContext& ctx);
};

/// Registers all PSM services with the specified service manager.
void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace Service::PSM
