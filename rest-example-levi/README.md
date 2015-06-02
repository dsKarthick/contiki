REST example
============

Open a terminal and go to "<CONTIKI_HOME>/examples/rest-example-levi/" directory.

MAIN EXAMPLE: rest-server-example.c : A RESTful server example showing how to
use the REST layer to develop server-side applications.
Look at the source code to see which resources are available. (check the
RESOURCE macros in the code).  Each resource has a handler function which is
called by the REST layer to serve the request.  (i.e. "helloworld" resource has
a handler function named "helloworld_handler" which is called when a web
service request is received for "helloworld" resource.)


To run REST examples in COOJA on Linux
--------------------------------------------

Accessing the server from outside:

1. Start COOJA and load the simulation "rest-server-example.csc" by the following command.

        make TARGET=cooja rest-server-example.csc

2. After loading the COOJA file, open another another terminal pointing to the
   same directory and connect to the COOJA simulation using tunslip6:

        make connect-router-cooja

3. Start COOJA simulation

4. You need to use a HTTP client to interact with the COOJA nodes
   running REST code.  In this setting, two servers are available: IP addresses
   are aaaa::0212:7402:0002:0202 and aaaa::0212:7403:0003:0303. HTTP uses 8080 
   port in default configuration.  First, ping the COOJA nodes to test the connectivity.

        ping6 aaaa::0212:7402:0002:0202
        ping6 aaaa::0212:7403:0003:0303

HTTP Examples
-------------

You can use curl as an http client to interact with the COOJA motes running
REST code.

    curl -H "User-Agent: curl" aaaa::0212:7402:0002:0202:8080/status #get status plain text

CONSOLE TAB 1
$ cd /home/user/contiki/examples/rest-example-levi
$ make clean && make TARGET=cooja rest-server-example.csc

CONSOLE TAB 2
$ cd /home/user/contiki/examples/rest-example-levi
$ make connect-router-cooja

START COOJA SIMULATION

CONSOLE TAB 3
$ cd /home/user/contiki/examples/rest-example-levi
$ curl -H "User-Agent: curl" aaaa::0212:7403:0003:0303:8080/status -i