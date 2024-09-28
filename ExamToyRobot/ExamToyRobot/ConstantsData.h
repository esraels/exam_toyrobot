#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "Geometry.h"

namespace ExamToyRobot {

    using namespace std;
    using namespace Tools;

    //---Directions:
    enum class EDir : int8_t {
        INVALID,

        EAST,
        NORTH,
        WEST,
        SOUTH,

        _MAX,

    };

    extern Point mapDirToVec[(int)EDir::_MAX];
    extern string mapDirToStr[(int)EDir::_MAX];

    extern unordered_map<string, EDir> mapKeyToDir;

    //---Commands:
    enum ECmd : int8_t {
        INVALID,

        PLACE,
        LEFT,
        RIGHT,
        MOVE,
        REPORT,

        _MAX
    };

    extern unordered_map<string, ECmd> mapKeyToCmd;

}//namespace...