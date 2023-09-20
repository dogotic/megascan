#include <fstream>
#include <sstream>
#include <iostream>

#include "gpio.h"

const std::string GPIO_PATH = "/sys/class/gpio/gpio4/";

// Function to read the GPIO value
int GPIO_ReadValue()
{
    std::ifstream valueFile(GPIO_PATH + "value");
    if (valueFile.is_open())
    {
        int value = 0;
        valueFile >> value;
        return value;
    }
    return -1; // Error reading value
}

bool GPIO_Init()
{
    // Export GPIO 4
    std::ofstream exportFile("/sys/class/gpio/export");
    if (exportFile.is_open())
    {
        exportFile << "4";
        exportFile.close();
    }
    else
    {
        std::cerr << "Failed to export GPIO 4." << std::endl;
        return false;
    }

    // Set the direction of GPIO 4 to input
    std::ofstream directionFile(GPIO_PATH + "direction");
    if (directionFile.is_open())
    {
        directionFile << "in";
        directionFile.close();
    }
    else
    {
        std::cerr << "Failed to set direction for GPIO 4." << std::endl;
        return false;
    }

    return true;
}

bool GPIO_Close()
{
    // Unexport GPIO 4 (cleanup)
    std::ofstream unexportFile("/sys/class/gpio/unexport");
    if (unexportFile.is_open())
    {
        unexportFile << "4";
        unexportFile.close();
        return true;
    }
    else
    {
        std::cerr << "Failed to unexport GPIO 4." << std::endl;
        return false;
    }
}