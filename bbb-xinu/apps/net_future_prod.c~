#include <prodcons.h>

int net_future_prod(future *fut) 
{
	int j, result;
	j=0;
	j = netserver();
	result =future_set(fut, &j);
	if(result == SYSERR){
		printf("Error setting value in future\n");
	}
	return OK;
}
