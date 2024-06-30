/*
** Julien ROIRON, 2023
** init_picow.c
** File description:
** Main function of blink web.
*/
#include "../include/pico_net_boot.h"

/// @brief Function which initializes the needed resources.
/// - Initialize the stdio stack.
/// - Initialize the network stack.
/// - Initialize PIN control.
/// - Connect to the Wi-Fi network.
///
/// @return 0 on success, 1 on failure.
int main(void)
{
    stdio_init_all();
    printf("Connection to the network...\n");
    cyw43_arch_init_with_country(CYW43_COUNTRY_FRANCE);
    cyw43_arch_enable_sta_mode();
    gpio_init(CONTROL_PIN);
    gpio_set_dir(CONTROL_PIN, GPIO_OUT);
    if (cyw43_arch_wifi_connect_timeout_ms(SSID, PASSWORD,
    CYW43_AUTH_WPA2_MIXED_PSK, (uint32_t){30000})) {
        printf("Failed to connect\n");
        return 1;
    }
    printf("Connected !\n");
    run_socket_server();
    cyw43_arch_deinit();
    return 0;
}
