cmake_minimum_required(VERSION 3.5)
project(logging.h LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(Git)

#Targets
add_library(Logging src/logging.c)
target_include_directories(Logging PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_executable(example example/main.c)
target_link_libraries(example Logging)

#Install
install(TARGETS Logging EXPORT LoggingTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(DIRECTORY include/logging DESTINATION include)
install(FILES LICENSE.txt DESTINATION .)

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
set(CPACK_BUNDLE_NAME "logging.h")
set(CPACK_PACKAGE_CONTACT "arwed.mett@googlemail.com")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://gitea.metthub.de/Pfeifenjoy/argparse")
set(CPACK_PACKAGE_CHECKSUM "SHA512")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/LICENSE.txt")

if(GIT_CURRENT_VERSION MATCHES "[0-9]+.[0-9]+.[0-9]+")
	set(CPACK_PACKAGE_FILE_NAME
		"logging.h-${CMAKE_SYSTEM_NAME}-${GIT_CURRENT_VERSION}")
else()
	set(CPACK_PACKAGE_FILE_NAME
		"logging.h-${CMAKE_SYSTEM_NAME}-${GIT_BRANCH}-${GIT_COMMIT_HASH}")
endif()

message(STATUS "Package name: ${CPACK_PACKAGE_FILE_NAME}")

if(APPLE)
	set(CPACK_GENERATOR "TGZ;ZIP;productbuild")
elseif(UNIX)
	set(CPACK_GENERATOR "TGZ;ZIP;RPM;DEB")
elseif(WIN32)
	set(CPACK_GENERATOR "ZIP;NSIS;NSIS64")
else()
	set(CPACK_GENERATOR "TGZ;ZIP")
endif()

include(CPack)
