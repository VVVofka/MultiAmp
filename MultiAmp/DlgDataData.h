#pragma once
#include <vector>
class DlgDataData{
public:
	size_t szX;
	size_t szY;
	size_t cnt;
	std::vector<size_t> v;

	size_t szAll(){ return szX * szY; }
	size_t getX(size_t offset){ return offset % szX; }
	size_t getY(size_t offset){ return offset / szY; }

};

