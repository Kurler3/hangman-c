#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

int* checkIfGuessedLetter(char word_to_guess[], char guessed_letters[], char guessed_letter);
int* findCharIndexesInString(const char *str, char ch, int *count);

int main() {

    // 

    // Init game states
    char *gamestates[]={
                     "   =====|\n"
                     "        |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "        |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     "        |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     "  |     |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     "  |-    |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     " -|-    |\n"
                     "        |\n"
                     "       ===\n",

                     "  |=====|\n"
                     "  O     |\n"
                     " -|-    |\n"
                     "  |     |\n"
                     "       ===\n",

                     "   |=====|\n"
                     "   O     |\n"
                     "  -|-    |\n"
                     "  //     |\n"
                     "       ===\n"

    };

    // Game states length
    int gamestates_length = sizeof(gamestates) / sizeof(gamestates[0]);

    // Init guesses
    int guesses = gamestates_length - 1;

    //TODO Get random word from API (make sure its lower case)
    char word_to_guess[] = "test";

    int word_to_guess_length = strlen(word_to_guess);

    // Init guessed letters, with allocated memory of the same size of bytes as the size of the word to guess * bytes of a char
    char guessed_letters[word_to_guess_length + 1];

    // Set all guessed letters to underscore initially.
    memset(guessed_letters, '_', word_to_guess_length);

    guessed_letters[word_to_guess_length] = '\0';

    // Loop until either no more guesses, or guessed right
    while(guesses > 0) {

        // Print the gamestate
        printf("%s\n", gamestates[guesses]);

        // Print the guessed letters
        printf("Guessed letters: %s\n", guessed_letters);

        printf("Guess a letter: ");

        // Get the user char
        char curr_guessed_letter;

        scanf(" %c", &curr_guessed_letter);  

        // Make sure its lower case
        curr_guessed_letter = tolower(curr_guessed_letter);

        // Get the guessed indexes
        int* guessed_indexes = checkIfGuessedLetter(word_to_guess, guessed_letters, curr_guessed_letter);

        // If guessed correct => put the chars in the guessed_letters and check if won
        if(guessed_indexes != NULL && guessed_indexes[0] != -1) {

            int guessed_indexes_length = sizeof(guessed_indexes) / sizeof(guessed_indexes[0]);

            // Loop through the indexes and put the chars in the guessed_letters
            for(int i = 0; i < guessed_indexes_length; i++) {
                guessed_letters[guessed_indexes[i]] = curr_guessed_letter;
            }

            // Check if won
            if(strcmp(guessed_letters, word_to_guess) == 0) {
                printf("Congratulations! You guessed the word correctly!\n");
                return 0;
            }
        } else {
            // Print
            printf("You guessed wrong!\n");
            guesses -= 1;
            printf("You have %d guesses left!\n", guesses);
        }
    }

    printf("Looks like you didn't guess the word correctly! This was the word: %s", word_to_guess);

    return 0;
}

// Check if guessed letter correctly
int* checkIfGuessedLetter(char word_to_guess[], char guessed_letters[], char guessed_letter) {

    int countOfIdxInGuessedLetters;

    // Check if guessed letter is already in guessed letters
    int* indexesInGuessedLetters = findCharIndexesInString(
        guessed_letters,
        guessed_letter,
        &countOfIdxInGuessedLetters
    );

    // If count is bigger than 0 (already guessed this char) => return null pointer
    if(countOfIdxInGuessedLetters > 0) {
        return NULL;
    }

    // Find the indexes in the word to guess
    int countOfIdxInWordToGuess;

    // Check if guessed letter is already in guessed letters
    int* indexesInWordToGuess = findCharIndexesInString(
        word_to_guess,
        guessed_letter,
        &countOfIdxInWordToGuess
    );

    return indexesInWordToGuess;
}

// Check if char is in string
int* findCharIndexesInString(const char *str, char ch, int *count) {
    int len = strlen(str);
    int* indexes = NULL;
    int index_count = 0;

    // Allocate memory for the maximum possible number of indexes
    indexes = (int*)malloc(len * sizeof(int));
    if (indexes == NULL) {
        *count = 0;
        return NULL; // Memory allocation failed
    }

    // Loop through the string to find the indexes
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            indexes[index_count++] = i;
        }
    }

    // Resize the memory to fit the actual number of indexes found
    indexes = realloc(indexes, index_count * sizeof(int));
    if (indexes == NULL && index_count > 0) {
        *count = 0;
        return NULL;
    }

    *count = index_count;
    return indexes;
}


//TODO Get random word from API or file
