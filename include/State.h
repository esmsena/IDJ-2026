#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"

class State {
public:
    State();
    ~State();

    void Update(float dt);
    void Render() const;
    bool QuitRequested() const;

    State(const State&) = delete;
    State& operator=(const State&) = delete;

private:
    Sprite* bg;
    Music* music;
    bool quitRequested;
};

#endif
