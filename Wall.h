#pragma once
#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

namespace arkanoid {

    class Wall : public GameObject
    {
    public:
        Wall(Point topLeft, double width, double height);
        ~Wall() override = default;

        double velocity() const = delete;
        void setVelocity(double velocity) = delete;

        double angle() const = delete;
        void setAngle(double angle) = delete;

        void move(const Point& delta) = delete;
    };
}  // namespace arkanoid
#endif