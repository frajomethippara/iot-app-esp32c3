#include <iostream>
extern "C" {
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    #include "nvs_flash.h"
    #include "esp_log.h"
}

class HelloWorld {
public:
    void say_hello() {
        std::cout << "Hello, World from C++!" << std::endl;
    }
};

extern "C" void app_main() {
    HelloWorld hello;
    hello.say_hello();

    // Example: Pause the program to allow observation
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
    }
}