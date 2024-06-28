#include "PitchHook.hpp"
#include "Addresses/SettingsPtr.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include <algorithm>

bool PitchHook::Prepare()
{
    std::array<uintptr_t, 1> address_array = { AsAddress(
        dku::Hook::Assembly::search_pattern<"E8 7A 26 00 00 F3 44 0F">()) };
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

int64_t PitchHook::OverrideFunc(int64_t a1, int64_t a2, int64_t a3)
{
    auto* state = State::GetSingleton();
    auto* settings = Settings::GetSingleton();

    if (*settings->unlock_pitch)
    {
        bool is_rotating = *(bool*)(a1 + 1113) & 1;
        if (is_rotating)
        {
            state->pitch += (float)state->dy * 0.0025f * *settings->pitch_speed *
                            *settings->mouse_rotation_speed;
            state->dy = 0;
            float min = *(settings->min_pitch);
            float max = *(settings->max_pitch);
            state->pitch = std::clamp(state->pitch, min, max);
            *(float*)(SettingsPtr::Read() + 0xCCC) = state->pitch;
            *(float*)(SettingsPtr::Read() + 0xCE4) = state->pitch;  // combat
            *(float*)(SettingsPtr::Read() + 0xCC0) = state->pitch;
            *(float*)(SettingsPtr::Read() + 0xCD8) = state->pitch;  // combat
        }
    }

    return OriginalFunc(a1, a2, a3);
}
