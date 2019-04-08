all: tesseract video

LIBS = `pkg-config opencv --libs`

clean:
	rm -f tesseract
	rm -f *.o

tesseract: sampleOpenCV_ContribOCR.cpp
	g++ $< -o $@ $(LIBS)

video: teste.cpp
	g++ $< -o $@ $(LIBS)
