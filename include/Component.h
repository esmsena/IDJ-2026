#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
public:
    explicit Component(GameObject& associated) : associated(associated) {}
    virtual ~Component() = default;

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

protected:
    GameObject& associated;
};

#endif
