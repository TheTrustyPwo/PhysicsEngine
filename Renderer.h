#ifndef PHYSICS_ENGINE_RENDERER_H
#define PHYSICS_ENGINE_RENDERER_H

#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"

using namespace sf;

class Renderer {
public:
    explicit Renderer(RenderTarget &target);

    void render(World world);

private:
    RenderTarget &m_target;
};

#endif
