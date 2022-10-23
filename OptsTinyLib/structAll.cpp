#include "structAll.h"

bool structAll::isEqual(const structAll* other)const {
	for(size_t j = 0; j < v.size(); j++)
		if(v[j]->isEqual(other->v[j]) == false) return false;
	return true;
} // /////////////////////////////////////////////////////////////////////////////
bool structAlls::isEqual() const{
	return cur.isEqual(&old);
} // /////////////////////////////////////////////////////////////////////////////
