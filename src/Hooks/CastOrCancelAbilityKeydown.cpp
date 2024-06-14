#include "CastOrCancelAbilityKeydown.hpp"
#include "../GameCommand.hpp"
#include "../InputFaker.hpp"
#include "../Patches/BlockCancelActionStoppingMovementPatch.hpp"
#include "../Settings.hpp"
#include "../State.hpp"

using enum GameCommand;

struct CastOrCancelAbilityKeydownProlog : Xbyak::CodeGenerator
{
    CastOrCancelAbilityKeydownProlog()
    {
        mov(word[rax], 0);
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

struct CastOrCancelAbilityKeydownEpilog : Xbyak::CodeGenerator
{
    CastOrCancelAbilityKeydownEpilog()
    {
        pop(r11);
        pop(r10);
        pop(r9);
        pop(r8);
        pop(rdx);
        pop(rcx);
        pop(rbx);
        pop(rax);
    }
};

bool CastOrCancelAbilityKeydown::Prepare()
{
    std::array<uintptr_t, 1> address_array = { AsAddress(
        dku::Hook::Assembly::search_pattern<"49 8B D6 FF 50 58 E9">()) };
    addresses = address_array;

    all_found = true;
    int i = 0;
    for (const auto& address : addresses)
    {
        if (!address)
        {
            State::GetSingleton()->mod_found_all_addresses = false;
            WARN("CastOrCancelAbilityKeydown #{} not found", i);
            all_found = false;
        }
        ++i;
    }
    return all_found;
}

void CastOrCancelAbilityKeydown::Enable()
{
    if (not all_found)
    {
        return;
    }
    int i = 0;
    for (const auto& address : addresses)
    {
        CastOrCancelAbilityKeydownProlog prolog;
        prolog.ready();
        CastOrCancelAbilityKeydownEpilog epilog;
        epilog.ready();
        handle = DKUtil::Hook::AddCaveHook(address, { 0, 6 }, FUNC_INFO(Func), &prolog, &epilog,
            DKUtil::Hook::HookFlag::kRestoreBeforeProlog);
        handle->Enable();
        DEBUG("Hooked CastOrCancelAbilityKeydown #{}: {:X}", i, AsAddress(address));
        ++i;
    }
}

// TODO sometimes command_struct is the correct pointer and it works brilliantly, sometimes it is a
// small int or a huge int and it crashes.
void CastOrCancelAbilityKeydown::Func(int64_t a1, int64_t a2, int64_t command_struct)
{
    auto* state = State::GetSingleton();

    if (*Settings::GetSingleton()->enable_improved_mouselook)
    {
        int command_id = *(int*)command_struct;
        bool is_key_down = *(reinterpret_cast<bool*>(command_struct) + 32);

        if (command_id == ActionCancel && is_key_down)
        {
            state->last_time_cancel_action_pressed2 = SDL_GetTicks();
        }
    }
}
