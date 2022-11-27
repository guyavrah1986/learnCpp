//evv_evi_base.c

#include <stdlib.h>
#include <stdio.h>

#include "evv_evi_base.h"

evv_svc_base* new_evi_base(const char* pRd)
{
	evv_svc_base* pBaseObj = new_svc_base(pRd);

	evv_evi_base* new_evi_base = (evv_evi_base*)malloc(sizeof(evv_evi_base));
	pBaseObj->pDerivedObj = new_evi_base;
	printf("new_evi_base - create new evv_evi_base at address:%p\n", new_evi_base);
	pBaseObj->Init = evv_evi_base_init;
	pBaseObj->ContinueWork = evv_evi_base_continue_work;
	
	return pBaseObj;
}

          
void delete_evi_base(evv_svc_base* pEvvEviBase)
{
	printf("delete_evi_base - about to delete evv_evi_base at adress:%p\n", pEvvEviBase);
	free(pEvvEviBase);
}      

void evv_evi_base_init(evv_svc_base* pEvvEviBase)
{
	printf("evv_evi_base_init - about to initialize evv_evi_base at adress:%p\n", pEvvEviBase);
}

void evv_evi_base_continue_work(evv_svc_base* pEvvEviBase)
{
	printf("evv_evi_base_continue_work - for evv_evi_base at adress:%p\n", pEvvEviBase);
}
