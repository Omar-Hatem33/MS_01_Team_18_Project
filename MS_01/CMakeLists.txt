# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set Pico SDK path
set(PICO_SDK_PATH "C:/Users/omar/.pico-sdk/sdk/2.0.0")

# Initialize pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Set the board type
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

project(test3 C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable with source files
add_executable(test3 test3.c mpu6050.c motor_driver.c ir_driver.c)

# Link necessary libraries for pico_w (including Wi-Fi if needed)
target_link_libraries(test3
    pico_stdlib
    hardware_i2c
    hardware_pwm
    hardware_pwm  # Ensure this is required for motor control
)

# Set program name and version
pico_set_program_name(test3 "test3")
pico_set_program_version(test3 "0.1")

# Configure output for UART/USB
pico_enable_stdio_uart(test3 0)
pico_enable_stdio_usb(test3 1)

# Add extra outputs (e.g., UF2 file for flashing)
pico_add_extra_outputs(test3)
