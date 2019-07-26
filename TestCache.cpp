#include "StdAfx.h"
#include "TestCache.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CTestCache)
CTestCache::CTestCache()
{

}

CTestCache::~CTestCache()
{

}

void CTestCache::setUp()
{
	printf("%s","Enter CTestCache::setUp\n");
}

void CTestCache::tearDown()
{
	printf("%s","Exit  CTestCache::TearDown\n");
}

void CTestCache::test_demo_1()
{
	printf("CTestCache::test_demo_1\n");
}
void CTestCache::test_demo_2()
{
	printf("CTestCache::test_demo_2\n");
}
