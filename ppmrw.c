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

void read_p3(Pixel *buffer, FILE *input_file, int width, int height);

void read_p6(Pixel *buffer, FILE *input_file, int width, int height);

void write_p3(Pixel *buffer, FILE *output_file, int width, int height, int max_color);

void write_p6(Pixel *buffer, FILE *output_file, int width, int height, int max_color);

int main(int argc, char *argv[]) {
	/*
	simple error checking, ensures that the user provides the format to convert to,
	the file to be read, and the file to be written.
	*/
	int width;
	int height;
	int max_color;
	int read_character;
	int original_format;
	FILE *input_file;
	FILE *output_file;
	Pixel *buffer;
	if(argc != 4){
		printf("Incorrect number of arguments. Args given: %d\r\n", argc);
		return EXIT_FAILURE;
	}
	input_file = fopen(argv[2], "r");
	if(input_file == NULL){
		printf("Failed to open input file.\r\n");
		return EXIT_FAILURE;
	}
	//reading the image type (should be P3 or P6)
	read_character = getc(input_file);
	if(read_character != 'P'){
		printf("Input file is not in PPM format.\r\n");
	}
	original_format = getc(input_file);
	if(!(original_format != '6'|| original_format != '3')){
		printf("Please provide a PPM image in either P3 or P6 format. Input given: %c.\r\n", original_format);
	}
	read_character = getc(input_file); //should get newline
	read_character = getc(input_file);//should get either a comment character or number
	//read and print out any comment in image to console
	if (read_character == '#'){
		while(read_character != '\n'){
			read_character = getc(input_file);
		}
		printf("%c", read_character);
	}
	else{  //if there wasn't a comment, we want to go back one character so we're at the start of the line.
		ungetc(read_character, input_file);
	}
	//get width, height, and max color value
	fscanf(input_file, "%d %d\n%d\n", &width, &height, &max_color);
	output_file = fopen(argv[3], "w");
	if(output_file == NULL){
		printf("Error creating output file.\r\n");
		return EXIT_FAILURE;
	} 
	//allocate memory for all the pixels
	buffer = (Pixel *)malloc(width*height*sizeof(Pixel));
	if(original_format == '3'){
		printf("Reading PPM image in P3 format...\r\n");
		read_p3(buffer, input_file, width, height);
	}
	else if(original_format == '6'){
		printf("Reading PPM image in P6 format...\r\n");
		read_p6(buffer, input_file, width, height);
	}
	else{
		printf("Error: Unknown format.");
		return EXIT_FAILURE;
	}
	if(*argv[1]== '3'){
		printf("Creating PPM image in P3 format...\r\n");
		write_p3(buffer, output_file, width, height, max_color);	
	}
	else if(*argv[1]== '6'){
		printf("Creating PPM image in P6 format...\r\n");
	 	write_p6(buffer, output_file, width, height, max_color);
	}
	else{
		printf("Inappropriate format value. Please enter 3 or 6. Value given %c.\r\n", *argv[1]);
		return EXIT_FAILURE;
	}	
	fclose(input_file);
	fclose(output_file);
	return EXIT_SUCCESS;
}

void read_p3(Pixel *buffer, FILE *input_file, int width, int height){
//fgetc() and atoi() to read and convert ascii
	int current_read;
	int red, green, blue;
	for(int i = 0; i < width*height; i++){
		current_read = fgetc(input_file);
		while(current_read  == ' ' || current_read  == '\n'){ //jumps to first character of first number
			current_read = fgetc(input_file);
		}
		ungetc(current_read, input_file); //since we're now at the beginning of a number, go back one.
		fscanf(input_file, "%d %d %d", &red, &green, &blue);
		buffer[i].r = red;
		buffer[i].g = green;
		buffer[i].b = blue;
	}	
}

void read_p6(Pixel *buffer, FILE *input_file, int width, int height){
	//reading each pixel into memory for a P6 image
	for(int i = 0; i < width*height; i++){
		fread(&buffer[i].r, 1, 1, input_file);
		fread(&buffer[i].g, 1, 1, input_file);
		fread(&buffer[i].b, 1, 1, input_file);
	}
}

void write_p3(Pixel *buffer, FILE *output_file, int width, int height, int max_color){
	fprintf(output_file, "P3\n%d %d\n%d\n", width, height, max_color);
	int current_width = 1;
	for(int i = 0; i < width*height; i++){
		fprintf(output_file, "%d %d %d ", buffer[i].r, buffer[i].g, buffer[i].b);
		if(current_width >= 70%12){ //ppm line length = 70, max characters to pixels = 12.
			fprintf(output_file, "\n");
			current_width = 1;
		}
		else{
			current_width++;
		}
	}
}

void write_p6(Pixel *buffer, FILE *output_file, int width, int height, int max_color){
	//fwrite() to write binary
	fprintf(output_file, "P6\n%d %d\n%d\n", width, height, max_color);
	char string[20];
	for(int i = 0; i < width*height; i++){
		fwrite(&buffer[i].r, 1, sizeof(buffer[i].r), output_file);
		fwrite(&buffer[i].g, 1, sizeof(buffer[i].g), output_file);
		fwrite(&buffer[i].b, 1, sizeof(buffer[i].b), output_file);
	}		
}

