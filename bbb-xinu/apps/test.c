#include <newmem.h>

int add(int i);

 void test(){
  	
	int sum = add(100);
	int result = memkill(currpid);
	if(result == SYSERR){
		printf("Error terminating process.\n");	
	}	
	return 0;		
 }

int add(int i){
	
	int sum = 0;
	if(i!=0){		
		sum = i + add(--i);
	}	
	return sum;	
}
