cmake_minimum_required(VERSION 2.8.12)
project(restconf_sever)
set(RCS_DESC "YANG-based system repository")
include(GNUInstallDirs)

# setup version
set(RCS_MAJOR_VERSION 0)
set(RCS_MINOR_VERSION 0)
set(RCS_MICRO_VERSION 1)
set(RCS_VERSION ${RCS_MAJOR_VERSION}.${RCS_MINOR_VERSION}.${RCS_MICRO_VERSION})
set(RCS_SOVERSION ${RCS_MAJOR_VERSION}.${RCS_MINOR_VERSION})

# sourcs
add_subdirectory(src)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

# Tests
find_package(CMOCKA)
if(CMOCKA_FOUND)
	MESSAGE(STATUS "CMocka found, tests are enabled.")
	enable_testing()
	add_subdirectory(tests)
else(CMOCKA_FOUND)
	MESSAGE(WARNING "CMocka not found, tests are disabled.")
	SET(ENABLE_TESTS false)
endif(CMOCKA_FOUND)
