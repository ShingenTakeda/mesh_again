
/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_mesh.h"
#include "esp_mesh_internal.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "driver/uart.h"
#include "esp_system.h"

#include "mpack/mpack.h"
#include <stdbool.h>

#include "utils.h"
#include "mesh_network.h"
#include "uart.h"

#define RX_BUF_SIZE 1024
#define ROUTER_SSID "ValenteTakeda" // SSID da rede Wi-Fi do roteador
#define ROUTER_PWD "ackmakVT96"   // senha da rede Wi-Fi do roteador
#define MESH_AP_PASS "mesh_password"
#define MESH_CHANNEL 6
#define MESH_AP_PASS "mesh_password"

static uint8_t MESH_ID[6] = { 0x12, 0x34, 0x56, 0x78, 0x90, 0x91 }; // endereço MAC da rede mesh (mesh ID)
static const char *DEBUG_TAG_Main = "Debug Main";

static bool is_mesh_connected = false;
static mesh_addr_t mesh_parent_addr;
static int mesh_layer = -1;
static esp_netif_t *netif_sta = NULL;

#define RX_BUF_SIZE 256
#define TX_BUF_SIZE 128

//WiFi router credentials size
#define MAX_SSID_LEN 32  // Comprimento máximo do SSID
#define MAX_PASS_LEN 64  // Comprimento máximo da senha

//extern QueueHandle_t send_message_mesh_q;

void app_main()
{
    // mpack_tree_t mtree;
    // char msgpack_data[] = {0x82, 0xa7, 0x63, 0x6f, 0x6d, 0x70, 0x61, 0x63, 0x74, 0xc3, 
    // 0xa6, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x05};
    // mpack_tree_init_data(&mtree, msgpack_data, 18);
    // mpack_tree_parse(&mtree);
    // mpack_node_t root_node = mpack_tree_root(&mtree);
    
    // bool compact = mpack_node_bool(mpack_node_map_cstr(root_node, "compact"));
    // int schema = mpack_node_i32(mpack_node_map_cstr(root_node, "schema"));
    // size_t root_size = mpack_node_map_count(root_node);

    // printf("compact value %i\n", compact);
    // printf("schema value %i\n", schema);
    // printf("message size value %i\n", root_size);

    // if (mpack_tree_destroy(&mtree) != mpack_ok)
    // {
    //     fprintf(stderr, "An error occurred decoding the data!\n");
    //     return;
    // }

    // mpack_node_map_count(root_node);

    start_uart();
    start_mesh(ROUTER_SSID, ROUTER_PWD, MESH_ID, MESH_AP_PASS);
}