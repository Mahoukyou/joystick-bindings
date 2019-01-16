#include "axis_bindings.h"

namespace prim_bindings
{
	axis_binding::axis_binding(const sf::Joystick::Axis axis, const float dead_zone) :
		axis_{ axis },
		dead_zone_{ dead_zone },
		previous_value_{ 0.0 }
	{

	}

	void axis_binding::pool_joystick(const int joystick_id, const double delta_time)
	{
		if (joystick_id < 0 || !sf::Joystick::isConnected(joystick_id))
		{
			return;
		}

		if (!sf::Joystick::hasAxis(joystick_id, axis_))
		{
			return;
		}

		const float new_value = sf::Joystick::getAxisPosition(joystick_id, axis_);
		const bool is_active = abs(new_value) > dead_zone_;
		if (is_active)
		{
			if (on_active)
			{
				on_active(previous_value_, new_value, delta_time);
			}

			if (on_value_change && previous_value_ != new_value)
			{
				on_value_change(previous_value_, new_value, delta_time);
			}
		}
		else if (on_inactive)
		{
			on_inactive();
		}

		previous_value_ = new_value;
	}
}
