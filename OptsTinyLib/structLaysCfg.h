#pragma once
#include <vector>
struct structLaysCfg{
	size_t topX = 1, topY = 1;
	size_t laysCnt = 5;
	std::vector<float> vkf;

	size_t bottomX(){ return topX << (laysCnt - 1); }
	size_t bottomY(){ return topY << (laysCnt - 1); }
};
