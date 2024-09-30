#pragma once

#include <string>
#include "Geometry.h"

namespace ExamToyRobot {

    using namespace std;
    using namespace Tools;

    class AppArguments {
    public:
        enum class EOptions : uint8_t {
            INVALID,

            VERBOSE,
            HELP,
            NO_END,
            TABLE_SIZE,

            _MAX
        };

        struct SOptionFlags {
            union {
                struct {
                    bool bVerbose : 1;
                    bool bNoEnd : 1;
                    bool bShowHelp : 1;
                    bool bTableSize : 1;
                };
                uint16_t bAll;
            };
            SOptionFlags() : bAll(0) {}
            void clear() { bAll = 0; }
        };

    protected:
        string m_sAppName;
        string m_sHelp;
        SOptionFlags m_flags;
        Point m_vTableSize;
    public:
        AppArguments();
        ~AppArguments();

		void ProcessArgs(int argc, char* argv[]);
        auto const& getHelpMessage() { return m_sHelp;  }

        auto const& flags() { return m_flags; }

        void updateTableSize(Point& size);

        void getKeyParam(string const& sArg, string& sKey, string& sParam);

    protected:
        void InitializeHelpMsg();

	};

}//namespace...
