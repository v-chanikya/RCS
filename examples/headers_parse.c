#include <stdio.h>

#include "header_handler.h"
char header_test_data[512] = "GET /root/my HTTP/1.1\n\
Accept: text/json\n\
Content-Length: 245\n\
Special-head: special-dat\n\n";

void main(){
	request_t req;
	int ret_val = parse_header(header_test_data, &req);
	printf("url is %s\n",req.url);
	printf("first : %s\n",req.headers[0]->header_data);
	printf("second : %s\n",req.headers[1]->header_data);
	return;
}
