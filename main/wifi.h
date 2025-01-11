#include <cstring>

#include "esp_event.h"

class wifi{
    private:
        wifi();
        // EventGroupHandle_t *wifi_event_group;

    public:
        static void wifiEventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

        static wifi* getInstance();

        bool init();
        bool connect(char *, char *);
        bool disconnect();

        void *getWifiHandlerAddress();
};