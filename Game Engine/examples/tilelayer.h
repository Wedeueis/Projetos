#pragma once

#include "../src/graphic/layers/layer.h"
#include "../src/graphic//renderer/batch2Drenderer.h"



class TileLayer: public sge::graphics::Layer{
public:
	TileLayer(sge::graphics::Shader* shader);
	~TileLayer();
};	
