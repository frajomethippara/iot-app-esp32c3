#include <iostream>

extern "C" {
    #include "esp_wifi.h"
    

    #include "nvs_flash.h"
    #include "esp_log.h"
}

#include "wifi.h"

static const char* WIFI_TAG = "WiFi";

void wifi::wifiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGI(WIFI_TAG, "Disconnected from Wi-Fi, retrying...");
        esp_wifi_connect();
    }
}

wifi::wifi()
{
}

wifi* wifi::getInstance()
{
    static wifi singleton_wifi_ins;
    return &singleton_wifi_ins;
}

bool wifi::init( )
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    return true;
}

bool wifi::connect(char *wifi_ssid, char *wifi_pass)
{    
    wifi_config_t wifi_config = {};

    std::strncpy((char*)wifi_config.sta.ssid, wifi_ssid, sizeof(wifi_config.sta.ssid) - 1);
    std::strncpy((char*)wifi_config.sta.password, wifi_pass, sizeof(wifi_config.sta.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    return true;
}

void* wifi::getWifiHandlerAddress()
{
    printf("Wifi Handler Address in class:%p\n", (void*)(&wifi::wifiEventHandler));
    return (void*)(&wifi::wifiEventHandler);
}

bool wifi::disconnect()
{
    return true;
}