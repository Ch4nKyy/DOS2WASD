#pragma once

typedef int64_t QWORD;

class AfterInitialLoadInputConfigHook
{
public:
    static void Enable();
    static bool Prepare();
    static int64_t CallOriginal(QWORD* a1);
    static bool IsValid();

private:
    static int64_t Hook(QWORD* a1);
    static inline std::add_pointer_t<decltype(Hook)> OriginalFunc = nullptr;
    static inline std::array<uintptr_t, 1> addresses;
    static inline bool all_found = false;
};
