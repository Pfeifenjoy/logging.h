cmake_minimum_required(VERSION 3.5)
project(logging.h VERSION 0.0.1 LANGUAGES C)

add_library(logging.h src/logging.c)
target_include_directories(logging.h PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

add_executable(example example/main.c)
target_link_libraries(example logging.h)

install(TARGETS logging.h EXPORT Targets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)
install(DIRECTORY include/logging DESTINATION include)
install(EXPORT Targets
	FILE Targets.cmake
	NAMESPACE Logging.h::
	DESTINATION lib/cmake/logging.h
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(Logging.hConfig.cmake
	COMPATIBILITY SameMajorVersion
)

install(FILES build/Logging.hConfig.cmake DESTINATION lib/cmake/logging.h)

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
