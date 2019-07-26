// testdiameter.cpp : 定义控制台应用程序的入口点。
// leijianming

#include "stdafx.h"
#include <memory.h> 
#include <stdio.h>
#include "CAvp.h"
#include "Diameter.h"
#include "itestdiameter.h" 
 
#include "TestSuite.h"
using namespace TEST_DIAMETER; 

class TestDemo
{
public:
    void test();
};

class TestDemo1
{
public:
    void test();
    //static TestDemo *td=new TestDemo ;
};

template<class T> void Swap(T &a, T &b);
template<class T> void Swap();

int main(int argc, char* argv[])
{   
    TEST_EXECALL( );    //execAll 
    RUNALL_TESTCASESUITE();
    printf(typeid(TestDemo).name());
    int a=1;
    int b=2;
    Swap(a,b);
    Swap<int>();

    return 1; 
}


template<class T> void Swap(T &a, T& b)
{
        T temp =a;
        a=b;
        b=temp;
        return ;
}

//TestFixture 
typedef void(*NEWPTestMethod)()  ;

#define START_TESTSUITE(CLASSNAME)\
CLASSNAME() \
{
#define REGISTER_TESTCLASS(CLASSNAME)\
CLASSNAME *pclass=new CLASSNAME();
#define REGISTER_TESTFN(p_ptMethod)\
    NEWPTestMethod ptMethod=(NEWPTestMethod) p_ptMethod;
#define END_TESTSUITE()\
};

//TEST_REGAPI(  96021,test);  
class TestClass
{
    typedef   void(TestClass::*PFUN)(); 
public:
    START_TESTSUITE(TestClass)
    REGISTER_TESTCLASS(TestClass)
    //REGISTER_TESTFN(test())
    PFUN ptMethod= &TestClass::test;
    pclass->test();
    //TestClass::(* ptMethod)();
    END_TESTSUITE()
 
    void  test()
    {
        return ;
    };
};

TEST_REGAPI(  96001,exec_testApi_96001);  
int  exec_testApi_96001(int appid)
{

    CDiameterMsg cmsg;  
    // CAvp process
    CAvp *pcavp=new CAvp();  
    pcavp->setValue  (AVPCODE_RETCODE,1L);       
    cmsg.addAvp( pcavp  );    
    pcavp=new CAvp();  
    pcavp->setValue (AVPCODE_STRING,"abcdef");   
    cmsg.addAvp( pcavp );      
    
    CAvps *pavps=new CAvps;
     pcavp=new CAvp();  
     pcavp->setValue (AVPCODE_RETCODE,1L);   
     pavps->addAvp( pcavp );  
     pcavp=new CAvp();  
     pcavp->setValue ( AVPCODE_STRING,"1L");   
     pavps->addAvp( pcavp );  
     CAvp *pgrp=new CAvp() ;
     pgrp->setValue(AVPCODE_GROUP,pavps);
     cmsg.addAvp( pgrp );  
    CAvp &pgrpref=*pgrp;

    char     *msgbuffer  = NULL;
    unsigned int   msglen     = 0;
    cmsg.encode(msgbuffer,msglen);
    cmsg.decode(msgbuffer,msglen);

    // write code fo file
    FILE *f=NULL;
    fopen_s(&f,"f:\\diametermsg.bin","wb+");    
    if(f!=NULL && msgbuffer!=NULL)
    {
        fwrite( msgbuffer,msglen,1,f);          
    }   
    fclose(f);
    return 0;    
}

template<class T> void Swap()
{
    T a=1;
    T b=2;
    T c = a+b;

}

