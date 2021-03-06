.PHONY: run
run: main
	./main ../build/Debug/BGR.jpg

main: main.o
	clang++ -L/usr/local/Cellar/opencv/2.4.12_2/lib/ -lopencv_highgui -lopencv_core -lopencv_imgproc -L/usr/local/Cellar/curl/7.49.0/lib -lcurl $(^) -o $(@)

methods.o: methods.cpp
	clang++ -I/usr/local/Cellar/opencv/2.4.12_2/include/ -c $(^) -o $(@)

main.o: main.cpp
	clang++ -I/usr/local/Cellar/opencv/2.4.12_2/include/ -c $(^) -o $(@)