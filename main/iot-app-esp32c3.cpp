#include <iostream>
#include <cstring>
extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    // #include "esp_system.h"

    #include "esp_wifi.h"
    #include "esp_event.h"

    #include "nvs_flash.h"
    #include "esp_log.h"

    
}

#include "wifi.h"

#include "esp_log.h"
static const char* TAG = "WiFi";

static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0; // Define the connection bit flag

extern "C" void ip_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {

        // ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        // ESP_LOGI(TAG, "Connected! IP Address: %s", esp_ip4addr_ntoa(&event->ip_info.ip));
        // xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);

        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

        char ip_str[16]; // Buffer to hold the IP address as a string
        esp_ip4addr_ntoa(&event->ip_info.ip, ip_str, sizeof(ip_str));

        ESP_LOGI(TAG, "Connected! IP Address: %s", ip_str);
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        std::cout << "IP address printed from ip instance"<< std::endl;
    }
}

extern "C" void app_main() {

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGI(TAG, "NVS initialized");

    /* Setting up wifi */
    ESP_LOGI(TAG, "Initializing Wi-Fi...");
    wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
        (esp_event_handler_t)wifi::getInstance()->getWifiHandlerAddress(), NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL, NULL));

    ESP_ERROR_CHECK(esp_netif_init());
    
    esp_netif_create_default_wifi_sta();

    wifi::getInstance()->init();
    wifi::getInstance()->connect("Pixel 4a", "123456789");

    ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    ESP_LOGI(TAG, "Wi-Fi connected successfully!");


    // Example: Pause the program to allow observation
    while (true) {

        std::cout<<"End of program"<<std::endl;
        
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
    }
}