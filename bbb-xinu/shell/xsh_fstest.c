#include <xinu.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "fs.h"

#define SIZE 2000

void clean_up(char *buf1, char *buf2);
/**
 * @ingroup shell
 *
 * Shell command fstest.
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_fstest(int nargs, char *args[])
{
    	int rval;
    	int fd, i, j, fd1;
    	char *buf1, *buf2;
    	char *filename;
    
    	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    	{
       		printf("Usage: %s filename\n\n", args[0]);
        	printf("Description:\n");
        	printf("\tFilesystem Test\n");
		
        	printf("Options:\n");
		printf("\tFile name\n");
        	printf("\t--help\tdisplay this help and exit\n");
        	return OK;
    	}

    /* Check for correct number of arguments */
    	if (nargs > 2)
    	{
        	fprintf(stderr, "%s: too many arguments\n", args[0]);
        	fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        	return SYSERR;
    	}
    	if (nargs < 2)
    	{
        	fprintf(stderr, "%s: too few arguments\n", args[0]);
        	fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
		printf("\tRequired file name to demonstrate\n");
        	return SYSERR;
    	}

    	filename = getmem(FILENAMELEN * sizeof(char));

    	strncpy(filename,args[1],FILENAMELEN);

#ifdef FS_H

    	bs_mkdev(0, MDEV_BLOCK_SIZE, MDEV_NUM_BLOCKS); /* device "0" and default blocksize (=0) and count */
    	fs_mkfs(0,DEFAULT_NUM_INODES); /* bsdev 0*/
    
    	buf1 = getmem(MAXSIZE*sizeof(char));
    	buf2 = getmem(MAXSIZE*sizeof(char));
    	fs_printfreemask();

    	fd = fs_create(filename, O_CREAT);
	if(fd!=OK){
		printf("\n Creation failed.");
		clean_up(buf1, buf2);
    	}

	if(fd!=OK){
		printf("\n Creation failed.");
		clean_up(buf1, buf2);
    	}

    	for(i=0; i<SIZE; i++)
    	{
        	j = i%(127-33);
        	j = j+33;
       		buf1[i] = j;
    	}
    

    	fd = fs_open(filename,O_WRONLY);
	if(fd==-1){
		printf("\n Opened failed.");
		clean_up(buf1, buf2);
    	}
	
    	
    	rval = fs_write(fd,buf1,SIZE);
    	if(rval == 0 || rval != SIZE )
    	{
        	printf("\n\r File write failed");
        	clean_up(buf1, buf2);
    	}
    	printf("\n %d bytes written!\n",rval);
    	//fs_printfreemask();
    	if(fs_close(fd)!=OK){
		printf("\n File close failed.");
		clean_up(buf1, buf2);
    	}

	/* Read after seeking to different position */
	if((fd = fs_open(filename,O_RDONLY)) == -1){
		clean_up(buf1, buf2);
	}
	
	if(fs_seek(fd, FS_BEGIN, 1023)==-1){
		clean_up(buf1, buf2);
	}
	
	rval = fs_read(fd, buf2, SIZE);
	printf("\n Data read: \n %s",buf2);
	printf("\n Data read %d bytes.\n",rval);
	if(rval < 0){
		clean_up(buf1, buf2);
	}
	
	if(fs_close(fd)!=OK){
		printf("\n File close failed.");
		clean_up(buf1, buf2);
    	}
	printf("\n File closed after reading.\n");
    	fs_printfreemask();
	clean_up(buf1, buf2);   
#else
    	printf("No filesystem support\n");
#endif

    	return OK;
}

void clean_up(char *buf1, char *buf2){
	freemem(buf1,MAXSIZE);
    	freemem(buf2,MAXSIZE);
	exit(1);
}

