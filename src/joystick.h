#pragma once

#include <vector>
#include "button_bindings.h"
#include "axis_bindings.h"



namespace prim_bindings
{
	class joystick final
	{
		explicit joystick(int id);
		~joystick() = default;

		//void add_binding(/*binding*/);
		//void /*binding*/ find_binding(/*binding- keys?*/); // key combination
		//void remove_binding(/*binding*/); // key combination

		void pool_joystick(bool self_update);

		std::vector<button_binding> button_bindings;
		std::vector<axis_binding> axis_bindings;
	};
}