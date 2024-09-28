#include "ConstantsData.h"

namespace ExamToyRobot {

    using namespace std;

    Point mapDirToVec[(int)EDir::_MAX] = {
        Vec::ZERO,
        
        Vec::RIGHT,
        Vec::UP,
        Vec::LEFT,
        Vec::DOWN,
        
    };

    string mapDirToStr[(int)EDir::_MAX] = {
        "",
        "EAST",
        "NORTH",
        "WEST",
        "SOUTH",
    };

    unordered_map<string, EDir> mapKeyToDir = {
        { "east",  EDir::EAST  },
        { "north", EDir::NORTH },
        { "west",  EDir::WEST  },
        { "south", EDir::SOUTH },
        
        //{ "n", EDir::NORTH },
        //{ "e", EDir::EAST  },
        //{ "s", EDir::SOUTH },
        //{ "w", EDir::WEST  },
    };


    unordered_map<string, ECmd> mapKeyToCmd = {
            { "place",  ECmd::PLACE },
            { "left",   ECmd::LEFT  },
            { "right",  ECmd::RIGHT },
            { "move",   ECmd::MOVE  },
            { "report", ECmd::REPORT  },
    };


}//namespace...