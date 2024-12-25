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

class HelloWorld {
public:
    void say_hello() {
        std::cout << "Hello, World from C++!" << std::endl;
        
    }
};

#include "wifi.h"

#include "esp_log.h"
static const char* TAG = "WiFi";

extern "C" void app_main() {
    HelloWorld hello;
    hello.say_hello();

    //Initialize NVS
    // esp_err_t ret_res = nvs_flash_init();
    // if( ESP_ERR_NVS_NO_FREE_PAGES == ret_res || ESP_ERR_NVS_NEW_VERSION_FOUND == ret_res )
    // {
    //     ESP_ERROR_CHECK(nvs_flash_erase())
    //     ret_res = nvs_flash_init();
    // }

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_LOGI(TAG, "NVS initialized");

    wifi::getInstance()->init();
    wifi::getInstance()->connect("pixel 4a", "123456789");

    // Example: Pause the program to allow observation
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
    }
}