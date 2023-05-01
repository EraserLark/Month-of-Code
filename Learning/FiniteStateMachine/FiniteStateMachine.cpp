class LightState;

class Light{
public:
    Light();
    inline LightState* getCurrentState() const {return currentState;}
    void toggle();
    void setState(LightState& newState);
private:
    LightState* currentState;
};

//Pure abstract class
class LightState{
public:
    virtual void enter(Light* light) = 0;
    virtual void toggle(Light* light) = 0;
    virtual void exit(Light* light) = 0;
    virtual ~LightState() {}
};

class LightOff: public LightState{
public:
    void enter(Light* light) {}
    void toggle(Light* light);
    void exit(Light* light) {}
    static LightState& getInstance();
private:
    LightOff() {}
    LightOff(const LightOff& other);
    LightOff& operator=(const LightOff& other);
};

class LowIntensity : public LightState
{
public:
	void enter(Light* light) {}
	void toggle(Light* light);
	void exit(Light* light) {}
	static LightState& getInstance();

private:
	LowIntensity() {}
	LowIntensity(const LowIntensity& other);
	LowIntensity& operator=(const LowIntensity& other);
};

class MediumIntensity : public LightState
{
public:
	void enter(Light* light) {}
	void toggle(Light* light);
	void exit(Light* light) {}
	static LightState& getInstance();

private:
	MediumIntensity() {}
	MediumIntensity(const MediumIntensity& other);
	MediumIntensity& operator=(const MediumIntensity& other);
};

class HighIntensity : public LightState
{
public:
	void enter(Light* light) {}
	void toggle(Light* light);
	void exit(Light* light) {}
	static LightState& getInstance();

private:
	HighIntensity() {}
	HighIntensity(const HighIntensity& other);
	HighIntensity& operator=(const HighIntensity& other);
};

int main()
{

}

Light::Light()
{
    currentState = &LightOff::getInstance();
}

void Light::setState(LightState& newState)
{
    currentState->exit(this);   //do stuff before we change state
    currentState = &newState;   //actually change states now
    currentState->enter(this);  //do stuff after we change state
}

void Light::toggle()
{
    //Delegate the task of determining the next state to the current state
    currentState->toggle(this);
}

//Off
void LightOff::toggle(Light* light)
{
    light->setState(LowIntensity::getInstance());
}

LightState& LightOff::getInstance()
{
    static LightOff singleton;
    return singleton;
}

//Low
void LowIntensity::toggle(Light* light)
{
	// Low -> Medium
	light->setState(MediumIntensity::getInstance());
}

LightState& LowIntensity::getInstance()
{
	static LowIntensity singleton;
	return singleton;
}

//Medium
void MediumIntensity::toggle(Light* light)
{
	// Medium -> High
	light->setState(HighIntensity::getInstance());
}

LightState& MediumIntensity::getInstance()
{
	static MediumIntensity singleton;
	return singleton;
}

//High
void HighIntensity::toggle(Light* light)
{
	// High -> Low
	light->setState(LightOff::getInstance());
}

LightState& HighIntensity::getInstance()
{
	static HighIntensity singleton;
	return singleton;
}