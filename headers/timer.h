#ifndef TIMER
#define TIMER
#include "ob.h"
#include "rayextended.h"

class Timer : public Ob
{
private:
    float m_timeSinceInit;
public:
    void init() override;
    void update() override;

    float currentTime() { return m_timeSinceInit; }
    float timeSince(float a) { return m_timeSinceInit - a; }
};

#endif