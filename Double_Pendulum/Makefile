
CC := g++
CFLAGS := -lpthread -lglfw -lGL -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window -lsfml-system
EXECUTABLE := main
$(EXECUTABLE): main.cpp  $(wildcard /home/nabin/Data/.archives/sfml/Double_Pendulum/src/*.c /home/nabin/Data/.archives/sfml/Double_Pendulum/src/*.cpp) 
	$(CC)  $^  -I/home/nabin/Data/.archives/sfml/Double_Pendulum/include -o $@  $(CFLAGS)
run: $(EXECUTABLE)
	/home/nabin/Data/.archives/sfml/Double_Pendulum/$(EXECUTABLE)

clean:
	rm ./$(EXECUTABLE)

