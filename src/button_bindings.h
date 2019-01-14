#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <map>


namespace prim_bindings
{
	class button_combination
	{
	public:
		bool add_key(int id, bool state)
		{
			if (has_key(id))
			{
				return false;
			}

			buttons_combination_.insert(std::make_pair(id, state));
			return true;
		}

		bool has_key(int id, bool state)
		{
			const auto key = buttons_combination_.find(id);

			return key != buttons_combination_.end() && key->second == state;
		}

		bool has_key(int id)
		{
			return buttons_combination_.find(id) != buttons_combination_.end();
		}

		void remove_key(int id)
		{
			buttons_combination_.erase(id);
		}

		void remove_key(int id, bool state)
		{
			const auto key = buttons_combination_.find(id);
			if (key != buttons_combination_.end() && key->second == state)
			{
				buttons_combination_.erase(key);
			}
		}

	//private:
		std::map<unsigned int, bool> buttons_combination_;
	};

	class button_binding
	{
	public:
		button_binding();

		button_combination button_combination_;

		/* Called every pool if the combination is active */
		std::function<void()> on_active_;

		/* Called every pool if the combination is inactive*/
		std::function<void()> on_inactive_;

		/* Called when the state changes*/
		std::function<void(bool)> on_state_change_;

		void pool_joystick(int joystick_id);

	private:
		void set_state(bool new_state);

		bool current_state_;
	};
}