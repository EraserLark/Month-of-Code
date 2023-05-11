#pragma once
#include <vector>
#include "StateMachine.h"

class Textbox;
struct DrawMaterials;

class TextboxState : public WaitState {
public:
    TextboxState(std::string, StateStack*, DrawMaterials*);
    TextboxState(std::string*, int, StateStack*, DrawMaterials*);
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
    DrawMaterials* drawMaterials;
};