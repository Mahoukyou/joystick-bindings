#pragma once


// some helper functions that can be used to bind controller to keyboard and mouse
namespace prim_bindings
{
	void move_cursor_x(int delta_value);
	void move_cursor_y(int delta_value);
	void mouse_cursor(int delta_x, int delta_y);

	void press_key(unsigned char key);
	void release_key(unsigned char key);
}