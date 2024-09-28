#include "Geometry.h"

namespace Tools {

    
    const Point Vec::UP    = { 0, 1 };
    const Point Vec::DOWN  = { 0, -1 };
    const Point Vec::LEFT  = { -1, 0 };
    const Point Vec::RIGHT = { 1, 0 };

    const Point Vec::ONE  = { 1, 1 };
    const Point Vec::ZERO = { 0, 0 };

    void Vec::rotateLeft90() {
        val_t origX = this->x;
        this->x = -this->y;
        this->y = origX;
    }

    void Vec::rotateRight90() {
        val_t origX = this->x;
        this->x = this->y;
        this->y = -origX;
    }

    bool Rect::isInside(const Vec& p) {
        return pos.x <= p.x && p.x <= (size.x + pos.x) &&
               pos.y <= p.y && p.y <= (size.y + pos.y);
    }

}//namespace...