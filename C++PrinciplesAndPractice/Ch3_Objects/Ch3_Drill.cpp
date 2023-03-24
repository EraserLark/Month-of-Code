#include <iostream>

int main()
{
    std::string firstName;
    std::string friendName;
    char friendGender = 0;

    std::cout << "Enter recipient name: ";
    std::cin >> firstName;
    std::cout << "Enter friend name: ";
    std::cin >> friendName;
    std::cout << "Enter friend's gender (m/f/other): ";
    std::cin >> friendGender;

    std::cout << "Dear " << firstName << ",\n";
    std::cout << "  How are you? I am fine. I miss you." << std::endl;
    std::cout << "  Have you seen " << friendName << " lately?\n";

    std::string friendPronouns;
    switch (friendGender)
    {
        case 'm':
            friendPronouns = "him";
            break;
        case 'f':
            friendPronouns = "her";
            break;
        default:
            friendPronouns = "them";
            break;
    }

    std::cout << "  If you see " << friendName << ", please ask " << friendPronouns << " to call me.";
}