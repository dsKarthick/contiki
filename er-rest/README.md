A Quick Introduction to the Erbium (Er) REST Engine
===================================================

EXAMPLE FILES
-------------

- er-server.c: A RESTful server simulating a single parking node.
- er-server-p.c: A RESTful server simulating a private parking node.

- er-client1.c: A CoAP client that polls the parking node.
- er-client2.c: A CoAP client that polls the parking node.
- er-client3.c: A CoAP client that polls the parking node.

PRELIMINARIES
-------------

- Make sure rpl-border-router has the same stack and fits into mote memory:
  You can disable RDC in border-router project-conf.h (not really required as BR keeps radio turned on).
    #undef NETSTACK_CONF_RDC
    #define NETSTACK_CONF_RDC     nullrdc_driver
- For convenience, define the Cooja addresses in /etc/hosts
      aaaa::0212:7401:0001:0101 cooja1
      aaaa::0212:7402:0002:0202 cooja2
      ...
- Get the Copper (Cu) CoAP user-agent from
  [https://addons.mozilla.org/en-US/firefox/addon/copper-270430](https://addons.mozilla.org/en-US/firefox/addon/copper-270430)
- Optional: Save your target as default target
      make TARGET=sky savetarget

COOJA HOWTO
-----------

###Server only:

    make TARGET=cooja sim.csc

Open new terminal

    make connect-router-cooja


###With client:

    make TARGET=cooja sim.csc

Open new terminal

    make connect-router-cooja

DETAILS
-------

Erbium currently implements draft 13.  Central features are commented in
er-example-server.c.  In general, apps/er-coap-13 supports:

- All draft 13 header options
- CON Retransmissions (note COAP_MAX_OPEN_TRANSACTIONS)
- Blockwise Transfers (note REST_MAX_CHUNK_SIZE, see er-plugtest-server.c for
  Block1 uploads)
- Separate Responses (no rest_set_pre_handler() required anymore, note
  coap_separate_accept(), _reject(), and _resume())
- Resource Discovery
- Observing Resources (see EVENT_ and PRERIODIC_RESOURCE, note
  COAP_MAX_OBSERVERS)

REST IMPLEMENTATIONS
--------------------

The Makefile uses WITH_COAP to configure different implementations for the
Erbium (Er) REST Engine.

- WITH_COAP=13 uses Erbium CoAP 13 apps/er-coap-13/.  The default port for
  coap-13 is 5683.
- WITH_COAP=12 uses Erbium CoAP 12 apps/er-coap-12/.  The default port for
  coap-12 is 5683.
- WITH_COAP=7 uses Erbium CoAP 08 apps/er-coap-07/.  The default port for
  coap-07/-08 is 5683.
- WITH_COAP=3 uses Erbium CoAP 03 apps/er-coap-03/.  The default port for
  coap-03 is 61616.  er-coap-03 produces some warnings, as it not fully
  maintained anymore.
- WITH_COAP=0 is a stub to link an Erbium HTTP engine that uses the same
  resource abstraction (REST.x() functions and RESOURCE macros.
