#include "hw5.c"

char **my_load_vocabulary(char *filename, size_t *num_words) {
	char **out = NULL;
	unsigned long long size_out = 0;
	unsigned long long cap = 16;
	char my_buf[7];

	out = (char **) realloc(out, cap * sizeof(char *));
	FILE *infile = fopen(filename, "r");

	while (fgets(my_buf, 7, infile)) {
		my_buf[5] = '\0';
		*(out+size_out) = strdup(my_buf);
		size_out += 1;
		if (size_out >= cap) {
			cap *= 2;
			out = (char **) realloc(out, cap * sizeof(char *));
		}

	}

	fclose(infile);
	*num_words = size_out;

	return out;
}
/*
void my_free_vocabulary(char **vocabulary, size_t num_words) {
	for (size_t count = 0; count < num_words; count++) {
		free(vocabulary[count]);
		vocabulary[count] = NULL;
	}

	free(vocabulary);
	vocabulary = NULL;
}
*/

int main(void) {
	char result[6] = {0};

	score_guess("titan", "titan", result);
	printf("%s\n", result);

	score_guess("abcde", "ghijk", result);
	printf("%s\n", result);
	score_guess("abcde", "bcdea", result);
	printf("%s\n", result);
	score_guess("abcde", "afbez", result);
	printf("%s\n", result);
	score_guess("xggyx", "agygz", result);
	printf("%s\n", result);
	
	printf("\n");
	char *small_vocab[] = {"tully", "aborn", "story", "kings",
		"maple", "johan", "rohan", "mohan", "sohan", "tibor"};
	
	if (valid_guess("tully", small_vocab, 10)) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}
	if (valid_guess("tibor", small_vocab, 10)) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}
	if (valid_guess("asdfg", small_vocab, 10)) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}
	if (valid_guess("slsls", small_vocab, 10)) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}
	
	printf("\n");

	size_t num_words1 = 0;
	size_t num_words2 = 0;
	char **list1 = load_vocabulary("vocabulary.txt", &num_words1);
	char **list2 = my_load_vocabulary("vocabulary.txt", &num_words2); 
	bool match = true;

	for (int i = 0; i < 2309; i++) {
		if (strcmp(list1[i], list2[i]) != 0) {
			match = false;
			break;
		}
	}

	if (match) {
		printf("Students words load correctly.\n");
	}
	else {
		printf("There's a mistake somewhere.\n");
	}


	printf("%zu words were read from student", num_words1); // 2309
	printf("%s\n", list1[0]); // cigar
	printf("%s\n", list1[2308]); // shave

	/*
	for (int count = 0; count < 10; count++) {
		printf("%s\n", list1[count]);
	}
	*/

	free_vocabulary(list1, num_words1);
	free_vocabulary(list2, num_words2);

	return 0;
}
