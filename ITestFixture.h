#ifndef __ITESTFIXTURE__
#define __ITESTFIXTURE__
#include <string>
#include <map>

class CTestResult
{

};

//static CTestSuiteFactroy  testSuiteFactroy##testcaseSuite(#testcaseSuite,(ITestFixture*)new testcaseSuite());	

#define CPPUNIT_TEST_SUITE(ATestFixtureType)\
typedef  ATestFixtureType __ThisTestFixtureType;\
virtual void makeTestCase()\
{

#define CPPUNIT_TEST_SUITE1()\
virtual void makeTestCase()\
{

#define CPPUNIT_TEST_SUITE_END()\
};

//static TestCaseClass itestcase##TestCaseName(std::string(#TestCaseName), &TestCaseClass::TestCaseName );
//REG_TESTCASE(ITestFixture,test) 
//static ITestFixture itestcasetest(std::string("TestCaseName"), &ITestFixture::test);
class ITestFixture;
typedef   void(  ITestFixture::*PTestCase)(); 
//#define CPPUNIT_TEST(TestCaseClass,TestCaseName)\  
//reg_TestCase(std::string(#TestCaseName), (PTestCase)&TestCaseClass::TestCaseName );

#define CPPUNIT_TEST(PTestCaseName)\
	reg_TestCase(std::string(#PTestCaseName), (PTestCase) &__ThisTestFixtureType::PTestCaseName );

//store  testcase pointer; call by name
typedef   std::map <std::string, PTestCase  > Map_TestCase; 
class ITestFixture
{	
public:
	ITestFixture();
	ITestFixture(std::string tcName, PTestCase ptc);	
	~ITestFixture();

public:
	virtual void setUp(){};//=0;
	virtual void tearDown(){};//=0;
	void runTest(CTestResult *pTestResult, std::string testcaseName="");
	virtual void makeTestCase(){};

	Map_TestCase *getMap_TestCase();
	void reg_TestCase( std::string tcName, PTestCase ptc);
	//void test(){};
protected:
	void runOne(CTestResult *pTestResult,std::string tcName);
	void runAll(CTestResult *pTestResult);
	void runTest(CTestResult *pTestResult, PTestCase pTestCase);
private:
	PTestCase find_TestCase(std::string tcName);
	Map_TestCase *m_ptestCase;
	
};

#endif 

//end 
