/**
 * @file hid_handler.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef HID_HANDLER_H
#define HID_HANDLER_H

/**
 * @brief 
 * 
 * @param c 
 */
void hid_sendch(uint8_t c);

/**
 * @brief 
 * 
 * @param str 
 */
void hid_sendstr(char *str);


#endif // HID_HANDLER_H