// evv_svc_base.c

#include <stdio.h>
#include <stdlib.h>
#include "evv_svc_base.h"

evv_svc_base* new_svc_base(const char* pRd)
{
	evv_svc_base* new_evv_svc_base_obj = (evv_svc_base*)malloc(sizeof(evv_svc_base));
	printf("new_svc_base - allocated evv_svc_base at address:%p\n", new_evv_svc_base_obj);
	new_evv_svc_base_obj->pDerivedObj = new_evv_svc_base_obj;
    	//Initializing interface for access to functions
    	new_evv_svc_base_obj->Init = NULL; 		//evv_svc_base_init;
    	new_evv_svc_base_obj->ContinueWork = NULL; 	//evv_svc_base_continue_work;
	return new_evv_svc_base_obj;
}


void delete_svc_base(evv_svc_base* pSvcBase)
{
	printf("delete_svc_base - free-ing evv_svc_base at address:%p\n", pSvcBase);
	free(pSvcBase);
}


