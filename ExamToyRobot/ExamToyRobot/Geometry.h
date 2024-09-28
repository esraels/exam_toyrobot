#pragma once


namespace Tools {

    using namespace std;

    struct Point {
        typedef int val_t;    //note: val_t can be int, float, double, or any number data type.

        val_t x, y;
        Point(val_t a = 0, val_t b = 0) :x(a), y(b) {}

        Point operator += (const Point& p) {
            this->x += p.x;
            this->y += p.y;
            return *this;
        }

    };

    inline Point operator + (const Point& a, const Point& b) {
        return Point(a.x + b.x, a.y + b.y);
    }

    inline bool operator == (const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }

    struct Vec : Point {

        using Point::Point;
        
        Vec(const Point& p) :Point(p.x, p.y) {}

        //---constants:
        const static Point UP;
        const static Point DOWN;
        const static Point LEFT;
        const static Point RIGHT;

        const static Point ONE;
        const static Point ZERO;

        

        //---operations:
        void rotateLeft90();
        void rotateRight90();

    };

    struct Rect {
        Vec pos;
        Vec size;

        Rect(Vec s = Vec::ONE) :pos(Vec::ZERO), size(s) {};
        bool isInside(const Vec&);

    };

}//namespace...




