/**
 * @file rcs.h
 * @author Chanikya
 * @brief Restconf server header
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

#ifndef RCS_H
#define RCS_H

/**
 * @brief restconf server error codes
 */
typedef enum rcs_err_code_e {
	RCS_ERR_OK,
	RCS_ERR_INVALID_REQUEST,
	RCS_ERR_INTERNAL_ERR
}rcs_err_code_t

/**
 * @brief Request methods
 */
typedef enum request_method_s {
	OPTIONS_T,
	HEAD_T,
	GET_T,
	POST_T,
	PUT_T,
	PATCH_T,
	DELETE_T,
	UNSUPPORTED_METHOD_T
}request_method_t;

/**
 * @brief HTTP version
 */
typedef enum http_version_e {
	HTTP_V1_T,
	HTTP_V1_1_T,
	UNSUPPORTED_VERSION_T
}http_version_t;

/**
 * @brief type of http
 */
typedef enum http_type_e {
	HTTP_T,
	HTTPS_T,
	UNSUPPORTED_HTTP_TYPE_T
}http_type_t;

/**
 * @brief type of headers
 */
typedef enum header_type_e {
	ACCEPT_T,
	CONTENT_TYPE_T,
	CONTENT_LENGTH_T,
	LAST_MODIFIED_T,
	IF_MODIFIED_SINCE_T,
	IF_UNMODIFIED_SINCE_T,
	E_TAG_T,
	IF_MATCH_T,
	IF_NONE_MATCH_T,
	ACCEPT_PATCH_T,
	LOCATION_T,
	DATE_T,
	CACHE_CONTROL_T,
	ACCEPT_ENCODING_T,
	LAST_EVENT_ID_T,
	UNHANDLED_HEADER_T
}header_type_t;

/**
 * @brief header of the request
 */
typedef struct header_s {
	header_type_t 	header_type;
	char 			*header_data;
	void 			*header_struct;
}header_t;

/**
 * @brief structure that contains the entire request
 */
typedef struct request_s {
	http_type_t 		http_type;
	http_version_t 		http_version;
	request_method_t 	request_method;
	char 				*url;
	header_t 			**headers;
	int 				no_headers;
	char 				*body;
}request_t;

/**
 * @brief response code enum
 */
typedef enum response_code_e{
	RC_200_T,
	RC_201_T,
	RC_400_T,
	RC_401_T,
	RC_403_T,
	RC_404_T,
	RC_405_T,
	RC_406_T,
	RC_409_T,
	RC_412_T,
	RC_413_T,
	RC_500_T,
	RC_501_T
}response_code_t;

/**
 * @brief error type enum
 */
typedef enum res_error_type_e{
	TRANSPORT_T,
	RPC_T,
	PROTOCOL_T,
	APPLICATION_T
}res_error_type_t;

/**
 * @brief error tag enum
 */
typedef enum res_error_tag_e{
	IN_USE_T,
	INVALID_VALUE_T,
	TOO_BIG_T,
	MISSING_ATTRIBUTE_T,
	BAD_ATTRIBUTE_T,
	UNKNOWN_ATTRIBUTE_T,
	BAD_ELEMENT_T,
	UNKNOWN_ELEMENT_T,
	UNKNOWN_NAMESPACE_T,
	ACCESS_DENIED_T,
	LOCK_DENIED_T,
	RESOURCE_DENIED_T,
	ROLLBACK_FAILED_T,
	DATA_EXISTS_T,
	DATA_MISSING_T,
	OPERATION_NOT_SUPPORTED_T,
	OPERATION_FAILED_T,
	PARTIAL_OPERATION_T,
	MALFORMED_MESSAGE_T
}res_error_tag_t;

/**
 * @brief error structure for response
 */
typedef struct res_error_s{
	res_error_type_t 	error_type;
	res_error_tag_t 	error_tag;
	char 				*error_app_tag;
	char 				*error_path;
	char 				*error_message;
}res_error_t;

/**
 * @brief structure that contains the entire response
 */
typedef struct response_s{
	http_type_t 		http_type;
	http_version_t 		http_version;
	response_code_t 	response_code;
	header_t 			**headers;
	int 				no_headers;
	char 				*body;
	res_error_t 		*error;
}response_t;

/**
 * @brief structure that contains all the data related to a
 * single restconf transcaction
 */
typedef struct rc_trans_s{
	char 				*raw_req;
	char 				*raw_res;
	request_t 			*req;
	response_t 			*res;
}rc_trans_t;

/**
 * @brief free the restconf transaction structure
 */
int rct_free(rc_trans_t *rct);

/**
 * @brief free the restconf request structure
 */
int rct_req_free(request_t *req);

/**
 * @brief free the restconf response structure
 */
int rct_res_free(response_t *res);

/**
 * @brief prints the restconf transaction structure
 */
void rct_print(rc_trans_t *rct);

/**
 * @brief prints the restconf request structure
 */
void rct_req_print(request_t *req);

/**
 * @brief prints the restconf response structure
 */
void rct_res_print(response_t *res);

/**
 * @brief Generic enum case to return string of the case.
 */
#define E_CASE(x) \
    case x: \
    return  #x ;

#endif /* RCS_H */
