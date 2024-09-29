#pragma once

#include "Robot.h"
#include "TableTop.h"
#include "Commands.h"

namespace ExamToyRobot {

	class MgrApp {
	protected:
		Robot m_robot;
		TableTop m_table;
		Commands m_commands;

		bool m_bIsRunning;

	public:
		MgrApp();
		~MgrApp();
	
		auto& commands() { return m_commands; }
		auto& robot() { return m_robot; }
		auto& table() { return m_table; }

		void Start() { m_bIsRunning = true; }
		bool isRunning() { return m_bIsRunning; };

	protected:
		void setupCommands();

		//---helper functions
		const string& computeFacingInfo(Vec const& d);
		bool CheckError(bool bCond, string const& errMsg);

	};


}//namespace...

