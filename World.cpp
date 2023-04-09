#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#include "World.h"

World::World(Vector2f gravity) : m_gravity(gravity) {}

void World::addObject(RigidBody &object) {
    m_objects.push_back(object);
}

std::vector<RigidBody> &World::getObjects() {
    return m_objects;
}

void World::applyGravity() {
    for (auto &body: m_objects) {
        body.accelerate(m_gravity);
    }
}

void World::checkConstraints() {
    for (auto &body: m_objects) {
        Vector2f v = m_constraint_center - body.position;
        const float dist = sqrt(v.x * v.x + v.y * v.y);
        if (dist > m_constraint_radius - body.radius) {
            const Vector2f n = v / dist;
            body.position = m_constraint_center - n * (m_constraint_radius - body.radius);
        }
    }
}

void World::checkCollisions(float dt) {
    const float response_coef = 0.75f;
    const uint64_t objects_count = m_objects.size();
    for (uint64_t i{0}; i < objects_count; ++i) {
        RigidBody &object_1 = m_objects[i];
        for (uint64_t k{i + 1}; k < objects_count; ++k) {
            RigidBody &object_2 = m_objects[k];
            const sf::Vector2f v = object_1.position - object_2.position;
            const float dist2 = v.x * v.x + v.y * v.y;
            const float min_dist = object_1.radius + object_2.radius;
            if (dist2 < min_dist * min_dist) {
                const float dist = sqrt(dist2);
                const Vector2f n = v / dist;
                const float mass_ratio_1 = object_1.radius / (object_1.radius + object_2.radius);
                const float mass_ratio_2 = object_2.radius / (object_1.radius + object_2.radius);
                const float delta = 0.5f * response_coef * (dist - min_dist);
                object_1.position -= n * (mass_ratio_2 * delta);
                object_2.position += n * (mass_ratio_1 * delta);
            }
        }
    }
}

void World::updateObjects(float dt) {
    for (auto &body: m_objects) {
        body.update(dt);
    }
}

void World::update() {
    m_time += m_frame_dt;
    const float step_dt = getStepDt();
    for (uint32_t i = m_sub_steps; i--;) {
        applyGravity();
        checkCollisions(step_dt);
        checkConstraints();
        updateObjects(step_dt);
    }
}

void World::setSimulationUpdateRate(uint32_t rate) {
    m_frame_dt = 1.0f / static_cast<float>(rate);
}

void World::setConstraint(Vector2f position, float radius) {
    m_constraint_center = position;
    m_constraint_radius = radius;
}

void World::setSubStepsCount(uint32_t sub_steps) {
    m_sub_steps = sub_steps;
}

void World::setObjectVelocity(RigidBody &object, Vector2f v) const {
    object.setVelocity(v, getStepDt());
}

[[nodiscard]] Vector3f World::getConstraint() const {
    return {m_constraint_center.x, m_constraint_center.y, m_constraint_radius};
}

[[nodiscard]] uint64_t World::getObjectsCount() const {
    return m_objects.size();
}

[[nodiscard]] float World::getTime() const {
    return m_time;
}

[[nodiscard]] float World::getStepDt() const {
    return m_frame_dt / static_cast<float>(m_sub_steps);
}
