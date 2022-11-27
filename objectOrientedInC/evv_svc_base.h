//evv_svc_base.h
#pragma once

typedef struct _evv_svc_base evv_svc_base; 

//declaration of pointers to functions
typedef void    (*fptrInit)(evv_svc_base*);
typedef void    (*fptrContinueWork)(evv_svc_base*);

typedef struct _evv_svc_base 
{
    void* pDerivedObj;
    char* rd[9];
    unsigned long evi_index;

    //interface for function
    fptrInit         Init;
    fptrContinueWork ContinueWork;
}evv_svc_base;


evv_svc_base* new_svc_base(const char* pRd);           //constructor
void delete_svc_base(evv_svc_base* pSvcBase);    //destructor
void evv_svc_base_init(evv_svc_base* pEvvSvcBase);
void evv_svc_base_continue_work(evv_svc_base* pEvvSvcBase);

