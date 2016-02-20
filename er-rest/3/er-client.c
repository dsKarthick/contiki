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

  uip_ip6addr(&server_ipaddrs[0], 0xfe80, 0, 0, 0, 0x0212, 0x7421, 0x0021, 0x2121);
  uip_ip6addr(&server_ipaddrs[1], 0xfe80, 0, 0, 0, 0x0212, 0x7422, 0x0022, 0x2222);
  uip_ip6addr(&server_ipaddrs[2], 0xfe80, 0, 0, 0, 0x0212, 0x7423, 0x0023, 0x2323);
  uip_ip6addr(&server_ipaddrs[3], 0xfe80, 0, 0, 0, 0x0212, 0x7424, 0x0024, 0x2424);
  uip_ip6addr(&server_ipaddrs[4], 0xfe80, 0, 0, 0, 0x0212, 0x7425, 0x0025, 0x2525);
  uip_ip6addr(&server_ipaddrs[5], 0xfe80, 0, 0, 0, 0x0212, 0x7426, 0x0026, 0x2626);
  uip_ip6addr(&server_ipaddrs[6], 0xfe80, 0, 0, 0, 0x0212, 0x7427, 0x0027, 0x2727);
  uip_ip6addr(&server_ipaddrs[7], 0xfe80, 0, 0, 0, 0x0212, 0x7428, 0x0028, 0x2828);
  uip_ip6addr(&server_ipaddrs[8], 0xfe80, 0, 0, 0, 0x0212, 0x7429, 0x0029, 0x2929);
  uip_ip6addr(&server_ipaddrs[9], 0xfe80, 0, 0, 0, 0x0212, 0x742a, 0x002a, 0x2a2a);
  uip_ip6addr(&server_ipaddrs[10], 0xfe80, 0, 0, 0, 0x0212, 0x742b, 0x002b, 0x2b2b);
  uip_ip6addr(&server_ipaddrs[11], 0xfe80, 0, 0, 0, 0x0212, 0x742c, 0x002c, 0x2c2c);
  uip_ip6addr(&server_ipaddrs[12], 0xfe80, 0, 0, 0, 0x0212, 0x742d, 0x002d, 0x2d2d);
  uip_ip6addr(&server_ipaddrs[13], 0xfe80, 0, 0, 0, 0x0212, 0x742e, 0x002e, 0x2e2e);
  uip_ip6addr(&server_ipaddrs[14], 0xfe80, 0, 0, 0, 0x0212, 0x742f, 0x002f, 0x2f2f);

  uip_ip6addr(&server_ipaddrs[15], 0xfe80, 0, 0, 0, 0x0212, 0x7430, 0x0030, 0x3030);
  uip_ip6addr(&server_ipaddrs[16], 0xfe80, 0, 0, 0, 0x0212, 0x7431, 0x0031, 0x3131);
  uip_ip6addr(&server_ipaddrs[17], 0xfe80, 0, 0, 0, 0x0212, 0x7432, 0x0032, 0x3232);
  uip_ip6addr(&server_ipaddrs[18], 0xfe80, 0, 0, 0, 0x0212, 0x7433, 0x0033, 0x3333);
  uip_ip6addr(&server_ipaddrs[19], 0xfe80, 0, 0, 0, 0x0212, 0x7434, 0x0034, 0x3434);
  uip_ip6addr(&server_ipaddrs[20], 0xfe80, 0, 0, 0, 0x0212, 0x7435, 0x0035, 0x3535);
  uip_ip6addr(&server_ipaddrs[21], 0xfe80, 0, 0, 0, 0x0212, 0x7436, 0x0036, 0x3636);
  uip_ip6addr(&server_ipaddrs[22], 0xfe80, 0, 0, 0, 0x0212, 0x7437, 0x0037, 0x3737);
  uip_ip6addr(&server_ipaddrs[23], 0xfe80, 0, 0, 0, 0x0212, 0x7438, 0x0038, 0x3838);

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