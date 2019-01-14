#include "button_bindings.h"
#include "SFML/Window/Joystick.hpp"

namespace prim_bindings
{
	button_binding::button_binding() :
		current_state_{ false }
	{

	}

	void button_binding::pool_joystick(const int joystick_id)
	{
		if (joystick_id < 0 || !sf::Joystick::isConnected(joystick_id))
		{
			return;
		}

		bool combination_on = true;
	/*	for (size_t i = 0; i < sf::Joystick::getButtonCount(joystick_id); ++i)
		{
			if(button_combination_.has_key(i))
		}*/

		for(auto button : button_combination_.buttons_combination_)
		{
			if(button.first < sf::Joystick::getButtonCount(joystick_id))
			{
				if(button.second != sf::Joystick::isButtonPressed(joystick_id, button.first))
				{
					combination_on = false;
					break;
				}
			}
		}

		if(combination_on)
		{
			on_active_();
		}
		else
		{
			on_inactive_();
		}

		set_state(combination_on);
	}

	void button_binding::set_state(bool new_state)
	{
		if(current_state_ == new_state)
		{
			return;
		}

		current_state_ = new_state;
		on_state_change_(new_state);
	}
}
