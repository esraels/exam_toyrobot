#include "AppArguments.h"

#include <unordered_map>
#include <sstream>
#include <regex>

#include "Geometry.h"

namespace ExamToyRobot {

    AppArguments::AppArguments():
        m_vTableSize(Vec::ONE)
    {
        
    }

    AppArguments::~AppArguments() {

    }

    void AppArguments::getKeyParam(string const& sArg, string& sKey, string& sParam) {
        auto iFound = sArg.find(':');
        if (iFound != string::npos) {
            sParam = sArg.substr(iFound + 1, iFound - sArg.length());
        }
        else iFound = sArg.length();

        sKey = sArg.substr(0, iFound);
    }

    void AppArguments::updateTableSize(Point& size) {
        if (m_flags.bTableSize) size = m_vTableSize;
    }

    void AppArguments::ProcessArgs(int argc, char* argv[]) {
        
        m_sAppName = argv[0];
        m_flags.clear();

        InitializeHelpMsg();

        unordered_map<string, EOptions> mapOptions = {
            { "--verbose", EOptions::VERBOSE },
            { "--help",    EOptions::HELP },
            { "--noend",   EOptions::NO_END },
            { "--table",   EOptions::TABLE_SIZE },
            
            //---abbreviations
            { "-v", EOptions::VERBOSE },
            { "-h", EOptions::HELP },
            { "-?", EOptions::HELP },
            { "-t", EOptions::TABLE_SIZE },
        };

        for (int i = 1; i < argc; i++) {
            string sKey, sParam;
            this->getKeyParam(argv[i], sKey, sParam);

            switch (mapOptions[sKey]) {
                case EOptions::VERBOSE: m_flags.bVerbose = true; break;
                case EOptions::HELP:    m_flags.bShowHelp = true; break;
                case EOptions::NO_END:  m_flags.bNoEnd = true; break;
                case EOptions::TABLE_SIZE: {
                    if (sParam.empty()) break;

                    smatch m;
                    if (!regex_search(sParam, m, regex(R"((\d+),(\d+))", regex::icase))) break;
                     
                    stringstream(m[1].str()) >> m_vTableSize.x;
                    stringstream(m[2].str()) >> m_vTableSize.y;

                    m_flags.bTableSize = true;
                } break;
                default: break;
            }
        }
    }

    void AppArguments::InitializeHelpMsg() {
        m_sHelp =  "------------ H E L P -------------- \n";
        m_sHelp += "ExamToyRobot.exe [--verbose|-v] [--noend] [--help|-h-?] [--table|-t]";
        m_sHelp +=
            "                                                      \n"
            "flags:                                                \n"
            "  --verbose   :Show error messages.                   \n"
            "  --help      :Show help message.                     \n"
            "  --table:W,H :Change size of table.                  \n"
            "  --noend     :App will not exit on 'report' command. \n"
            "                Press Ctrl+c to exit.                 \n" 
            "     -v       :Same as --verbose.                     \n"
            "     -t:W,H   :Same as --table.                       \n"
            "     -h       :Same as --help.                        \n"
            "     -?       :Same as --help.                        \n";
    }



}//namespace...