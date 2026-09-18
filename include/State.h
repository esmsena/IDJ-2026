#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "Music.h"

class GameObject;

class State {
public:
    State();
    ~State();

    void Update(float dt);
    void Render() const;
    bool QuitRequested() const;
    void AddObject(GameObject* gameObject);

    State(const State&) = delete;
    State& operator=(const State&) = delete;

private:
    Music* music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif
