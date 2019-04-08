all: edges

clean:
	rm -f edges

edges: edges.cpp
	g++ edges.cpp -o edges `pkg-config opencv --libs` 