cmake_minimum_required(VERSION 3.16)
project(
	01PROJUPPER_TESTS
	DESCRIPTION "Testing..."
	LANGUAGES C
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB TEST_SOURCES "*.c")

foreach(test_src ${TEST_SOURCES})
	get_filename_component(test_name ${test_src} NAME_WE)

	add_executable(${test_name} ${test_src})

	target_link_libraries(${test_name}
		PRIVATE
		core
	)

	add_test(
		NAME ${test_name}
		COMMAND ${test_name}
	)

endforeach()
