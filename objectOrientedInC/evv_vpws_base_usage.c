#include <stdio.h>

#include "evv_vpws_base.h"
#include "evv_evi_base.h"

int main(int argc, char** argv)
{
	printf("main - start\n");
	evv_svc_base* vpws = (evv_svc_base*)new_vpws_base("1.1.1.1:5");
	printf("main - create evv_vpws_base on the heap\n");
	vpws->Init(vpws);
	evv_svc_base* evi = (evv_svc_base*)new_evi_base("2.2.2.2:5");
	printf("main - create evv_evi_base on the heap\n");
	evi->Init(evi);
	printf("main - end\n");
	return 0;
}
