// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <vector>
#include "common/logging/log.h"
#include "core/core_timing.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/kernel/event.h"
#include "core/hle/kernel/hle_ipc.h"
#include "core/hle/service/audio/audout_u.h"

namespace Service::Audio {

/// Switch sample rate frequency
constexpr u32 sample_rate{48000};
/// TODO(st4rk): dynamic number of channels, as I think Switch has support
/// to more audio channels (probably when Docked I guess)
constexpr u32 audio_channels{2};
/// TODO(st4rk): find a proper value for the audio_ticks
constexpr u64 audio_ticks{static_cast<u64>(CoreTiming::BASE_CLOCK_RATE / 500)};
const std::string audio_interface = "AudioInterface";

class IAudioOut final : public ServiceFramework<IAudioOut> {
public:
    IAudioOut() : ServiceFramework("IAudioOut"), audio_out_state(AudioState::Stopped) {
        static const FunctionInfo functions[] = {
            {0, &IAudioOut::GetAudioOutState, "GetAudioOutState"},
            {1, &IAudioOut::StartAudioOut, "StartAudioOut"},
            {2, &IAudioOut::StopAudioOut, "StopAudioOut"},
            {3, &IAudioOut::AppendAudioOutBuffer, "AppendAudioOutBuffer"},
            {4, &IAudioOut::RegisterBufferEvent, "RegisterBufferEvent"},
            {5, &IAudioOut::GetReleasedAudioOutBuffer, "GetReleasedAudioOutBuffer"},
            {6, nullptr, "ContainsAudioOutBuffer"},
            {7, &IAudioOut::AppendAudioOutBuffer, "AppendAudioOutBufferAuto"},
            {8, &IAudioOut::GetReleasedAudioOutBuffer, "GetReleasedAudioOutBufferAuto"},
            {9, nullptr, "GetAudioOutBufferCount"},
            {10, nullptr, "GetAudioOutPlayedSampleCount"},
            {11, nullptr, "FlushAudioOutBuffers"},
        };
        RegisterHandlers(functions);

        // This is the event handle used to check if the audio buffer was released
        buffer_event =
            Kernel::Event::Create(Kernel::ResetType::OneShot, "IAudioOutBufferReleasedEvent");

        // Register event callback to update the Audio Buffer
        audio_event = CoreTiming::RegisterEvent(
            "IAudioOut::UpdateAudioBuffersCallback", [this](u64 userdata, int cycles_late) {
                UpdateAudioBuffersCallback(userdata, cycles_late);
            });
    }

    ~IAudioOut() {
        CoreTiming::UnscheduleEvent(audio_event, 0);
    }

private:
    void GetAudioOutState(Kernel::HLERequestContext& ctx) {
        NGLOG_DEBUG(Service_Audio, "called");
        IPC::ResponseBuilder rb{ctx, 3};
        rb.Push(RESULT_SUCCESS);
        rb.Push(static_cast<u32>(audio_out_state));
    }

    void StartAudioOut(Kernel::HLERequestContext& ctx) {
        NGLOG_WARNING(Service_Audio, "(STUBBED) called");

        // Start audio
        audio_out_state = AudioState::Started;

        Reschedule();

        IPC::ResponseBuilder rb{ctx, 2};
        rb.Push(RESULT_SUCCESS);
    }

    void StopAudioOut(Kernel::HLERequestContext& ctx) {
        NGLOG_WARNING(Service_Audio, "(STUBBED) called");

        // Stop audio
        audio_out_state = AudioState::Stopped;

        acquired_queue_keys.clear();
        released_queue_keys.clear();

        CoreTiming::UnscheduleEvent(audio_event, 0);

        IPC::ResponseBuilder rb{ctx, 2};
        rb.Push(RESULT_SUCCESS);
    }

    void RegisterBufferEvent(Kernel::HLERequestContext& ctx) {
        NGLOG_WARNING(Service_Audio, "(STUBBED) called");

        IPC::ResponseBuilder rb{ctx, 2, 1};
        rb.Push(RESULT_SUCCESS);
        rb.PushCopyObjects(buffer_event);
    }

    void AppendAudioOutBuffer(Kernel::HLERequestContext& ctx) {
        IPC::RequestParser rp{ctx};

        const VAddr buffer_address{rp.Pop<VAddr>()};

        acquired_queue_keys.insert(acquired_queue_keys.begin(), buffer_address);

        NGLOG_WARNING(Service_Audio, "(STUBBED) called");

        if (!buffer_event->signaled)
            Reschedule();

        IPC::ResponseBuilder rb{ctx, 2};
        rb.Push(RESULT_SUCCESS);
    }

