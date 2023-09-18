SRC=qr_code_detection.cpp
BIN=qr_code_detection

all:
	g++ -o $(BIN) $(SRC) -I/usr/include/opencv4 -lopencv_core -lopencv_imgcodecs -lzbar

clean:
	rm -rf $(BIN)
