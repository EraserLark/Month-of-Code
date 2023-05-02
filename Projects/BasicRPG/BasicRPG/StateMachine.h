#pragma once
#include <stack>
#include "SDLfoundation.h"

class State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual ~State() {}
protected:
    State() {}
};

std::stack<State> stateStack;

class WaitState : public State {
public:
    virtual void Wait() = 0;
    virtual ~WaitState() {}
};

class MenuState : public WaitState {
    //Textbox tb;
    virtual ~MenuState() override;
};