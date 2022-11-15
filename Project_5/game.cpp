#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// declare global constants
const char WORDFILENAME[] = "./words2.txt";
const int MAX_WORD_COUNT = 9000;
const int MAX_WORD_LENGTH = 6;

int playOneRound(const char words[][MAX_WORD_LENGTH + 1], int nWords, int wordnum);

int main()
{
    char words[MAX_WORD_COUNT][MAX_WORD_LENGTH + 1]; // initialize array to hold all valid words
    int nWords = getWords(words, MAX_WORD_COUNT, WORDFILENAME); // call getwords to fill 2d cstring array

    if (nWords < 1) { // no words loaded, must exit program.
        cout << "No words were loaded, so I can't play the game." << endl;
        return -1; // failed, exit program
    }

    int gameRounds; // initialize int to store the user-inputted game rounds
    cout << "How many rounds do you want to play? ";
    cin >> gameRounds;
    cin.ignore(10000, '\n'); // remove the inputted game rounds from the cin buffer.
    if (gameRounds < 0) { // invalid user input
        cout << "The number of rounds must be positive." << endl;
        return -1; // failed, exit program
    }

    // initialize counters used for providing stats after each round.
    int maximum = 0;
    int minimum = 0;
    int total = 0;
    
    for (int i = 0; i < gameRounds; i++) {
        
        cout << endl << "Round " << i + 1 << endl;
        int wordIndex = randInt(0, nWords - 1); // get a random index to pick a hidden word.
        cout << "The hidden word is " << strlen(words[wordIndex]) << " letters long." << endl;
        int tries = playOneRound(words, nWords, wordIndex); // play a round of our game.

        // deal with plural and singular cases after each round.
        if (tries == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << tries << " tries." << endl;


        if (i == 0) // first round
            maximum = minimum = tries; // set max and min to the number of tries.
        else {
            if (tries < minimum)
                minimum = tries; // update new minimum
            if (tries > maximum)
                maximum = tries; // update new maximum
        }

        total += tries; // increment the total to use for average.
        double average = total * 1.00 / (i + 1); // calculate average while converting to double.

        // prepare cout to display two decimal places for average.
        cout.setf(ios::fixed);
        cout.precision(2);

        cout << "Average: " << average << ", ";
        cout << "minimum: " << minimum << ", ";
        cout << "maximum: " << maximum << endl;

    }

}

int playOneRound(const char words[][MAX_WORD_LENGTH + 1], int nWords, int wordnum) {
    // validity checks 
    if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
        return -1;

    int tries = 0; // initialize try counter to return at end of round.
    for (;;) {
        
        char chosenWord[10000]; // create cstring big enough to hold any input
        
        // get user word guess
        cout << "Probe word: ";
        cin.getline(chosenWord, 10000);

        // check if user's guess is lower case
        bool isAllLowerCase = true;
        for (int i = 0; i < strlen(chosenWord); i++) {
            if (!islower(chosenWord[i])) {
                isAllLowerCase = false;
            }
        }

        // check if user's guess is between 4 and 6 characters.
        bool is4to6Chars = (4 <= strlen(chosenWord) && 6 >= strlen(chosenWord));

        if (!is4to6Chars || !isAllLowerCase) {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue; // invalid guess, prompt user for next guess.
        }

        // make sure user's guess exists in out word bank.
        bool isValidWord = false;
        for (int i = 0; i < nWords; i++) {
            if (strcmp(words[i], chosenWord) == 0) {
                isValidWord = true;
            }
        }
        if (!isValidWord) {
            cout << "I don't know that word." << endl;
            continue;
        }

        tries++; // user's guess is valid, we increment the tries.
        
        if (strcmp(words[wordnum], chosenWord) == 0) {
            break; // they guessed the word
        }

        int gold = 0;
        int silver = 0;
        int index; // tentative location of matching letter.

        // create integer array for storing the letters we already counted.
        int usedIndexes[MAX_WORD_LENGTH + 1];
        for (int i = 0; i < MAX_WORD_LENGTH + 1; i++)
            usedIndexes[i] = -1; // initialize to a value we know won't be used.

        for (int i = 0; i < strlen(chosenWord); i++) {
            if (strchr(words[wordnum], chosenWord[i]) == NULL)
                continue; // letter at i is not in the wordle word.
                
            // use pointer to find index where chosenWord[i] matches the wordle word.
            index = strchr(words[wordnum], chosenWord[i]) - words[wordnum];

            // check if we already counted the matched letter.
            bool usedAlready = false;
            for (int j = 0; j < MAX_WORD_LENGTH + 1; j++) {
                if (usedIndexes[j] == index)
                    usedAlready = true;
            }

            if (index == i) { // we have a gold
                gold++;
                if (usedAlready) // we already counted this as a silver, so subtract
                    silver--;
            }
            else { // we have a silver
                if (!usedAlready)
                    silver ++;
            }
            usedIndexes[i] = index; // count our letter.
        }
        cout << "Golds: " << gold << ", " << "Silvers: " << silver << endl;
    }
    return tries;
}