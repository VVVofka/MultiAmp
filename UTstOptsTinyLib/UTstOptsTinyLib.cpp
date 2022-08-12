#include "pch.h"
#include "CppUnitTest.h"
#include "..\OptsTinyLib\Session.h"
#define DEFMASKA ("0001011101111111")
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UTstOptsTinyLib{
	TEST_CLASS(UTstOptsTinyLib){
public:

	TEST_METHOD(Crt_1){
		Session session;
		session.tstcrt();
	}
	TEST_METHOD(Create){
		Session session;
		session.create("tstxml1.xml");
		std::string smaska = session.get_maskA();
		Assert::IsTrue(smaska == DEFMASKA);
	}
	TEST_METHOD(CreateDefault){
		Session session;
		session.create();
		std::string smaska = session.get_maskA();
		Assert::IsTrue(smaska == DEFMASKA);
	}
	TEST_METHOD(ChangeMaskA){
		const char tstmask[] = "0101010101010101";
		Session session1, session2;
		session1.create("ChangeMaskA1.xml");
		session1.set_maskA(tstmask);
		session1.save("ChangeMaskA2.xml");
		session2.load("ChangeMaskA2.xml");
		std::string smaska2 = session2.get_maskA();
		Assert::IsTrue(smaska2 == tstmask);

		std::string smaska1 = session1.get_maskA();
		Assert::IsTrue(smaska1 == tstmask);
		session1.load("ChangeMaskA1.xml");
		std::string smaska1reload = session1.get_maskA();
		Assert::IsTrue(smaska1reload == DEFMASKA);
	}
	};
}
