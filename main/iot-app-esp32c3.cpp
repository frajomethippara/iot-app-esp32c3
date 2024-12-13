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

extern "C" void app_main() {
    HelloWorld hello;
    hello.say_hello();

    wifi::getInstance()->init();

    // Example: Pause the program to allow observation
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
    }
}