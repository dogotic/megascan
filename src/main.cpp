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

#include "gpio.h"
#include "qr_decoder.h"
#include "hid_handler.h"

using namespace std;


int main()
{
    string image_path = "/var/tmp/slika.jpg"; // Replace with the path to your image

    GPIO_Init();

    int previousValue = -1;

    while (true)
    {
        // Read the GPIO value
        int gpioValue = GPIO_ReadValue();

        if (gpioValue == 0 && previousValue == 1)
        {
            std::cout << "GPIO 4 transitioned from HIGH to LOW" << std::endl;
            // Add your code here to perform an action when the transition occurs
            system("rm -rf /var/tmp/slika.jpg; libcamera-still -o /var/tmp/slika.jpg  -t 1 --tuning-file /usr/share/libcamera/ipa/raspberrypi/imx219.json");
            std::string qr_code = QR_DECODER_readCode(image_path) + "\r\n";
            hid_sendstr((char *)(qr_code.c_str()));            
        }

        previousValue = gpioValue;

        // Delay for a short period to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    GPIO_Close();

    return 0;
}
