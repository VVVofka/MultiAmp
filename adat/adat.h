#pragma once

#include <array>
#include <string>

namespace adat{


	struct CfgMaskA{
		std::array<int, 16> v;
		std::string s() const;
		void set(const char* s);
		bool operator ==(const CfgMaskA& other) const{ return v == other.v; }
		bool operator !=(const CfgMaskA& other) const{ return v != other.v; }
	};

	struct CfgAll{
		CfgMaskA maska;
		bool operator ==(CfgAll& other) const{ return maska == other.maska; }
		bool operator !=(CfgAll& other) const{ return maska != other.maska; }
	};

	namespace maska{
		bool load(CfgMaskA& mask_a, const char* f_name);
		bool save(const CfgMaskA& mask_a, const char* f_name);
	}

	bool load(CfgAll& cfg_all, const char* f_name);
	bool save(const CfgAll& cfg_all, const char* f_name);

} // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@