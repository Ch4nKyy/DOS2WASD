#pragma once

typedef int64_t QWORD;

class ConcatInputconfigPathHook
{
public:
    static void Enable();
    static bool Prepare();

private:
    static QWORD* OverrideFunc(QWORD* Src, char* a2, size_t Size);
    static inline std::add_pointer_t<decltype(OverrideFunc)> OriginalFunc;
    static inline std::array<uintptr_t, 1> addresses;
    static inline bool all_found = false;
};
