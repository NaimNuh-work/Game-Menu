#include <iostream>
#include <conio.h>  // For _getch()
#include <windows.h> // For system() and SetConsoleCursorPosition()
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For seeding random number

using namespace std;

// ANSI Escape Codes for Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Menu options
const int menuSize = 4;
string menuOptions[menuSize] = { "Start Game", "Settings", "About", "Exit" };

// Function to set cursor position in the console
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to draw a boxy button
void drawBox(string text, bool selected, int x, int y) {
    gotoxy(x, y);     cout << (selected ? GREEN : YELLOW) << "┌───────────────┐" << RESET;
    gotoxy(x, y + 1); cout << (selected ? GREEN : YELLOW) << "│ " << text;
    for (int i = text.length(); i < 13; i++) cout << " "; // Padding
    cout << "│" << RESET;
    gotoxy(x, y + 2); cout << (selected ? GREEN : YELLOW) << "└───────────────┘" << RESET;
}

// Function to display the menu dynamically
int displayMenu() {
    int selected = 0;
    char key;

    do {
        system("cls");  // Clear screen
        cout << MAGENTA << "\n\t******** WELCOME TO RETRO MENU ********\n" << RESET;
        cout << CYAN << "\tUse UP & DOWN arrow keys to navigate, ENTER to select\n\n" << RESET;

        // Display menu options in a boxy format
        for (int i = 0; i < menuSize; i++) {
            drawBox(menuOptions[i], i == selected, 10, 6 + i * 3);
        }

        key = _getch();  // Get user key input

        // Handle arrow key input
        if (key == 72) {  // Up arrow key
            selected = (selected - 1 + menuSize) % menuSize;
        }
        else if (key == 80) {  // Down arrow key
            selected = (selected + 1) % menuSize;
        }

    } while (key != 13);  // Enter key to select

    return selected;
}

// Function to start the guessing game
void startGame() {
    system("cls");  // Clear screen
    srand(time(0)); // Seed random number generator
    int target = rand() % 100 + 1; // Random number between 1 and 100
    int guess;
    
    cout << GREEN << "\n*** Welcome to the Number Guessing Game! ***\n" << RESET;
    cout << YELLOW << "Guess a number between 1 and 100.\n" << RESET;

    // Game loop
    do {
        cout << "\nEnter your guess: ";
        cin >> guess;

        if (guess > target) {
            cout << RED << "Too high! Try again." << RESET << endl;
        }
        else if (guess < target) {
            cout << BLUE << "Too low! Try again." << RESET << endl;
        }
        else {
            cout << GREEN << "🎉 Correct! You guessed the number!" << RESET << endl;
        }
    } while (guess != target);

    // Ask user to play again or return to menu
    cout << YELLOW << "\nPress 'R' to play again, or any other key to return to the menu.\n" << RESET;
    char choice = _getch();
    if (choice == 'R' || choice == 'r') {
        startGame();
    }
}

// Function to execute the menu choice
void executeChoice(int choice) {
    system("cls");  // Clear screen
    switch (choice) {
        case 0:
            startGame();
            break;
        case 1:
            cout << YELLOW << "\nSettings coming soon...\n" << RESET;
            break;
        case 2:
            cout << CYAN << "\nAbout: This is a retro-style interactive menu with a simple game.\n" << RESET;
            break;
        case 3:
            cout << RED << "\nExiting the program. Goodbye!\n" << RESET;
            exit(0);
    }
    system("pause");  // Pause before returning to the menu
}

int main() {
    while (true) {
        int choice = displayMenu();  // Show menu
        executeChoice(choice);  // Perform the action
    }
    return 0;
}
