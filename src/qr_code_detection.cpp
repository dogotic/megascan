#include <iostream>
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <fstream>
#include <unistd.h>

using namespace std;
using namespace cv;
using namespace zbar;

const char NULL_CHAR = '\0';

void write_report(const std::string &report)
{
    std::ofstream fd("/dev/hidg0", std::ios::binary | std::ios::out);
    if (fd.is_open())
    {
        fd.write(report.c_str(), report.size());
        fd.close();
    }
    else
    {
        std::cerr << "Failed to open /dev/hidg0 for writing." << std::endl;
    }
}

void sendString(const std::string &str)
{
    for (char c : str)
    {
        // Press the key for the current character
        std::string key_press = std::string(2, NULL_CHAR) + c + std::string(5, NULL_CHAR);
        write_report(key_press);

        // Release the key
        write_report(std::string(8, NULL_CHAR));

        // Add a small delay (adjust as needed)
        usleep(50000); // 50 milliseconds
    }
}

// Function to detect and decode QR code
std::string detectQRCode(const string &image_path)
{
    std::string data = "";

    // Load the image
    Mat image = imread(image_path, IMREAD_GRAYSCALE);

    // Initialize the ZBar scanner
    ImageScanner scanner;

    // Configure the scanner to look for QR codes
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // Wrap the image data
    Image zbar_image(image.cols, image.rows, "Y800", image.data, image.cols * image.rows);

    // Scan the image for QR codes
    int n = scanner.scan(zbar_image);

    if (n == 0)
    {
        cout << "No QR codes found in the image." << endl;
    }
    else
    {
        for (Image::SymbolIterator symbol = zbar_image.symbol_begin(); symbol != zbar_image.symbol_end(); ++symbol)
        {
            // Extract the data from the QR code
            data = symbol->get_data();
            cout << "QR Code Data: " << data << endl;
        }
    }

    return data;
}

void SendQrCodeAsKeyPresses(std::string qr_code)
{
}

int main()
{
    string image_path = "slika.jpg"; // Replace with the path to your image
    system("libcamera-still -o slika.jpg -n -t 1");
    std::string qr_code = detectQRCode(image_path);
    sendString(qr_code);
    
    return 0;
}
