all: face_detection

clean:
	rm -f face_detection

face_detection: face_detection.cpp
	g++ face_detection.cpp -o face_detection `pkg-config opencv --libs`