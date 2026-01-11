cmake_minimum_required(VERSION 3.16)

project(
	01PROJUPPER
	VERSION 0.1.0
	DESCRIPTION "01PROJDESC"
	LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE 01PROJUPPER_SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE 01PROJUPPER_HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")

file(GLOB_RECURSE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.c")
file(GLOB_RECURSE TEST_HEADERS "${CMAKE_SOURCE_DIR}/tests/*.h")

set(ALL_C_FILES
	${01PROJUPPER_SOURCES}
	${01PROJUPPER_HEADERS}
	${TEST_SOURCES}
	${TEST_HEADERS}
)

add_executable(01PROJCMD
	${01PROJUPPER_SOURCES}
	${01PROJUPPER_HEADERS}
)

target_include_directories(01PROJCMD PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(01PROJCMD PRIVATE -Wall -Wextra)
add_dependencies(01PROJCMD clang-format)


# clang-format target
# Esures proper formatting of all code

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE AND ALL_C_FILES)
	add_custom_target(
		clang-format
		COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_C_FILES}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Running clang-format on source files"
	)
else()
	message(STATUS "clang-format not found, 'clang-format' target will be skipped")
endif()

# doxygen target
# Ensures documentation is created on all code
find_package(Doxygen)

if(DOXYGEN_FOUND)
	add_custom_target(
		docs
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Generating Documentation with Doxygen"
		VERBATIM
	)

else()
	message(STATUS "Doxygen not found, 'docs' target willbe skipped")
endif()
add_dependencies(docs 01PROJCMD)

# TESTS
enable_testing()

if(TEST_SOURCES)
	add_executable(test_runner
		${TEST_SOURCES}
		${TEST_HEADERS}
	)

	target_include_directories(test_runner PRIVATE "${CMAKE_SOURCE_DIR}/include")
	target_compile_options(test_runner PRIVATE -Wall -Wextra)
	add_test(NAME unit_tests COMMAND test_runner)
	add_custom_target(
		check
		COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
		DEPENDS test_runner
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Running unit tests (ctest)"
	)
else()
	message(STATUS "No tests found in tests/*.c. 'check' target will be skipped")
endif()

# Runs all targets
add_custom_target(build_all ALL
	COMMENT "Build all targets: 01PROJCMD, formatting, documentation, testing"
)

add_dependencies(build_all clang-format)
if (TARGET check)
	add_dependencies(build_all check)
else ()
	message(STATUS "No tests found in tests/*.c. 'check' target will be skipped")
endif ()
add_dependencies(build_all 01PROJCMD)
add_dependencies(build_all docs)

