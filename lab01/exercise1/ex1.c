#include <string.h>
#include <stdio.h>
#include "ex1.h"

/* Returns the number of times LETTER appears in STR.
There are two different ways to iterate through a string.
1st way hint: strlen() may be useful
2nd way hint: all strings end in a null terminator */
int num_occurrences(char *str, char letter) {
    int len = strlen(str);
    int occurrences_time = 0;
    for (int i = 0; i < len; i++) {
	    if (str[i] == letter) {
		    occurrences_time++;
	    }
    }
    return occurrences_time;
}

/* Populates DNA_SEQ with the number of times each nucleotide appears.
Each sequence will end with a NULL terminator and will have up to 20 nucleotides.
All letters will be upper case. */
void compute_nucleotide_occurrences(DNA_sequence *dna_seq) {
    char* seq = dna_seq->sequence;
    int len = strlen(dna_seq->sequence);
    dna_seq->A_count = num_occurrences(seq, 'A');
    dna_seq->G_count = num_occurrences(seq, 'G');
    dna_seq->T_count = num_occurrences(seq, 'T');
    dna_seq->C_count = num_occurrences(seq, 'C');
    return;
}
