#pragma once

using namespace DKUtil::Alias;

class CastOrCancelAbilityKeyup
{
public:
    static void Enable();
    static bool Prepare();
    static int64_t Func();

private:
    static inline std::array<uintptr_t, 1> addresses;
    static inline bool all_found = false;
    static inline std::unique_ptr<DKUtil::Hook::CaveHookHandle> handle;
};
