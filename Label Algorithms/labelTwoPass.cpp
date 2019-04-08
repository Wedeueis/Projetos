#include "disjointset.h"
#include "ppm.h"
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock clk;

struct pos{
	int i;
	int j;
};

void labeling(ppm &source, int width, int height){

	DisjointSet* sets = new DisjointSet();
	int nextLabel = 1;

	//first pass
	for(int y = 0; y<height; y++) {
		for(int x = 0; x<width; x++){
			int index = y*source.width + x;
			int pixel_value = (int) source.r[index];
			if(pixel_value == 0)
				continue;

			//find labeled neighbors
			std::vector<pos> v;
			pos n;
			n.i = y;
			n.j = x;
			if(n.j+1<width){
				pos viz;
				viz.i = n.i;
				viz.j = n.j + 1;
				int idx = viz.i*source.width + viz.j;
				if(source.r[idx] != 0 && source.r[idx] != 255){
					v.push_back(viz);
				}
			}
			if(n.j-1>=0){
				pos viz;
				viz.i = n.i;
				viz.j = n.j - 1;
				int idx = viz.i*source.width + viz.j;
				if(source.r[idx] != 0 && source.r[idx] != 255){
					v.push_back(viz);
				}
				
			}
			if(n.i+1<height){
				pos viz;
				viz.i = n.i + 1;
				viz.j = n.j;
				int idx = viz.i*source.width + viz.j;
				if(source.r[idx] != 0 && source.r[idx] != 255){
					v.push_back(viz);
				}
			}
			if(n.i-1>=0){
				pos viz;
				viz.i = n.i - 1;
				viz.j = n.j;
				int idx = viz.i*source.width + viz.j;
				if(source.r[idx] != 0 && source.r[idx] != 255){
					v.push_back(viz);
				}
			}

			if(v.size() > 0){
				if(v.size() == 1){
					int idx = v[0].i*source.width + v[0].j;
					source.r[index] = source.r[idx];
				}else{
					unsigned char minLabel = 255;
					for(int i = 0; i< v.size(); i++){
						int idx = v[i].i*source.width + v[i].j;
						if(source.r[idx] < minLabel)
							minLabel = source.r[idx];
					}
					if(minLabel!=255){
						source.r[index] = minLabel;

						for(int i = 0; i < v.size(); i++){
							int idx = v[i].i*source.width + v[i].j;
							std::vector<node*> nodes = sets->getNodes();
							sets->Union(nodes[minLabel-1],nodes[source.r[idx]-1]);
						}
					}
				}
			}else{
				sets->MakeSet(nextLabel);
				source.r[index] = (unsigned char)nextLabel;
				nextLabel++;
			}
		}
	}

	sets->Reduce();
 

   for(int y = 0; y<height; y++){
		for(int x = 0; x<width; x++){
			int index = y*source.width + x;
			if(source.r[index] == 0)
				continue;
			std::vector<node*> nodes = sets->getNodes();
			node* n = nodes[source.r[index]-1];
			node* f = sets->Find(n);
			source.r[index] = f->i;
		}
	}

}

void threshold(ppm &image){
	for(int i=0; i<image.size; i++){
		if(image.r[i] > 240){
			image.r[i] = (unsigned char)255;
		}else{
			image.r[i] = (unsigned char)0;
		}
	}
}

int main(){
	for(int i=0; i<9; i++){
		std::stringstream fname;
		fname << "imagens/teste" << i << ".ppm";
		ppm image(fname.str());
		int lin = image.height;
		int col = image.width;
		clk::time_point t1 = clk::now();
		labeling(image, col, lin);
		clk::time_point t2 = clk::now();
		long time_diff = (long)duration_cast<milliseconds>( t2 - t1 ).count();
		std::cout << time_diff << " ";
	}
	std::cout<<std::endl;
	return 0;
}