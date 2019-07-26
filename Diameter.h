#include "CAvp.h"
#include "CAvps.h"
 namespace TEST_DIAMETER
{

#ifndef  __CDIAMETER__H__
#define  __CDIAMETER__H__

struct  TDiameterMsg 
{
	friend   class CDiameterMsg;
	UINT4   version :8;
	UINT4   length 	:24;
	UINT4   cmdFlag	:8;
	UINT4   cmdCode	:24;
	UINT4   appID;
	UINT4   hopID;
	UINT4   endID;

	CAvps   m_body;
	UINT4   m_bodyLen;

	TDiameterMsg();	
	~TDiameterMsg();
public:
	unsigned encodeBody   ( const char *buffer );		
	unsigned encodeHeader ( const char *buffer );				
	unsigned  decodeBody   ( const char *buffer );		
	unsigned decodeHeader ( const char *buffer );				

private:
	void setVersion(int version);
	void setCmdFlag(int cmdFlag);
	void setCmdCode(int cmdCode);
	void setAppID(int appid);
	void setHopID(int hopID);
	void setEndID(int endID);
	void setLength();
	int getHeaderLength();
	int getLength();	
	CAvps& getBody();
	void setBody(char *buffer, unsigned int & len);
	int getBodyLen ();
	//是否要4字节对齐
	void setBodyLen(int len);
	void deleteBuffer();
	void logBody();
	void printMsg();
	
} ;

class CDiameterMsg
{
public:
	~CDiameterMsg(void);
	CDiameterMsg ( void);

public:
	
	unsigned decode( const char * buffer,UINT4  maxlen);
	void encode(  char * &buffer,UINT4 & msglen);

	// outer input
	void setMsgBody(char * buffer, unsigned int& len);	

	bool addAvp(CAvp* pavp,int avpnum);	
	bool addAvp(CAvp* pavp);
	bool modAvp(CAvp* pavp);
	int   removeAvp(TAVPCODE avpcode);
 
	CAvp * getAvp(TAVPCODE avpcode); 
//	CAvp * cloneAvp(CAvp* pavp);

private:
	CAvp * getAvp(TAVPCODE avpcode,TAVPCODE avpcode1)
		{return new CAvp();};	
	int  removeAvp(CAvp & avp);
	char *newBuffer(unsigned int buflen);
	void  deleteBuffer();	 

	TDiameterMsg& getDiameterMsg()
	{
		return m_diameterMsg;
	}; 
	CAvps& getBody()
	{
		return getDiameterMsg().getBody();
	};
	
private:	
	TDiameterMsg m_diameterMsg;	
	char *m_buffer;
		
};

#endif
};

