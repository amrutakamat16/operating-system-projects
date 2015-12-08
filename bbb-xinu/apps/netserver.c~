#include <newnet.h>
#include <stdlib.h>

int string_length(char s[]) {
   int c = 0;
 
   while (s[c] != '\0')
      c++;
 
   return c;
}
 int netserver(void){
  
	int32	delay	= 5000;	
	uint32 mask;
	uint32 rmtIp;
	int retries = 3;
	uint16	locport	= 5444;
	uint16	remotePort = 5443;
	dot2ip("192.168.1.100",&mask);
	dot2ip("192.168.1.101",&rmtIp);
	int32 slot;
	int retval;
	int i;
	char msg[] = "Message From XINU";
	int msglen;
	int val;
	
	msglen = string_length(msg);
	slot = udp_register(mask, remotePort, locport);
	
	if(slot == SYSERR){
		printf("Error getting UDP slot.\n");
		return SYSERR;	
	}	
	
	for (i=0; i<retries; i++) {
	
		printf("Requesting value from linux.....\n");    			
		udp_send(slot, msg, msglen);

		printf("Waiting for message from linux.\n");
		retval = udp_recv(slot, msg, sizeof(msg), delay);

		if (retval == TIMEOUT) {
			continue;
		} else if (retval == SYSERR) {
			udp_release(slot);
			return 1;
		}else{
			break;
		}
		
	}
	printf("Received message %s", msg);	
	val = atoi(msg);
	udp_release(slot);
	return val;	
 }
