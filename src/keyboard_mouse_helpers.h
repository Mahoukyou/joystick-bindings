#pragma once

// some helper functions that can be used to bind controller to keyboard and mouse
namespace prim_bindings
{

	void move_cursor_x(int delta_value);
	void move_cursor_y(int delta_value);
	void mouse_cursor(int delta_x, int delta_y);

#ifdef _WINDOWS
	enum class mouse_button { left, right, middle };

	void press_key(unsigned char key);
	void release_key(unsigned char key);

	void press_mouse_button(mouse_button button);
	void release_mouse_button(mouse_button button);
	void send_mouse_button(mouse_button button, bool press);
#else
	//button presses are only available on windows atm
#endif
}