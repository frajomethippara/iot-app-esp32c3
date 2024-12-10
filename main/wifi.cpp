#include <iostream>
#include "wifi.h"

wifi::wifi()
{
    std::cout<<"Singleton constructor is called and the class is invoked"<<std::endl;
}

wifi* wifi::getInstance()
{
    static wifi singleton_wifi_ins;
    return &singleton_wifi_ins;
}

void wifi::print()
{
    std::cout << "Hello. After Constructor is called, print function is invoked!!!!!!"<< std::endl;
}



