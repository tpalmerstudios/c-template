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
set(ALL_C_FILES
	${01PROJUPPER_SOURCES}
	${01PROJUPPER_HEADERS}
)
add_executable(01PROJCMD
	${01PROJUPPER_SOURCES}
	${01PROJUPPER_HEADERS}
)

target_include_directories(01PROJCMD PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(01PROJCMD PRIVATE -Wall -Wextra)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
target_compile_definitions(01PROJCMD PRIVATE $<$<CONFIG:Debug>:DEBUG>)

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

# doxygen target
find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(
		docs
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Generating Documentation with Doxygen"
	)
else()
	message(STATUS "Doxygen not found, 'docs' target will be skipped")
endif()
add_dependencies(docs 01PROJCMD)

# Runs all targets
add_custom_target(dev_build
	COMMENT "Build all targets: 01PROJCMD, formatting, and documentation")

add_dependencies(dev_build clang-format)
add_dependencies(dev_build 01PROJCMD)
add_dependencies(dev_build docs)

