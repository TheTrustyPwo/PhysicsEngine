#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class RigidBody {
public:
    Vector2f position;
    Vector2f position_last;
    Vector2f acceleration;
    float radius = 10.0f;
    Color color = Color::Yellow;

    RigidBody() = default;
    RigidBody(Vector2f position_, float radius_)
        : position(position_)
        , position_last(position_)
        , acceleration(0.0f, 0.0f)
        , radius(radius_)
    {}

    void update(float dt) {
        const Vector2f displacement = position - position_last;
        position_last = position;
        position += displacement + acceleration * (dt * dt);
        acceleration = {};
    }

    void accelerate(Vector2f a) {
        acceleration += a;
    }

    void setVelocity(Vector2f v, float dt) {
        position_last = position - v * dt;
    }

    void addVelocity(Vector2f v, float dt) {
        position_last -= v * dt;
    }

    [[nodiscard]] Vector2f getVelocity(float dt) const {
        return (position - position_last) / dt;
    }
};
