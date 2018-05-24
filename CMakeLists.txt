cmake_minimum_required(VERSION 3.5)
project(logging VERSION 0.0.1 LANGUAGES C)

add_library(logging src/logging.c)
target_include_directories(logging PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

install(TARGETS logging EXPORT LoggingTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(DIRECTORY include/logging DESTINATION include)
install(EXPORT LoggingTargets
	FILE LoggingTargets.cmake
	NAMESPACE Logging::
	DESTINATION lib/cmake/logging
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(LoggingConfigVersion.cmake
	COMPATIBILITY SameMajorVersion
)

install(FILES build/LoggingConfigVersion.cmake
	DESTINATION lib/cmake/logging
)

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
