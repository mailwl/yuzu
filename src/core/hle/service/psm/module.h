// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "core/hle/service/service.h"

namespace Service::PSM {

class Module final {
public:
    class Interface : public ServiceFramework<Interface> {
    public:
        Interface(std::shared_ptr<Module> module, const char* name);

        void CreateBcatService(Kernel::HLERequestContext& ctx);

    protected:
        std::shared_ptr<Module> module;
    };
};

/// Registers all PSM services with the specified service manager.
void InstallInterfaces(SM::ServiceManager& service_manager);

} // namespace Service::PSM
