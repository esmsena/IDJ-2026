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

    void Start();
    void LoadAssets();
    void Update(float dt);
    void Render() const;
    bool QuitRequested() const;
    std::weak_ptr<GameObject> AddObject(GameObject* gameObject);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* gameObject);

    State(const State&) = delete;
    State& operator=(const State&) = delete;

private:
    Music music;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif
