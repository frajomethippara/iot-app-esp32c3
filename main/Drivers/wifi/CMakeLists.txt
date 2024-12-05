#creates a library target for the wifi module
add_library(wifi_driver wifi.cpp)

#include the directory containing ifi.h in the library's interface
target_include_directories(wifi_driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})