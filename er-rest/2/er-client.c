#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contiki.h"
#include "contiki-net.h"

#include "dev/button-sensor.h"

#if WITH_COAP == 3
#include "er-coap-03-engine.h"
#elif WITH_COAP == 6
#include "er-coap-06-engine.h"
#elif WITH_COAP == 7
#include "er-coap-07-engine.h"
#elif WITH_COAP == 12
#include "er-coap-12-engine.h"
#elif WITH_COAP == 13
#include "er-coap-13-engine.h"
#else
#error "CoAP version defined by WITH_COAP not implemented"
#endif

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINT6ADDR(addr) PRINTF("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF("[%02x:%02x:%02x:%02x:%02x:%02x]",(lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3],(lladdr)->addr[4], (lladdr)->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

#define LOCAL_PORT      UIP_HTONS(COAP_DEFAULT_PORT+1)
#define REMOTE_PORT     UIP_HTONS(COAP_DEFAULT_PORT)

#define SERVERS_NUMBER 24
#define NUMBER_OF_URLS 1

static uip_ipaddr_t server_ipaddrs[SERVERS_NUMBER];
static struct etimer et;
static process_event_t event_data_ready;

char* service_urls[NUMBER_OF_URLS] = {"status"};

/* This function is will be passed to COAP_BLOCKING_REQUEST() to handle responses. */
void client_chunk_handler(void *response)
{
  const uint8_t *chunk;

  int len = coap_get_payload(response, &chunk);
  //printf("|%.*s\n", len, (char *)chunk);
  PRINTF("%.*s", len, (char *)chunk);
}

PROCESS(loop_client, "Lopp for the Client");
PROCESS(coap_client_example, "COAP Client");

AUTOSTART_PROCESSES(&loop_client, &coap_client_example);

PROCESS_THREAD(loop_client, ev, data)
{
  static int count = 0;
  PROCESS_BEGIN();

  event_data_ready = process_alloc_event();

  uip_ip6addr(&server_ipaddrs[0], 0xaaaa, 0, 0, 0, 0x0212, 0x7403, 0x0003, 0x0303);
  uip_ip6addr(&server_ipaddrs[1], 0xaaaa, 0, 0, 0, 0x0212, 0x7404, 0x0004, 0x0404);
  uip_ip6addr(&server_ipaddrs[2], 0xaaaa, 0, 0, 0, 0x0212, 0x7405, 0x0005, 0x0505);
  uip_ip6addr(&server_ipaddrs[3], 0xaaaa, 0, 0, 0, 0x0212, 0x7406, 0x0006, 0x0606);
  uip_ip6addr(&server_ipaddrs[4], 0xaaaa, 0, 0, 0, 0x0212, 0x7407, 0x0007, 0x0707);
  uip_ip6addr(&server_ipaddrs[5], 0xaaaa, 0, 0, 0, 0x0212, 0x7408, 0x0008, 0x0808);
  uip_ip6addr(&server_ipaddrs[6], 0xaaaa, 0, 0, 0, 0x0212, 0x7409, 0x0009, 0x0909);
  uip_ip6addr(&server_ipaddrs[7], 0xaaaa, 0, 0, 0, 0x0212, 0x740a, 0x000a, 0x0a0a);
  uip_ip6addr(&server_ipaddrs[8], 0xaaaa, 0, 0, 0, 0x0212, 0x740b, 0x000b, 0x0b0b);
  uip_ip6addr(&server_ipaddrs[9], 0xaaaa, 0, 0, 0, 0x0212, 0x740c, 0x000c, 0x0c0c);
  uip_ip6addr(&server_ipaddrs[10], 0xaaaa, 0, 0, 0, 0x0212, 0x740d, 0x000d, 0x0d0d);
  uip_ip6addr(&server_ipaddrs[11], 0xaaaa, 0, 0, 0, 0x0212, 0x740e, 0x000e, 0x0e0e);
  uip_ip6addr(&server_ipaddrs[12], 0xaaaa, 0, 0, 0, 0x0212, 0x740f, 0x000f, 0x0f0f);

  uip_ip6addr(&server_ipaddrs[13], 0xaaaa, 0, 0, 0, 0x0212, 0x7410, 0x0010, 0x1010);
  uip_ip6addr(&server_ipaddrs[14], 0xaaaa, 0, 0, 0, 0x0212, 0x7411, 0x0011, 0x1111);
  uip_ip6addr(&server_ipaddrs[15], 0xaaaa, 0, 0, 0, 0x0212, 0x7412, 0x0012, 0x1212);
  uip_ip6addr(&server_ipaddrs[16], 0xaaaa, 0, 0, 0, 0x0212, 0x7413, 0x0013, 0x1313);
  uip_ip6addr(&server_ipaddrs[17], 0xaaaa, 0, 0, 0, 0x0212, 0x7414, 0x0014, 0x1414);
  uip_ip6addr(&server_ipaddrs[18], 0xaaaa, 0, 0, 0, 0x0212, 0x7415, 0x0015, 0x1515);
  uip_ip6addr(&server_ipaddrs[19], 0xaaaa, 0, 0, 0, 0x0212, 0x7416, 0x0016, 0x1617);
  uip_ip6addr(&server_ipaddrs[20], 0xaaaa, 0, 0, 0, 0x0212, 0x7417, 0x0017, 0x1717);
  uip_ip6addr(&server_ipaddrs[21], 0xaaaa, 0, 0, 0, 0x0212, 0x7418, 0x0018, 0x1818);
  uip_ip6addr(&server_ipaddrs[22], 0xaaaa, 0, 0, 0, 0x0212, 0x7419, 0x0019, 0x1919);
  uip_ip6addr(&server_ipaddrs[23], 0xaaaa, 0, 0, 0, 0x0212, 0x741a, 0x001a, 0x1a1a);

  etimer_set(&et, 15*CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

    process_post(&coap_client_example, event_data_ready, &server_ipaddrs[count % SERVERS_NUMBER]);

    count ++;
    etimer_reset(&et);
  }

  PROCESS_END();
}

PROCESS_THREAD(coap_client_example, ev, server_ipaddr)
{
  PROCESS_BEGIN();

  static coap_packet_t request[1]; /* This way the packet can be treated as pointer as usual. */

  /* receives all CoAP messages */
  coap_receiver_init();

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == event_data_ready);

    /* prepare request, TID is set by COAP_BLOCKING_REQUEST() */
    coap_init_message(request, COAP_TYPE_CON, COAP_GET, 0 );
    coap_set_header_uri_path(request, service_urls[0]);


    PRINTF("\nINFO");
    PRINTF("|");
    PRINT6ADDR(server_ipaddr);
    PRINTF("|");

    COAP_BLOCKING_REQUEST(server_ipaddr, REMOTE_PORT, request, client_chunk_handler);
  }

  PROCESS_END();
}