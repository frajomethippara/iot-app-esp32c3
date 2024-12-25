#include <iostream>


extern "C" {
    // #include "freertos/FreeRTOS.h"
    // #include "freertos/task.h"
    // #include "esp_system.h"

    #include "esp_wifi.h"
    #include "esp_event.h"

    #include "nvs_flash.h"
    #include "esp_log.h"
}

#include "wifi.h"

static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0; // Define the connection bit flag
static const char* TAG = "WiFi";

#define WIFI_SSID      "Pixel 4a"
#define WIFI_PASSWORD  "123456789"

// Event handler for Wi-Fi events
extern "C" void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGI(TAG, "Disconnected from Wi-Fi, retrying...");
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {

        // ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        // ESP_LOGI(TAG, "Connected! IP Address: %s", esp_ip4addr_ntoa(&event->ip_info.ip));
        // xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);

        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

        char ip_str[16]; // Buffer to hold the IP address as a string
        esp_ip4addr_ntoa(&event->ip_info.ip, ip_str, sizeof(ip_str));

        ESP_LOGI(TAG, "Connected! IP Address: %s", ip_str);
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

wifi::wifi()
{
    std::cout<<"Singleton constructor is called and the class is invoked"<<std::endl;
}

wifi* wifi::getInstance()
{
    static wifi singleton_wifi_ins;
    return &singleton_wifi_ins;
}

bool wifi::init()
{
    // ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_LOGI(TAG, "NVS initialized");

    /* Setting up wifi */
    ESP_LOGI(TAG, "Initializing Wi-Fi...");
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {};
    std::strncpy((char*)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
    std::strncpy((char*)wifi_config.sta.password, WIFI_PASSWORD, sizeof(wifi_config.sta.password));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    ESP_LOGI(TAG, "Wi-Fi connected successfully!");

    return true;
}

bool wifi::connect(char *wifi_ssid, char *wifi_pass)
{    
    // ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_LOGI(TAG, "NVS initialized");

    // /* Setting up wifi */
    // ESP_LOGI(TAG, "Initializing Wi-Fi...");
    // wifi_event_group = xEventGroupCreate();

    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());
    // esp_netif_create_default_wifi_sta();

    // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    // ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    // wifi_config_t wifi_config = {};
    // std::strncpy((char*)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
    // std::strncpy((char*)wifi_config.sta.password, WIFI_PASSWORD, sizeof(wifi_config.sta.password));

    // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    // ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    // ESP_ERROR_CHECK(esp_wifi_start());

    // ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
    // xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    // ESP_LOGI(TAG, "Wi-Fi connected successfully!");

    return true;
}

bool wifi::disconnect()
{
    return true;
}

void wifi::print()
{
    std::cout << "Hello. After Constructor is called, print function is invoked!!!!!!"<< std::endl;
}



