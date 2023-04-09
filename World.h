#ifndef WORLD_H
#define WORLD_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "RigidBody.h"

using namespace sf;

class World {
private:
    Vector2f m_gravity = {0.0f, 980.7f};
    std::vector<RigidBody> m_objects;
    uint32_t m_sub_steps = 1;
    Vector2f m_constraint_center;
    float m_constraint_radius = 100.0f;
    float m_time = 0.0f;
    float m_frame_dt = 0.0f;

public:
    explicit World(Vector2f gravity);

    void addObject(RigidBody &object);

    [[nodiscard]] std::vector<RigidBody> &getObjects();

    void applyGravity();

    void checkConstraints();

    void checkCollisions(float dt);

    void updateObjects(float dt);

    void update();

    void setSimulationUpdateRate(uint32_t rate);

    void setConstraint(Vector2f position, float radius);

    void setSubStepsCount(uint32_t sub_steps);

    void setObjectVelocity(RigidBody &object, Vector2f v) const;

    [[nodiscard]] Vector3f getConstraint() const;

    [[nodiscard]] uint64_t getObjectsCount() const;

    [[nodiscard]] float getTime() const;

    [[nodiscard]] float getStepDt() const;
};

#endif
