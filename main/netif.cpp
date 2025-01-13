#include <iostream>

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "netif.h"

static const char* TAG = "WiFi";

void netif::netifHandlerFunction(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

        char ip_str[16]; // Buffer to hold the IP address as a string
        esp_ip4addr_ntoa(&event->ip_info.ip, ip_str, sizeof(ip_str));

        ESP_LOGI(TAG, "Connected! IP Address: %s", ip_str);
    }
}

bool netif::init( )
{
    std::cout << "Netif initialization"<< std::endl;

    ESP_ERROR_CHECK(esp_netif_init());
    esp_netif_create_default_wifi_sta();

    return true;
}

void* netif::getNetIfHandlerAddress()
{
    return (void *)(&netif::netifHandlerFunction);
}

bool netif_user::init( )
{
    std::cout << "Netif user defined initialization" << std::endl;

    return true;
}
