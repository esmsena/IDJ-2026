#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    Animation(int frameStart, int frameEnd, float frameTime)
        : frameStart(frameStart), frameEnd(frameEnd), frameTime(frameTime) {}

    int frameStart;
    int frameEnd;
    float frameTime;
};

#endif
