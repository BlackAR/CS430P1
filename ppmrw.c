/*
 ============================================================================
 Name        : ppmrw.c
 Author      : Anthony Black
 Description : CS430 Project 1: Converting between PPM P3 and P6
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Pixel{
	unsigned char r, b, g;
}Pixel;

int main(int argc, char *argv[]) {
	/*
	simple error checking, ensures that the user provides the format to convert to,
	the file to be read, and the file to be written.
	*/
	int width;
	int height;
	int max_color;
	int read_character;
	FILE *input_file;
	FILE *output_file;
	int current_width;
	Pixel *buffer;
	if(argc != 4){
		printf("Incorrect number of arguments. Args given: %d\r\n", argc);
		return EXIT_FAILURE;
	}
	input_file = fopen(argv[2], "r");
	//reading the image type (should be P3 or P6)
	read_character = getc(input_file);
	if(read_character != 'P'){
		printf("Input file is not in PPM format.\r\n");
	}
	read_character = getc(input_file);
	printf("Type of image: P%c.\r\n", read_character);
	read_character = getc(input_file);
	if(read_character == '\n'){
		printf("End of line.");
	}
	read_character = getc(input_file);
	//read and print out any comment in image to console
	if (read_character == '#'){
		while(read_character != '\n'){
			printf("%c", read_character);
			read_character = getc(input_file);
		}
		printf("%c", read_character);
	}
	else{  //if there wasn't a comment, we want to go back one character so we're at the start of the line.
		ungetc(read_character, input_file);
	}
	//get width, height, and max color value
	fscanf(input_file, "%d %d\n%d\n", &width, &height, &max_color);
	printf("width: %d, height: %d, max color: %d \r\n", width, height, max_color);
	output_file = fopen(argv[3], "w");
	//allocate memory for all the pixels
	buffer = (Pixel *)malloc(width*height*sizeof(Pixel));	
	//reading each pixel into memory for a P6 image
	for(int i = 0; i < width*height; i++){
		fread(&buffer[i].r, 1, 1, input_file);
		fread(&buffer[i].g, 1, 1, input_file);
		fread(&buffer[i].b, 1, 1, input_file);
	}
	//writing each pixel into file in P3 format
	fprintf(output_file, "P3\n%d %d\n%d\n", width, height, max_color);
	current_width = 1;
	for(int i = 0; i < width*height; i++){
		fprintf(output_file, "%d %d %d ", buffer[i].r, buffer[i].g, buffer[i].b);
		if(current_width == width){
			fprintf(output_file, "\n");
			current_width = 1;
		}
		else{
			current_width++;
		}
	}
	fclose(input_file);
	fclose(output_file);
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
