#include <iostream>
#include "Number.h"
#include <exception>

using namespace std;

int main() {
    Number n;
    cout << n.getNum();
    int attempts = 0;

    cout << "\n Welcome To The Random Guessing Game !!! \n" << endl;

    do {
        // Display remaining attempts
        cout << " You Have " << (n.getMaxGuess() - attempts) << " Tries Left " << endl;

        // Try to set the guess with error handling
        try {
            n.setGuess(); // This may throw an exception if input is invalid
            attempts++;

            // Calculate the difference
            int diff = 0;
            if (n.getGuess() != n.getNum()) {
                if (n.getGuess() > n.getNum()) {
                    diff = n.getGuess() - n.getNum();
                } else {
                    diff = n.getNum() - n.getGuess();
                }

                // Provide feedback based on proximity
                if (diff < 10) {
                    cout << " You are very close! " << endl;
                } else if (diff < 30) {
                    cout << " You are fairly close! " << endl;
                } else if (diff < 60) {
                    cout << " You are far away! " << endl;
                } else {
                    cout << " You are very far away! " << endl;
                }
            } else {
                cout << "\n Congratulations! You guessed the number in " << attempts << " attempts." << endl;
                break;
            }

        } catch (const invalid_argument &e) {
            // Catch invalid input errors (e.g., non-numeric input)
            cerr << e.what() << endl;
        } catch (const out_of_range &e) {
            // Catch out-of-range errors (e.g., guess not between 1 and 100)
            cerr << e.what() << endl;
        }

        // Check if attempts have reached the maximum allowed
        if (attempts >= n.getMaxGuess()) {
            cout << "\n Sorry, you've used all your attempts! The correct number was " << n.getNum() << "." << endl;
            break;
        }

    } while (n.getGuess() != n.getNum());

    return 0;
}
