cmake_minimum_required(VERSION 3.16)
project(
	01PROJUPPER
	VERSION 0.0.1
	DESCRIPTION "01PROJDESC"
	LANGUAGES C
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE 01PROJUPPER_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE 01PROJUPPER_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE 01PROJUPPER_TESTS "${CMAKE_SOURCE_DIR}/tests/*.c")
set(ALL_C_FILES
	${01PROJUPPER_SOURCES}
	${01PROJUPPER_HEADERS}
)

# core library
file(GLOB_RECURSE 01PROJUPPER_SRC_LIB "${CMAKE_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM 01PROJUPPER_SRC_LIB
	"${CMAKE_SOURCE_DIR}/src/main.c"
)
add_library(core ${01PROJUPPER_SRC_LIB})
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# executable
add_executable(01PROJCMD
	${CMAKE_SOURCE_DIR}/src/main.c
)
target_link_libraries(01PROJCMD PRIVATE core)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
target_compile_definitions(01PROJCMD PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# Set these options off for a Release Build
option(BUILD_TESTS "Build Tests" ON)
if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

option(ENABLE_WARNINGS "Enable Compiler Warnings" ON)
if (ENABLE_WARNINGS)
	target_compile_options(01PROJCMD PRIVATE -Wall -Wextra)
	target_compile_options(core PRIVATE -Wall -Wextra)
endif()

add_custom_target(docs)
add_dependencies(docs 01PROJCMD)

find_package(Doxygen)
if (DOXYGEN_FOUND)
	add_custom_command(
		TARGET docs
		POST_BUILD
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Generating Documentation with Doxygen"
	)
else()
	message(STATUS "Doxygen not found: skipping")
endif()

# clang-format target
find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE AND ALL_C_FILES)
	add_custom_target(
		clang-format
		COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_C_FILES}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running clang-format on source and include files"
	)
else()
	message(STATUS "clang-format not found, 'clang-format' target will be skipped")
endif()

add_custom_target(run_tests
	COMMAND ${CMAKE_CTEST_COMMAND}
)
add_dependencies(run_tests flags)

# Runs all targets
add_custom_target(dev_build
	COMMENT "Build all targets: 01PROJCMD, formatting, and documentation")

add_dependencies(dev_build clang-format)
add_dependencies(dev_build 01PROJCMD)
add_dependencies(dev_build docs)
add_dependencies(dev_build run_tests)

