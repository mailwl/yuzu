// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::ES {

class ES final : public ServiceFramework<ES> {
public:
    explicit ES();
    ~ES() = default;

private:
    // void GetBatteryChargePercentage(Kernel::HLERequestContext& ctx);
    // void OpenSession(Kernel::HLERequestContext& ctx);
};

/// Registers all ES services with the specified service manager.
void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace Service::ES
