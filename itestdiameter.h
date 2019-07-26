
#ifndef __ITESTDIAMETER__H_
#define __ITESTDIAMETER__H_

#include <map>
#include <string>

// unit test register macro
#define TEST_REGAPI(appid,testappfn)\
	int testappfn( int apiid );\
	static  itest regapi##appid ( appid, testappfn, #testappfn );

#define TEST_EXECALL()\
	itest::execAll();

#define TEST_EXECAPI(api)\
	itest::execApi(api);

//#advp define
const int AVPDATA_MAXLENGTH=1024;
const int DIAMMSG_MAXLENGTH=AVPDATA_MAXLENGTH*10;

const int ERR_OK 				= 0;
const int ERR_BASESTART			= -20000;
const int ERR_NULLPOINT			= ERR_BASESTART-1;
const int ERR_GROUPHASNOCHILD	= ERR_BASESTART-2;
const int ERR_NOFOUND			= ERR_BASESTART-3;
const int ERR_DIAMMSG_TOOLONG	= ERR_BASESTART-4;

typedef unsigned UINT4;
typedef long			TINT4;
typedef long long TINT8;
typedef double TDouble;
typedef char *  TSTRING;
typedef char *  TBINARY;

typedef unsigned  TAVPCODE;
enum TAvpType 
{
	AVPTYPE_INT32,
	AVPTYPE_INT64,
	AVPTYPE_DOUBLE,
	AVPTYPE_STRING,
	AVPTYPE_BINARY,
	AVPTYPE_GROUP
};

const TAVPCODE  AVPCODE_RETCODE = 268;
const TAVPCODE  AVPCODE_INT4			= 30000;
const TAVPCODE  AVPCODE_INT8			= 30001;
const TAVPCODE  AVPCODE_STRING	= 30002;
const TAVPCODE  AVPCODE_DOUBLE	= 30003;
const TAVPCODE  AVPCODE_GROUP		= 30004;

//avp code avptype
const int avpdef[124][2]=
{
	{AVPCODE_RETCODE,AVPTYPE_INT32},
	{269,AVPTYPE_INT64},
	{	AVPCODE_STRING,AVPTYPE_STRING},
	{222,AVPTYPE_GROUP},
	{	AVPCODE_GROUP,AVPCODE_GROUP	}
};

// itest define
typedef int(*PTestMethod)(int appid)  ;
typedef struct testApi
{
	int appid;
	PTestMethod pTestMethod;
} TTestAPI;
typedef std::map <int  ,PTestMethod > Map_TestApiFN;
typedef std::map <int  ,std::string > Map_TestApiName;

class itest 
{

	static Map_TestApiFN *   getMapApi() 
	{ 
		static Map_TestApiFN  m_map ; 
		return &m_map;
	} 
	static Map_TestApiName *   getMapApiName() 
	{ 
		static Map_TestApiName  m_mapName ; 
		return &m_mapName;
	} 

public:	  
	itest(int appid,PTestMethod  pTestMethod);	
	itest(int appid,PTestMethod  pTestMethod, char* p_str);	
	static int execApi(int appid );
	static int execAll( );
protected:
	itest(void);
	static void RegAPI(int appid,PTestMethod  pTestMethod ) ;
	static void RegAPI(int appid,std::string &pstr ) ;
	static PTestMethod findApi(int appid);
public:	
	~itest(void);
};

const unsigned INT_MAXAPINUM=1024;
static TTestAPI g_testapi[INT_MAXAPINUM];
class itestdiameter:public itest
{
private: 
	static int apinum;
public:
	itestdiameter(int appid,PTestMethod pTestMethod );	
	static int execApi(int appid );
	static int execAll( );

protected:	
	//itestdiameter(void); 
	static void RegAPI(int appid,PTestMethod  pTestMethod ) ;
	static PTestMethod findApi(int appid);
public:
	~itestdiameter(void);

};
 
#endif

