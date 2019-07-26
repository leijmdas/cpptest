#include "StdAfx.h"
#include "ITestFixture.h"
#include <stdio.h>
#include <exception>

//static ITestFixture itestcase1(std::string("TestCase::test"), &ITestFixture::test);
//REG_TESTCASE(ITestFixture,test) 

ITestFixture::ITestFixture()
{
	m_ptestCase=NULL;
}

ITestFixture::ITestFixture( std::string tcName, PTestCase ptc )
{
	reg_TestCase(tcName,ptc);
}

ITestFixture::~ITestFixture( )
{
	if(m_ptestCase!=NULL)
	{
		delete m_ptestCase;
		m_ptestCase=NULL;
	}
}
void ITestFixture::runTest( CTestResult *pTestResult,  std::string testcaseName )
{	
	this->makeTestCase();
	if( testcaseName.length()==0 )
	{
		runAll(pTestResult);
	} else
	{
		runOne(pTestResult,testcaseName);
	}
}

//run testcase
void ITestFixture::runTest(CTestResult *pTestResult, PTestCase pTestCase )
{
    //    assert( pTestCase  != NULL );
	try
	{
		setUp();
		//run testcase
		if( pTestCase  != NULL )
        	{    
		    (this->*pTestCase)(); 
               }
	}
	catch (std::exception * e)
	{
		tearDown();	
		return;
	}
	tearDown();	

}

void ITestFixture::runOne( CTestResult *pTestResult,std::string tcName )
{
	printf("runOne %s\n",tcName.c_str() );
	PTestCase pTestCase = find_TestCase(tcName) ;
	runTest( pTestResult, pTestCase);			//(this->*pTestCase)(); 
}
 
void ITestFixture::runAll(CTestResult *pTestResult)
{
	::printf("runAll\n");
	Map_TestCase::iterator it=getMap_TestCase()->begin();
	while(it !=getMap_TestCase()->end() )
	{ 
		PTestCase pTestCase = it->second;
        	runTest(pTestResult, pTestCase);	 //(this->*pTestCase)(); 
		it++;
	}
}

Map_TestCase * ITestFixture::getMap_TestCase()
{
	//static Map_TestCase map_TestCase;
	//return &map_TestCase;
	///////////////////////////
	if(m_ptestCase==NULL)
	{
		m_ptestCase= new Map_TestCase;
	}
	return m_ptestCase;
}

void ITestFixture::reg_TestCase( std::string tcName, PTestCase ptc )
{
	this->getMap_TestCase()->insert(Map_TestCase::value_type(tcName,ptc));
}

PTestCase ITestFixture::find_TestCase( std::string tcName )
{
	Map_TestCase::iterator it;
	it = getMap_TestCase()->find(tcName);
	if ( it != getMap_TestCase()->end() )
	{
		return it->second;
	}
	return NULL;
}
