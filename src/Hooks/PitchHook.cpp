#include "PitchHook.hpp"
#include "../Settings.hpp"
#include "../State.hpp"
#include <algorithm>

bool PitchHook::Prepare()
{
    std::array<uintptr_t, 2> address_array = {
        AsAddress(dku::Hook::Assembly::search_pattern<"E8 F5 BA FF FF F2 0F 10 00">()),
        AsAddress(dku::Hook::Assembly::search_pattern<"E8 35 BB FF FF">())
    };
    addresses = address_array;

    all_found = true;
    int i = 0;
    for (const auto& address : addresses)
    {
        if (!address)
        {
            State::GetSingleton()->mod_found_all_addresses = false;
            WARN("PitchHook #{} not found", i);
            all_found = false;
        }
        ++i;
    }
    return all_found;
}

void PitchHook::Enable()
{
    if (not all_found)
    {
        return;
    }
    int i = 0;
    for (const auto& address : addresses)
    {
        OriginalFunc = dku::Hook::write_call<5>(address, OverrideFunc);
        DEBUG("Hooked PitchHook #{}: {:X}", i, AsAddress(address));
        ++i;
    }
}

float* PitchHook::OverrideFunc(int64_t a1, float* a2, float a3)
{
    auto* state = State::GetSingleton();
    auto* settings = Settings::GetSingleton();

    float* ret = OriginalFunc(a1, a2, a3);

    if (*settings->unlock_pitch)
    {
        bool is_rotating = *(bool*)(a1 + 1113);
        if (is_rotating)
        {
            state->pitch += (float)state->dy * 0.0025f * *settings->pitch_speed;
            state->dy = 0;
            state->pitch = std::clamp(state->pitch, -0.85f, 0.85f);
        }
        ret[1] = state->pitch;
    }

    return ret;
}
