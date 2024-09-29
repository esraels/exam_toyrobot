#include "MgrApp.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>


namespace ExamToyRobot {

    MgrApp::MgrApp() :
        m_bIsRunning(false),
        m_bEnableLogError(true)
    {
        m_table.setSize({ 5,5 });  //default table size.
        setupCommands();
	}

	MgrApp::~MgrApp() {

	}

	void MgrApp::setupCommands() {
        
        m_commands.setCommandRegex(R"(^\s*(\w+)\s*)");

        m_commands.add( Const::toStr(ECmd::PLACE), R"((\d+)\s*,\s*(\d+)\s*,\s*(\w+)\s*)", [&](Cmd::params_t const& params) {
            enum {
                P_POSX,
                P_POSY,
                P_FACE,
            };
            auto eDir = Const::toEDir(params[P_FACE]);
            if (CheckError( eDir == EDir::INVALID, "INVALID Facing value.")) return false;
            
            Point pos;
            stringstream(params[P_POSX]) >> pos.x;   //note: type independent conversion code.
            stringstream(params[P_POSY]) >> pos.y;   //todo: implement more optimized version.

            if (CheckError( !m_table.isValidPos(pos), "INVALID position on table")) return false;

            Point dir = Const::toVec(eDir);
            m_robot.Place(pos, dir);

            return true;
        });
        m_commands.add( Const::toStr(ECmd::MOVE), [&](Cmd::params_t const& params) -> bool {

            if (CheckError( !m_table.isValidPos(m_robot.getPosAhead()) , "Move not possible")) return false;

            m_robot.Move();
            return true;
        });
        m_commands.add( Const::toStr(ECmd::LEFT), [&](Cmd::params_t const& params) -> bool {
            m_robot.FaceLeft();
            return true;
        });
        m_commands.add( Const::toStr(ECmd::RIGHT), [&](Cmd::params_t const& params) -> bool {
            m_robot.FaceRight();
            return true;
        });
        m_commands.add( Const::toStr(ECmd::REPORT), [&](Cmd::params_t const& params) -> bool {
            auto pos = m_robot.getPos();
            auto sFaceInfo = computeFacingInfo(m_robot.getDir());
            cout << "Output: " << pos.x << "," << pos.y << "," << sFaceInfo << endl;
            m_bIsRunning = false;
            return true;
        });
	}

    const string& MgrApp::computeFacingInfo(Vec const& d) {
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

    void MgrApp::LogError(string const& errMsg) {
        if (m_bEnableLogError) {
            cerr << errMsg << endl;
        }
    }

    bool MgrApp::CheckError(bool bCond, string const& errMsg) {
        if (bCond && m_bEnableLogError) {
            cerr << "ERROR: " << errMsg << endl;
        }
        return bCond;
    }
}//namespace...
