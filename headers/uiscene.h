#ifndef UISCENE
#define UISCENE
#include <type_traits>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "ob.h"
#include "uielement.h"

class UiScene : public Ob
{
public: // this will be private
    std::vector<UiElement*> m_elements{};
public:
    UiScene() {}
    ~UiScene()
    {
        for (auto& e : m_elements)
        {
            delete e;
        }
    }

    void init() override
    {
        for (auto& e : m_elements)
        {
            e->init();
        }
    }

    void update() override
    {
        for (auto& e : m_elements)
        {
            e->update();
        }
    }

    void draw() override
    {
        for (auto& e : m_elements)
        {
            e->draw();
        }
    }

    template<typename T>
    T* getElement(int index)
    {
        try{
            if (index < m_elements.size() && m_elements[index] && std::is_base_of<UiElement, T>::value) // not a null pointer
            {
                return dynamic_cast<T*>(m_elements[index]);
            }
            else
                throw index;
        }
        catch(int i)
        {
            std::cerr << "error getting ui element in uiscene.h index '" << i << "'\n";
            std::exit(0);
        }
    }
    template<typename T>
    T* getElement(std::string name)
    {
        try{
            for (auto e : m_elements)
            {   
                if (e && e->getName() == name)
                {
                    if (std::is_base_of<UiElement, T>::value)
                        return dynamic_cast<T*>(e);
                    else
                        throw name;
                }
            }
            throw name;
        }
        catch(std::string n)
        {
            std::cerr << "error getting ui element in uiscene.h name '" << n << "'\n";
            std::exit(0);
        }
    }

    template<typename T>
    void addElement(T uie, std::string name)
    {
        if (std::is_base_of<UiElement, T>::value)
        {
            m_elements.push_back(new T{uie});
            m_elements[m_elements.size()-1]->setName(name);
            m_elements[m_elements.size()-1]->init();
        }
    }
    
    template<typename T>
    void addElements(std::vector<T> elements, std::vector<std::string> names) // if the names vector is shorter than the strings vector then the last ones will be unnamed
    {
        if (!std::is_base_of<UiElement, T>::value)
            return;
        
        for (int i{}; i < elements.size(); ++i)
        {
            m_elements.push_back(new T{elements[i]});
            if (i < names.size())
                m_elements[m_elements.size()-1]->setName(names[i]);
            m_elements[m_elements.size()-1]->init();
        }
    }

    void deleteElement(int index)
    {
        if (index < m_elements.size() && index >= 0)
        {
            delete m_elements[index];
            m_elements.erase(m_elements.begin() + index);
        }
    }
    void deleteElement(std::string name)
    {
        for (int i{}; i < m_elements.size(); ++i)
        {
            if (m_elements[i] && m_elements[i]->getName() == name) // not a null pointer
            {
                delete m_elements[i];
                m_elements.erase(m_elements.begin() + i);
                break;
            }
        }
    }
};

#endif