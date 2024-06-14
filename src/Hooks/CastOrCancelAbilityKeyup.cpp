#include "CastOrCancelAbilityKeyup.hpp"
#include "../GameCommand.hpp"
#include "../InputFaker.hpp"
#include "../Patches/BlockCancelActionStoppingMovementPatch.hpp"
#include "../Settings.hpp"
#include "../State.hpp"

using enum GameCommand;

struct CastOrCancelAbilityKeyupProlog : Xbyak::CodeGenerator
{
    CastOrCancelAbilityKeyupProlog()
    {
        push(rax);
        push(rbx);
        push(rcx);
        push(rdx);
        push(r8);
        push(r9);
        push(r10);
        push(r11);
    }
};

struct CastOrCancelAbilityKeyupEpilog : Xbyak::CodeGenerator
{
    CastOrCancelAbilityKeyupEpilog()
    {
        test(rax, rax);
        pop(r11);
        pop(r10);
        pop(r9);
        pop(r8);
        pop(rdx);
        pop(rcx);
        pop(rbx);
        pop(rax);
        mov(rcx, qword[rcx]);
    }
};

bool CastOrCancelAbilityKeyup::Prepare()
{
    std::array<uintptr_t, 1> address_array = { AsAddress(
        dku::Hook::Assembly::search_pattern<"48 8B 09 48 85 C9 74 1D E8 B3">()) };
    addresses = address_array;

    all_found = true;
    int i = 0;
    for (const auto& address : addresses)
    {
        if (!address)
        {
            State::GetSingleton()->mod_found_all_addresses = false;
            WARN("CastOrCancelAbilityKeyup #{} not found", i);
            all_found = false;
        }
        ++i;
    }
    return all_found;
}

void CastOrCancelAbilityKeyup::Enable()
{
    if (not all_found)
    {
        return;
    }
    int i = 0;
    for (const auto& address : addresses)
    {
        CastOrCancelAbilityKeyupProlog prolog;
        prolog.ready();
        CastOrCancelAbilityKeyupEpilog epilog;
        epilog.ready();
        handle = DKUtil::Hook::AddCaveHook(address, { 0, 6 }, FUNC_INFO(Func), &prolog, &epilog,
            DKUtil::Hook::HookFlag::kSkipNOP);
        handle->Enable();
        DEBUG("Hooked CastOrCancelAbilityKeyup #{}: {:X}", i, AsAddress(address));
        ++i;
    }
}

int64_t CastOrCancelAbilityKeyup::Func()
{
    auto* state = State::GetSingleton();

    if (*Settings::GetSingleton()->enable_improved_mouselook)
    {
        uint32_t time_now = SDL_GetTicks();
        uint32_t time_diff_millis = time_now - state->last_time_cancel_action_pressed2;
        if (time_diff_millis > *Settings::GetSingleton()->rotate_threshold)
        {
            return false;  // block cancel
        }
        return true;  // allow cancel
    }
}
