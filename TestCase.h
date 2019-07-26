#pragma once
#include "itestfixture.h"
#include "TestSuite.h"


class CTestCase :	public ITestFixture
{
//Register
	CPPUNIT_TEST_SUITE(CTestCase)
	CPPUNIT_TEST(test_demo_1) 
	CPPUNIT_TEST(test_demo_2)
	CPPUNIT_TEST_SUITE_END()

public:
	CTestCase(void);
	~CTestCase(void);
	virtual void setUp();
	virtual void tearDown();
	void test_demo_1();
	void test_demo_2();
	//	REG_TESTCASE(CTestCase::test_demo_1)
	//	static CTestCase itestcase1("TestCase::test_demo_1",  &CTestCase::test_demo_1  );
	//static CTestCase itestcase1(std::string("TestCase::test_demo_1"),  NULL);

};
