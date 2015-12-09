#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 5443   //local port
#define XINUPORT 5444 // remote port
 
int main(void)
{
    struct sockaddr_in si_me, si_other;
   
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    char sbuf[50];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("Error getting socket.\n");
	return 0; 
    }
    
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
   
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(XINUPORT);
    inet_pton(AF_INET, "192.168.1.101", &(si_other.sin_addr));   

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        printf("Error binding socket.\n");
	return 0; 
    }
    
    while(1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);
        
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            printf("Error receiving data.\n");
	    return 0; 
        }
        
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Message: %s\n" , buf);
       
	 printf("Enter the value be sent : ");
        fgets(sbuf,50,stdin);
   
    	printf("Value sent to XINU : %s\n", sbuf);
        
        //now reply the client with the same data
        if (sendto(s, sbuf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            printf("Error sending data.\n");
	    return 0; 
        }
    }
 
    close(s);
    return 0;
}
