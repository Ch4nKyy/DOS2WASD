#include "AfterChangingKeybindInMenuHook.hpp"
#include "State.hpp"
#include "InputconfigPatcher.hpp"

bool AfterChangingKeybindInMenuHook::Prepare()
{
    std::array<uintptr_t, 2> address_array = {
        AsAddress(dku::Hook::Assembly::search_pattern<"E8 48 F5 FF FF E9 F3">()),
        AsAddress(dku::Hook::Assembly::search_pattern<"E8 27 F5 FF FF 48 B9">())
    };
    addresses = address_array;

    all_found = true;
    int i = 0;
    for (const auto& address : addresses)
    {
        if (!address)
        {
            State::GetSingleton()->mod_found_all_addresses = false;
            WARN("AfterChangingKeybindInMenuHook #{} not found", i);
            all_found = false;
        }
        ++i;
    }
    return all_found;
}

void AfterChangingKeybindInMenuHook::Enable()
{
    if (not all_found)
    {
        return;
    }
    int i = 0;
    for (const auto& address : addresses)
    {
        OriginalFunc = dku::Hook::write_call<5>(address, Hook);
        DEBUG("Hooked AfterChangingKeybindInMenuHook #{}: {:X}", i, AsAddress(address));
        ++i;
    }
}

bool AfterChangingKeybindInMenuHook::IsValid() { return OriginalFunc != nullptr; }

int64_t AfterChangingKeybindInMenuHook::Hook(int64_t a1)
{
    auto ret = CallOriginal(a1);

    InputconfigPatcher::Patch();

    return ret;
}

int64_t AfterChangingKeybindInMenuHook::CallOriginal(int64_t a1) { return OriginalFunc(a1); }
