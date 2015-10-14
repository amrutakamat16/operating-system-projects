#include <future.h> 
#include <stdio.h>

/*Global variable for producer consumer*/
extern int n; /*this is just declaration*/

/* Declare the required semaphores */
extern sid32 consumed, produced;   

/*function Prototype*/
void consumer(int count);
void producer(int count);


/* Declare the required futures */
extern future *f1, *f2, *f3;   

/*function Prototype*/
uint future_cons(future *fut);
uint future_prod(future *fut);

