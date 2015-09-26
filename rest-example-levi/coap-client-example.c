#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "rest.h"
#include "buffer.h"

// Este sera el nodo recolector encargado de guardar los datos que recibe

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#define PRINT6ADDR(addr) PRINTF("%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#define PRINTLLADDR(lladdr) PRINTF(" %02x:%02x:%02x:%02x:%02x:%02x ",(lladdr)->addr[0], (lladdr)->addr[1], (lladdr)->addr[2], (lladdr)->addr[3],(lladdr)->addr[4], (lladdr)->addr[5])
#else
#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)
#endif

#define LOCAL_PORT 61617
#define REMOTE_PORT 61616

char temp[100];
int xact_id;

static uip_ipaddr_t server_ips[3];
static struct uip_udp_conn* client_connections[3];

static struct etimer et;
#define MAX_PAYLOAD_LEN   100

#define NUMBER_OF_URLS 1
char* service_urls[NUMBER_OF_URLS] = {"status"};

static void
response_handler(coap_packet_t* response)
{
  uint16_t payload_len = 0;
  uint8_t* payload = NULL;
  payload_len = coap_get_payload(response, &payload);

  PRINTF("Response transaction id: %u", response->tid);
  if (payload) {
    memcpy(temp, payload, payload_len);
    temp[payload_len] = 0;
    PRINTF(" payload: %s\n", temp);
  }
}

static void
send_data(struct uip_udp_conn* client_conn)
{
  char buf[MAX_PAYLOAD_LEN];

  if (init_buffer(COAP_DATA_BUFF_SIZE)) {
    int data_size = 0;
    int service_id = random_rand() % NUMBER_OF_URLS;
    coap_packet_t* request = (coap_packet_t*)allocate_buffer(sizeof(coap_packet_t));
    init_packet(request);

    coap_set_method(request, COAP_GET);
    request->tid = xact_id++;
    request->type = MESSAGE_TYPE_CON;
    coap_set_header_uri(request, service_urls[service_id]);

    data_size = serialize_packet(request, buf);

    PRINTF("Client sending request to:[");
    PRINT6ADDR(&client_conn->ripaddr);
    PRINTF("]:%u/%s\n", (uint16_t)REMOTE_PORT, service_urls[service_id]);

    uip_udp_packet_send(client_conn, buf, data_size);

    delete_buffer();
  }
}

static void
handle_incoming_data()
{
  PRINTF("Incoming packet size: %u \n", (uint16_t)uip_datalen());
  if (init_buffer(COAP_DATA_BUFF_SIZE)) {
    if (uip_newdata()) {
      coap_packet_t* response = (coap_packet_t*)allocate_buffer(sizeof(coap_packet_t));
      if (response) {
        parse_message(response, uip_appdata, uip_datalen());
        response_handler(response);
      }
    }
    delete_buffer();
  }
}

PROCESS(coap_client_example, "COAP Client Example");
AUTOSTART_PROCESSES(&coap_client_example);

PROCESS_THREAD(coap_client_example, ev, data)
{
  PROCESS_BEGIN();

  uip_ip6addr(&server_ips[0], 0xfe80, 0, 0, 0, 0x0212, 0x7403, 0x0003, 0x0303);
  uip_ip6addr(&server_ips[1], 0xfe80, 0, 0, 0, 0x0212, 0x7404, 0x0004, 0x0404);
  uip_ip6addr(&server_ips[2], 0xfe80, 0, 0, 0, 0x0212, 0x7405, 0x0005, 0x0505);

  int iter;
  for (iter = 0; iter < 3; iter++)
  {
    /* new connections with server */
    client_connections[iter] = udp_new(&server_ips[iter], UIP_HTONS(REMOTE_PORT), NULL);
    udp_bind(client_connections[iter], UIP_HTONS(LOCAL_PORT));
  }

  etimer_set(&et, 15 * CLOCK_SECOND);
  while(1) {
    PROCESS_YIELD();
    if (etimer_expired(&et)) {
      PRINTF("Estamos enviando\n");
      for (iter = 0; iter < 3; iter++) {
        send_data(client_connections[iter]);
      }

      etimer_reset(&et);
    }
    // else {
    //   if (ev == tcpip_event) {
    //     handle_incoming_data();
    //   }
    // }
  }

  PROCESS_END();
}
