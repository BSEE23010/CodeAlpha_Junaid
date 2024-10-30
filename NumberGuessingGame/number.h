#ifndef NUMBERGUESSINGGAME_NUMBER_H
#define NUMBERGUESSINGGAME_NUMBER_H

class Number {
    int guess;     // Store the guessed number
    int num;       // Store the random number to be guessed
    int maxGuess;  // Maximum number of allowed guesses
public:
    Number();         // Constructor
    int getNum();     // Getter for 'num'
    void setGuess();  // Setter for 'guess' with error handling
    int getGuess();   // Getter for 'guess'
    int getMaxGuess(); // Getter for 'maxGuess'
};

#endif //NUMBERGUESSINGGAME_NUMBER_H
