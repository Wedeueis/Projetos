#include "tilelayer.h"



TileLayer::TileLayer(sge::graphics::Shader* shader)
	:Layer(new sge::graphics::Batch2DRenderer(), shader, sge::math::mat4::orthographic(0.0f, 16.0f, 
													0.0f, 9.0f, -1.0f, 1.0f)) {
}

TileLayer::~TileLayer(){
}
