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
	void 			*header_structur;
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
}request_t;

#endif /* RCS_H */
