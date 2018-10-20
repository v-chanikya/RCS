/**
 * @file header_handler.c
 * @author Chanikya
 * @brief Restconf server header handler.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "rcs.h"
#include "header_handler.h"

char *parse_head(char *head_line, request_t *req){
	char *req_head[3];
	int i = 0;
	
	req_head[0] = head_line;
	while(*head_line != '\n'){
		if(*head_line == ' '){
			*head_line = '\0';
			req_head[++i] = head_line + 1;
		}
		head_line++;
	}
	*head_line = '\0';
	
	/* Determine request method */
	if(strcmp(req_head[0],"OPTIONS") == 0)
		req->request_method = OPTIONS_T;
	else if(strcmp(req_head[0],"HEAD") == 0)
		req->request_method = HEAD_T;
	else if(strcmp(req_head[0],"GET") == 0)
		req->request_method = GET_T;
	else if(strcmp(req_head[0],"POST") == 0)
		req->request_method = POST_T;
	else if(strcmp(req_head[0],"PUT") == 0)
		req->request_method = PUT_T;
	else if(strcmp(req_head[0],"PATCH") == 0)
		req->request_method = PATCH_T;
	else if(strcmp(req_head[0],"DELETE") == 0)
		req->request_method = DELETE_T;
	else
		req->request_method = UNSUPPORTED_METHOD_T;

	/* url */
	req->url = req_head[1];

	/* http */
	if(strstr(req_head[2],"HTTPS") != NULL)
		req->http_type = HTTPS_T;
	else if(strstr(req_head[2],"HTTP") != NULL)
		req->http_type = HTTP_T;
	else
		req->http_type = UNSUPPORTED_HTTP_TYPE_T;

	if(strstr(req_head[2],"1.1") != NULL)
		req->http_version = HTTP_V1_1_T;
	else if(strstr(req_head[2],"1.0") != NULL)
		req->http_version = HTTP_V1_T;
	else
		req->http_version = UNSUPPORTED_VERSION_T;

	return ++head_line;
}

header_type_t determine_header_type(char *header_type){
	if(strcmp(header_type, "Accept") == 0 )
		return ACCEPT_T;
	else if(strcmp(header_type, "Content-Type") == 0 )
		return CONTENT_TYPE_T;
	else if(strcmp(header_type, "Content-Length") == 0 )
		return CONTENT_LENGTH_T;
	else if(strcmp(header_type, "Last-Modified") == 0 )
		return LAST_MODIFIED_T;
	else if(strcmp(header_type, "If-Modified-Since") == 0 )
		return IF_MODIFIED_SINCE_T;
	else if(strcmp(header_type, "If-Unmodified-Since") == 0 )
		return IF_UNMODIFIED_SINCE_T;
	else if(strcmp(header_type, "E-Tag") == 0 )
		return E_TAG_T;
	else if(strcmp(header_type, "If-Match") == 0 )
		return IF_MATCH_T;
	else if(strcmp(header_type, "If-None-Match") == 0 )
		return IF_NONE_MATCH_T;
	else if(strcmp(header_type, "Accept-Patch") == 0 )
		return ACCEPT_PATCH_T;
	else if(strcmp(header_type, "Location") == 0 )
		return LOCATION_T;
	else if(strcmp(header_type, "Date") == 0 )
		return DATE_T;
	else if(strcmp(header_type, "Cache-Control") == 0 )
		return CACHE_CONTROL_T;
	else if(strcmp(header_type, "Accept-Encoding") == 0 )
		return ACCEPT_ENCODING_T;
	else if(strcmp(header_type, "Last-Event-Id") == 0 )
		return LAST_EVENT_ID_T;
	else
		return UNHANDLED_HEADER_T;
}

int parse_header(char *in_buf, request_t *req){
	char *header_buf 	= NULL;
	int no_of_headers 	= 0;
	header_t **headers 	= NULL;
	char *header_type 	= NULL;
	header_type_t header_type_enum = UNHANDLED_HEADER_T;
	bool skip 			= false;
	bool done_parse 	= false;

	/* Read the first line to determine request_method
	http_versions, http_type, url */
	header_buf = parse_head(in_buf, req);
	
	while (1){
		if(!skip){
			headers = (header_t **) realloc(headers, sizeof(header_t *) * (no_of_headers + 1));
			headers[no_of_headers] = (header_t *) malloc(sizeof(header_t));
		}else{
			skip = false;
		}
		header_type = header_buf;
		while(*header_buf != '\n'){
			if(!done_parse && *header_buf == ':'){
				*header_buf = '\0';
				header_type_enum = determine_header_type(header_type);
				if(header_type_enum != UNHANDLED_HEADER_T){
					headers[no_of_headers]->header_type = header_type_enum;
					headers[no_of_headers]->header_data = header_buf + 2;
				}else{
					skip = true;
				}
				done_parse = true;
			}
			header_buf++;
		}
		*header_buf = '\0';
		done_parse = false;
		header_type_enum = UNHANDLED_HEADER_T;
		if (*(header_buf + 1) == '\n')
			break;
		no_of_headers++;
		header_buf++;
	}

	req->headers = headers;
	req->no_headers = no_of_headers;
	return 0;
}
