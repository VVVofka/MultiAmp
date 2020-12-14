#include "pch.h"
using namespace System;
//int main(array<System::String ^> ^args)
//{
//    return 0;
//}
#include "Form1.h"
#include "OptionExternDecl.h"
using namespace System::Windows::Forms;

[STAThread]
int main(){
	static bool first = true;
	Application::EnableVisualStyles();
	if(first)
		first = false, Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProjekt::Form1());
	return 0;
} // /////////////////////////////////////////////////////////////////////////////////////////////
int openDlgOptions(int* iArr, double* dArr){
	static bool first = true;
	Application::EnableVisualStyles();
	if(first)
		first = false, Application::SetCompatibleTextRenderingDefault(false);
	auto frm = gcnew CppCLRWinformsProjekt::Form1();
	frm->setArr(iArr, dArr);
	Application::Run(frm);
	int ret =  iArr[InpOptions::Restart];
	//int ret =  1;
	return ret;
} // //////////////////////////////////////////////////////////////////////////////////////////////