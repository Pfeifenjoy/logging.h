cmake_minimum_required(VERSION 3.5)
project(logging.h LANGUAGES C)
message(STATUS ${CMAKE_SYSTEM_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(require-git)

#Targets
add_library(Logging OBJECT src/logging.c)
target_include_directories(Logging PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
set_property(TARGET Logging PROPERTY POSITION_INDEPENDENT_CODE 1)
add_library(shared SHARED $<TARGET_OBJECTS:Logging>)
target_include_directories(shared PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
add_library(static STATIC $<TARGET_OBJECTS:Logging>)
target_include_directories(static PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_executable(example example/main.c)
	target_link_libraries(example shared)
endif()

#Install
install(TARGETS static shared EXPORT LoggingTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(DIRECTORY include/logging DESTINATION include)

install(EXPORT LoggingTargets
	FILE LoggingTargets.cmake
	NAMESPACE Logging::
	DESTINATION lib/cmake/Logging
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("LoggingConfigVersion.cmake"
	VERSION ${Logging_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(
	FILES
		"cmake/LoggingConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/LoggingConfigVersion.cmake"
	DESTINATION
		lib/cmake/Logging
)

include(pack)
