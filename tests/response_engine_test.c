/**
 * @file response_engine_type.c
 *
 * @brief this file tests response engine functionality
 */

#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "rcs.h"
#include "response_engine.h"

void response_print_test (void **state)
{
	response_t res;
	res_error_t error;
	res.http_version = HTTP_V1_T;
	res.http_type    = HTTPS_T;
	res.response_code= RC_403_T;
	res.body 		 = NULL;
	res.error        = &error;
	error.error_type = RPC_T;
	error.error_tag  = TOO_BIG_T;
	error.error_message = strdup("test error");
	send_response(&res);
}

int setup (void **state)
{
	return 0;
}

int teardown (void **state)
{
	return 0;
}

int main(void){
	const struct CMUnitTest tests [] =
	{
		cmocka_unit_test (response_print_test),
	};

	int count_fail_tests = 
		cmocka_run_group_tests(tests, setup, teardown);

	return count_fail_tests;
}
