#include "stdafx.h"
#include "CAvp.h"
using namespace TEST_DIAMETER;

void  test_logDiameter(char*type,char *format,char *msg)
{
}

void  test_logDiameter(char*type,char *format,int msg)
{
	printf (format,msg);
}
TAvp::TAvp()
{
	memset(this,0,sizeof(TAvp));
	m_pavps=NULL;
}

TAvp::~TAvp()
{
	if(NULL!=m_pavps)
	{
		delete m_pavps;
		m_pavps=NULL;
	}
}
unsigned  TAvp::getAvpHeaderLength()
{ 
	unsigned iAvpheaderLen=12;
	if( !hasVendorID () )
	{
		iAvpheaderLen -= 4 ;
	} 
	return iAvpheaderLen;
};

TAVPCODE TAvp::getAvpCode()
{
	return this->avpcode ;
}

void TAvp::setAvpCode(TAVPCODE avpcode)
{
	this->avpcode=avpcode;
}

 
void TAvp::setGroupValue(CAvps* pgroup)
{
	if(m_pavps==NULL)
	{
		m_pavps=pgroup;
	} else
	{
		delete m_pavps;
		m_pavps=pgroup;
	}
	setAvpValueSize( m_pavps->getLength_Align() );
}

TAvpType TAvp::getAvpType()
{		  
	return m_avptype;
};

void TAvp::setAvpType(TAvpType avptype)
{
	this->m_avptype=avptype;		
}

CAvps & TAvp::getBody()
{
	if(m_pavps==NULL)
	{
		 m_pavps=new CAvps;
	}
	return *m_pavps;
}


bool TAvp::hasVendorID()
{
	return avpflag_v==1 ;
}
 
TAvp& CAvp::getAvp()
{
	return m_avp;
};


CAvp::CAvp()
{
    
};

CAvp::~CAvp()
{
     
};
 

void CAvp::setValue( TAVPCODE avpCode, int ivalue)
{
	getAvp().setAvpCode(avpCode);
	getAvp().setInt4Value(ivalue);
}

void  CAvp::setValue (TAVPCODE avpCode,long long   lvalue)
{
	getAvp().setAvpCode(avpCode);
	getAvp().setInt8Value(lvalue);
};

void  CAvp::setValue (TAVPCODE avpCode,  char *strValue, unsigned ulen)
{
	getAvp().setAvpCode(avpCode);
	getAvp().setStrValue(strValue,ulen);
}

void CAvp::setValue ( TAVPCODE avpCode, CAvps *pgroup )
{
		getAvp().setAvpCode(avpCode);
		getAvp().setAvpType(AVPTYPE_GROUP);
		getAvp().setGroupValue(pgroup);
};

int CAvp::encode ( char *pbuffer, unsigned  & ulen )
{			
	if(pbuffer==NULL)
	{
		return ERR_NULLPOINT;
	}

	// build header
	getAvp().encodeHeader(pbuffer,ulen);
	// build avpbody
	unsigned  iAvpHeaderLen =  getAvp().getAvpHeaderLength();		
	getAvp().encodeBody(pbuffer,ulen);
	return ERR_OK;
}

unsigned TEST_DIAMETER::TAvp::getAvpLength_Align()
{
	int len=getAvpLength() ;
	if(len%4>0)
	{
		len=len+(4-len%4);
	}
	return len;
}

unsigned TEST_DIAMETER::TAvp::getAvpLength()
{
	return this->avplength;
}

void TEST_DIAMETER::TAvp::setStrValue( char* strValue,unsigned ulen )
{
	strcpy( this->avpvalue.strValue,strValue);
	setAvpValueSize(ulen);
}

void TEST_DIAMETER::TAvp::setInt8Value( long long lValue )
{
	this->avpvalue.lValue=lValue;
		setAvpValueSize(8);
}

void TEST_DIAMETER::TAvp::setInt4Value( int iValue )
{
	this->avpvalue.iValue=iValue;
	setAvpValueSize(4);
}

void TEST_DIAMETER::TAvp::setAvpValueSize( unsigned size )
{
	avpvaluesize=size;
	avplength=getAvpHeaderLength()+avpvaluesize;
}

void TEST_DIAMETER::CAvp::setValue( TAVPCODE avpCode, char *strValue )
{
	setValue( avpCode,strValue,strlen(strValue) );
	getAvp().setAvpType(AVPTYPE_BINARY);
}

void TEST_DIAMETER::CAvp::addAvp( CAvp*pavp )
{
	getAvp().getBody().addAvp(pavp);
}

unsigned TEST_DIAMETER::CAvp::getAvpLength_Align()
{
	return getAvp().getAvpLength_Align();
}
