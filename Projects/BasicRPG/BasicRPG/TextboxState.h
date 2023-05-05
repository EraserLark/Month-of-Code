#pragma once
#include "StateMachine.h"

class TextboxState : public WaitState {
public:
    TextboxState(std::string, StateStack*);
    TextboxState(std::string*, int, StateStack*);
    virtual void Enter() override;
    virtual void Wait() override;
    virtual void Exit() override;
    virtual void runCurrentState() override;
    virtual ~TextboxState();
private:
    enum class subState { Enter, Wait, Exit };
    subState currentState;
    Textbox* tb;
    std::vector<std::string> texts;
};