cmake_minimum_required (VERSION 3.2)

project (JoystickBindings)

#SFML
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "Link SFML libraries statically")
set(SFML_DIR "" CACHE FILEPATH "Location of the SFML directory")

if(MSVC)
	set(SFML_STATIC_LIBRARIES ON)
else(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
endif(MSVC)

find_package(SFML 2.5.1 COMPONENTS window REQUIRED)

include_directories(".")
add_subdirectory(src)
