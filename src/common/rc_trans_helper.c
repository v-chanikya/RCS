/**
 *
 * @brief All helper functions related to an http transaction
 * which is composed of http request and http response.
 */

#include <stdio.h>
#include <stdlib.h>

#include "rcs.h"

/* freeing functions */
int free_header_struct(header_type_t header_type, void *header_struct){
	return 0;
}

int rct_req_free(request_t *req){
	int i = 0;
	header_t **headers = req->headers;
	if(req){
		for(;i<req->no_headers;i++){
			if(headers[i]->header_struct)
				free_header_struct(headers[i]->header_type, headers[i]->header_struct);
			free(headers[i]);
		}
		free(req);
	}
	return 0;
}

int rct_res_free(response_t *res){
	int i = 0;
	header_t **headers = res->headers;
	res_error_t *err = res->error;
	if(res){
		for(;i<res->no_headers;i++){
			if(headers[i]->header_struct)
				free_header_struct(headers[i]->header_type, headers[i]->header_struct);
			free(headers[i]);
		}
		if(err){
			if(err->error_app_tag)
				free(err->error_app_tag);
			if(err->error_path)
				free(err->error_path);
			if(err->error_message)
				free(err->error_message);
			free(err);
		}
		if(res->body)
			free(res->body);
		free(res);
	}
	return 0;
}

int rct_free(rc_trans_t *rct){
	if(rct->raw_req)
		free(rct->raw_req);
	if(rct->raw_res)
		free(rct->raw_res);
	rct_req_free(rct->req);
	rct_res_free(rct->res);
}

/* enum printers */
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

char * response_code_2_str(response_code_t e){
	switch(e){
		E_CASE(RC_200_T);
		E_CASE(RC_201_T);
		E_CASE(RC_400_T);
		E_CASE(RC_401_T);
		E_CASE(RC_403_T);
		E_CASE(RC_404_T);
		E_CASE(RC_405_T);
		E_CASE(RC_406_T);
		E_CASE(RC_409_T);
		E_CASE(RC_412_T);
		E_CASE(RC_413_T);
		E_CASE(RC_500_T);
		E_CASE(RC_501_T);
	}
	return NULL;
}

char * res_error_type_2_str(res_error_type_t e){
	switch(e){
		E_CASE(TRANSPORT_T);
		E_CASE(RPC_T);
		E_CASE(PROTOCOL_T);
		E_CASE(APPLICATION_T);
	}
	return NULL;
}

char * res_error_tag_2_str(res_error_tag_t e){
	switch(e){
		E_CASE(IN_USE_T);
		E_CASE(INVALID_VALUE_T);
		E_CASE(TOO_BIG_T);
		E_CASE(MISSING_ATTRIBUTE_T);
		E_CASE(BAD_ATTRIBUTE_T);
		E_CASE(UNKNOWN_ATTRIBUTE_T);
		E_CASE(BAD_ELEMENT_T);
		E_CASE(UNKNOWN_ELEMENT_T);
		E_CASE(UNKNOWN_NAMESPACE_T);
		E_CASE(ACCESS_DENIED_T);
		E_CASE(LOCK_DENIED_T);
		E_CASE(RESOURCE_DENIED_T);
		E_CASE(ROLLBACK_FAILED_T);
		E_CASE(DATA_EXISTS_T);
		E_CASE(DATA_MISSING_T);
		E_CASE(OPERATION_NOT_SUPPORTED_T);
		E_CASE(OPERATION_FAILED_T);
		E_CASE(PARTIAL_OPERATION_T);
		E_CASE(MALFORMED_MESSAGE_T);
	}
	return NULL;
}

/* printers */
void rct_headers_print(int no, header_t **headers){
	int i = 0;
	for (;i<no;i++){
		printf("\n\tHeader     : %s\n",header_type_2_str(headers[i]->header_type));
		printf("\tHeader data: %s\n",headers[i]->header_data);
	}
}

void rct_error_print(res_error_t *err){
	printf("\n\tERROR in request\n");
	printf("\terror_type     :%s\n",res_error_type_2_str(err->error_type));
	printf("\terror tag      :%s\n",res_error_tag_2_str(err->error_tag));
	if(err->error_app_tag)
		printf("\terror app tag  :%s\n",err->error_app_tag);
	if(err->error_path)
		printf("\terror path     :%s\n",err->error_path);
	if(err->error_message)
		printf("\terror message  :%s\n",err->error_message);
}

void rct_req_print(request_t *req){
	printf("############################################\n");
	printf("REQUEST DATA\n");
	printf("############################################\n");
	printf("%s %s\n",http_type_2_str(req->http_type),http_version_2_str(req->http_version));
	printf("Method     : %s\n",request_method_2_str(req->request_method));
	printf("Request URL: %s\n",req->url);
	rct_headers_print(req->no_headers, req->headers);
	if(req->body)
		printf("\nBODY\n\n%s\n",req->body);
	printf("############################################\n\n");
}

void rct_res_print(response_t *res){
	printf("############################################\n");
	printf("RESPONSE DATA\n");
	printf("############################################\n");
	printf("%s %s\n",http_type_2_str(res->http_type),http_version_2_str(res->http_version));
	printf("CODE     : %s\n",response_code_2_str(res->response_code));
	rct_headers_print(res->no_headers, res->headers);
	if(res->body)
		printf("\nBODY\n\n%s\n",res->body);
	if(res->error)
		rct_error_print(res->error);
	printf("############################################\n\n");
}

void rct_print(rc_trans_t *rct){
	if(rct->raw_req){
		printf("############################################\n");
		printf("RAW REQUEST DATA\n");
		printf("############################################\n");
		printf("%s",rct->raw_req);
		printf("############################################\n\n");
	}
	if(rct->req){
		rct_req_print(rct->req);
	}
	if(rct->res){
		rct_res_print(rct->res);
	}
	if(rct->raw_res){
		printf("############################################\n");
		printf("RAW RESPONSE DATA\n");
		printf("############################################\n");
		printf("%s",rct->raw_res);
		printf("############################################\n\n");
	}
}
