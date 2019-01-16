option(COMPILE_BINDINGS_EXAMPLE "Compile bindings example" TRUE)

if(COMPILE_BINDINGS_EXAMPLE)
	add_subdirectory(Example_Bindings)
endif()

option(COMPILE_JOYSTICKCHECK_EXAMPLE "Compile joystick check example" TRUE)

if(COMPILE_JOYSTICKCHECK_EXAMPLE)
	add_subdirectory(Example_JoystickCheck)
endif()
