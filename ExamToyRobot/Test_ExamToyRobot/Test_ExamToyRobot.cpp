#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
//#include "../ExamToyRobot/main.cpp"
#include "../ExamToyRobot/MgrApp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestExamToyRobot
{
	TEST_CLASS(TestExamToyRobot)
	{
	public:
		
		TEST_METHOD(Test_TableBounds)
		{
		}

		TEST_METHOD(Test_RobotRotate)
		{
		}

		TEST_METHOD(Test_CommandParsing) {
			using namespace ExamToyRobot;

			MgrApp app;
			app.enableLogError(false);
			app.table().setSize({ 5,5 });
			
			auto fnToLower = [](auto& s) {
				std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
			};

			struct {
				Point p;
				Point d;
				char const* s;
			} list[] = {
				{ {1,4}, Vec::UP, "place 1,4,NORTH" },
				{ {2,0}, Vec::RIGHT, " plAcE 2 ,0,east" },
				{ {3,1}, Vec::LEFT, "PLACE 3 ,1,WeST" },
				{ {4,2}, Vec::DOWN, "place 4, 2,SOUth" },
				{ {0,3}, Vec::UP, "Place 0,3 ,north " },
				{ {1,4}, Vec::DOWN, "placE 1,4, soUtH" },

				{ {2,0}, Vec::LEFT, "    pLAce   2   ,  0   ,      west   " },
				{ {3,1}, Vec::RIGHT, "  \t\t  plaCe   3   \t,  1 \t  \t  ,   \t   EAST  \t " },

				//todo: add other commands.

			};

			auto& comm = app.commands();
			auto& robot = app.robot();

			robot.Place({ 0,0 }, Vec::RIGHT);

			int num = sizeof(list) / sizeof(list[0]);
			for (int i = 0; i < num; i++) {
				auto& item = list[i];
				string sComm(item.s);
				fnToLower(sComm);
				comm.execute(sComm);
				auto& pos = robot.getPos();
				auto& dir = robot.getDir();
				wstringstream sMsg;	sMsg << L"index: " << i;
				Assert::IsTrue(item.p == pos && item.d == dir, sMsg.str().c_str());
			}
		}

		TEST_METHOD(Test_CommandSequence)
		{
			//todo: add sequence of commands and final output.

		}

		TEST_METHOD(Test_ReportOutput)
		{
			std::string expected = "";

			std::stringstream buffer;
			std::streambuf* sbuf = std::cout.rdbuf(); // Save cout's buffer
			std::cout.rdbuf(buffer.rdbuf()); // Redirect cout to the stringstream buffer

			// Call main() in your test
			//int result = main();

			// When finished, redirect cout to the original buffer 
			std::cout.rdbuf(sbuf);
			std::cout << "std original buffer: \n";
			std::cout << buffer.get();

			// Test
			Assert::AreEqual(expected, buffer.str());

		}

	};
}
