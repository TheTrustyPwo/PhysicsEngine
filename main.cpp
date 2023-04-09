#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Renderer.h"

using namespace sf;

int32_t main(int32_t, char *[]) {

    constexpr int32_t window_width = 1000;
    constexpr int32_t window_height = 1000;

    ContextSettings settings;
    settings.antialiasingLevel = 1;
    RenderWindow window(VideoMode(window_width, window_height), "Feesix", Style::Default, settings);
    const uint32_t frame_rate = 60;
    window.setFramerateLimit(frame_rate);

    World world({0.0f, 981.0f});
    Renderer renderer{window};

    world.setConstraint({static_cast<float>(window_width) * 0.5f, static_cast<float>(window_height) * 0.5f}, 450.0f);
    world.setSubStepsCount(8);
    world.setSimulationUpdateRate(frame_rate);

    const float object_spawn_delay = 0.25f;
    const float object_spawn_speed = 1200.0f;
    const Vector2f object_spawn_position = {250.0f, 250.0f};
    const float object_min_radius = 1.0f;
    const float object_max_radius = 20.0f;
    const uint32_t max_objects_count = 1000;
    const float max_angle = 1.0f;

    Clock clock;
    while (window.isOpen()) {
        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }

        if (world.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            RigidBody body = RigidBody(object_spawn_position, 10.0f);
            world.addObject(body);
        }

        world.update();
        window.clear(Color::White);
        renderer.render(world);
        window.display();
    }

    return 0;
}