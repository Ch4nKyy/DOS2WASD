#pragma once

#include "DKUtil/Config.hpp"

using namespace DKUtil::Alias;

class Settings : public DKUtil::model::Singleton<Settings>
{
public:
    String toggle_walkspeed{ "ToggleWalkspeed", "ModHotkeys" };
    String toggle_movement_mode{ "ToggleMovementMode", "ModHotkeys" };
    String hold_movement_mode{ "HoldMovementMode", "ModHotkeys" };
    String toggle_autoforward{ "ToggleAutoforward", "ModHotkeys" };
    String hold_walkspeed{ "HoldWalkspeed", "ModHotkeys" };
    String reload_config{ "ReloadConfig", "ModHotkeys" };
    // TODO ToggleMouselook
    // String toggle_mouselook{ "ToggleMouselook", "ModHotkeys" };

    Double walk_speed{ "WalkSpeed", "Core" };
    Boolean walking_is_default{ "WalkingIsDefault", "Core" };
    Boolean walk_after_combat{ "SwitchToWalkingAfterCombat", "Core" };
    // TODO character_leftright_is_rotate
    // Boolean character_leftright_is_rotate{ "CharacterLeftRightIsRotateInsteadOfMove", "Core" };

    Boolean enable_auto_toggling_movement_mode{ "EnableAutoTogglingMovementMode",
        "AutoToggleMovementMode" };

    Boolean enable_improved_mouselook{ "EnableMouselook", "Mouselook" };
    Boolean enable_rotate_plus_lmb_is_forward{ "EnableRotatePlusLeftclickMovesForward",
        "Mouselook" };
    // TODO ToggleMouselook
    // Boolean toggle_movement_toggles_mouselook{ "ToggleMovementModeAlsoTogglesMouselook",
    //     "Mouselook" };
    Integer rotate_threshold{ "RotateThreshold", "Mouselook" };

    Boolean block_interact_move{ "BlockInteractMove", "InteractMoveBlocker" };

    Double mouse_rotation_speed{ "MouseRotationSpeed", "Camera" };
    Double hotkey_rotation_speed{ "HotkeyRotationSpeed", "Camera" };
    Boolean unlock_pitch{ "UnlockPitch", "Camera" };
    Double pitch_speed{ "PitchSpeed", "Camera" };
    Double vertical_offset{ "VerticalOffset", "Camera" };
    Double min_zoom{ "MinZoom", "Camera" };
    Double max_zoom{ "MaxZoom", "Camera" };
    Double zoom_speed{ "ZoomSpeed", "Camera" };
    Double camera_movespeed{ "CameraMovespeed", "Camera" };
    Double fov{ "FieldOfView", "Camera" };
    Double min_pitch{ "MinPitch", "Camera" };
    Double max_pitch{ "MaxPitch", "Camera" };
    Boolean improve_sky{ "ImproveSky", "Camera" };

    void Load() noexcept;
    std::vector<std::string> GetBoundKeycombos(std::string setting);

private:
    TomlConfig config = COMPILE_PROXY("NativeMods/DOS2WASD.toml"sv);
    bool first_time_loaded = true;

    void InitState();
};
