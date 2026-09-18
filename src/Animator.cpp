#include "Animator.h"

#include "GameObject.h"
#include "SpriteRenderer.h"

Animator::Animator(GameObject& associated)
    : Component(associated), frameStart(0), frameEnd(0), frameTime(0.0f),
      currentFrame(0), timeElapsed(0.0f) {}

void Animator::Update(float dt) {
    if (frameTime == 0.0f) {
        return;
    }

    timeElapsed += dt;
    if (timeElapsed > frameTime) {
        ++currentFrame;
        timeElapsed -= frameTime;
        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        if (SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>()) {
            renderer->SetFrame(currentFrame);
        }
    }
}

void Animator::Render() {}

void Animator::SetAnimation(const std::string& name) {
    const auto iterator = animations.find(name);
    if (iterator == animations.end()) {
        return;
    }

    frameStart = iterator->second.frameStart;
    frameEnd = iterator->second.frameEnd;
    frameTime = iterator->second.frameTime;
    currentFrame = frameStart;
    timeElapsed = 0.0f;

    if (SpriteRenderer* renderer = associated.GetComponent<SpriteRenderer>()) {
        renderer->SetFrame(currentFrame);
    }
}

void Animator::AddAnimation(const std::string& name, const Animation& animation) {
    if (animations.find(name) == animations.end()) {
        animations.emplace(name, animation);
    }
}
