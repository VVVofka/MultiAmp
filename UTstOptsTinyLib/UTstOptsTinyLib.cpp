#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\Session.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsTinyLib){
public:

	TEST_METHOD(Crt_1){
		Session session;
		session.tstcrt();
	}
	TEST_METHOD(TestMethod1){
		Session session;
		session.load();
	}
	};
}