    void GetReleasedAudioOutBuffer(Kernel::HLERequestContext& ctx) {
        // TODO(st4rk): This is how libtransistor currently implements the
        // GetReleasedAudioOutBuffer, it should return the key (a VAddr) to the app and this address
        // is used to know which buffer should be filled with data and send again to the service
        // through AppendAudioOutBuffer. Check if this is the proper way to do it.
        u64 key{0};

        if (!released_queue_keys.empty()) {
            key = released_queue_keys.back();
            released_queue_keys.pop_back();
        }

        ctx.WriteBuffer(&key, sizeof(u64));

        IPC::ResponseBuilder rb{ctx, 3};
        rb.Push(RESULT_SUCCESS);
        // TODO(st4rk): This might be the total of released buffers, needs to be verified on
        // hardware
        rb.Push<u32>(static_cast<u32>(released_queue_keys.size()));

        NGLOG_WARNING(Service_Audio, "(STUBBED) called, 0x{:X}", key);
    }

    void UpdateAudioBuffersCallback(u64 userdata, int cycles_late) {
        if (audio_out_state != AudioState::Started) {
            return;
        }

        if (acquired_queue_keys.empty()) {
            return;
        }

        u64 key = acquired_queue_keys.back();
        acquired_queue_keys.pop_back();

        released_queue_keys.insert(released_queue_keys.begin(), key);

        buffer_event->Signal();

        Reschedule();
    }

    void Reschedule() {
        // NGLOG_ERROR(Service_Audio, "Reschedule start, {}", acquired_queue_keys.size());
        if (!acquired_queue_keys.empty()) {
            AudioOutBuffer buffer{};
            VAddr buffer_address = acquired_queue_keys.back();
            Memory::ReadBlock(buffer_address, &buffer, sizeof(AudioOutBuffer));

            // TODO: 2 -> sample size
            s64 duration = 1000000 * (buffer.size / (2 * audio_channels)) / (sample_rate / 1000);

            // Start the audio event
            CoreTiming::ScheduleEvent(audio_ticks, audio_event);
            NGLOG_ERROR(Service_Audio, "Reschedule, {}, {}", duration / 10, audio_ticks);
        }
    }

    enum class AudioState : u32 {
        Started,
        Stopped,
    };

    struct AudioOutBuffer {
        AudioOutBuffer* next;
        void* buffer;
        size_t buffer_size;
        size_t size;
    };

    /// This is used to trigger the audio event callback that is going to read the samples from the
    /// audio_buffer list and enqueue the samples using the sink (audio_core).
    CoreTiming::EventType* audio_event;

    /// This is the evend handle used to check if the audio buffer was released
    Kernel::SharedPtr<Kernel::Event> buffer_event;

    /// (st4rk): This is just a temporary workaround for the future implementation. Libtransistor
    /// uses the key as an address in the App, so we need to return when the
    /// GetReleasedAudioOutBuffer_1 is called, otherwise we'll run in problems, because
    /// libtransistor uses the key returned as an pointer.
    std::vector<u64> acquired_queue_keys;
    std::vector<u64> released_queue_keys;

    AudioState audio_out_state;
};

void AudOutU::ListAudioOuts(Kernel::HLERequestContext& ctx) {
    NGLOG_WARNING(Service_Audio, "(STUBBED) called");

    ctx.WriteBuffer(audio_interface.c_str(), audio_interface.size());

    IPC::ResponseBuilder rb{ctx, 3};

    rb.Push(RESULT_SUCCESS);
    // TODO(st4rk): We're currently returning only one audio interface (stringlist size). However,
    // it's highly possible to have more than one interface (despite that libtransistor requires
    // only one).
    rb.Push<u32>(1);
}

void AudOutU::OpenAudioOut(Kernel::HLERequestContext& ctx) {
    NGLOG_WARNING(Service_Audio, "(STUBBED) called");

    if (!audio_out_interface) {
        audio_out_interface = std::make_shared<IAudioOut>();
    }
    ctx.WriteBuffer(audio_interface.c_str(), audio_interface.size());

    IPC::ResponseBuilder rb{ctx, 6, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.Push<u32>(sample_rate);
    rb.Push<u32>(audio_channels);
    rb.Push<u32>(static_cast<u32>(PcmFormat::Int16));
    rb.Push<u32>(0); // This field is unknown
    rb.PushIpcInterface<Audio::IAudioOut>(audio_out_interface);
}

AudOutU::AudOutU() : ServiceFramework("audout:u") {
    static const FunctionInfo functions[] = {{0, &AudOutU::ListAudioOuts, "ListAudioOuts"},
                                             {1, &AudOutU::OpenAudioOut, "OpenAudioOut"},
                                             {2, &AudOutU::ListAudioOuts, "ListAudioOutsAuto"},
                                             {3, &AudOutU::OpenAudioOut, "OpenAudioOutAuto"}};
    RegisterHandlers(functions);
}

} // namespace Service::Audio
