
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    // Load an image (replace 'your_image.jpg' with the actual image file)
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);

    if (image.empty())
    {
        std::cerr << "Error: Could not load the image." << std::endl;
        return 1;
    }

    // Convert the image to grayscale
    cv::Mat grayscale;
    cv::cvtColor(image, grayscale, cv::COLOR_BGR2GRAY);

    // Create a QR code detector
    cv::QRCodeDetector qrCodeDetector;

    // Detect the QR code in the grayscale image
    std::string decodedText = qrCodeDetector.detectAndDecode(grayscale);

    if (!decodedText.empty())
    {
        // Print the decoded text
        std::cout << "Decoded QR code: " << decodedText << std::endl;

        // Get the bounding box of the detected QR code
        std::vector<cv::Point> points;
        qrCodeDetector.detect(grayscale, points);

        if (points.size() == 4)
        {
            // Crop the image to the QR code region
            cv::Rect qrCodeRect = cv::boundingRect(points);
            cv::Mat croppedImage = image(qrCodeRect);

            // Save the cropped QR code image
            cv::imwrite("cropped_qr_code.jpg", croppedImage);

            std::cout << "Cropped QR code image saved as 'cropped_qr_code.jpg'" << std::endl;
        }
        else
        {
            std::cerr << "Error: Invalid number of QR code points." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: No QR code detected in the image." << std::endl;
    }

    return 0;
}
