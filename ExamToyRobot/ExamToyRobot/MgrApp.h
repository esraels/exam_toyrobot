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
		bool m_bEnableLogError;

	public:
		MgrApp();
		~MgrApp();
	
		auto& commands() { return m_commands; }
		auto& robot() { return m_robot; }
		auto& table() { return m_table; }

		void Start() { m_bIsRunning = true; }
		bool isRunning() { return m_bIsRunning; };

		void enableLogError(bool bEnable = true) { m_bEnableLogError = bEnable; }

		//---helper functions
		const string& computeFacingInfo(Vec const& d);
		void LogError(string const& errMsg);
		bool CheckError(bool bCond, string const& errMsg);

	protected:
		void setupCommands();

	};


}//namespace...

