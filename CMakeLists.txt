# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

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
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(BitDogLab_Interrupts C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Automatically gather all source files from src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# Add executable using the gathered source files and BitDogLab_Interrupts.c
add_executable(BitDogLab_Interrupts ${SRC_FILES} ${CMAKE_SOURCE_DIR}/BitDogLab_Interrupts.c)

pico_set_program_name(BitDogLab_Interrupts "BitDogLab_Interrupts")
pico_set_program_version(BitDogLab_Interrupts "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(BitDogLab_Interrupts 1)
pico_enable_stdio_usb(BitDogLab_Interrupts 1)

pico_generate_pio_header(BitDogLab_Interrupts ${CMAKE_CURRENT_LIST_DIR}/src/pio_matrix.pio)

# Add the standard library to the build
target_link_libraries(BitDogLab_Interrupts
        pico_stdlib
        hardware_pio
	    hardware_adc
        pico_bootrom)

# Add the standard include files to the build
target_include_directories(BitDogLab_Interrupts PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries
target_link_libraries(BitDogLab_Interrupts 
        
        )

pico_add_extra_outputs(BitDogLab_Interrupts)

