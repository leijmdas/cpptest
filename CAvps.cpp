#include "stdafx.h"
#include <string.h>
#include "CAvps.h"
#include <assert.h>

using namespace TEST_DIAMETER;
CAvps::CAvps()
{
	m_avpNum=0;
	memset(m_avps,0,sizeof(m_avps));
}

CAvps::~CAvps()
{
  clearAvps();
}

void CAvps::clearAvps()
{
	 for(int i=0;i<getAvpNum();i++)
    {
       delete m_avps[i];
		m_avps[i]=NULL;
		decAvpNum();
    }
}


bool CAvps::addAvp(CAvp* pavp,int avpNum)
{
    if (avpNum<=0)
    {
        return false;
    }
        
    for(int i=0;i<avpNum;i++)
    {
        addAvp(&pavp[i]);
    }       
	return true;
}
	
bool CAvps::addAvp(CAvp* pavp)
{
	if( getAvpNum() < MAX_AVPSCHILD)
	{
		m_avps[ getAvpNum()]= pavp;
		incAvpNum();
	}
    
    return getAvpNum()<= MAX_AVPSCHILD;

} 

int CAvps::modAvp(CAvp& avp )
{
    return ERR_OK;
    int iindex=findAvp(avp);
    if(iindex>=0)
    {
       m_avps[iindex]=&avp;
    }
    return iindex>=0;

}   

int CAvps::findAvp(CAvp & avp)
{
    for(int iindex =0;iindex<getAvpNum();iindex++)
    {
        if(m_avps[iindex]->getAvpCode()==avp.getAvpCode())
        {
            return iindex;
        }
    }
    return ERR_NOFOUND;

}  

/* return>0 array index */
int CAvps::findAvp(  TAVPCODE avpcode )
{
    for(int iindex =0;iindex<getAvpNum();iindex++)
    {
        if(m_avps[iindex]->getAvpCode()==avpcode)
        {
            return iindex;
        }
    }
    return ERR_NOFOUND;
}  

CAvp * CAvps::getAvp(  TAVPCODE avpcode )
{
	int iindex=findAvp(avpcode);
	if(iindex>=0)
	{
		return m_avps[iindex];
	}
	return NULL;
}

int  CAvps::removeAvp(  TAVPCODE avpcode )
{
    int iindex=findAvp(avpcode);
    return removeAvpOfIndex(iindex);
}

int CAvps::removeAvp(CAvp & avp)
{
    int iindex=findAvp(avp);
    return removeAvpOfIndex(iindex);    
}

int  CAvps::removeAvpOfIndex(  int iindex )
{
    CAvp *m_avpsnew[MAX_AVPSCHILD];		
    int j=0;
    if(iindex>=0)
    {
        for(int i=0;i<getAvpNum();i++)
        {
            if(iindex!=i)
            {
                m_avpsnew[j++]=m_avps[i];
            } else
            {
                delete m_avps[i];
				 decAvpNum(); 
            }
        }
       
        for(int i=0;i<getAvpNum();i++)
        {
            m_avps[i]=m_avpsnew[i];
        }
    }
	return ERR_OK;
    
}

unsigned CAvps::encode(  char* pbuffer,  unsigned  umaxLen )    
{
    if(pbuffer=NULL)
	{
		return 0;
	}
	assert(umaxLen>0);
	unsigned ulen=0;
    for(int ipos =0;ipos<getAvpNum();ipos++)
    {
        unsigned int  avpbuflen=0;
        m_avps[ipos]->encode( pbuffer+ulen,avpbuflen );
        if(avpbuflen+ulen>umaxLen)
        {
            test_logDiameter("INFO","CAvps::buildBuffer ERR_DIAMMSG_TOOLONG=%lld",ERR_DIAMMSG_TOOLONG);
            return avpbuflen;
        } 
        umaxLen += avpbuflen;
    }   
    return 0;
}




unsigned TEST_DIAMETER::CAvps::getLength_Align()
{
	unsigned ulen=0;
	for(int i=0; i<getAvpNum();i++)
	{
		ulen += m_avps[i]->getAvpLength_Align();
	}
	return ulen;
}

int TEST_DIAMETER::CAvps::decAvpNum()
{
	if(getAvpNum ()>0)
	{
		m_avpNum--;
	}
	return ERR_OK;				
}

int TEST_DIAMETER::CAvps::incAvpNum()
{ 
		m_avpNum++;
		return ERR_OK;
	 
}

int TEST_DIAMETER::CAvps::getAvpNum()
{
return m_avpNum;

}
