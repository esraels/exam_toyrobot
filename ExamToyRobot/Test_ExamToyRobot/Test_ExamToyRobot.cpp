#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
//#include "../ExamToyRobot/main.cpp"
#include "../ExamToyRobot/MgrApp.h"
#include "../ExamToyRobot/Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define WMSG(m) [&]{ std::wstringstream _ss; _ss << m; return _ss.str(); }().c_str()

namespace TestExamToyRobot
{
	TEST_CLASS(TestExamToyRobot)
	{
	public:
		
		TEST_METHOD(Test_ParseCommands) {
			using namespace ExamToyRobot;
			using namespace Tools;
			
			struct {
				bool r;    //return value
				Point p;   //result position
				EDir f;    //result face
				ECmd c;    //accepted command
				char const* s;  //command string
			} list[] = {
				//---place command
				{ true,  {0,3}, EDir::WEST,  ECmd::PLACE, "place 0,3,west" },
				{ true,  {1,4}, EDir::NORTH, ECmd::PLACE, "place 1,4,NORTH" },
				{ true,  {2,0}, EDir::EAST,  ECmd::PLACE, " plAcE 2 ,0,east" },
				{ true,  {3,1}, EDir::WEST,  ECmd::PLACE, "PLACE 3 ,1,WeST" },
				{ true,  {4,2}, EDir::SOUTH, ECmd::PLACE, "place 4, 2,SOUth" },
				{ true,  {0,3}, EDir::NORTH, ECmd::PLACE, "Place 0,3 ,north " },
				{ true,  {1,4}, EDir::SOUTH, ECmd::PLACE, "placE 1,4, soUtH" },
						 
				{ true,  {2,0}, EDir::WEST,  ECmd::PLACE, "    pLAce   2   ,  0   ,      west   " },
				{ true,  {3,1}, EDir::EAST,  ECmd::PLACE, "  \t\t  plaCe   3   \t,  1 \t  \t  ,   \t   EAST  \t " },

				{ true,  {2,3}, EDir::NORTH, ECmd::PLACE, "place 2,3,north" },   //set initial pos.
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE 1,4, soUtH     extra chars *(&(%&^$" },
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE 1,4, WEST," }, 
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "pla cE: 1,4, EAST" },
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "pl@cE 1,4, soUtH" },
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "plcE 1,4, soUtH" },
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE 1,4, southeast" },
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE one,4, south" },
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE 1,two, south" },
				{ false, {2,3}, EDir::NORTH, ECmd::PLACE, "placE asdf 1,two, south" },
				
				//---move
				{ true,  {0,0}, EDir::NORTH, ECmd::PLACE, "place 0,0,north" },   //set initial pos.
				{ true,  {0,1}, EDir::NORTH, ECmd::MOVE, "move" },
				{ true,  {0,2}, EDir::NORTH, ECmd::MOVE, "  mOVE" },
				{ true,  {0,3}, EDir::NORTH, ECmd::MOVE, "    MovE    " },
				{ true,  {0,4}, EDir::NORTH, ECmd::MOVE, "\t \tMOVE   \t\t \t " },
				{ true,  {0,4}, EDir::EAST,  ECmd::RIGHT, "right" },             //avoid pos beyond table bounds.
				{ true,  {1,4}, EDir::EAST,  ECmd::MOVE, "\t\tmove\t\t\t" },

				{ true,  {2,3}, EDir::NORTH, ECmd::PLACE, "place 2,3,north" },   //set initial pos.
				{ false, {2,3}, EDir::NORTH, ECmd::MOVE, "MoVe    //extra chars 75%$47&(*& " },      //NOTE: comments might be supported in the future, specially if commands are from file.
				{ false, {2,3}, EDir::NORTH, ECmd::MOVE, "move place" },
				{ false, {2,3}, EDir::NORTH, ECmd::MOVE, "move 2" },            //NOTE: invalid for now.
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "m0ve" },
				{ false, {2,3}, EDir::NORTH, ECmd::MOVE, "move:" },

				//---left
				{ true,  {2,2}, EDir::NORTH, ECmd::PLACE, "place 2,2,north" },   //set initial pos.
				{ true,  {2,2}, EDir::WEST,  ECmd::LEFT, "left" },
				{ true,  {2,2}, EDir::SOUTH, ECmd::LEFT, "   LEfT" },
				{ true,  {2,2}, EDir::EAST,  ECmd::LEFT, "   leFT   " },
				{ true,  {2,2}, EDir::NORTH, ECmd::LEFT, "\t \tLEFt   \t\t \t " },
				{ true,  {2,2}, EDir::WEST, ECmd::LEFT, "\t\tleft\t\t\t" },

				{ true,  {2,3}, EDir::NORTH, ECmd::PLACE, "place 2,3,north" },   //set initial pos.
				{ false, {2,3}, EDir::NORTH, ECmd::LEFT, "LeFt    //extra chars 75%$47&(*& " },      //NOTE: comments might be supported in the future, specially if commands are from file.
				{ false, {2,3}, EDir::NORTH, ECmd::LEFT, "left right" },
				{ false, {2,3}, EDir::NORTH, ECmd::LEFT, "left 2" },            //NOTE: invalid for now.
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "l3fT" },
				{ false, {2,3}, EDir::NORTH, ECmd::LEFT, "left:" },

