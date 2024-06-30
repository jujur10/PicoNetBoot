/*
** EPITECH PROJECT, 2024
** status.h
** File description:
** status.h.
*/

#pragma once

#include "style/common_macros.h"

/// @brief Enumeration representing the success or the failure.
///
/// @var FAILURE Representing the failure.
/// @var SUCCESS Representing the success.
typedef enum status_s {
    FAILURE,
    SUCCESS
} PACKED status_t;
