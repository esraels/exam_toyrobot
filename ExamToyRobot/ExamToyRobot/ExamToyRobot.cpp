// ExamToyRobot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

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

struct Vec : Point {
    
    Point::Point;

    Vec(const Point&p):Point(p.x, p.y) {}

    //---constants:
    const static Point ZERO;
    const static Point UP;
    const static Point DOWN;
    const static Point LEFT;
    const static Point RIGHT;

    //---operations:
    void rotateLeft90() {
        val_t origX = this->x;
        this->x *= -this->y;
        this->y = origX;
    }

    void rotateRight90() {
        val_t origX = this->x;
        this->x = this->y;
        this->y *= -origX;
    }
    
};

const Point Vec::ZERO = { 0, 0 };
const Point Vec::UP = { 0, 1 };
const Point Vec::DOWN = { 0, -1 };
const Point Vec::LEFT = { -1, 0 };
const Point Vec::RIGHT = { 1, 0 };

enum class EDir: int8_t {
    INVALID = -1, 

    NORTH,
    EAST,
    SOUTH,
    WEST,

    _COUNT,

};

const Point mapDirToVec[(int)EDir::_COUNT] = {
    Vec::UP,
    Vec::RIGHT,
    Vec::DOWN,
    Vec::LEFT,
};

const std::unordered_map<std::string, EDir> mapKeyToDir = {
    { "north", EDir::NORTH },
    { "east",  EDir::EAST  },
    { "south", EDir::SOUTH },
    { "west",  EDir::WEST  },
};

class ToyRobot {

protected:
    Vec m_vPos;
    Vec m_vDir;

public:
    ToyRobot() :m_vPos(Vec::ZERO), m_vDir(Vec::UP) {}

    //---actions:
    void FaceLeft() {
        m_vDir.rotateLeft90();
    }

    void FaceRight() {
        m_vDir.rotateRight90();
    }

    void Move() {
        m_vPos += m_vDir;
    }

};



int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
