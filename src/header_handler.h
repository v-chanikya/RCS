/**
 * @file header_handler.h
 */

#ifndef HEADER_HANDLER_H_
#define HEADER_HANDLER_H_

#define HELLO_MY 0
#include "rcs.h"

int parse_header(char* in_buf, request_t *req);

#endif /* HEADER_HANDLER_H_ */
