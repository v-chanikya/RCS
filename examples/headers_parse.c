#include <stdio.h>

#include "header_handler.h"
#include "rcs.h"

char header_test_data[512] = "GET /root/my HTTP/1.1\n\
Accept: text/json\n\
Content-Length: 245\n\
Special-head: special-dat\n\n";

void main(){
	request_t req = {0};
	int ret_val = parse_header(header_test_data, &req);
	rct_req_print(&req);
	return;
}
