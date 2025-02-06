#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
using namespace std;

bool correct = false;
void logic(string &guess, string &word);

int main()
{
    cout << "Welcome to WORDLE, i'm thinking of a 5 letter word." << endl << "Can you guess it ?" << endl;
    string word, guess;
    ifstream myfile("words.txt");
    vector<string> listWords;

    while (myfile >> word)
    {
        listWords.push_back(word);
    }

    srand(time(0));
    word = listWords[rand() % listWords.size()];

    while (!correct)
    {
        cout << "Guess a word (or type 'quit' to exit): ";
        getline(cin, guess);

        if (guess == "quit")
        {
            return 0;
        }

        if (guess.size() != 5)
        {
            cout << "Maximum/Minimum number of words per guess is 5. Please enter again!" << endl;
            continue;
        }
        
        for (int i = 0; i < guess.size(); i++)
        {
            guess[i] = toupper(guess[i]);
        }
 
        logic(guess, word);
        if (correct)
        {
            cout << "Do you want to play again ? (y/n): ";
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y')
            {
                correct = false;
                system("clear");
                word = listWords[rand() % listWords.size()];
                cin.ignore();
            }
        }
    }
    return 0;
}

void logic(string &guess, string &word)
{
    bool marked[5] = {false};

    if (guess == word)
    {
        cout << "The word is " << word << "! You guessed it right!!!" << endl; 
        correct = true;
        return;
    }

    for (int i = 0; i < word.size(); i++)
    {
        if (guess[i] == word[i])
        {
            cout << "\033[1;32m" << guess[i] << "\033[0m";
            marked[i] = true;
        }
        else
        {
            bool none = true;
            for (int j = 0; j < word.size(); j++)
            {              
                if (guess[i] == word[j] && j != i && !marked[j])
                {
                    cout << "\033[1;33m" << guess[i] << "\033[0m";
                    marked[j] = true;
                    none = false;
                    break;
                }
            }
            if (none == true)
            {
                cout << guess[i];
            }  
        }
        cout << " ";
    }
    cout << endl;
}