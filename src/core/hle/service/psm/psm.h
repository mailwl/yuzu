// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/psm/module.h"

namespace Service::PSM {

class PSM final : public Module::Interface {
public:
    explicit PSM(std::shared_ptr<Module> module);
};

} // namespace Service::PSM
