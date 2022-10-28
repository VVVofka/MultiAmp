#pragma once
#include "ProcessA.h"
#include "ProcessF.h"
#include "SessionData.h"

namespace executor{
	class Processes{
	public:
		SessionData* data = NULL;

		ProcessA processA;
		ProcessF processF;

		void Create(SessionData* data_inp);
		void RunAll(const int_2 shift);
	}; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

}