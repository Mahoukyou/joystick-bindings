#pragma once

#include <vector>
#include "button_bindings.h"
#include "axis_bindings.h"



namespace prim_bindings
{
	class joystick final
	{
	public:
		enum { any_joystick = -1};

		explicit joystick(int id);
		~joystick() = default;

		void pool_joystick(bool self_update);

		std::vector<button_binding> button_bindings;
		std::vector<axis_binding> axis_bindings;

		int get_joystick_id() const { return id_; }

	private:
		int id_;
	};
}