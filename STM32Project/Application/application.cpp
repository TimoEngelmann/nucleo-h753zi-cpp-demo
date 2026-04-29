/// ====================================================================================================================
/// \file       application.cpp
/// \brief      This file contains a simple C++ application for the STM32H7.
/// \details
/// ====================================================================================================================


//======================================================================================================================
// MARK: Inclusions
//======================================================================================================================
#include "main.h"          // Needed for the pin and port defines.
#include "stm32h7xx_hal.h" // Needed for the HAL functions like HAL_GetTick(), HAL_GPIO_WritePin(), etc.
#include <cstdint>         // Needed for fixed width integer types like uint32_t, uint64_t, etc.
#include <cstdio>          // Needed for printf() function.
#include <inttypes.h>      // Needed for the PRIu64 macro to print uint64_t values with printf().
#include <cassert>         // Needed for assert() function.
#include <limits>          // Needed for std::numeric_limits to check for overflow in millisToTicks() function.


//======================================================================================================================
// MARK: Globals
//======================================================================================================================


// --------------------------------------------------------------------------------------------------------------------
// Macros:
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// Forward declarations:
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// Typedefs:
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// Enums:
// --------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------------------------------------
// Variables / Objects:
// --------------------------------------------------------------------------------------------------------------------
// Application stuff:
// Some global counters to test the live watch feature of ST-Link debugger:
static uint32_t tickValToToggleLed1 = 0;
static uint32_t tickValToToggleLed2 = 0;
static uint64_t loopCounter = 0;
static uint64_t counterGreenLed = 0;
static uint64_t counterOrangeLed = 0;
static uint64_t counterButton = 0;


// --------------------------------------------------------------------------------------------------------------------
// Constants:
// --------------------------------------------------------------------------------------------------------------------
// Application stuff:
// Some constants to configure the application:
constexpr uint32_t delayLed1Ms = 500;
constexpr uint32_t delayLed2Ms = 1000;


//======================================================================================================================
// MARK: Helper
//======================================================================================================================

/// --------------------------------------------------------------------------------------------------------------------
/// \brief   Converts milliseconds to timer ticks.
/// \details This function converts a duration in milliseconds to the equivalent duration in timer ticks.
///          Template parameter T specifies the return type (e.g., ULONG, uint32_t, uint16_t).
/// --------------------------------------------------------------------------------------------------------------------
static inline uint32_t millisToTicks(uint32_t millis)
{
    constexpr uint64_t millisPerSec = 1000u;
    if (millis == 0)
    {
        return 0;
    }
    // Integer ceil-Division: (a + b - 1) / b
    volatile uint64_t tickFreq = static_cast<uint64_t>(HAL_GetTickFreq()) * 1000u;
    volatile uint64_t numerator = static_cast<uint64_t>(millis) * tickFreq;
    volatile uint64_t ticks = (numerator + (millisPerSec - 1)) / millisPerSec;
    assert(ticks <= std::numeric_limits<uint32_t>::max()); // Check for overflow of the return type.
    return static_cast<uint32_t>(ticks);
}


//======================================================================================================================
// MARK: Setup
//======================================================================================================================

/// --------------------------------------------------------------------------------------------------------------------
/// \brief      Application Setup function.
/// \details    This function implements the behavior of the main application setup.
///             It is called once at the beginning of the application.
/// --------------------------------------------------------------------------------------------------------------------
uint32_t dbgVal = 0;
extern "C" void Setup(void)
{
    // --- Init Application:
    // Place here initialization stuff that needs to be done before starting the threads.
    // Initialize LED1 (turn on at startup)
    HAL_GPIO_WritePin(LED1_Green_GPIO_Port, LED1_Green_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED2_Orange_GPIO_Port, LED2_Orange_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_Red_GPIO_Port, LED3_Red_Pin, GPIO_PIN_SET);

    // Initialize the tick values for the LED toggling:
    uint32_t now = HAL_GetTick();
    tickValToToggleLed1 = now + millisToTicks(delayLed1Ms);
    tickValToToggleLed2 = now + millisToTicks(delayLed2Ms);

    // Say hello:
    printf("\033[2J\033[H"); // Clear terminal
    printf("============================================\n");
    printf("Welcome to the very simple C++ application!\n");
    printf("Press the blue button to get the statistics.\n");
    printf("============================================\n\n");
}


//======================================================================================================================
// MARK: Loop
//======================================================================================================================

/// --------------------------------------------------------------------------------------------------------------------
/// \brief      Application loop function.
/// \details    This function implements the behavior of the main application loop.
///             It is called cyclically driven by a endless loop in main.c.
/// --------------------------------------------------------------------------------------------------------------------
extern "C" void Loop(void)
{
    // --- Main Application:
    // Place here the cyclic application stuff.

    // Demo code - Just some dummy counter to test the live watch feature of ST-Link debugger:
    loopCounter++;
    uint32_t now = HAL_GetTick();

    // Demo code - Lets the green LED blink:
    if (now >= tickValToToggleLed1)
    {
        tickValToToggleLed1 = now + millisToTicks(delayLed1Ms);
        counterGreenLed++;
        HAL_GPIO_TogglePin(LED1_Green_GPIO_Port, LED1_Green_Pin);
    }

    // Demo code - Lets the orange LED blink:
    if (now >= tickValToToggleLed2)
    {
        tickValToToggleLed2 = now + millisToTicks(delayLed2Ms);
        counterOrangeLed++;
        HAL_GPIO_TogglePin(LED2_Orange_GPIO_Port, LED2_Orange_Pin);
    }

    // Demo code - Switch the red LED on when button B1 is pressed (active high).
    // TODO: Insert debouncing.
    if (HAL_GPIO_ReadPin(Button1_Blue_GPIO_Port, Button1_Blue_Pin) == GPIO_PIN_SET)
    {
        if (HAL_GPIO_ReadPin(LED3_Red_GPIO_Port, LED3_Red_Pin) == GPIO_PIN_RESET)
        {
            counterButton++;
            HAL_GPIO_WritePin(LED3_Red_GPIO_Port, LED3_Red_Pin, GPIO_PIN_SET);
            printf("Blue button pressed %" PRIu64 " times.\n", counterButton);
            printf("Orange LED toggled %" PRIu64 " times.\n", counterOrangeLed);
            printf("Green LED toggled %" PRIu64 " times.\n", counterGreenLed);
            printf("HAL_GetTick() = %u\n", HAL_GetTick());
            printf("loop counter = %" PRIu64 "\n\n", loopCounter);
        }
    }
    else
    {
        HAL_GPIO_WritePin(LED3_Red_GPIO_Port, LED3_Red_Pin, GPIO_PIN_RESET);
    }
}
