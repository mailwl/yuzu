// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/time/time.h"

namespace Service::Time {

class TIME_A final : public Module::Interface {
public:
    explicit TIME_A(std::shared_ptr<Module> time);
};

} // namespace Service::Time
