REST example
============

Open a terminal and go to "<CONTIKI_HOME>/examples/rest-example-levi/" directory.

MAIN EXAMPLE: rest-server-example.c : A RESTful server example showing how to
use the REST layer to develop server-side applications (possible to run it over
either COAP or HTTP) To use COAP as the underlying application protocol, one
should define WITH_COAP = 1 in rest-example/Makefile. Otherwise, HTTP is used.
Look at the source code to see which resources are available. (check the
RESOURCE macros in the code).  Each resource has a handler function which is
called by the REST layer to serve the request.  (i.e. "status" resource has
a handler function named "status_handler" which is called when a web
service request is received for "status" resource.)


To run REST examples in COOJA on Linux
--------------------------------------------

Accessing the server from outside:

1. Start COOJA and load the simulation "rest-server-example.csc" by the following command.

        make TARGET=cooja coap-client-server-example.csc

coap-client-server-example.csc : Runs rest-server-example.c as the server (over
COAP) (IP:aaaa::0212:7401:0003:0303 and IP:aaaa::0212:7401:0004:0404) in two nodes
and coap-client-example.c as the client (IP: aaaa::0212:7402:0002:0202) in another
node.  Client periodically accesses resources of server (only to one server/node because
the server ip is hard coded in coap-client-example.c SERVER_NODE) and prints the payload.

2. After loading the COOJA file, open another another terminal pointing to the
   same directory and connect to the COOJA simulation using tunslip6:

        make connect-router-cooja

3. Start the simulation in COOJA