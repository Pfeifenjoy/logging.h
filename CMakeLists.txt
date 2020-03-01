cmake_minimum_required(VERSION 3.5)
project(logging LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(require-git)

# Library
add_library(logging src/logging.c)
target_include_directories(logging PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# Example
add_executable(example example/main.c)
target_link_libraries(example PRIVATE logging)

#Install
install(TARGETS logging EXPORT loggingTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(DIRECTORY include/logging DESTINATION include)

install(EXPORT loggingTargets
	FILE loggingTargets.cmake
	NAMESPACE logging::
	DESTINATION lib/cmake/logging
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("loggingConfigVersion.cmake"
	VERSION ${logging_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(
	FILES
		"cmake/loggingConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/loggingConfigVersion.cmake"
	DESTINATION
		lib/cmake/logging
)

include(pack)
