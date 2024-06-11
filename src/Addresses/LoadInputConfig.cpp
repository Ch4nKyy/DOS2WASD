#include "LoadInputConfig.hpp"
#include "../State.hpp"

bool LoadInputConfig::Prepare()
{
    uintptr_t address = AsAddress(dku::Hook::Assembly::search_pattern<
        "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 4C 89 74 24 20 55 48 8B EC 48 83 EC 70 48 8B "
        "05 5D 28 1F 01">());

    if (!address)
    {
        State::GetSingleton()->mod_found_all_addresses = false;
        WARN("LoadInputConfig not found.");
        return false;
    }

    Func = reinterpret_cast<tLoadInputConfig>(address);
    DEBUG("LoadInputConfig found: {:X}", AsAddress(Func))
    return true;
}

bool LoadInputConfig::IsValid() { return Func != nullptr; }

int64_t LoadInputConfig::Call(int64_t a1, char a2)
{
    if (!IsValid())
    {
        return 0;
    }

    return Func(a1, a2);
}
