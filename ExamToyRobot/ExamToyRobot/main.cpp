// ExamToyRobot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once


#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <regex>
#include "Geometry.h"
#include "Robot.h"
#include "TableTop.h"

namespace ExamToyRobot {

    using namespace std;


    const string& dirToStr(const Vec& d) {
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

        return mapDirToStr[(int)eDir];
    }

    ostream& operator << (ostream& os, const Point& p) {
        return os << p.x << "," << p.y;
    }

    ostream& operator << (ostream& os, const Robot& r) {
        auto& pos = r.getPos();
        auto& dir = r.getDir();
        return os << pos << "," << dirToStr(dir);
        //return os << pos << "," << dir << ",(" << dirToStr(dir) << ")";
    }

    ostream& operator << (ostream& os, const TableTop& table) {
        auto& size = table.getSize();
        return os << size.x << "x" << size.y;
    }

}

int main()
{
    using namespace Tools;
    using namespace ExamToyRobot;

    string sInput;

    Robot robot;
    TableTop board({5,5});

    robot.Place({ 0,0 }, Vec::UP); //???: temp code.

    //cout << "Robot: " << robot << endl;
    //cout << "Board: " << board << endl;
    //cout << "Vec list:" << endl;
    //for (auto item : mapDirToVec) {
    //    cout << item << endl;
    //}

    bool bExit = false;

    while (!bExit) {
        cin >> sInput;

        //todo: search the first valid PLACE command.

        //todo: apply regex and tolower here.
        //auto sKey = std::transform(sInput.begin(), sInput.end(), ::tolower);
        auto sKey = sInput;

        switch (mapKeyToCmd[sKey]) {
            case ECmd::PLACE: 
                
                break;
            case ECmd::LEFT:  
                robot.FaceLeft();  
                break;
            case ECmd::RIGHT: 
                robot.FaceRight();  
                break;
            case ECmd::MOVE: 
                if (board.isValidPos( robot.getPosAhead() )) {
                    robot.Move();
                }
                break;
            case ECmd::REPORT: 
                cout << robot << endl;
                //bExit = true;
                break;
            default:
                break;
        }

    }

    return 0;
}


