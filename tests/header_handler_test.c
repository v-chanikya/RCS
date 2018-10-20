#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "header_handler.h"
#include "rcs.h"

void header_parser_positive_test (void ** state) {
	request_t req;
	char header[256] = "GET /root/my HTTP/1.1\nAccept: text/json\nContent-Length: 245\nSpecial-head: special-dat\n\n";
	int ret_val = parse_header(header, &req);
	printf("url is %s\n",req.url);
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
