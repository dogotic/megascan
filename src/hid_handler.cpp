#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "usb_hid_keys.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

#include "hid_handler.h"
#include "ascii_to_hid.h"

void hid_sendch(uint8_t c)
{
    uint8_t buffer[8] = {0};

    if (c > 127)
        return;
    if (c < 32)
        return;

    c -= 32; // offset ignore the first 32 symbols in ascii table

    buffer[0] = ascii_to_hid_key_map[c][0];
    buffer[2] = ascii_to_hid_key_map[c][1];

    FILE *f = fopen("/dev/hidg0", "wb");
    fwrite(buffer, sizeof(char), 8, f);
    fclose(f);

    usleep(10000);

    buffer[0] = 0;
    buffer[2] = 0;
    f = fopen("/dev/hidg0", "wb");
    fwrite(buffer, sizeof(char), 8, f);
    fclose(f);

    usleep(50000);
}

void hid_sendstr(char *str)
{
    uint8_t l = strlen(str);
    for (uint8_t i = 0; i < l; i++)
    {
        hid_sendch(str[i]);
    }
}

