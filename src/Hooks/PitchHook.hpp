#pragma once

class PitchHook
{
public:
    static void Enable();
    static bool Prepare();

private:
    static float* OverrideFunc(int64_t a1, float* a2, float a3);
    static inline std::add_pointer_t<decltype(OverrideFunc)> OriginalFunc;
    static inline std::array<uintptr_t, 2> addresses;
    static inline bool all_found = false;
};
