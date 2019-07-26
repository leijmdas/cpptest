#include "StdAfx.h"
#include "TestSuite.h"


CTestSuite::CTestSuite()
{
}

CTestSuite::CTestSuite( char* tcSuiteName,ITestFixture* ptcSuite )
{	
}

CTestSuite::~CTestSuite()
{
	Map_TestCaseSuite::iterator it=getMap_TestCaseSuite().begin();
	while(it!=getMap_TestCaseSuite().end())
	{
		delete (ITestFixture*)(it->second);
	}
	getMap_TestCaseSuite().clear();
}

Map_TestCaseSuite & CTestSuite::getMap_TestCaseSuite()
{ 
	static Map_TestCaseSuite map_TestCaseSuite;
	return map_TestCaseSuite; 
}

void CTestSuite::register_TestCaseSuite( char*  tcSuiteName,ITestFixture* ptcSuite )
{
	std::string tcname=tcSuiteName;
	if( getMap_TestCaseSuite().find(tcname)==getMap_TestCaseSuite().end())
	{ 
		getMap_TestCaseSuite().insert( Map_TestCaseSuite::value_type(tcname,ptcSuite) )	;
	}
}

//end 
void CTestSuite::runTest( char* tcSuiteName/*=""*/,char *testcaseName/*=""*/ )
{
	CTestResult testResult; 
	std::string sname  =tcSuiteName;
	std::string tcname =testcaseName;
	if(  sname.length()>0  )
	{
		ITestFixture *tf=find_TestCaseSuite(sname);
		if( NULL != tf )
		{
			tf->runTest(&testResult, testcaseName);
		}
	} else
	{
		runAll(&testResult);
	}
	
}

ITestFixture * CTestSuite::find_TestCaseSuite( std::string  tcSuiteName )
{
	Map_TestCaseSuite::iterator it=getMap_TestCaseSuite().begin();
	while(it!=getMap_TestCaseSuite().end())
	{ 
		if(tcSuiteName==it->first)
		{
			return (ITestFixture*)(it->second);
		}
		it++;
	}
	return NULL;
}

void CTestSuite::runAll(CTestResult *pTestResult)
{
	Map_TestCaseSuite::iterator it=getMap_TestCaseSuite().begin();
	while(it!=getMap_TestCaseSuite().end())
	{ 
		ITestFixture* tf= (ITestFixture*)(it->second);
		if(NULL!=tf)
		{
			tf->runTest(pTestResult);
		}
		it++;
	}
}

void CTestSuite::setUp()
{

}

void CTestSuite::tearDown()
{

}

CTestSuiteFactroy::CTestSuiteFactroy(char* tcSuiteName,ITestFixture* ptcSuite)
{
	CTestSuite::register_TestCaseSuite(tcSuiteName,ptcSuite);
}

CTestSuiteFactroy::~CTestSuiteFactroy()
{

}
