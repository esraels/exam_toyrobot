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

#include "ConstantsData.h"
#include "MgrApp.h"
#include "Commands.h"

namespace ExamToyRobot {

    using namespace std;

    void toLowerStr(string& s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    }

}//namespace...

int main()
{
    using namespace std;
    using namespace ExamToyRobot;

    MgrApp app;
    app.table().setSize({5,5});
    app.enableLogError(false);

    auto& commands = app.commands();

    bool bExit = false;

    string sInput;

    //---wait for valid and successfully executed place command.
    auto const& sPlaceCmd = Const::toStr(ECmd::PLACE);
    while (true) {
        std::getline(cin, sInput);
        toLowerStr(sInput);
        if (commands.executeIfName(sPlaceCmd, sInput)) {
            app.Start();
            break;
        } else {
            app.LogError("FAILED: Command not executed");
        }
    }

    //---execute incoming commands.
    while (app.isRunning()) {
        std::getline(cin, sInput);
        toLowerStr(sInput);
         
        bool bSuccess = commands.execute(sInput);

        if (!bSuccess) {
            app.LogError("FAILED: Command not executed");
        }
        
    }

    return 0;

}//main()...


