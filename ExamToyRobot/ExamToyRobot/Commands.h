#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <functional>

namespace Tools {

	using namespace std;

	class Cmd {
	public:
		using params_t = vector<string>;
		using func_t = function<bool(const params_t&)>;
	protected:
		regex m_rxParams;
		func_t m_fnAction;
	public:
		Cmd(string const& rx = "", func_t const& fn = nullptr) {
			m_rxParams = rx;
			m_fnAction = fn;
		}
		bool apply(string const& p_sParams) const;
	};

	class Commands {
	public:
		using map_t = unordered_map<string, Cmd>;
	protected:
		regex m_rxCmdKey;
		map_t m_listCmd;
		string m_lastCmd;
	public:
		
		Commands(string const& rx = R"(\w+)", bool iCase = true) {
			setCommandRegex(rx, iCase);
		}

		/* setCommandRegex(rx,iCase)
		*  rx - regex pattern to capture command and parameters.
		*  if rx has no capture group:
		*       whole match -> command-key
		*       suffix -> parameters
		*  if rx has 1 capture group:
		*       group1 -> command key
		*       suffix -> parameters
		*  if rx has 2 capture groups:
		*       group1 -> command key
		*       group2 -> parameters
		*/
		void setCommandRegex(string const& rx, bool iCase = true) {
			m_rxCmdKey = iCase ? regex(rx, regex::icase) : regex(rx);
		}

		auto const& lastCmd() { return m_lastCmd; }

		void add(string const& sKey, string const& rxParams, Cmd::func_t const& fnAction);
		void add(string const& sKey, Cmd::func_t const& fnAction);
		void add(string const& sKey, Cmd const& p_cmd);
		void setList(map_t const& list);

		bool execute(string const& sCommand);
		bool executeIfName(string const& sKey, string const& sCommand);
		bool executeWithParams(string const& sKey, string const& sParams);

	};


}//namespace...
