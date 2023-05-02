#pragma once
#include <stack>
#include "SDLfoundation.h"

class Textbox;
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
    State() {}
};

class WaitState : public State {
public:
    virtual void Enter() {}
    virtual void Exit() {}
    virtual void runCurrentState() = 0;
    virtual void Wait() = 0;
    virtual ~WaitState() {}
protected:
    WaitState() {}
};

class TextboxState : public WaitState {
public:
    TextboxState();
    void SetTextbox(Textbox*);
    virtual void Enter() override;
    virtual void Wait() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    ~TextboxState() {};
private:
    enum class subState { Enter, Wait, Exit };
    subState currentState;
    Textbox* tb;
};

//class MenuState : public WaitState {
//    //Textbox tb;
//
//    virtual void Enter() override;
//    virtual void Wait() override;
//    virtual void Exit() override;
//    virtual void runCurrentState() override;
//    virtual ~MenuState() override;
//};