				//---right
				{ true,  {2,2}, EDir::NORTH, ECmd::PLACE, "place 2,2,north" },   //set initial pos.
				{ true,  {2,2}, EDir::EAST,  ECmd::RIGHT, "right" },
				{ true,  {2,2}, EDir::SOUTH, ECmd::RIGHT, "   RigHt" },
				{ true,  {2,2}, EDir::WEST,  ECmd::RIGHT, "   rigHt   " },
				{ true,  {2,2}, EDir::NORTH, ECmd::RIGHT, "\t \tRIGht   \t\t \t " },
				{ true,  {2,2}, EDir::EAST, ECmd::RIGHT, "\t\trIght\t\t\t" },

				{ true,  {2,3}, EDir::NORTH, ECmd::PLACE, "place 2,3,north" },   //set initial pos.
				{ false, {2,3}, EDir::NORTH, ECmd::RIGHT, "RighT    //extra chars 75%$47&(*& " },      //NOTE: comments might be supported in the future, specially if commands are from file.
				{ false, {2,3}, EDir::NORTH, ECmd::RIGHT, "right place" },
				{ false, {2,3}, EDir::NORTH, ECmd::RIGHT, "right 2" },            //NOTE: invalid for now.
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "ri9ht" },
				{ false, {2,3}, EDir::NORTH, ECmd::RIGHT, "right:" },
				
				//---report
				{ true,  {1,2}, EDir::NORTH, ECmd::PLACE, "place 1,2,north" },   //set initial pos.
				{ true,  {1,2}, EDir::NORTH, ECmd::REPORT, "report" },
				{ true,  {1,2}, EDir::NORTH, ECmd::REPORT, "   REpOrt" },
				{ true,  {1,2}, EDir::NORTH, ECmd::REPORT, "   repOrT   " },
				{ true,  {1,2}, EDir::NORTH, ECmd::REPORT, "\t \REPORt   \t\t \t " },
				{ true,  {1,2}, EDir::NORTH, ECmd::REPORT, "\t\trePort\t\t\t" },

				{ true,  {2,3}, EDir::NORTH, ECmd::PLACE, "place 2,3,north" },   //set initial pos.
				{ false, {2,3}, EDir::NORTH, ECmd::REPORT, "Report    //extra chars 75%$47&(*& " },      //NOTE: comments might be supported in the future, specially if commands are from file.
				{ false, {2,3}, EDir::NORTH, ECmd::REPORT, "report all info" },
				{ false, {2,3}, EDir::NORTH, ECmd::REPORT, "report 5" },
				{ false, {2,3}, EDir::NORTH, ECmd::INVALID, "rep0rt" },
				{ false, {2,3}, EDir::NORTH, ECmd::REPORT, "report:" },

			};

			MgrApp app;
			app.enableLogError(false);
			app.table().setSize({ 5,5 });

			auto& comm = app.commands();
			auto& robot = app.robot();

			robot.Place({ 0,0 }, Vec::RIGHT);

			const int num = sizeof(list) / sizeof(list[0]);
			for (int i = 0; i < num; i++) {
				auto const& item = list[i];

				bool bSuccess = comm.execute( toLowerCase(item.s) );
				auto& pos = robot.getPos();
				auto& dir = robot.getDir();

				auto sMsg = [&](auto sVal) { return wstring(WMSG("[" << i << "]: " << sVal << " for '" << item.s << "'")); };

				Assert::AreEqual(item.r, bSuccess, sMsg("execute stat").c_str());
				Assert::AreEqual(Const::toStr(item.c), comm.lastCmd(), sMsg("command name").c_str());

				Assert::AreEqual(Const::toStr(item.f), app.computeFacingInfo(dir), sMsg("direction").c_str());
				Assert::IsTrue(item.p == pos, sMsg("position").c_str());
				
			}
		}

		TEST_METHOD(Test_CommandSequence)
		{
			using namespace ExamToyRobot;
			using namespace Tools;

			struct {
				const char* tn;   //test name
				Point t;          //table size.
				struct RobStat {
					Point p;  //position
					EDir d;   //direction
				};
				RobStat vF;   //final position
				RobStat vS;   //start position
				vector<string> comms;  //command sequence.
			} list[] = {
				//---moves
				{ "m1", {5,5}, {{0,2},EDir::NORTH },                    //desc: testname, table-size, final pos & dir.
						       {{0,0},EDir::NORTH }, {"move", "move"}},  //desc: start pos & dir, command sequence
				{ "m2", {5,5}, {{4,0},EDir::EAST  },
						       {{0,0},EDir::EAST  }, {"move", "move", "move", "move"}},
				{ "m3", {5,5}, {{3,0},EDir::NORTH },
						   	   {{2,2},EDir::SOUTH }, {"move", "left", "move", "right", "move", "left", "left"}},
				{ "m4", {5,5}, {{4,4},EDir::WEST  },
						       {{2,2},EDir::SOUTH }, {"move", "left", "move", "right", "move", "place 4,4,west"}},
				{ "m5", {5,5}, {{2,1},EDir::WEST  },
							   {{0,0},EDir::NORTH}, {"place 1,1,east", "place 2,2,SOUTH", "move", "right", "move", "place 3,3,NORTH", "place 2,1,west"}},

				//---rotations
				{ "r1", {5,5}, {{3,3},EDir::EAST  },
							   {{2,3},EDir::EAST  }, {"left", "left", "left", "left", "move"}},
				{ "r2", {5,5}, {{2,4},EDir::NORTH },
							   {{2,3},EDir::NORTH }, {"right", "right", "right", "right", "move"}},
				{ "r3", {5,5}, {{1,3},EDir::NORTH },
							   {{1,2},EDir::NORTH }, {"right", "left", "right", "left", "move"}},

				//---out of the table.
				{ "ot1", {5,5}, {{0,0},EDir::WEST  },
								{{0,0},EDir::EAST  }, {"left", "left", "move", "move", "move"}},
				{ "ot2", {5,5}, {{0,1},EDir::NORTH },
								{{0,0},EDir::SOUTH }, {"move", "move", "move", "right", "right", "move"}},
				{ "ot3", {5,5}, {{4,4},EDir::NORTH },
								{{3,3},EDir::EAST  }, {"move", "move", "move", "left", "move", "move", "move"}},
				{ "ot4",{10,9}, {{9,7},EDir::NORTH },
								{{5,5},EDir::EAST  }, {"move", "move", "move", "move", "move", "move", "move", "move", "left", "move", "move"}},
			};

			MgrApp app;
			app.enableLogError(false);
			auto& robot = app.robot();

			int num = sizeof(list) / sizeof(list[0]);
			for (int i = 0; i < num; i++) {
				auto const& item = list[i];

				app.table().setSize(item.t);
				app.robot().Place(item.vS.p, Const::toVec(item.vS.d));
				for (auto const& comm : item.comms) {
					app.commands().execute( toLowerCase(comm) );
				}

				auto& pos = robot.getPos();
				auto& dir = robot.getDir();

				Point pE = item.vF.p; //expected position

				Assert::AreEqual(Const::toStr(item.vF.d), app.computeFacingInfo(dir), WMSG(item.tn << ": direction"));
				Assert::IsTrue(pE == pos, WMSG(item.tn << ": position: Expected{" << pE.x << "," << pE.y << "} != Actual{" << pos.x << "," << pos.y << "}"));

			}

		}

		//TEST_METHOD(Test_ReportOutput)
		//{
		//	std::string expected = "";

		//	std::stringstream buffer;
		//	std::streambuf* sbuf = std::cout.rdbuf(); // Save cout's buffer
		//	std::cout.rdbuf(buffer.rdbuf()); // Redirect cout to the stringstream buffer

		//	// Call main() in your test
		//	//int result = main();

		//	// When finished, redirect cout to the original buffer 
		//	std::cout.rdbuf(sbuf);
		//	std::cout << "std original buffer: \n";
		//	std::cout << buffer.get();

		//	// Test
		//	Assert::AreEqual(expected, buffer.str());

		//}

	};
}
