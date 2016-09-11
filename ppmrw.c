/*
 ============================================================================
 Name        : ppmrw.c
 Author      : Anthony Black
 Description : CS430 Project 1: Converting between PPM P3 and P6
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	/*
	simple error checking, ensures that the user provides the format to convert to,
	the file to be read, and the file to be written.
	*/
	if(argc != 4){
		printf("Incorrect number of arguments. Args given: %d\r\n", argc);
		return EXIT_FAILURE;
	}
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
