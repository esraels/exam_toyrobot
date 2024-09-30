#include "AppArguments.h"

#include <unordered_map>

namespace ExamToyRobot {

    AppArguments::AppArguments() {
        
    }

    AppArguments::~AppArguments() {

    }

    void AppArguments::ProcessArgs(int argc, char* argv[]) {
        
        m_sAppName = argv[0];

        InitializeHelpMsg();

        unordered_map<string, EOptions> mapOptions = {
            { "--verbose", EOptions::VERBOSE },
            { "--help",    EOptions::HELP },
            { "--noend",   EOptions::NO_END },
            
            //---abbreviations
            { "-v", EOptions::VERBOSE },
            { "-h", EOptions::HELP },
            { "-?", EOptions::HELP },
        };

        for (int i = 1; i < argc; i++) {
            switch (mapOptions[argv[i]]) {
                case EOptions::VERBOSE: m_flags.bVerbose = true; break;
                case EOptions::HELP:    m_flags.bShowHelp = true; break;
                case EOptions::NO_END:  m_flags.bNoEnd = true; break;
            }
        }
    }

    void AppArguments::InitializeHelpMsg() {
        m_sHelp =  "------------ H E L P -------------- \n";
        m_sHelp += "ExamToyRobot.exe [--verbose|-v] [--noend] [--help|-h-?]";
        m_sHelp +=
            "                                                         \n"
            "flags:                                                   \n"
            "  --verbose   :Show error messages.                      \n"
            "  --noend     :App will not exit on 'report' command.    \n"
            "  --help      :Show help message.                        \n"
            "     -v       :Same as --verbose.                        \n"
            "     -h       :Same as --help.                           \n"
            "     -?       :Same as --help.                           \n";
    }



}//namespace...