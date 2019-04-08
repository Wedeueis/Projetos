all: skew_angle

LIBS = `pkg-config opencv --libs`

clean:
	rm -f skew_angle
	rm -f *.o

skew_angle: skew_angle.cpp
	g++ $< -o $@ $(LIBS)