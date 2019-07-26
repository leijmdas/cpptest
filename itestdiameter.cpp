#include "StdAfx.h"
#include "itestdiameter.h"
#include <map>
#include "Winsock2.h"
int itestdiameter::apinum=0;

//itest define
//Map_TestApiFN  itest::g_pMap ;
itest::itest(int appid,PTestMethod pTestMethod )
{ 
	itest::RegAPI(appid,pTestMethod );
}
itest::itest()
{
}

itest::itest( int appid,PTestMethod pTestMethod, char * p_str )
{
	itest::RegAPI(appid,pTestMethod );
	//std::string ps=p_str;
	//itest::RegAPI(appid,ps );
}

itest::~itest()
{ 
}
void itest::RegAPI(int appid, PTestMethod pTestMethod ) 
{
	getMapApi()->insert( Map_TestApiFN::value_type(appid,pTestMethod) ); 
}

void itest::RegAPI( int appid,std::string &pstr )
{
	getMapApiName()->insert( Map_TestApiName::value_type(appid,pstr) ); 
}

PTestMethod itest::findApi(int appid)
{
	return (PTestMethod) (*getMapApi())[appid] ;	 
};

int itest::execAll( )
{	 
	 Map_TestApiFN::iterator  it;
	 for(it=getMapApi()->begin();it!=getMapApi()->end();it++)
	{
		int iappid=(*it).first;
		PTestMethod pTestMethod= (*it).second;
		if( pTestMethod !=NULL )
		{
			(* pTestMethod)(iappid);  
		} 
	 }	 
	return 0;
}

int itest::execApi(int appid )
{	
	 unsigned long ul=1;
	 ul=htonl(ul);
	 PTestMethod pTestMethod= findApi( appid);
	 if(pTestMethod != NULL )
	 {
		(* pTestMethod)(appid);
	 } 
	 return 0;
}
 
//**********************************
//itestdiameter
//************************************
itestdiameter::itestdiameter(int appid,PTestMethod  pTestMethod)
{
	RegAPI(appid,pTestMethod);
}

itestdiameter::~itestdiameter()
{ 
}
PTestMethod itestdiameter::findApi(int appid)
{ 
	for(int i=0;i<apinum;i++)
	{
		if(g_testapi[i].appid==appid)
		{
			return g_testapi[i].pTestMethod;
		}
	}
	return NULL;

};

int itestdiameter::execAll( )
{	
	for(int i=0;i<apinum;i++)
	{
		PTestMethod pTestMethod=g_testapi[i].pTestMethod;
		int appid=g_testapi[i].appid;
		if(pTestMethod!=NULL)
			(* pTestMethod)(appid);
	} 
	return 0;
}

int itestdiameter::execApi(int appid )
{	
	PTestMethod pTestMethod = findApi( appid);
	if(pTestMethod !=NULL)
	{
		(* pTestMethod)(appid);
	} 
	return 0;
}

void itestdiameter::RegAPI(int appid, PTestMethod pTestMethod ) 
{  
	if(apinum<INT_MAXAPINUM)
	{
		g_testapi[apinum].appid	= appid ;
		g_testapi[apinum].pTestMethod = pTestMethod ;
		apinum++;
	} 
}

//end

