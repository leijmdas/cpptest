#include "StdAfx.h"
#include "TestCase.h"

 
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CTestCase)
//static CTestSuiteFactroy  testSuitetestcaseSuite( "CTestCase",new CTestCase() );	 

CTestCase::CTestCase()
{

}

CTestCase::~CTestCase()
{
}

void CTestCase::setUp()
{
	printf("%s","Enter CTestCase::setUp\n");
}

void CTestCase::tearDown()
{
	printf("%s","Exit  CTestCase::TearDown\n");
}

void CTestCase::test_demo_1()
{
	printf("CTestCase::test_demo_1\n");
}
void CTestCase::test_demo_2()
{
	printf("CTestCase::test_demo_2\n");
}
