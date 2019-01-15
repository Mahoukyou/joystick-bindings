set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) 
 
set(
	SRCS
	joystick.h
	joystick.cpp
	button_bindings.h
	button_bindings.cpp
	axis_bindings.h
	axis_bindings.cpp
	keyboard_mouse_helpers.h
	keyboard_mouse_helpers.cpp
)

add_library(JoystickBindings ${SRCS})
set_target_properties(JoystickBindings PROPERTIES LINKER_LANGUAGE CXX) 
target_link_libraries(JoystickBindings sfml-window)