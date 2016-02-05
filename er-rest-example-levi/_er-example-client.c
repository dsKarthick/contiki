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
#define PRINT6ADDR(addr) PRINTF("[%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x]", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF("[%02x:%02x:%02x:%02x:%02x:%02x]",(lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3],(lladdr)->addr[4], (lladdr)->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

/* TODO: This server address is hard-coded for Cooja. */
#define SERVER_NODE(ipaddr)   uip_ip6addr(ipaddr, 0xaaaa, 0, 0, 0, 0x0212, 0x7402, 0x0002, 0x0202) /* cooja2 */

#define LOCAL_PORT      UIP_HTONS(COAP_DEFAULT_PORT+1)
#define REMOTE_PORT     UIP_HTONS(COAP_DEFAULT_PORT)

#define TOGGLE_INTERVAL 45

static uip_ipaddr_t server_ipaddrs[3];
static struct etimer et;

/* Example URIs that can be queried. */
#define NUMBER_OF_URLS 1
/* leading and ending slashes only for demo purposes, get cropped automatically when setting the Uri-Path */
char* service_urls[NUMBER_OF_URLS] = {"status"};

/* This function is will be passed to COAP_BLOCKING_REQUEST() to handle responses. */
void
client_chunk_handler(void *response)
{
  const uint8_t *chunk;

  int len = coap_get_payload(response, &chunk);
  printf("|%.*s", len, (char *)chunk);
}

PROCESS(coap_client_example, "COAP Client Example");
AUTOSTART_PROCESSES(&coap_client_example);

PROCESS_THREAD(coap_client_example, ev, data)
{
  PROCESS_BEGIN();

  static coap_packet_t requests[3][1]; /* This way the packet can be treated as pointer as usual. */

  uip_ip6addr(&server_ipaddrs[0], 0xaaaa, 0, 0, 0, 0x0212, 0x7403, 0x0003, 0x0303);
  uip_ip6addr(&server_ipaddrs[1], 0xaaaa, 0, 0, 0, 0x0212, 0x7404, 0x0004, 0x0404);
  uip_ip6addr(&server_ipaddrs[2], 0xaaaa, 0, 0, 0, 0x0212, 0x7405, 0x0005, 0x0505);

  /* receives all CoAP messages */
  coap_receiver_init();

  etimer_set(&et, TOGGLE_INTERVAL * CLOCK_SECOND);

  while(1) {
    PROCESS_YIELD();

    if (etimer_expired(&et)) {

      //Este bucle no funciona, solo se haceuna vez
      static int iter;
      for (iter = 0; iter < 3; iter = iter + 1)
      {
        /* prepare request, TID is set by COAP_BLOCKING_REQUEST() */
        coap_init_message(requests[iter], COAP_TYPE_CON, COAP_GET, 0 );
        coap_set_header_uri_path(requests[iter], service_urls[0]);

        printf("--Requesting %s--\n", service_urls[0]);

        /* new connections with server */
        PRINTF("Direccion %i\n", iter);
        PRINT6ADDR(&server_ipaddrs[iter]);
        PRINTF(" : %u\n", UIP_HTONS(REMOTE_PORT));

        COAP_BLOCKING_REQUEST(&server_ipaddrs[iter], REMOTE_PORT, requests[iter], client_chunk_handler);

        printf("\n--Done--\n");
      }

      etimer_reset(&et);
    }
  }

  PROCESS_END();
}