// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/time/time_a.h"

namespace Service::Time {

TIME_A::TIME_A(std::shared_ptr<Module> time) : Module::Interface(std::move(time), "time:a") {
    static const FunctionInfo functions[] = {
        {0, &TIME_A::GetStandardUserSystemClock, "GetStandardUserSystemClock"},
        {1, &TIME_A::GetStandardNetworkSystemClock, "GetStandardNetworkSystemClock"},
        {2, &TIME_A::GetStandardSteadyClock, "GetStandardSteadyClock"},
        {3, &TIME_A::GetTimeZoneService, "GetTimeZoneService"},
        {4, &TIME_A::GetStandardLocalSystemClock, "GetStandardLocalSystemClock"},
        {5, nullptr, "GetEphemeralNetworkSystemClock"},
        {50, nullptr, "SetStandardSteadyClockInternalOffset"},
        {100, nullptr, "IsStandardUserSystemClockAutomaticCorrectionEnabled"},
        {101, nullptr, "SetStandardUserSystemClockAutomaticCorrectionEnabled"},
        {102, nullptr, "GetStandardUserSystemClockInitialYear"},
        {200, nullptr, "IsStandardNetworkSystemClockAccuracySufficient"},
        {300, nullptr, "CalculateMonotonicSystemClockBaseTimePoint"},
        {400, nullptr, "GetClockSnapshot"},
        {401, nullptr, "GetClockSnapshotFromSystemClockContext"},
        {500, nullptr, "CalculateStandardUserSystemClockDifferenceByUser"},
        {501, nullptr, "CalculateSpanBetween"},
    };
    RegisterHandlers(functions);
}

} // namespace Service::Time
