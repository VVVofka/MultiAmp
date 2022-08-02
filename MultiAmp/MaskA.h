#pragma once
#include <string>
namespace options::maska{
	class MaskA{
		int v_i[16] = {-1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	public:
		void set(unsigned u);
		void set(char* ptr_ch);
		int* vi();

		const std::string ptr_ch_def = "0001011101111111";
	private:
	};
}
