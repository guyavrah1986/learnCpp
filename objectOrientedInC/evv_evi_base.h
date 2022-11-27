//evv_evi_base.h

#include "evv_svc_base.h"

typedef struct _evv_evi_base
{
    evv_svc_base* pBaseObj;
    unsigned long irbifcIndex;

    fptrInit         Init;
    fptrContinueWork ContinueWork;
    
    //If there is any employee specific functions; add interface here.
    // ...
	
}evv_evi_base;

evv_svc_base* new_evi_base(const char* pRd);           //constructor
void delete_evi_base(evv_svc_base* pSvcBase);        //destructor
void evv_evi_base_init(evv_svc_base* pEvvEviBase);
void evv_evi_base_continue_work(evv_svc_base* pEvvEviBase);

