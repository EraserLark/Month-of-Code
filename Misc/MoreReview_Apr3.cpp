#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

enum class Moods { Happy, Sad, Angry, Anxious, Confused, Tired, Silly, Flabbergasted, Unsure, Hopeful};

int main()
{
    srand(time(0));
    int randNum = rand() % 9;

    string moodName;
    const Moods mood = Moods(randNum);
    switch(mood)
    {
        case Moods::Happy:
            moodName = "happy";
            break;
        case Moods::Sad:
            moodName = "sad";
            break;
        case Moods::Angry:
            moodName = "angry";
            break;
        case Moods::Anxious:
            moodName = "anxious";
            break;
        case Moods::Confused:
            moodName = "confused";
            break;
        case Moods::Tired:
            moodName = "tired";
            break;
        case Moods::Silly:
            moodName = "silly";
            break;
        case Moods::Flabbergasted:
            moodName = "flabbergasted";
            break;
        case Moods::Unsure:
            moodName = "unsure";
            break;
        case Moods::Hopeful:
            moodName = "hopeful";
            break;
        default:
            "Unclear";
            break;
    }

    cout << "Mood number: " << (int)mood << endl;
    cout << "Are you feeling " << moodName << " currently? y/n" << endl;
    char answer;
    cin >> answer;

    if(answer == 'y')
    {
        cout << "I knew it" << endl;
    }
    else if(answer == 'n')
    {
        cout << "Are you sure?" << endl;
    }
    else
    {
        cout << "I'm not sure what you mean. Goodbye." << endl;
    }
    
}