#include "StdAfx.h"
#include "Diameter.h"
#include "CAvps.h"
#include "CAvp.h"

using namespace TEST_DIAMETER;
TDiameterMsg::TDiameterMsg()
{
	memset(this,0,sizeof(this));
	(*this).setVersion(1);
	(*this).setCmdFlag(1);
	(*this).setCmdCode(272); 
	//htons(272);//ntohs 、 ntohl 、 htons 和 htonl
	(*this).setAppID(1);
	(*this).setHopID(2);
	(*this).setEndID(3);
	(*this).printMsg(); 
}

TDiameterMsg::~TDiameterMsg()
{
	deleteBuffer();

}

void TDiameterMsg::printMsg()	
{
	test_logDiameter ("","version=%d\n",version);
	test_logDiameter ("","length=%d\n",length);
	test_logDiameter ("","cmdFlag=%d\n",cmdFlag);
	test_logDiameter ("","cmdCode=%d\n",cmdCode);
	test_logDiameter ("","AppID=%d\n",appID);
	test_logDiameter ("","HopID=%d\n",hopID);
	test_logDiameter ("","EndID=%d\n",endID);
}
 

int TDiameterMsg::getBodyLen ()
{
	return getBody().getLength_Align();
} 

//是否要4字节对齐
void TDiameterMsg::setBodyLen(int len)
{
	m_bodyLen=len;
}; 

void TDiameterMsg::deleteBuffer()
{

} 

void TDiameterMsg::logBody()
{
	for(int i=0;i<getBodyLen(); i++)
	{
		//test_logDiameter("INFO","%02d",*(m_pBody+i));
	}		
}

void TDiameterMsg::setVersion(int version)
{
	this->version=version;
} 

void TDiameterMsg::setCmdFlag(int cmdFlag)
{
	this->cmdFlag=cmdFlag;
}  

void TDiameterMsg::setCmdCode(int cmdCode)
{
	this->cmdCode=cmdCode;
} 

void TDiameterMsg::setAppID(int appid)
{
	this->appID=appid;
} 

void TDiameterMsg::setHopID(int hopID)
{
	this->hopID=hopID;
} 

void TDiameterMsg::setEndID(int endID)
{
	this->endID=endID;
} 

void TDiameterMsg::setLength()
{
	length=getHeaderLength()+getBodyLen();		
} 

int TDiameterMsg::getHeaderLength()
{
	return 8; //no vendorod //sizeof(TDiameterMsg)-sizeof(char *)-sizeof(int);
} 

int TDiameterMsg::getLength()
{
	setLength();
	return length;
} 
	

unsigned TDiameterMsg::encodeHeader(const char *buffer)
{
	setLength();
	if(buffer!=NULL)
	{
		memcpy((void*)buffer,this,getHeaderLength());
		return getHeaderLength();
	}
	return 0;
}
	
unsigned TDiameterMsg::encodeBody(const char * buffer)
{
	if(buffer==NULL)
	{
		return 0;
	}
	memcpy((void*)buffer,this,getHeaderLength());
	return ERR_OK;
}

CDiameterMsg::CDiameterMsg(void)
{
    memset( &m_diameterMsg,0,sizeof(m_diameterMsg) );
    m_buffer=NULL;   
}


CDiameterMsg::~CDiameterMsg(void)
{
    deleteBuffer();
	
}

void CDiameterMsg::deleteBuffer()
{
    if(m_buffer!=NULL)
	{
		delete[] m_buffer;	
		m_buffer=NULL;
	}
}

char * CDiameterMsg::newBuffer( unsigned int buflen )
{
    deleteBuffer();
	m_buffer = new char[buflen];
	memset( m_buffer,0, buflen );
	return m_buffer;
}


bool CDiameterMsg::addAvp(CAvp* pavp,int avpnum)
{
    return getBody().addAvp(pavp,avpnum);
}

bool CDiameterMsg::addAvp(CAvp* pavp)
{
    return  getBody().addAvp(pavp);
}

int CDiameterMsg::removeAvp(CAvp & avp) 
{
    return getBody().removeAvp(avp);
}

int   CDiameterMsg::removeAvp(TAVPCODE avpcode)
{
    return getBody().removeAvp(avpcode);
}

bool CDiameterMsg::modAvp(CAvp* pavp)
{
	removeAvp(*pavp) ;
	return addAvp(pavp);
};
	
CAvp * CDiameterMsg::getAvp( TAVPCODE avpcode )
{
	return getBody().getAvp(avpcode);
}

void CDiameterMsg::encode(  char*& buffer, unsigned & msglen )
{	
	msglen = getDiameterMsg().getLength();
	buffer   = newBuffer(msglen);
	unsigned hlen=getDiameterMsg().encodeHeader   (  buffer );			
	unsigned blen=getDiameterMsg().encodeBody  (  buffer+hlen );			
}
unsigned CDiameterMsg::decode( const char * buffer,UINT4  maxlen)
{
	unsigned headlen=getDiameterMsg().decodeHeader   (  buffer );			
	unsigned bodylen=getDiameterMsg().decodeBody(  buffer+headlen );	
	return headlen+bodylen;
}

// end of diameter.cpp



CAvps& TEST_DIAMETER::TDiameterMsg::getBody()
{
	return m_body;
}

unsigned TEST_DIAMETER::TDiameterMsg::decodeBody( const char *buffer )
{
return 1;
}

unsigned TEST_DIAMETER::TDiameterMsg::decodeHeader( const char *buffer )
{
return 1;
}
