set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) 

set(
	SRCS
	main.cpp
)

add_executable(Example_JoystickCheck ${SRCS})
target_link_libraries(Example_JoystickCheck JoystickBindings)