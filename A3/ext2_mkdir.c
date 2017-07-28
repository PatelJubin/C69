#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <getopt.h>
#include "ext2.h"
#include <errno.h>
#include <string.h>
#include <ext2_utilities.h>

unsigned char *disk;

int main(int argc, char *argv[]) {
	//Check number of arguments
	if(argc != 3){
		fprintf(stderr, "Usage: ext2_mkdir <image file name> <path>\n");
		exit(1);
	}
	//Open image
	int fd = open(argv[1], O_RDWR);

	//Map disk image
	disk = mmap(NULL, 128 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(disk == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	char *parent_dir = find_parent(argv[2]);
	struct ext2_inode *p_inode = find_inode(parent_dir, disk);
	
	//error checking
	if(p_inode == NULL){
		printf("directory path doesn't exist");
		exit(ENOENT);
	}
	if(find_inode(argv[2], disk) != NULL){
		printf("file/directory exists");
		exit(EEXIST);
	}
	//code for mkdir
	
}