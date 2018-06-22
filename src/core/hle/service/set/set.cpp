// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <chrono>
#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/kernel/client_port.h"
#include "core/hle/kernel/client_session.h"
#include "core/hle/service/set/set.h"

namespace Service::Set {

void SET::GetAvailableLanguageCodes(Kernel::HLERequestContext& ctx) {
    static constexpr std::array<LanguageCode, 17> available_language_codes = {{
        LanguageCode::JA,
        LanguageCode::EN_US,
        LanguageCode::FR,
        LanguageCode::DE,
        LanguageCode::IT,
        LanguageCode::ES,
        LanguageCode::ZH_CN,
        LanguageCode::KO,
        LanguageCode::NL,
        LanguageCode::PT,
        LanguageCode::RU,
        LanguageCode::ZH_TW,
        LanguageCode::EN_GB,
        LanguageCode::FR_CA,
        LanguageCode::ES_419,
        LanguageCode::ZH_HANS,
        LanguageCode::ZH_HANT,
    }};
    ctx.WriteBuffer(available_language_codes.data(), available_language_codes.size());

    IPC::ResponseBuilder rb{ctx, 4};
    rb.Push(RESULT_SUCCESS);
    rb.Push(static_cast<u64>(available_language_codes.size()));

    NGLOG_DEBUG(Service_SET, "called");
}

void SET::GetRegionCode(Kernel::HLERequestContext& ctx) {
    IPC::ResponseBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(1);

    NGLOG_WARNING(Service_SET, "called");
}

SET::SET() : ServiceFramework("set") {
    static const FunctionInfo functions[] = {
        {0, nullptr, "GetLanguageCode"},
        {1, &SET::GetAvailableLanguageCodes, "GetAvailableLanguageCodes"},
        {2, nullptr, "MakeLanguageCode"},
        {3, nullptr, "GetAvailableLanguageCodeCount"},
        {4, &SET::GetRegionCode, "GetRegionCode"},
        {5, &SET::GetAvailableLanguageCodes, "GetAvailableLanguageCodes2"},
        {6, nullptr, "GetAvailableLanguageCodeCount2"},
        {7, nullptr, "GetKeyCodeMap"},
        {8, nullptr, "GetQuestFlag"},
    };
    RegisterHandlers(functions);
}

} // namespace Service::Set
