/**
 *
 * @brief All helper functions related to an http transaction
 * which is composed of http request and http response.
 */

#include <stdio.h>
#include <stdlib.h>

#include "rcs.h"

int free_header_struct(header_type_t header_type, void *header_struct){
	return 0;
}

int rct_req_free(request_t *req){
	int i = 0;
	header_t **headers = req->headers;
	for(;i<req->no_headers;i++){
		if(headers[i]->header_struct)
			free_header_struct(headers[i]->header_type, headers[i]->header_struct);
		free(headers[i]);
	}
	free(req);
	return 0;
}

/* printers */
char * http_type_2_str(http_type_t e){
	switch(e){
		E_CASE(HTTP_T);
		E_CASE(HTTPS_T);
		E_CASE(UNSUPPORTED_HTTP_TYPE_T);
	}
	return NULL;
}

char * http_version_2_str(http_version_t e){
	switch(e){
		E_CASE(HTTP_V1_T);
		E_CASE(HTTP_V1_1_T);
		E_CASE(UNSUPPORTED_VERSION_T);
	}
	return NULL;
}

char * header_type_2_str(header_type_t e){
	switch(e){	
		E_CASE(ACCEPT_T);
		E_CASE(CONTENT_TYPE_T);
		E_CASE(CONTENT_LENGTH_T);
		E_CASE(LAST_MODIFIED_T);
		E_CASE(IF_MODIFIED_SINCE_T);
		E_CASE(IF_UNMODIFIED_SINCE_T);
		E_CASE(E_TAG_T);
		E_CASE(IF_MATCH_T);
		E_CASE(IF_NONE_MATCH_T);
		E_CASE(ACCEPT_PATCH_T);
		E_CASE(LOCATION_T);
		E_CASE(DATE_T);
		E_CASE(CACHE_CONTROL_T);
		E_CASE(ACCEPT_ENCODING_T);
		E_CASE(LAST_EVENT_ID_T);
		E_CASE(UNHANDLED_HEADER_T);
	}
	return NULL;
}

char * request_method_2_str(request_method_t e){
	switch(e){
		E_CASE(OPTIONS_T);
		E_CASE(HEAD_T);
		E_CASE(GET_T);
		E_CASE(POST_T);
		E_CASE(PUT_T);
		E_CASE(PATCH_T);
		E_CASE(DELETE_T);
		E_CASE(UNSUPPORTED_METHOD_T);
	}
	return NULL;
}

void rct_req_print(request_t *req){
	int i = 0;
	
	printf("############################################\n");
	printf("%s %s\n",http_type_2_str(req->http_type),http_version_2_str(req->http_version));
	printf("Method     : %s\n",request_method_2_str(req->request_method));
	printf("Request URL: %s\n",req->url);
	for (;i<req->no_headers;i++){
		printf("\n\tHeader     : %s\n",header_type_2_str(req->headers[i]->header_type));
		printf("\tHeader data: %s\n",req->headers[i]->header_data);
	}
	if(req->body)
		printf("\nBODY\n\n%s\n",req->body);
	printf("############################################\n");
}
