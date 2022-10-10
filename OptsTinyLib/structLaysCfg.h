#pragma once
#include <vector>
struct structLaysCfg{
	size_t topX = 1, topY = 1;
	int digits = 2;
	std::vector<int> vkf;

	size_t laysCnt(){ return vkf.size(); }
	size_t bottomX(){ return topX << (vkf.size() - 1); }
	size_t bottomY(){ return topY << (vkf.size() - 1); }

	static const size_t DEF_SIZE = 5;

private:
};
