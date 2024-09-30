#pragma once

#include <string>

namespace ExamToyRobot {

    using namespace std;

    class AppArguments {
    public:
        enum class EOptions : uint8_t {
            INVALID,

            VERBOSE,
            HELP,
            NO_END,

            //TABLE_SIZE,   //todo: implement setting table size.

            _MAX
        };

        struct SOptionFlags {
            bool bVerbose : 1;
            bool bNoEnd : 1;
            bool bShowHelp : 1;

            SOptionFlags() {
                bVerbose = false;
                bNoEnd = false;
                bShowHelp = false;
            }

        };

    protected:
        string m_sAppName;
        string m_sHelp;
        SOptionFlags m_flags;
    public:
        AppArguments();
        ~AppArguments();

		void ProcessArgs(int argc, char* argv[]);
        auto const& getHelpMessage() { return m_sHelp;  }

        auto const& flags() { return m_flags; }

    protected:
        void InitializeHelpMsg();

	};

}//namespace...
