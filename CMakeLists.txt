cmake_minimum_required(VERSION 3.29)

# Set network SSID and password
set(SSID "Network Name")
set(PASSWORD "Network Password")
set(SOCKET_PORT 6969)

# Pass the variable to the C code
add_compile_definitions(SSID="${SSID}")
add_compile_definitions(PASSWORD="${PASSWORD}")
add_compile_definitions(SOCKET_PORT="${SOCKET_PORT}")

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
set(PICO_SDK_PATH /path/to/pico-sdk)
set(PICO_BOARD pico_w)
set(LWIP_DIR ${PICO_SDK_PATH}/lib/lwip)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)
include_directories(include)

set(CMAKE_BUILD_TYPE Release)

# Project(my_project)
project(PicoNetBoot CXX C ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(PicoNetBoot
    src/main.c
    src/socket_server.c
    src/execute_instruction.c
    src/parse_instruction.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(PicoNetBoot
    pico_stdlib
    pico_cyw43_arch_lwip_poll
)

# Set the compile options.
target_compile_options(PicoNetBoot PRIVATE
    $<$<CONFIG:DEBUG>:-g3>
    $<$<CONFIG:RELEASE>:-Ofast>
)

# USB
pico_enable_stdio_usb(PicoNetBoot 1)
pico_enable_stdio_uart(PicoNetBoot 0)

# Create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(PicoNetBoot)
