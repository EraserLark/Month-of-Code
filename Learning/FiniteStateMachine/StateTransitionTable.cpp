//Tutorial: https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#include <iostream>
#include <map>

using namespace std;

enum class LightState{ Off, Low, Medium, High };

map<LightState, LightState> lightTransitions = {
    {LightState::Off, LightState::Low},
    {LightState::Low, LightState::Medium},
    {LightState::Medium, LightState::High},
	{LightState::High, LightState::Off}
};

class Light{
public:
    Light();
    void toggle();
    inline LightState getCurrentState() const {return currentState;}
private:
    LightState currentState;
};

Light::Light()
{
    currentState = LightState::Off;
}

void Light::toggle()
{
    currentState = lightTransitions[currentState];
}

int main()
{
    Light light;
    light.toggle();
    light.toggle();
}