/**
 * @file response_engine.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rcs.h"
#include "response_engine.h"

char *response_code_string(response_code_t code){
	switch(code){
		case RC_200_T:
			return "200 OK";
		case RC_201_T:
			return "201 Created";
		case RC_400_T:
			return "400 Bad Request";
		case RC_401_T:
			return "401 Unauthorized";
		case RC_403_T:
			return "403 Forbidden";
		case RC_404_T:
			return "404 Not Found";
		case RC_405_T:
			return "405 Method Not Allowed";
		case RC_406_T:
			return "406 Not Acceptable";
		case RC_409_T:
			return "409 Conflict";
		case RC_412_T:
			return "412 Precondition Failed";
		case RC_413_T:
			return "413 Payload Too Large";
		case RC_500_T:
			return "500 Internal Server Error";
		case RC_501_T:
			return "501 Not Implemented";
		default:
			return NULL;
	}
}

char *http_type_string(http_version_t v, http_type_t t){
	switch(3*v + t){
		case 0:
			return "HTTP/1.0";
		case 1:
			return "HTTPS/1.0";
		case 3:
			return "HTTP/1.1";
		case 4:
			return "HTTPS/1.1";
		default:
			return NULL;
	}
}

char *construct_response_header(header_t **headers, int n){
	int i = 0;
	for(;i<n;i++){

	}
}

int construct_response(response_t *res){
	char resp[512] = {0,};
	char *headers = NULL;
	int rc = RCS_ERR_OK;

	/* silent drop for invalid request */
	if(res->http_type == UNSUPPORTED_HTTP_TYPE_T || res->http_version == UNSUPORTED_VERSION_T
			||res->response_code > RC_501_T){
		rc = RCS_ERR_INVALID_REQUEST;
		goto clenaup;
	}
	sprintf(resp,"%s %s\n",http_type_string(res->http_version),response_code_string(res->http_type));
	headers = construct_response_header(res->headers, no_headers);
	if(!headers)
		rc = RCS_ERR_INTERNAL_ERR;
	strcat(resp,headers);
cleanup:
	return rc;
}

int send_response(response_t *res){
	rct_res_print(res);
}
