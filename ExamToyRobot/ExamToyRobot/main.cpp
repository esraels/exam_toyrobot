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
#include "Utils.h"


int main()
{
    using namespace std;
    using namespace ExamToyRobot;
    using namespace Tools;

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
        if (commands.executeIfName( sPlaceCmd, transformLower(sInput) )) {
            app.Start();
            break;
        } else {
            app.LogError("FAILED: Command not executed");
        }
    }



    //---execute incoming commands.
    while (app.isRunning()) {
        std::getline(cin, sInput);
        bool bSuccess = commands.execute( transformLower(sInput) );
        if (!bSuccess) {
            app.LogError("FAILED: Command not executed");
        }
    }

    return 0;

}//main()...


