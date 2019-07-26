//#pragma once
#ifndef  __CTESTSUITE__
#define __CTESTSUITE__
#include "itestfixture.h"

#include <map>
#include <string>
class CTestSuiteFactroy;

#define RUNALL_TESTCASESUITE()\
	CTestSuite::runTest();	

#define RUNONE_TESTCASESUITE(tcSuiteName)\
	CTestSuite::runTest( #tcSuiteName );	

#define RUNONE_TESTCASE(tcSuiteName,tcName)\
	CTestSuite::runTest( #tcSuiteName ,#tcName);	

#define CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(testcaseSuite) \
	static CTestSuiteFactroy  testSuiteFactroy##testcaseSuite(#testcaseSuite,(ITestFixture*)new testcaseSuite());	

typedef std::map <std::string,ITestFixture * > Map_TestCaseSuite;

class CTestSuite : public ITestFixture
{
public:
	CTestSuite();
	CTestSuite(char* tcSuiteName,ITestFixture* ptcSuite);

	~CTestSuite();
	//������ʵ������
	static Map_TestCaseSuite & getMap_TestCaseSuite() ;
	//ע�������
	static void register_TestCaseSuite(char* tcSuiteName,ITestFixture* ptcSuite);
	static ITestFixture * find_TestCaseSuite(std::string tcSuiteName); 
	//����ִ��
	// in tcSuiteName=""ִ��ȫ��
	//		tcSuiteName != "" testcaseName="" ִ��ָ�������������
	//		tcSuiteName != "" testcaseName!="' ִ��ָ���������һ������
	static void runTest( char* tcSuiteName="",char *testcaseName="");
private :
	static void runAll(CTestResult *pTestResult);
	void setUp();
	void tearDown();
};

class CTestSuiteFactroy
{
public:
	CTestSuiteFactroy(char* tcSuiteName,ITestFixture* ptcSuite);
	~CTestSuiteFactroy();
};

#endif 
//end