cmake_minimum_required(VERSION 3.0)
project(qr_code_scanner)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add your source files
set(SOURCE_FILES
    main.cpp
    gpio.cpp
    hid_handler.cpp
    qr_decoder.cpp
    # Add any additional source files here
)

# Add your header files (if needed)
set(HEADER_FILES
    gpio.h
    hid_handler.h
    qr_decoder.h
    ascii_to_hid.h
    usb_hid_keys.h
    # Add any additional header files here
)

# Add the executable
add_executable(qr_code_scanner ${SOURCE_FILES} ${HEADER_FILES})

# Link OpenCV libraries to your executable
target_link_libraries(qr_code_scanner ${OpenCV_LIBS})

# Link ZBar library explicitly
target_link_libraries(qr_code_scanner -lzbar)
