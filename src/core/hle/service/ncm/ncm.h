// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::NCM {

class NCM final : public ServiceFramework<NCM> {
public:
    explicit NCM();
    ~NCM() = default;

private:
    // void GetBatteryChargePercentage(Kernel::HLERequestContext& ctx);
    // void OpenSession(Kernel::HLERequestContext& ctx);
};

/// Registers all NCM services with the specified service manager.
void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace Service::NCM
