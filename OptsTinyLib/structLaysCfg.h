#pragma once
#include <vector>
struct structLaysCfg{
	size_t topX = 1, topY = 1;
	int digits = 2;
	std::vector<int> vkf;

	size_t bottomX(){ return topX << (vkf.size() - 1); }
	size_t bottomY(){ return topY << (vkf.size() - 1); }

	void setDefault(){
		topX = 1;
		topY = 1;
		digits = 2;
		vkf.resize(DEF_SIZE, 1);
	} // ///////////////////////////////////////////////////////////////////////

private:
	const size_t DEF_SIZE = 5;
};
