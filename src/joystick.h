#pragma once

#include <vector>
#include "button_bindings.h"
#include "axis_bindings.h"
#include "SFML/Window/Joystick.hpp"



namespace prim_bindings
{
	class joystick final
	{
	public:
		enum { any_joystick = -1};

		explicit joystick(int id);
		~joystick() = default;

		void pool_joystick(bool self_update, double delta_time);

		bool add_button_binding(const button_binding& binding);
		bool add_axis_binding(const axis_binding& binding);
		void remove_button_binding(unsigned int button_id);
		void remove_axis_binding(sf::Joystick::Axis axis);
		bool has_button_binding(unsigned int button_id) const;
		bool has_axis_binding(sf::Joystick::Axis axis) const;



		int get_joystick_id() const { return id_; }

	private:
		std::vector<button_binding> button_bindings_;
		std::vector<axis_binding> axis_bindings_;

		int id_;
	};
}