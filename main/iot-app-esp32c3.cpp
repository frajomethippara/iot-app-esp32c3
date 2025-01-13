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
#include "netif.h"

#include "esp_log.h"
static const char* TAG = "WiFi";

static EventGroupHandle_t wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0; // Define the connection bit flag

extern "C" void app_main() {

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGI(TAG, "NVS initialized");

    /* Setting up wifi */
    ESP_LOGI(TAG, "Initializing Wi-Fi...");
    wifi_event_group = xEventGroupCreate();

    netif *ptr_netif;
    netif ins_netif;
    ptr_netif = &ins_netif;

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
        (esp_event_handler_t)wifi::getInstance()->getWifiHandlerAddress(), NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, 
        (esp_event_handler_t)ptr_netif->getNetIfHandlerAddress(), NULL, NULL));
    
    ptr_netif->init();

    // Runtime polymorphism implemented. Inorder to call derived functions, umcomment below.
    // netif_user ins_netif_ud;  //ud - user defined
    // ptr_netif = &ins_netif_ud;
    // ptr_netif->init();

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