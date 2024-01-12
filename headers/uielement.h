#ifndef UIELEMENT
#define UIELEMENT
#include "rayextended.h"
#include "ob2d.h"
#include <string>

class UiElement : public Ob2D
{
private:
    std::string m_name{};
public:
    UiElement(std::string name) : m_name{name} {}
    UiElement() = default;

    void setName(std::string name) {m_name = name;}
    std::string getName() {return m_name;}

    virtual std::string getElementTypeName() {return "baseelement";}
};

#endif