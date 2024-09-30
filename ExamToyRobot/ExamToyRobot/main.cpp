#pragma once

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <functional>

#include "ConstantsData.h"
#include "MgrApp.h"
#include "Commands.h"
#include "Utils.h"
#include "AppArguments.h"


int main(int argc, char* argv[])
{
    using namespace std;
    using namespace ExamToyRobot;
    using namespace Tools;

    AppArguments appArgs;

    appArgs.ProcessArgs(argc, argv);
    auto const& flags = appArgs.flags();
    
    if (flags.bShowHelp) {
        cout << appArgs.getHelpMessage();
        return 0;
    }

    MgrApp app;
    app.table().setSize({5,5});
    app.enableLogError(flags.bVerbose);

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
    while (app.isRunning() || flags.bNoEnd) {
        std::getline(cin, sInput);
        bool bSuccess = commands.execute( transformLower(sInput) );
        if (!bSuccess) {
            app.LogError("FAILED: Command not executed");
        }
    }

    return 0;

}//main()...


