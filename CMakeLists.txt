cmake_minimum_required(VERSION 3.5)
project(Logging VERSION 0.0.1 LANGUAGES C)

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

install(FILES "LoggingConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/LoggingConfigVersion.cmake" DESTINATION lib/cmake/Logging)


#CPack
set(CPACK_PACKAGE_CONTACT "arwed.mett@googlemail.com")

if(APPLE)
	set(CPACK_GENERATOR "TGZ;ZIP;productbuild")
elseif(UNIX)
	set(CPACK_GENERATOR "TGZ;ZIP;RPM;DEB")
elseif(WIN32)
	set(CPACK_GENERATOR "ZIP;NSIS;NSIS64")
else()
	set(CPACK_GENERATOR "TGZ;ZIP")
endif()

set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
include(CPack)
