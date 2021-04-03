typedef struct MouseState
{
	v2 position;
	v2 delta;
	bool leftbutton_down;
	bool leftbutton_was_down;
} MouseState;

MouseState mousestate;
typedef struct PadState
{
	bool buttons[10];
	v2 left_stick;
	v2 right_stick;
} PadState;

PadState game_pads[4];

enum Keys
{
	Keys_Backspace = 8,
	Keys_Tab = 9,
	Keys_Enter = 13,
	Keys_Escape = 27,
	Keys_Space = 32,
	Keys_Left = 37, Keys_Up, Keys_Right, Keys_Down,
	Keys_Delete = 46,
	Keys_A = 65, Keys_B, Keys_C, Keys_D, Keys_E, Keys_F, Keys_G, Keys_H, Keys_I, Keys_J, Keys_K, Keys_L, Keys_M, Keys_N, Keys_O, Keys_P, Keys_Q, Keys_R, Keys_S, Keys_T, Keys_U, Keys_V, Keys_W, Keys_X, Keys_Y, Keys_Z,
	Keys_Add = 107,
	Keys_Subtract = 109,
	Keys_NumPad0 = 96, Keys_NumPad1, Keys_NumPad2, Keys_NumPad3, Keys_NumPad4, Keys_NumPad5, Keys_NumPad6, Keys_NumPad7, Keys_NumPad8, Keys_NumPad9,
	Keys_F4 = 115,
	Keys_LCtrl = 162,
};

enum Buttons
{
	LEFT,
	RIGHT,
	DOWN,
	JUMP,
	PUNCH
};

bool keys_down[256];
bool keys_stale[256]; //whether a key has been pressed for more than one consecutive frame
bool keyboard_state[256];

enum Keys control_mappings[4][5] = //each row represents a player's control scheme
{
	{Keys_A,       Keys_D ,       Keys_S,		 Keys_W,	   Keys_Q },
	{Keys_J,       Keys_L,        Keys_K,        Keys_I,       Keys_U },
	{Keys_Left,    Keys_Right,    Keys_Down,     Keys_Up,      Keys_Delete },
	{Keys_NumPad4, Keys_NumPad6,  Keys_NumPad5,  Keys_NumPad8, Keys_NumPad7 }
};

bool KeyDownFresh(enum Keys key)
{
	return keys_down[key] && !keys_stale[key];
}

bool KeyDown(enum Keys key)
{
	return keys_down[key];
}

bool ButtonDown(int player, enum Buttons action)
{
	return KeyDown(control_mappings[player][action]);
}

bool ButtonDownFresh(int player, enum Buttons action)
{
	return KeyDownFresh(control_mappings[player][action]);
}

void PollKeyboard()
{
	for (int i = 0; i < 256; i++)
		keys_stale[i] = keys_down[i];

	GetKeyboardState(keyboard_state);

	for (int i = 0; i < 256; i++)
		keys_down[i] = keyboard_state[i] & 128;

	for (int i = 0; i < 256; i++)
	{
		if (!keys_down[i])
			keys_stale[i] = false;
	}
}