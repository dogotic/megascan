/**
 * @file gpio.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef GPIO_H
#define GPIO_H

/**
 * @brief 
 * 
 * @return int 
 */
int GPIO_ReadValue();

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool GPIO_Init();

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool GPIO_Close();

#endif // GPIO_H