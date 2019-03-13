cmake_minimum_required(VERSION 3.5)

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git describe --abbrev=0 --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

if(GIT_VERSION MATCHES "[0-9]+.[0-9]+.[0-9]+")
	message(STATUS "Using git version ${GIT_VERSION}")
	project(Logging VERSION "${GIT_VERSION}" LANGUAGES C)
else()
	project(Logging VERSION "0.0.0" LANGUAGES C)
endif()


add_library(Logging src/logging.c)
target_include_directories(Logging PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_executable(example example/main.c)
target_link_libraries(example Logging)

install(TARGETS Logging EXPORT LoggingTargets
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


#CPack
set(CPACK_PACKAGE_CONTACT "arwed.mett@googlemail.com")

if(APPLE)
	set(CPACK_GENERATOR "TGZ;ZIP;productbuild")
elseif(UNIX)
	set(CPACK_GENERATOR "TGZ;ZIP")
elseif(WIN32)
	set(CPACK_GENERATOR "ZIP;NSIS;NSIS64")
else()
	set(CPACK_GENERATOR "TGZ;ZIP")
endif()

set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
include(CPack)
