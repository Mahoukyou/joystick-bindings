#pragma once

#include "SFML/Window/Joystick.hpp"
#include <functional>

namespace prim_bindings
{
	class axis_binding
	{
	public:
		explicit axis_binding(sf::Joystick::Axis axis, float dead_zone);

		void pool_joystick(int joystick_id);

		/* Called every pool if axis is active (outside dead_zone) */
		std::function<void(float, float)> on_active;

		/* Called every pool if axis is active (inside dead_zone) */
		std::function<void()> on_inactive;

		/* Called the value changes and it is outside the dead_zone */
		std::function<void(float, float)> on_value_change;

	private:
		sf::Joystick::Axis axis_;
		float dead_zone_;

		float previous_value_;
	};
}