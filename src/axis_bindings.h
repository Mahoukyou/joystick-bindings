#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <map>


namespace prim_bindings
{
	class axis_binding
	{
		int axis_id;

		float dead_zone;

		void pool_joystick();
	};
}