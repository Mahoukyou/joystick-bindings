#include "joystick.h"
#include "SFML/Window/Joystick.hpp"

namespace prim_bindings
{
	joystick::joystick(const int id) :
		id_{ id }
	{
		
	}

	void joystick::pool_joystick(const bool self_update, const double delta_time)
	{
		if(self_update)
		{
			sf::Joystick::update();
		}

		// todo remove any_joystick or leave it?
		for(auto& binding : button_bindings_)
		{
			if (id_ == any_joystick)
			{
				for (int joystick = 0; joystick < sf::Joystick::Count; ++joystick)
				{
					binding.pool_joystick(joystick);
				}
			}
			else
			{
				binding.pool_joystick(id_);
			}
		}

		for (auto& binding : axis_bindings_)
		{
			if (id_ == any_joystick)
			{
				for (int joystick = 0; joystick < sf::Joystick::Count; ++joystick)
				{
					binding.pool_joystick(joystick, delta_time);
				}
			}
			else
			{
				binding.pool_joystick(id_, delta_time);
			}
		}
	}

	bool joystick::add_button_binding(const button_binding& binding)
	{
		if(has_button_binding(binding.get_id()))
		{
			return false;
		}

		button_bindings_.push_back(binding);
		return true;
	}

	bool joystick::add_axis_binding(const axis_binding& binding)
	{
		if (has_axis_binding(binding.get_axis()))
		{
			return false;
		}

		axis_bindings_.push_back(binding);
		return true;
	}

	void joystick::remove_button_binding(const unsigned button_id)
	{
		std::remove_if(button_bindings_.begin(), button_bindings_.end(), [button_id](const button_binding& binding) -> bool
		{
			return binding.get_id() == button_id;
		});
	}

	void joystick::remove_axis_binding(const sf::Joystick::Axis axis)
	{
		std::remove_if(axis_bindings_.begin(), axis_bindings_.end(), [axis](const axis_binding& binding) -> bool
		{
			return binding.get_axis() == axis;
		});
	}

	bool joystick::has_button_binding(const unsigned button_id) const
	{
		const auto iterator = std::find_if(button_bindings_.begin(), button_bindings_.end(), [button_id](const button_binding& binding) -> bool
		{
			return binding.get_id() == button_id;
		});

		return iterator != button_bindings_.end();
	}

	bool joystick::has_axis_binding(const sf::Joystick::Axis axis) const
	{
		const auto iterator = std::find_if(axis_bindings_.begin(), axis_bindings_.end(), [axis](const axis_binding& binding) -> bool
		{
			return binding.get_axis() == axis;
		});

		return iterator != axis_bindings_.end();
	}
}
