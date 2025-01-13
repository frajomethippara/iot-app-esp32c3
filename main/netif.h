#include "esp_event.h"

class netif
{
private:

public:
    virtual bool init();

    static void netifHandlerFunction(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
    void* getNetIfHandlerAddress();

protected:

};

class netif_user: public netif
{
private:

public:
    bool init();
protected:
};