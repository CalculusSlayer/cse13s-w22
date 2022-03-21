#include "search_util.c"

char **load_vocabulary(char *filename, size_t *num_words) {
    char **out = NULL;
    size_t n = 0;
    char buf[10];
    size_t array_size = 1;
    out = (char **) calloc(sizeof(char *), array_size);
    FILE *infile = fopen(filename, "r");
    while (fgets(buf, 10, infile) != NULL) {
        n++;
        if (n >= array_size) {
            array_size *= 2;
            out = (char **) realloc(out, sizeof(char *) * array_size);
        }
        out[n - 1] = strndup(buf, 6);
        out[n - 1][5] = '\0';
    }
    fclose(infile);
    *num_words = n;
    return out;
}

int my_score_letter(char letter, char **vocabulary, size_t num_words) {

    int score = 0;

    // TODO(you): implement this function!
    for (size_t i = 0; i < num_words; i++) {
        if (*(vocabulary + i) == NULL) {
            continue;
        }
        if (strchr(*(vocabulary + i), letter) != NULL) {
            score += 1;
        }
    }

    return score;
}

int my_score_word(char *word, int *letter_scores) {

    // TODO(you): implement this function!

    int sum = 0;
    char temp;

    // Maybe check if word is NULL before?
    char *sorted_word = strdup(word);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (sorted_word[j] > sorted_word[j + 1]) {
                temp = sorted_word[j + 1];
                sorted_word[j + 1] = sorted_word[j];
                sorted_word[j] = temp;
            }
        }
    }

    sum += *(letter_scores + (sorted_word[0] - 97));

    for (int i = 1; i < 5; ++i) {
        if (sorted_word[i] != sorted_word[i - 1]) {
            sum += *(letter_scores + (sorted_word[i] - 97));
        }
    }

    // printf("sorted word - %s\n", sorted_word);

    free(sorted_word);

    return sum;
}

int main(void) {
	//printf("This is a test.\n");
	size_t num_words = 0;
	char **voc = load_vocabulary("small_vocabulary.txt", &num_words);
	/*
	int score1, score2, score3, score4;
	score1 = score_letter('a', voc, num_words); 
	score2 = score_letter('b', voc, num_words); 
	score3 = score_letter('c', voc, num_words); 
	score4 = score_letter('d', voc, num_words); 
	printf("Score1 = %i, Score2 = %i, Score3 = %i, Score4 = %i\n", score1, score2, score3, score4);
	*/

	int *scores = (int *) malloc(sizeof(int) * 26);
	for (unsigned int i=0; i < 26; i++) {
		*(scores+i) = score_letter(i + 'a', voc,  num_words);
	}
	
	printf("********************* TESTING SCORE_LETTER (1ST FUNC) *******************\n");
	for (unsigned int i=0; i < 26; i++) {
		if (my_score_letter(i + 'a', voc, num_words) != *(scores+i)) {
			printf("Error at index: %u.\n", i);
		}
	}

	int *word_scores = (int *) malloc(sizeof(int) * num_words);
	for (unsigned int i=0; i < 26; i++) {
		*(word_scores+i) = score_word(voc[i], scores);
	}

	printf("****************** TESTING SCORE_WORD (2ND FUNC) *******************\n");
	for (unsigned int i=0; i < 26; i++) {
		if (my_score_word(voc[i], scores) != *(word_scores+i)) {
			printf("Error at index: %u.\n", i);
		}
	}

	/*
	int w1, w2, w3, w4;
	w1 = score_word(voc[0], my_scores);
	w2 = score_word(voc[1], my_scores);
	w3 = score_word(voc[2], my_scores);
	w4 = score_word(voc[10], my_scores);
	printf("w1 = %i, w2 = %i, w3 = %i, w4 = %i\n", w1, w2, w3, w4);
	*/


	return 0;
}
