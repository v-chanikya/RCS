set(COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/common")
set(UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/utils")
set(EXEC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/exec")

include_directories(
	"${PROJECT_SOURCE_DIR}/inc"
	"${COMMON_DIR}"
	"${UTILS_DIR}"
	"${EXEC_DIR}"
)

# common sources
set(COMMON_SOURCES
	${COMMON_DIR}/rcs_common.c
	${UTILS_DIR}/rcs_utils.c
)

# restconf server sources
set(RCS_SOURCES
	header_handler.c
)

add_library(COMMON OBJECT ${COMMON_SOURCES})
set_property(TARGET COMMON PROPERTY COMPILE_FLAGS "-fPIC")

add_library(RCS OBJECT ${RCS_SOURCES})
set_property(TARGET RCS PROPERTY COMPILE_FLAGS "-fPIC")

# sysrepo daemon
add_executable(rcsd ${EXEC_DIR}/rc_server.c)


install(TARGETS rcsd DESTINATION ${CMAKE_INSTALL_BINDIR})
