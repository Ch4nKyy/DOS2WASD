#pragma once

using namespace DKUtil::Alias;

class CastOrCancelAbilityKeydown
{
public:
    static void Enable();
    static bool Prepare();
    static void Func(int64_t a1, int64_t a2, int64_t command_struct);

private:
    static inline std::array<uintptr_t, 1> addresses;
    static inline bool all_found = false;
    static inline std::unique_ptr<DKUtil::Hook::CaveHookHandle> handle;
};
