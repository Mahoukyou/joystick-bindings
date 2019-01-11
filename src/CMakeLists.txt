set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) 
 
set(
	SRCS
	main.cpp
	joystick.h
	joystick.cpp
	button_bindings.h
	button_bindings.cpp
	axis_bindings.h
	axis_bindings.cpp
)

add_executable(JoystickBindings ${SRCS})

target_link_libraries(JoystickBindings sfml-window)