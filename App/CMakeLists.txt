# CMakeList.txt : CMake project
cmake_minimum_required (VERSION 3.8)

set(APPTARGET ${CMAKE_PROJECT_NAME})
set(LIBTARGET ${CMAKE_PROJECT_NAME}_dev)
set(LIBTARGET ${CMAKE_PROJECT_NAME}_dev PARENT_SCOPE)

######################
# Configure SFML build

configure_file(${CMAKE_SOURCE_DIR}/deps/sfml/CMakeLists.txt.in ${CMAKE_SOURCE_DIR}/build/sfml-download/CMakeLists.txt)

execute_process(
	COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/sfml-download
)

if(result)
	message(FATAL_ERROR "CMake step for sfml failed: ${result}")
endif()

execute_process(
	COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/sfml-download
)

if(result)
  message(FATAL_ERROR "Build step for sfml failed: ${result}")
endif()

# Add sfml directly to our build.
add_subdirectory(
	${CMAKE_SOURCE_DIR}/build/sfml-src
	${CMAKE_SOURCE_DIR}/build/sfml-build
)

##############################
# organize include directories

set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/build/sfml-build/include/)

set(APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(APP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

file(GLOB_RECURSE APP_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${SFML_INCLUDE_DIR} ${APP_INCLUDE_DIR})

if((NOT WIN32) AND (NOT WIN64))
	include_directories (/usr/include/freetype2)
endif()

add_executable (${APPTARGET} ${APP_SRC_FILES})
add_library (${LIBTARGET} ${APP_SRC_FILES})

if(WIN32 OR WIN64)
	target_link_libraries(${APPTARGET} sfml-window sfml-system sfml-graphics)
	target_link_libraries(${LIBTARGET} sfml-window sfml-system sfml-graphics)
else()
	target_link_libraries(${APPTARGET} sfml-window sfml-system sfml-graphics pthread X11)
	target_link_libraries(${LIBTARGET} sfml-window sfml-system sfml-graphics pthread X11)
endif()
