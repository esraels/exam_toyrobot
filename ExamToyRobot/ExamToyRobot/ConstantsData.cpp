#include "ConstantsData.h"

namespace ExamToyRobot {

    using namespace std;

    
    Point Const::toVec(EDir eVal) {
        static Point map[(int)EDir::_MAX] = {
            Vec::ZERO,
            Vec::RIGHT,
            Vec::UP,
            Vec::LEFT,
            Vec::DOWN,
        };
        if (eVal < EDir::INVALID || EDir::_MAX <= eVal) {
            eVal = EDir::INVALID;
        }
        return map[(int)eVal];
    }

    string const& Const::toStr(EDir eVal) {
        static string map[(int)EDir::_MAX] = {
            "",
            "EAST",
            "NORTH",
            "WEST",
            "SOUTH",
        };
        if (eVal < EDir::INVALID || EDir::_MAX <= eVal) {
            eVal = EDir::INVALID;
        }
        return map[(int)eVal];
    }

    EDir Const::toEDir(string const& s) {
        static unordered_map<string, EDir> map = {
            { "east",  EDir::EAST  },
            { "north", EDir::NORTH },
            { "west",  EDir::WEST  },
            { "south", EDir::SOUTH },

            //---add alternative keywords if needed.
            //{ "n", EDir::NORTH },
            //{ "e", EDir::EAST  },
            //{ "s", EDir::SOUTH },
            //{ "w", EDir::WEST  },
        };
        return map[s]; //note: this will return 0 (EDir::INVALID) if key not found.
    }

    string const& Const::toStr(ECmd eVal) {
        static string map[(int)ECmd::_MAX] = {
            "",
            "place",
            "left",
            "right",
            "move",
            "report",
        };
        if (eVal < ECmd::INVALID || ECmd::_MAX <= eVal) {
            eVal = ECmd::INVALID;
        }
        return map[(int)eVal];
    }

    ECmd Const::toECmd(string const& s) {
        static unordered_map<string, ECmd> map = {
            { toStr(ECmd::PLACE),  ECmd::PLACE  },
            { toStr(ECmd::LEFT),   ECmd::LEFT   },
            { toStr(ECmd::RIGHT),  ECmd::RIGHT  },
            { toStr(ECmd::MOVE),   ECmd::MOVE   },
            { toStr(ECmd::REPORT), ECmd::REPORT },

            //---add alternative keywords if needed.
            //{ "put",  ECmd::PLACE  },
            //{ "l",    ECmd::LEFT   },
            //{ "r",    ECmd::RIGHT  },
            //{ "go",   ECmd::MOVE   },
            //{ "stat", ECmd::REPORT },
        };
        return map[s]; //note: this will return 0 (EDir::INVALID) if key not found.
    }


}//namespace...