#pragma once

#include <functional>

namespace prim_bindings
{
	class button_binding
	{
	public:
		explicit button_binding(unsigned int button_id);

		// todo, remove active&inactive ? 
		/* Called every pool if the combination is active */
		std::function<void()> on_active;

		/* Called every pool if the combination is inactive*/
		std::function<void()> on_inactive;

		/* Called when the state changes, passed argument indicates if button is pressed*/
		std::function<void(bool)> on_state_change;

		void pool_joystick(int joystick_id);

	private:
		void set_state(bool new_state);

		unsigned int button_id_;
		bool current_state_;
	};
}