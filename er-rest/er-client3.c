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

  uip_ip6addr(&server_ipaddrs[0], 0xfe80, 0, 0, 0, 0x0212, 0x743f, 0x003f, 0x3f3f);

  uip_ip6addr(&server_ipaddrs[1], 0xfe80, 0, 0, 0, 0x0212, 0x7440, 0x0040, 0x4040);
  uip_ip6addr(&server_ipaddrs[2], 0xfe80, 0, 0, 0, 0x0212, 0x7441, 0x0041, 0x4141);
  uip_ip6addr(&server_ipaddrs[3], 0xfe80, 0, 0, 0, 0x0212, 0x7442, 0x0042, 0x4242);
  uip_ip6addr(&server_ipaddrs[4], 0xfe80, 0, 0, 0, 0x0212, 0x7443, 0x0043, 0x4343);
  uip_ip6addr(&server_ipaddrs[5], 0xfe80, 0, 0, 0, 0x0212, 0x7444, 0x0044, 0x4444);
  uip_ip6addr(&server_ipaddrs[6], 0xfe80, 0, 0, 0, 0x0212, 0x7445, 0x0045, 0x4545);
  uip_ip6addr(&server_ipaddrs[7], 0xfe80, 0, 0, 0, 0x0212, 0x7446, 0x0046, 0x4646);
  uip_ip6addr(&server_ipaddrs[8], 0xfe80, 0, 0, 0, 0x0212, 0x7447, 0x0047, 0x4747);
  uip_ip6addr(&server_ipaddrs[9], 0xfe80, 0, 0, 0, 0x0212, 0x7448, 0x0048, 0x4848);
  uip_ip6addr(&server_ipaddrs[10], 0xfe80, 0, 0, 0, 0x0212, 0x7449, 0x0049, 0x4949);
  uip_ip6addr(&server_ipaddrs[11], 0xfe80, 0, 0, 0, 0x0212, 0x744a, 0x004a, 0x4a4a);
  uip_ip6addr(&server_ipaddrs[12], 0xfe80, 0, 0, 0, 0x0212, 0x744b, 0x004b, 0x4b4b);
  uip_ip6addr(&server_ipaddrs[13], 0xfe80, 0, 0, 0, 0x0212, 0x744c, 0x004c, 0x4c4c);
  uip_ip6addr(&server_ipaddrs[14], 0xfe80, 0, 0, 0, 0x0212, 0x744d, 0x004d, 0x4d4d);
  uip_ip6addr(&server_ipaddrs[15], 0xfe80, 0, 0, 0, 0x0212, 0x744e, 0x004e, 0x4e4e);
  uip_ip6addr(&server_ipaddrs[16], 0xfe80, 0, 0, 0, 0x0212, 0x744f, 0x004f, 0x4f4f);

  uip_ip6addr(&server_ipaddrs[17], 0xfe80, 0, 0, 0, 0x0212, 0x7450, 0x0050, 0x5050);
  uip_ip6addr(&server_ipaddrs[18], 0xfe80, 0, 0, 0, 0x0212, 0x7451, 0x0051, 0x5151);
  uip_ip6addr(&server_ipaddrs[19], 0xfe80, 0, 0, 0, 0x0212, 0x7452, 0x0052, 0x5252);
  uip_ip6addr(&server_ipaddrs[20], 0xfe80, 0, 0, 0, 0x0212, 0x7453, 0x0053, 0x5353);
  uip_ip6addr(&server_ipaddrs[21], 0xfe80, 0, 0, 0, 0x0212, 0x7454, 0x0054, 0x5454);
  uip_ip6addr(&server_ipaddrs[22], 0xfe80, 0, 0, 0, 0x0212, 0x7455, 0x0055, 0x5555);
  uip_ip6addr(&server_ipaddrs[23], 0xfe80, 0, 0, 0, 0x0212, 0x7456, 0x0056, 0x5656);


  etimer_set(&et, 2*CLOCK_SECOND);

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