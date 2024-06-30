/*
** EPITECH PROJECT, 2024
** instructions.h
** File description:
** instructions.h.
*/

#pragma once

#include <lwip/tcp.h>

#include "style/common_macros.h"

/// @brief Enumeration representing the different possible instructions.
///
/// @var START_INSTRUCTION Representing the start instruction. (in order to
/// start the computer).
/// @var REBOOT_INSTRUCTION Representing the reboot instruction. (in order to
/// reboot the computer).
/// @var STOP_INSTRUCTION Representing the stop instruction. (in order to
/// shutdown the computer).
/// @var UNKNOWN_INSTRUCTION Representing the unknown instruction. (when an
/// unknown instruction is received).
typedef enum instructions_command_s {
    START_INSTRUCTION,
    POWER_OFF_INSTRUCTION,
    REBOOT_INSTRUCTION,
    UNKNOWN_INSTRUCTION
} PACKED instruction_command_t;

/// @brief Function prototype of instruction to execute for a given
/// instruction command.
///
/// @param tpcb The TCP protocol control block.
typedef void (*instruction_t)(struct tcp_pcb PTR);

/// @brief Function used to convert the received buffer into an instruction.
///
/// @param buffer The received buffer.
/// @param instruction The interpreted instruction.
void get_instruction_from_buffer(const char ARRAY buffer,
    instruction_command_t PTR instruction);
