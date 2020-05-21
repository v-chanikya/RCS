/**
 * @file response_engine.h
 */

#ifndef RESPONSE_ENGINE_H_
#define RESPONSE_ENGINE_H_

#include "rcs.h"

/**
 * @brief Construct the response string from response_t
 */
int construct_response(response_t *res);

/**
 * @brief sends the response string back to client
 */
int send_response(response_t *res);

#endif /* RESPONSE_ENGINE_H_ */
