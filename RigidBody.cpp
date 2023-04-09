#include "RigidBody.h"

RigidBody::RigidBody() : radius(10.0f), color(Color::Yellow) {}

RigidBody::RigidBody(Vector2f position_, float radius_)
        : position(position_), position_last(position_), acceleration(0.0f, 0.0f), radius(radius_),
          color(Color::Yellow) {}

void RigidBody::update(float dt) {
    const Vector2f displacement = position - position_last;
    position_last = position;
    position += displacement + acceleration * (dt * dt);
    acceleration = {};
}

void RigidBody::accelerate(Vector2f a) {
    acceleration += a;
}

void RigidBody::setVelocity(Vector2f v, float dt) {
    position_last = position - v * dt;
}

void RigidBody::addVelocity(Vector2f v, float dt) {
    position_last -= v * dt;
}

[[nodiscard]] Vector2f RigidBody::getVelocity(float dt) const {
    return (position - position_last) / dt;
}