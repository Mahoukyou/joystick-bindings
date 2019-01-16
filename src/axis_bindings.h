#pragma once

#include "SFML/Window/Joystick.hpp"
#include <functional>

namespace prim_bindings
{
	class axis_binding
	{
	public:
		explicit axis_binding(sf::Joystick::Axis axis, float dead_zone);

		/* Called every pool if axis is active (outside dead_zone)
		 * Parameters: previous_value, new_value, delta_time passed to pool_joystick
		 */
		std::function<void(float, float, double)> on_active;

		/* Called every pool if axis is inactive (inside dead_zone) */
		std::function<void()> on_inactive;

		/* Called when the axis value changes and it is outside the dead_zone
		 * Parameters: previous_value, new_value, delta_time passed to pool_joystick
		 */
		std::function<void(float, float, double)> on_value_change;

		void pool_joystick(int joystick_id, double delta_time);

		sf::Joystick::Axis get_axis() const { return axis_; }

	private:
		sf::Joystick::Axis axis_;
		float dead_zone_;

		float previous_value_;
	};
}