#include <iostream>

int main()
{
    std::string firstName;
    int recpAge = 0;
    std::string friendName;
    char friendGender = 0;

    std::cout << "Enter recipient name: ";
    std::cin >> firstName;
    std::cout << "Enter recipient age: ";
    do
    {
        std::cin >> recpAge;
    } while (recpAge < 0 || recpAge > 110);

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

    std::cout << "  If you see " << friendName << ", please ask " << friendPronouns << " to call me." << std::endl;
    std::cout << "  I hear you just had a birthday and you're now " << recpAge << " years old!" << std::endl;

    if(recpAge > 70)
    {
        std::cout << "  I hope you are enjoying retirement" << std::endl;
    }
    else if(recpAge == 17)
    {
        std::cout << "  Next year you will be able to vote" << std::endl;
    }
    else if(recpAge < 12)
    {
        std::cout << "  Next year you will be " << recpAge + 1 << std::endl;
    }

    std::cout << "Yours sincerely, " << std::endl << std::endl << "Conner";
}