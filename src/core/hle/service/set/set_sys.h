// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::Set {

class SET_SYS final : public ServiceFramework<SET_SYS> {
public:
    explicit SET_SYS();
    ~SET_SYS() = default;

private:
    void GetColorSetId(Kernel::HLERequestContext& ctx);
    void GetEulaVersions(Kernel::HLERequestContext& ctx);
    void SetEulaVersions(Kernel::HLERequestContext& ctx);
};

} // namespace Service::Set
