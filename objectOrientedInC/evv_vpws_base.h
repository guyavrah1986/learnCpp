//evv_vpws_base.h

#include "evv_svc_base.h"

typedef struct _evv_vpws_base evv_vpws_base;

typedef struct _evv_vpws_base
{
    evv_svc_base* pBaseObj;
    char l2_attributes;

    fptrInit         Init;
    fptrContinueWork ContinueWork;
    
    //If there is any employee specific functions; add interface here.
    // ...
	
}evv_vpws_base;

evv_svc_base* new_vpws_base(const char* pRd);           //constructor
void delete_vpws_base(evv_svc_base* pSvcBase);        //destructor
void evv_vpws_base_init(evv_svc_base* pEvvVpwsBase);
void evv_vpws_base_continue_work(evv_svc_base* pEvvVpwsBase);
