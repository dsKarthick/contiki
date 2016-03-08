
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "rest.h"

/* Resources are defined by RESOURCE macro, signature: resource name, the http methods it handles and its url*/
RESOURCE(status, METHOD_GET, "status");

/* For each resource defined, there corresponds an handler method which should be defined too.
 * Name of the handler method should be [resource name]_handler
 * */
void
status_handler(REQUEST* request, RESPONSE* response)
{
	const char *status;
  if ((random_rand() % 20) == 0){
  	status = "{status:1}\n";
  } else {
  	status = "{status:0}\n";
  }

  rest_set_header_content_type(response, APPLICATION_JSON);
  rest_set_response_payload(response, status, strlen(status));
}


PROCESS(rest_server_example, "Rest Server Example");
AUTOSTART_PROCESSES(&rest_server_example);

PROCESS_THREAD(rest_server_example, ev, data)
{
  PROCESS_BEGIN();

  printf("HTTP Server\n");

  rest_init();

  rest_activate_resource(&resource_status);

  PROCESS_END();
}