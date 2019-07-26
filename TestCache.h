#ifndef __CTESTCACHE__
#define __CTESTCACHE__

#include "itestfixture.h" 
#include "TestSuite.h" 

class CTestCache :	public ITestFixture
{
//Register
	CPPUNIT_TEST_SUITE(CTestCache)
	CPPUNIT_TEST(test_demo_1) 
	CPPUNIT_TEST(test_demo_2)
	CPPUNIT_TEST_SUITE_END()

public:
	CTestCache();
	~CTestCache();
	virtual void setUp();
	virtual void tearDown();
	void test_demo_1();
	void test_demo_2();
 
};

#endif 


