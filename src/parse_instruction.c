/*
** EPITECH PROJECT, 2024
** parse_instruction.c
** File description:
** Functions used to parse instruction.
*/
#include <string.h>

#include "style/pointer.h"
#include "instructions.h"

void get_instruction_from_buffer(const char ARRAY buffer,
    instruction_command_t PTR instruction)
{
    if (strncmp(buffer, "START", 5) == 0) {
        *instruction = START_INSTRUCTION;
    } else if (strncmp(buffer, "POWER-OFF", 9) == 0) {
        *instruction = POWER_OFF_INSTRUCTION;
    } else if (strncmp(buffer, "REBOOT", 6) == 0) {
        *instruction = REBOOT_INSTRUCTION;
    } else
        *instruction = UNKNOWN_INSTRUCTION;
}
