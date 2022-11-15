#include <array>
#include <string>

namespace adat{
	struct maskA{
		std::array<int, 16> v;
		//maskA(){ for(size_t j = 0; j < 16; j++) v[j] = 0; }

		std::string s() const{
			std::string ret(16, '0');
			_ASSERT(ret.size() == v.size());
			for(size_t j = 0; j < 16; j++)
				if(v[j] != 0)
					ret[j] = '1';
			return ret;
		} // ////////////////////////////////////////////

		bool operator ==(maskA& other) const{ return v == other.v; }
		bool operator !=(maskA& other) const{ return v != other.v; }
	};
}