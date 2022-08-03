#pragma once
#include <string>
//namespace maska{
	class MaskA4{
	public:
		static const size_t size = 16;
		bool check();

		int* set(unsigned u);
		int* set(const char* ptr_ch);
		int* setdef();

		int* getvi(){ return v; }
		unsigned getu();
		std::string gets();

		const std::string s_def = "0001011101111111";

	private:
		int v[size] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	};
//}
