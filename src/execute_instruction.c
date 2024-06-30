/*
** Julien ROIRON, 2023
** execute_instructions.c
** File description:
** Functions to execute instructions and send response.
*/
#include "pico_net_boot.h"
#include "instructions.h"

/// @brief Function called when start instruction is requested.
///
/// @param tpcb The TCP protocol control block.
static void start(struct tcp_pcb PTR tpcb)
{
    gpio_put(CONTROL_PIN, 1);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(200);
    gpio_put(CONTROL_PIN, 0);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    tcp_write(tpcb, "OK\n", 3, TCP_WRITE_FLAG_COPY);
}

/// @brief Function called when power off instruction is requested.
///
/// @param tpcb The TCP protocol control block.
static void power_off(struct tcp_pcb PTR tpcb)
{
    gpio_put(CONTROL_PIN, 1);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(5000);
    gpio_put(CONTROL_PIN, 0);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    tcp_write(tpcb, "OK\n", 3, TCP_WRITE_FLAG_COPY);
}

/// @brief Function called when reboot instruction is requested.
///
/// @param tpcb The TCP protocol control block.
static void reboot(struct tcp_pcb PTR tpcb)
{
    gpio_put(CONTROL_PIN, 1);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(5000);
    gpio_put(CONTROL_PIN, 0);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(1000);
    gpio_put(CONTROL_PIN, 1);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(200);
    gpio_put(CONTROL_PIN, 0);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    tcp_write(tpcb, "OK\n", 3, TCP_WRITE_FLAG_COPY);
}

/// @brief Function called when an unknown instruction is requested.
///
/// @param tpcb The TCP protocol control block.
static void unrecognized_instruction(struct tcp_pcb PTR tpcb)
{
    tcp_write(tpcb, "KO\n", 3, TCP_WRITE_FLAG_COPY);
}

/// @brief Function pointer array with every available instructions.
static instruction_t instructions[] = {
    start, power_off, reboot, unrecognized_instruction
};

void execute_instruction(struct tcp_pcb PTR tpcb, const char ARRAY buffer)
{
    instruction_command_t instruction;

    get_instruction_from_buffer(buffer, &instruction);
    return instructions[instruction](tpcb);
}
