#ifndef __CAVPMNGR__H__
#define __CAVPMNGR__H__

#include "itestdiameter.h"
#include "CAvp.h"
#include <string.h> 
#include <memory.h>
#include <stdio.h>
#include "CAvps.h"

namespace TEST_DIAMETER
{


//CAvp�Ĺ�����
const int MAX_AVPSCHILD=100;
class CAvp;
class CAvps ;
typedef CAvps    TGROUP;

class CAvps
{
public:
	CAvps();
	~CAvps();

	bool addAvp( CAvp* pavp);	
	bool addAvp( CAvp* pavp,int avpNum);	
	
	int  modAvp( CAvp& avp);	
	int  removeAvp( CAvp &avp );
	int  removeAvp(  TAVPCODE avpcode );
	/* return>0 array index */
	int findAvp(  TAVPCODE avpcode );
	int findAvp( CAvp& avp );	
	//	 return 
	CAvp * getAvp(  TAVPCODE avpcode );
	unsigned getLength_Align();
	//��ѡ���AVP������ΪDIAMETER��Ϣ�������groupAVP��DATA
	// out parameter: newAvpsBuf, newAvpsLen ;
	unsigned  encode( char* pbuffer, unsigned umaxLen ) ;   
	inline int getAvpNum () ;
	
private:		
	int removeAvpOfIndex( int iindex );
	inline int incAvpNum () ;
	inline int decAvpNum () ;	
private :
	void  clearAvps();	
	CAvp * m_avps[MAX_AVPSCHILD];//typedef std::map <TAvp *  ,CAvp*> MapCAvp;
	unsigned   m_avpNum;
};


};

#endif

