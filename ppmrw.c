/*
 ============================================================================
 Name        : ppmrw.c
 Author      : Anthony Black
 Description : CS430 Project 1: Converting between PPM P3 and P6
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Pixel{
	unsigned char r, b, g;
};

int main(int argc, char *argv[]) {
	/*
	simple error checking, ensures that the user provides the format to convert to,
	the file to be read, and the file to be written.
	*/
	if(argc != 4){
		printf("Incorrect number of arguments. Args given: %d\r\n", argc);
		return EXIT_FAILURE;
	}
	int read_character;
	FILE *input_file = fopen(argv[2], "r");
	read_character = getc(input_file);
	if(read_character != 'P'){
		printf("Input file is not in PPM format.\r\n");
	}
	read_character = getc(input_file);
	printf("Type of image: P%c.\r\n", read_character);
	FILE *output_file = fopen(argv[3], "w");
	/*
	buffer = buffer[height];
	for (int i=0; i<height; i++){
		buffer[i]= (Pixel *)malloc(width*sizeof(pixel);
	}*/
	return EXIT_SUCCESS;
}
/*
void read_p3(){
//fgetc() and atoi() to read and convert ascii
}

void read_p6(){
//fread() to read binary
}

void write_p3(){
//fprintf() to write ascii
}

void write_p6(){
//fwrite() to write binary
}
*/
