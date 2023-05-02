#pragma once

class State {
public:
    int currentState;
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState(int) = 0;
    virtual ~State() {}
protected:
    State() {}
};

class WaitState : public State {
public:
    virtual void Wait() = 0;
    virtual ~WaitState() {}
};

class Menu : public WaitState {
    Textbox tb;
    virtual ~Menu() override;
};