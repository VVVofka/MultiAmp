// Processes.cpp : Определяет функции для статической библиотеки.
#include "Processes.h"

namespace executor{
	using namespace concurrency::graphics;
	void Processes::Create(SessionData* data_inp){
		data = data_inp;
		processA.Create(&data->lays, &data->amask);
		processF.Create(&data->lays, &data->fmasks);
	} // //////////////////////////////////////////////////////////////////////
	void Processes::RunAll(const int_2 shift){
		processA.NormalizeV();
		processA.RunAll(shift);
		processF.RunAll(shift);
	} // //////////////////////////////////////////////////////////////////////

}
