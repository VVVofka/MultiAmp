#include "MiscCfg.h"

XMLNode* MiscCfg::set(const structMiscCfg* in_cfg){
	cfg = *in_cfg;
	if(node != NULL)
		node->Parent()->DeleteChild(node);
	//****************
	XMLDocument* doc = parent_node->GetDocument();
	XMLElement* ele_out = doc->NewElement(XMLName);
	ele_out->SetAttribute("size", new_cfg.v.size());
	ele_out->SetAttribute("seed", new_cfg.seed.c_str());
	ele_out->SetAttribute("sigma", new_cfg.sigma.c_str());
	ele_out->SetText(new_cfg.get_s().c_str());
	node = parent_node->InsertEndChild(ele_out);
	return node;
} // ///////////////////////////////////////////////////////////////////////////////////

