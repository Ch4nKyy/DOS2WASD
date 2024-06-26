#pragma once

class ASMPatchHandle;

struct CenterCameraAlwaysJumpsAsm : Xbyak::CodeGenerator
{
    CenterCameraAlwaysJumpsAsm()
    {
        test(rsp, rsp);
        nop();
        nop();
        nop();
        nop();
    }
};

// When changing Analog Stick Selection in the menu, ignore it.
class CenterCameraAlwaysJumps
{
public:
    static bool Prepare();
    static void Activate();
    static void Deactivate();
    static void Enable();

private:
    static inline std::array<uintptr_t, 1> addresses;
    static inline bool all_found = false;
    static inline std::unique_ptr<DKUtil::Hook::ASMPatchHandle,
        std::default_delete<DKUtil::Hook::ASMPatchHandle>>
        handle;
};
