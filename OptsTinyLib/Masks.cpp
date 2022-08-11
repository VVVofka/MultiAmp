#include "pch.h"
#include "Masks.h"

void Masks::create(XMLDocument& doc){
	maskA.create(doc);
	//maskF.create();
} // ///////////////////////////////////////////////////////
void Masks::load(XMLDocument& doc){
	maskA.load(doc);
} // ///////////////////////////////////////////////////////
