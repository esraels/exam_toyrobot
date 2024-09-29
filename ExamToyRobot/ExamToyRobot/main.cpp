// ExamToyRobot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once


#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <sstream>
#include <regex>
#include <functional>

#include "Geometry.h"
#include "Robot.h"
#include "TableTop.h"
#include "Commands.h"

namespace ExamToyRobot {

    using namespace std;


    const string& toFaceName(Vec const& d) {
        EDir eDir = EDir::INVALID;
        
        if (d == Vec::UP) {
            eDir = EDir::NORTH;
        } 
        else if (d == Vec::RIGHT) {
            eDir = EDir::EAST;
        }
        else if (d == Vec::DOWN) {
            eDir = EDir::SOUTH;
        }
        else if (d == Vec::LEFT) {
            eDir = EDir::WEST;
        }

        return Const::toStr(eDir);
    }

    void toLowerStr(string& s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    }

    ostream& operator << (ostream& os, Point const& p) {
        return os << p.x << "," << p.y;
    }

    ostream& operator << (ostream& os, Robot const& r) {
        auto& pos = r.getPos();
        auto& dir = r.getDir();
        return os << pos << "," << toFaceName(dir);
    }

    ostream& operator << (ostream& os, TableTop const& table) {
        auto& size = table.getSize();
        return os << size.x << "x" << size.y;
    }

}//namespace...

int main()
{
    using namespace std;
    using namespace Tools;
    using namespace ExamToyRobot;

    bool bExit = false;
    
    Robot robot;
    TableTop board({5,5});

    //---setup commands
    Commands commands(R"(^\s*(\w+)\s*)");
    commands.add(Const::toStr(ECmd::PLACE), R"((\d+)\s*,\s*(\d+)\s*,\s*(\w+)\s*)", [&](Cmd::params_t const& params) {
        enum {
            P_POSX,
            P_POSY,
            P_FACE,
        };
        auto eDir = Const::toEDir(params[P_FACE]);
        if (eDir == EDir::INVALID) {
            cerr << "ERROR: INVALID Facing value" << endl;
            return false;
        }

        Point pos;
        stringstream(params[P_POSX]) >> pos.x;   //note: type independent conversion code.
        stringstream(params[P_POSY]) >> pos.y;   //todo: implement more optimized version.

        if (!board.isValidPos(pos)) {
            cerr << "ERROR: INVALID position on board." << endl;
            return false;
        }

        Point dir = Const::toVec(eDir);
        robot.Place(pos, dir);

        return true;
    });
    commands.add(Const::toStr(ECmd::MOVE), [&](Cmd::params_t const& params) -> bool {
        if (!board.isValidPos(robot.getPosAhead())) {
            cerr << "ERROR: Move not possible." << endl;
            return false;
        }
        robot.Move();
        return true;
    });
    commands.add(Const::toStr(ECmd::LEFT), [&](Cmd::params_t const& params) -> bool {
        robot.FaceLeft();
        return true;
    });
    commands.add(Const::toStr(ECmd::RIGHT), [&](Cmd::params_t const& params) -> bool {
        robot.FaceRight();
        return true;
    });
    commands.add(Const::toStr(ECmd::REPORT), [&](Cmd::params_t const& params) -> bool {
        cout << robot << endl;
        bExit = true;
        return true;
    });

    string sInput;

    //---wait for valid and successfully executed place command.
    auto sPlaceCmd = Const::toStr(ECmd::PLACE);
    while (true) {
        std::getline(cin, sInput);
        toLowerStr(sInput);
        if (commands.executeIfName(sPlaceCmd, sInput)) {
            break;
        } else {
            cerr << "FAILED: Command not executed" << endl;
        }

    }

    //---execute incoming commands.
    while (!bExit) {
        std::getline(cin, sInput);
        toLowerStr(sInput);
        if (commands.execute(sInput)) {
            //
        }
        else {
            cerr << "FAILED: Command not executed" << endl;
        }
    }

    return 0;

}//main()...


