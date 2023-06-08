#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>

const static int minPassSize = 5;
const static int minNumOfPasswords = 1;

const static int maxPassSize = 100;
const static int maxNumOfPasswords = 1000;

const static int numOfCharactersAllowed = 86;
const static bool writeInFile = true;

void delayOutput(double seconds) {
    Sleep(seconds * 1000);
}

void clearConsole() {
    system("cls");
}

void outputLogo() {
    std::cout << "PPPP   AA   SSS   SSS  W     W  OOO  RRRR  DDD       GGG  EEEE N   N \n";
    std::cout << "P   P A  A S     S     W     W O   O R   R D  D     G     E    NN  N \n";
    std::cout << "PPPP  AAAA  SSS   SSS  W  W  W O   O RRRR  D  D     G  GG EEE  N N N \n";
    std::cout << "P     A  A     S     S  W W W  O   O R R   D  D     G   G E    N  NN \n";
    std::cout << "P     A  A SSSS  SSSS    W W    OOO  R  RR DDD       GGG  EEEE N   N \n";
}

void generatePassword(int passSize, bool writeToFile, std::ofstream& passwordsFile) {
    std::string password = "";
    char possibleCharacters[numOfCharactersAllowed] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                   '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                   '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '-', '+', '=', '{', '[', '}', ']', '|', ':', ';', '<', '>', '?'};

    std::random_device randomnessGen;
    std::mt19937 engine(randomnessGen());
    std::uniform_int_distribution<int> randInt(0, numOfCharactersAllowed);

    for (int K = 0; K < passSize; K++) {
        int randIndex = randInt(engine);
        std::string passwordAddUp = std::string(1, possibleCharacters[randIndex]);
        password += passwordAddUp;
    }

    if (!writeToFile) {
        std::cout << password << std::endl;
    }
    else {
        passwordsFile << password << std::endl;
        std::cout << "Password " << password << " has been successfully added to the passwords file." << std::endl;
    }
}

void connectMenu() {
    std::ofstream passwordsFile("passwords.txt", std::ios::app);

    int passwordsSize;
    int numberOfPasswords;

    clearConsole();

    outputLogo();
    std::cout << "\n How many passwords would you like to generate? [" << minNumOfPasswords << " min, " << maxNumOfPasswords << " max]" << std::endl;
    std::cin >> numberOfPasswords;
    if (numberOfPasswords >= minNumOfPasswords && numberOfPasswords <= maxNumOfPasswords) {
        std::cout << "What size would you like for your passwords in terms of the number of characters [" << minPassSize << " min, " << maxPassSize << " max] " << std::endl;
        std::cin >> passwordsSize;

        if (passwordsSize >= minPassSize && passwordsSize <= maxPassSize) {
             std::cout << "Very well, generating impossible-to-crack passwords based on the given data." << std::endl;

            for (int i = 0; i < numberOfPasswords; i++) {
                generatePassword(passwordsSize, true, passwordsFile);
                delayOutput(1);
            }
        }
        else {
            std::cout << "Improper input. Let's try this again." << std::endl;
            delayOutput(1.5);
            connectMenu();
        }
    }
    else {
        std::cout << "Improper input. Let's try this again." << std::endl;
        delayOutput(1.5);
        connectMenu();
    }
}

void outputMainMenu() {
    outputLogo();

    std::cout << "\t\t+-----------------------+" << std::endl;
    std::cout << "\t\t|      MENU OPTIONS     |" << std::endl;
    std::cout << "\t\t+-----------------------+" << std::endl;
    std::cout << "\t\t|   [C]onnect to program|" << std::endl;
    std::cout << "\t\t|        [E]xit         |" << std::endl;
    std::cout << "\t\t+-----------------------+" << std::endl << std::endl;
    std::cout << "\nInput: ";
}

void mainMenu() {
    outputMainMenu();

    std::string option;
    do {
        std::getline(std::cin, option);

        if (option == "C" || option == "c") {
            std::cout << "[LOADING...]" << std::endl;
            delayOutput(3);
            connectMenu();
        }
        else if (option == "E" || option == "e") {
            std::cout << "Roger that. Have a great day." << std::endl;
            return;
        }
        else {
            std::cout << "Improper input, please try again. " << std::endl;
            delayOutput(1.3);
            clearConsole();
            outputMainMenu();
            continue;
        }
    } while (option != "C" && option != "E");
}

int main() {
    mainMenu();
    return 0;
}
