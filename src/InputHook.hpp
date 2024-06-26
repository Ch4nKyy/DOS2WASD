#pragma once

#include "Settings.hpp"
#include "State.hpp"
#include "VirtualKeyMap.hpp"

#include <string>

class InputHook
{
public:
    static void Enable(HMODULE a_hModule);

private:
    static inline const DWORD CURRENT_PROCESS_ID = GetCurrentProcessId();
    static inline DWORD last_input_vk;
    static inline int last_transition;
    static inline bool is_shift_down;
    static inline bool is_ctrl_down;
    static inline bool is_alt_down;

    static LRESULT CALLBACK KeyboardProc(int a_nCode, WPARAM a_wParam, LPARAM a_lParam);
    static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static bool DidCommandChange(Command command, int transition);
    static void HandleInput();
    static bool SetLastInputVkByMouseInput(WPARAM wParam, DWORD mouseData);
    static void StartHookAsOwnThread(HMODULE a_hModule);

    static void AutoRun(State* state);
    static void ToggleMovementMode(State* state);
    static void WalkOrSprint(State* state);
    static void ReloadConfig();
    static void MouseLeftDown();
    static void ToggleMouselook();
};
