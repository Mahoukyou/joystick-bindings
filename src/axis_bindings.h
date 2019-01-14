#pragma once

namespace prim_bindings
{
	class axis_binding
	{
	public:
		void pool_joystick(int joystick_id);

		// todo, public(pod like) or setter and getter?
		int axis_id;
		float dead_zone;
	};
}