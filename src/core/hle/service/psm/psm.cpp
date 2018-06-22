// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/psm/psm.h"

namespace Service::PSM {

PSM::PSM(std::shared_ptr<Module> module)
    : Module::Interface(std::move(module), "psm") {
    static const FunctionInfo functions[] = {
        {0, &PSM::CreateBcatService, "CreateBcatService"},
    };
    RegisterHandlers(functions);
}
} // namespace Service::PSM
