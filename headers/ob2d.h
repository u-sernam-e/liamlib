#ifndef OB2D
#define OB2D
#include "ob.h"

class Ob2D : public Ob
{
protected:
    Vector2 m_pos{};
    Vector2 m_size{};
public:
    virtual Vector2 getPos() {return m_pos;}
    virtual void setPos(Vector2 p) {m_pos = p;}
    
    virtual Vector2 getSize() {return m_size;}
    virtual void setSize(Vector2 s) {m_size = s;}
};

#endif