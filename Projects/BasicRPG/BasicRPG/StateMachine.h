#pragma once
#include <stack>
#include "queue.h"
#include "action.h"

class State;

class StateStack {
public:
    StateStack() {}

    void PushState(State*);
    State* TopState();
    void StateFinish();

    ~StateStack();
private:
    std::stack<State*> states;
};

class State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual ~State() {}
protected:
    State(StateStack* stateStackPtr)
        :stateStack{ stateStackPtr }
    {}
    StateStack* stateStack;
};

class WaitState : public State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual void Wait() = 0;
    virtual ~WaitState() {}
protected:
    WaitState(StateStack* stateStackPtr)
        :State(stateStackPtr)
    {}
};