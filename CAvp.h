#ifndef  __CAVP__H__
#define  __CAVP__H__

#include <string.h> 
#include <memory.h>
#include <stdio.h>
#include "CAvps.h"
#include "itestdiameter.h"
void  test_logDiameter(char*type,char *format,char *msg);
void  test_logDiameter(char*type,char *format,int msg    );
namespace TEST_DIAMETER
{

class CAvp;
struct TAvp;
typedef std::map <TAvp *  ,CAvp*> MapCAvp;
 
class CAvps;
struct TAvp
{
	friend class CAvp;
	TAVPCODE avpcode;
	UINT4   avpflag_v		:1;
	UINT4   avpflag_m		:1;
	UINT4   avpflag_p		:1;
	UINT4   avpflag_reserve	:5;	
	UINT4   avplength		    :24;//8+4
	UINT4   vendorid;

	TAvpType m_avptype;
	union TAVPValue
	{
		TINT4 iValue;
		TINT8 lValue;
		TDouble dDouble;
		char strValue[AVPDATA_MAXLENGTH];	//string binary	
	};
	TAVPValue avpvalue;
	UINT4  avpvaluesize;	//getfrom fn static MapCAvp m_map;	//CAvps m_avps;
    CAvps  *m_pavps ;	
public:	
	TAvp();	
	~TAvp();	 
	int encodeHeader (const char *pbuffer,unsigned  & ibuflen ){return 0;};	
	int encodeBody    (const char *pbuffer,unsigned  & ibuflen ){return 0;};	
	CAvps& getBody();
	
public:
	unsigned  getAvpHeaderLength();
	unsigned getAvpLength();
	unsigned getAvpLength_Align();
	void  setAvpValueSize(unsigned size);
	unsigned getAvpValueSize();
	unsigned getAvpValueSize_Align();
	TAVPCODE getAvpCode();
	void setAvpCode(TAVPCODE avpcode);
	void setInt4Value(int iValue);
	void setInt8Value(long long lValue);
	void setStrValue(char* strValue,unsigned ulen);
	void setGroupValue(CAvps *pgroup);

private:	
	TAvpType getAvpType();
	void setAvpType(TAvpType avptype);
	bool hasVendorID();
 
}   ;
 
class CAvp
{
public:
	CAvp();
	~CAvp();
	//void operator=(CAvp* pavp);
	int encode ( char *pbuffer, unsigned int & ulen );	
	void setValue ( TAVPCODE avpCode, CAvps *pgroup );
	void setValue( TAVPCODE avpCode, int ivalue);
	void setValue (TAVPCODE avpCode,long long   lvalue);
	void setValue (TAVPCODE avpCode,  char *strValue, unsigned ulen);
	void setValue (TAVPCODE avpCode,  char *strValue);
	TAVPCODE getAvpCode(){return getAvp().getAvpCode();};
	unsigned getAvpLength_Align();
	TAvp& getAvp() ;
	void addAvp(CAvp*pavp);

private:
	TAvp m_avp;	

};
 
}

#endif

