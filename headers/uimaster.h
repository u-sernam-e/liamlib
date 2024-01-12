#ifndef UIMASTER
#define UIMASTER
#include "uiscene.h"
#include "ob.h"

class UiMaster : public Ob
{
private:
    std::vector<UiScene> scenes{};
    int currentScene{};
public:
    UiScene& getCurrentScene() { return scenes[currentScene]; }

    void setSceneIndex(int index) { if(index < scenes.size()) currentScene=index; }
    int getSceneIndex() { return currentScene; }

    void addScene() { scenes.push_back({}); }

    void init() override { scenes[currentScene].init(); }
    void update() override { scenes[currentScene].update(); }
    void draw() override { scenes[currentScene].draw(); }
};

#endif