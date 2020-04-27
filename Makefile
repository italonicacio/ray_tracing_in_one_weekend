CXX = g++

CXXFLAGS =  -g3 -O0 -Wall -Werror -std=c++11

EXECUTABLE = raytracer

IMAGE = output_image

LDLIBS =

OBJ = main.o buffer.o

$(EXECUTABLE):  $(OBJ)
	$(CXX) $(OBJ) -o $(EXECUTABLE) $(LDLIBS)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

buffer.o: buffer.cpp
	$(CXX) -c $(CXXFLAGS) buffer.cpp -o buffer.o


.PHONY: clean run png clpng view

clean:
	rm *.o $(EXECUTABLE) $(IMAGE).ppm 

run: $(EXECUTABLE)
	./$(EXECUTABLE)

png: $(IMAGE).ppm
	convert $(IMAGE).ppm $(IMAGE).png

clpng: $(IMAGE).png
	rm $(IMAGE).png

view: $(IMAGE).ppm
	gwenview $(IMAGE).ppm


