#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class RigidBody {
public:
    Vector2f position;
    Vector2f position_last;
    Vector2f acceleration;
    float radius;
    Color color;

    RigidBody();

    RigidBody(Vector2f position_, float radius_);

    void update(float dt);

    void accelerate(Vector2f a);

    void setVelocity(Vector2f v, float dt);

    void addVelocity(Vector2f v, float dt);

    [[nodiscard]] Vector2f getVelocity(float dt) const;

};

#endif
