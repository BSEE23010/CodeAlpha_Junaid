#include "Number.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace std;
// Constructor
Number::Number() {
    srand(time(0));
    num = rand() % 100 + 1;
    guess = 0;
    maxGuess = 10;
}

// Getter for 'num' (the random number to be guessed)
int Number::getNum() {
    return num;
}

// Setter for 'guess' (with error handling)
void Number::setGuess() {
    cout << "\n Enter your guess (between 1 and 100): ";
    cin >> guess;
    // Check for invalid input
    if (cin.fail()) {
        cin.clear();  // Clear the error flag
        cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
        throw std::invalid_argument(" Invalid input. Please enter a number.");
    }

    // Check if the guess is out of bounds
    if (guess < 1 || guess > 100) {
        throw out_of_range(" Guess must be between 1 and 100.");
    }
}

// Getter for 'guess'
int Number::getGuess() {
    return guess;
}

// Getter for 'maxGuess'
int Number::getMaxGuess() {
    return maxGuess;
}
