include_directories(
	"${PROJECT_SOURCE_DIR}/inc"
	"${PROJECT_SOURCE_DIR}/src"
)

add_executable(headers_parse headers_parse.c)
target_link_libraries(headers_parse rcs)

install(TARGETS headers_parse DESTINATION ${CMAKE_INSTALL_BINDIR})
