####################################################################################################
# @brief    core\ CMake Description
# @details  IDF Progrmming Guide -> Build system -> component CMakeLists.txt 
#
# @warn     adding SRC & SRC_DIRS together not recommended
#
####################################################################################################

# Build Config
idf_component_register(
                       SRC_DIRS
                         "."
                         "../appl"
                         "../lbr"
                         "mcu"
                         "rtos"
                         "system"
                       PRIV_REQUIRES
                         driver
                         esp_timer
                         spi_flash
                       INCLUDE_DIRS
                         "." 
                         "../appl"
                         "../lbr"
                         "mcu"
                         "rtos"
                         "system"
                      )

