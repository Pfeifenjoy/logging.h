cmake_minimum_required(VERSION 3.5)
project(logging LANGUAGES C)
message(STATUS ${CMAKE_SYSTEM_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(require-git)

#Targets
set(SRCS src/logging.c)
add_library(logging-headers INTERFACE)
target_include_directories(logging-headers INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_library(logging-shared SHARED ${SRCS})
target_link_libraries(logging-shared PUBLIC logging-headers)

add_library(logging-static STATIC ${SRCS})
target_link_libraries(logging-static PUBLIC logging-headers)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	add_executable(example example/main.c)
	target_link_libraries(example PRIVATE logging-shared)
endif()

#Install
install(TARGETS logging-headers logging-static logging-shared EXPORT loggingTargets
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
