#include "Renderer.h"

Renderer::Renderer(RenderTarget &target) : m_target(target) {}

void Renderer::render(World world) {
    const Vector3f constraint = world.getConstraint();
    CircleShape constraint_background{constraint.z};
    constraint_background.setOrigin(constraint.z, constraint.z);
    constraint_background.setFillColor(Color::Black);
    constraint_background.setPosition(constraint.x, constraint.y);
    constraint_background.setPointCount(128);
    m_target.draw(constraint_background);

    sf::CircleShape circle{1.0f};
    circle.setPointCount(32);
    circle.setOrigin(1.0f, 1.0f);
    const auto &objects = world.getObjects();
    for (const auto &obj: objects) {
        circle.setPosition(obj.position);
        circle.setScale(obj.radius, obj.radius);
        circle.setFillColor(obj.color);
        m_target.draw(circle);
    }
}