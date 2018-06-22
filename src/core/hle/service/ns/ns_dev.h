// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::NS {

class NS_DEV final : public ServiceFramework<NS_DEV> {
public:
    explicit NS_DEV();
    ~NS_DEV() = default;

private:
    // void GetBatteryChargePercentage(Kernel::HLERequestContext& ctx);
    // void OpenSession(Kernel::HLERequestContext& ctx);
};

} // namespace Service::NS
