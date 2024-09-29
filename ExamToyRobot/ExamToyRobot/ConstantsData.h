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

    struct Const {

        //---EDir conversions
        static Point toVec(EDir eVal);
        static string const& toStr(EDir eVal);
        static EDir toEDir(string const& s);

        //---ECmd conversions
        static ECmd toECmd(string const& s);
        static string const& toStr(ECmd eVal);

    };

}//namespace...