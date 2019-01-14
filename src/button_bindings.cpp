#include "button_bindings.h"
#include "SFML/Window/Joystick.hpp"

namespace prim_bindings
{
	button_binding::button_binding(unsigned int button_id) :
		button_id_{ button_id },
		current_state_{ false }
	{
		// todo check button id
	}

	void button_binding::pool_joystick(const int joystick_id)
	{
		if (joystick_id < 0 || !sf::Joystick::isConnected(joystick_id))
		{
			return;
		}

		if (button_id_ >= sf::Joystick::getButtonCount(joystick_id))
		{
			return;
		}

		const bool new_button_state = sf::Joystick::isButtonPressed(joystick_id, button_id_);
		if (new_button_state && on_active)
		{
			on_active();
		}
		else if(on_inactive)
		{
			on_inactive();
		}

		set_state(new_button_state);
	}

	void button_binding::set_state(const bool new_state)
	{
		if (current_state_ == new_state)
		{
			return;
		}

		current_state_ = new_state;

		if (on_state_change)
		{
			on_state_change(new_state);
		}
	}
}
