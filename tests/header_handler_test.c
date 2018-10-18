#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "header_handler.h"

void header_parser_positive_test (void ** state) {
	char *header = "hello world from test";
	int ret_val = parse_header(header);
	assert_false(ret_val);
}

void header_parser_negative_test (void ** state)
{
    assert_true (0);
}

/* These functions will be used to initialize
   and clean resources up after each test run */
int setup (void ** state)
{
    return 0;
}

int teardown (void ** state)
{
    return 0;
}


int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test (header_parser_positive_test),
        cmocka_unit_test (header_parser_negative_test),
    };

    int count_fail_tests =
        cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
