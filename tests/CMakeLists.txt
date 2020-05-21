set(TEST_REPOSITORY_LOC "${CMAKE_BINARY_DIR}/repository")

include_directories(
	"${PROJECT_SOURCE_DIR}/inc"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/common"
)

find_program(valgrind_FOUND valgrind)
find_program(timeout_FOUND timeout)

macro(ADD_UNIT_TEST_WITH_OPTS TEST_NAME USE_VALGRIND WRAP_FUNCTION)
    if ("${WRAP_FUNCTION}" STREQUAL "")
        set(test_link_flags "")
    else()
        set(test_link_flags "-Wl,--wrap,${WRAP_FUNCTION}")
    endif()

	add_executable(${TEST_NAME} ${TEST_NAME}.c)

	target_link_libraries(${TEST_NAME} ${CMOCKA_LIBRARIES} rcs ${test_link_flags})
    if(timeout_FOUND AND NOT ${CMAKE_C_FLAGS} MATCHES "-fsanitize")
        add_test(${TEST_NAME} timeout
            --signal=6 360
            ./${TEST_NAME})
    else()
        add_test(${TEST_NAME} ${TEST_NAME})
    endif()
    if(valgrind_FOUND AND ${USE_VALGRIND} AND NOT ${CMAKE_C_FLAGS} MATCHES "-fsanitize")
        add_test(${TEST_NAME}_valgrind valgrind
            --error-exitcode=1 --read-var-info=yes
            --leak-check=full --show-leak-kinds=all
            --suppressions=${TEST_HELPERS_DIR}valgrind.supp
            ./${TEST_NAME})
    endif()
endmacro(ADD_UNIT_TEST_WITH_OPTS)

macro(ADD_UNIT_TEST TEST_NAME)
	ADD_UNIT_TEST_WITH_OPTS(${TEST_NAME} "1" "")
endmacro(ADD_UNIT_TEST)

ADD_UNIT_TEST(header_handler_test)
ADD_UNIT_TEST(response_engine_test)
