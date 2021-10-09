#include "console.hpp"

// Clean command line
void clearLine() {
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Request integer from user
int getInt(std::string message, int low) {
    int answer = -10;
    while (answer < low) {
        std::cout << message;
        std::cin >> answer;
        if (std::cin.fail())
            clearLine();
    }
    clearLine();
    return answer;
}

// Ask yes/no question
bool yesNoQuestion(string question) {
    string answer;
    while (answer != "y" && answer != "n") {
        cout << question << " (y/n): ";
        std::cin >> answer;
    }
    clearLine();
    return answer == "y";
}