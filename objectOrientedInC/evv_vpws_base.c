//evv_vpws_base.c

#include <stdio.h>
#include <stdlib.h>
#include "evv_vpws_base.h"

evv_svc_base* new_vpws_base(const char* pRd)
{
	// calling base class ctor
	evv_svc_base* pBaseObj = new_svc_base(pRd);

	// calling self ctor
	evv_vpws_base* new_evv_vpws_base_obj = (evv_vpws_base*)malloc(sizeof(evv_vpws_base));
	printf("new_vpws_base - allocated evv_vpws_base at address:%p\n", new_evv_vpws_base_obj);
	pBaseObj->pDerivedObj = new_evv_vpws_base_obj;

    	//Initializing interface for access to functions (sort of "initializing the VTABLE")
    	pBaseObj->Init = evv_vpws_base_init; 		
    	pBaseObj->ContinueWork = evv_vpws_base_continue_work;
	return pBaseObj;
}

void delete_vpws_base(evv_svc_base* pVpwsBase)
{
	printf("delete_vpws_base - free-ing evv_vpws_base at address:%p\n", pVpwsBase);
	free(pVpwsBase);
}

void evv_vpws_base_init(evv_svc_base* pEvvVpwsBase)
{
	printf("evv_vpws_base_init - got pEvvVpwsBase at address:%p\n", pEvvVpwsBase);
}

void evv_vpws_base_continue_work(evv_svc_base* pEvvVpwsBase)
{
	printf("evv_vpws_base_continue_work - got pEvvVpwsBase at address:%p\n", pEvvVpwsBase);
}
