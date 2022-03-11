#include <stdio.h>

int main(void) {
	FILE *infile;
	infile = fopen("abc.txt", "r");
	
	char buf[4096];
	while (fgets(buf, 30, infile)) {
		 printf("%c", buf[0]);
		 printf("%c", buf[1]);
		// printf("%c\n", buf[2]);
		// printf("%c\n", buf[3]);
}
	fclose(infile);
	return 0;
}
