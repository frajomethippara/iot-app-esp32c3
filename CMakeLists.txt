# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(iot-app-esp32c3)

# Add main application executable
add_executable(main_app main/iot-app-esp32c3.cpp)

# Add drivers subdirectory
# add_subdirectory(main/Drivers/wifi)
add_subdirectory(main/Drivers/wifi)

# Link the wifi library to the main executable
target_link_libraries(main_app PRIVATE wifi_driver)