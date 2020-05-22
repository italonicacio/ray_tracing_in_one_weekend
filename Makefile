CXX = g++

CXXFLAGS =  -g3 -O0 -Wall -Werror -std=c++11 -fopenmp

EXECUTABLE = raytracer

IMAGE = output_image

LDLIBS = -fopenmp

OBJ = main.o buffer.o sphere.o hitable_list.o camera.o

$(EXECUTABLE):  $(OBJ)
	$(CXX) $(OBJ) -o $(EXECUTABLE) $(LDLIBS)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

buffer.o: buffer.cpp
	$(CXX) -c $(CXXFLAGS) buffer.cpp

sphere.o: sphere.cpp
	$(CXX) -c $(CXXFLAGS) sphere.cpp

hitable_list.o: hitable_list.cpp
	$(CXX) -c $(CXXFLAGS) hitable_list.cpp

camera.o: camera.cpp
	$(CXX) -c $(CXXFLAGS) camera.cpp


.PHONY: clean run png clpng view

clean:
	rm *.o $(EXECUTABLE) 

run: $(EXECUTABLE)
	./$(EXECUTABLE)

png: $(IMAGE).ppm
	convert $(IMAGE).ppm $(IMAGE).png

clpng: $(IMAGE).png
	rm $(IMAGE).png

view: $(IMAGE).ppm
	gwenview $(IMAGE).ppm


