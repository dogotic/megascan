#include <string>
#include <opencv2/opencv.hpp>
#include <zbar.h>
#include <chrono>
#include <iostream>

using namespace cv;
using namespace zbar;
using namespace std;

// Function to detect and decode QR code
std::string QR_DECODER_readCode(const std::string &image_path)
{
    std::string data = "ikke dataisk";

    auto start = std::chrono::high_resolution_clock::now();
    // Load the image
    Mat image = imread(image_path, IMREAD_GRAYSCALE);

    int up_width = 1024;
    int up_height = 768;
    Mat resized_up;
    // resize up
    resize(image, resized_up, Size(up_width, up_height), INTER_LINEAR);

    imwrite("/var/tmp/resized.jpg", resized_up);

    // Initialize the ZBar scanner
    ImageScanner scanner;

    // Configure the scanner to look for QR codes
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by code: " << duration.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    // Wrap the image data
    Image zbar_image(resized_up.cols,
                     resized_up.rows,
                     "Y800",
                     resized_up.data,
                     resized_up.cols * resized_up.rows);

    // Scan the image for QR codes
    int n = scanner.scan(zbar_image);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by code: " << duration.count() << " ms" << std::endl;

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
