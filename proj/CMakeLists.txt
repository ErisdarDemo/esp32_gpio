####################################################################################################
 #  @file     CMakeLists.txt
 #  @brief    Project Description
 #  @details  x
 #
 #  @section    Detail
 #      Standard cmake components for compile
 #
 #  @section    Reference
 #      1. https://github.com/espressif/esp-idf/issues/10568
 #
####################################################################################################
cmake_minimum_required(VERSION 3.16)

# Cmake Source Directories
set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_LIST_DIR}/../core)

# Root Cmake Config 
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# PROJECT_NAME
project(esp32_base)

# BUG [1]
set_source_files_properties(${CMAKE_SOURCE_DIR}/components/esp_lcd/rgb/esp_lcd_panel_rgb.c PROPERTIES HEADER_FILE_ONLY TRUE)