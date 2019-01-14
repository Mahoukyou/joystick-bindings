#include "joystick.h"
#include "SFML/Window/Joystick.hpp"

namespace prim_bindings
{
	joystick::joystick(const int id) :
		id_{ id }
	{
		
	}

	void joystick::pool_joystick(const bool self_update)
	{
		if(self_update)
		{
			sf::Joystick::update();
		}

		constexpr int max_joysticks_sfml = 8;

		// todo remove any_joystick or leave it?
		for(auto& binding : button_bindings)
		{
			if (id_ == any_joystick)
			{
				for (int joystick = 0; joystick < max_joysticks_sfml; ++joystick)
				{
					binding.pool_joystick(joystick);
				}
			}
			else
			{
				binding.pool_joystick(id_);
			}
		}

		for (auto& binding : axis_bindings)
		{
			if (id_ == any_joystick)
			{
				for (int joystick = 0; joystick < max_joysticks_sfml; ++joystick)
				{
					binding.pool_joystick(joystick);
				}
			}
			else
			{
				binding.pool_joystick(id_);
			}
		}
	}
}