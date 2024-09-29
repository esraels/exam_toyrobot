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
		string m_lastCmd;   //desc: last command
	public:

		Commands(regex const& rx = regex(R"(\w+)", regex::icase)) {
			m_rxCmdKey = rx;
		};
		Commands(string const& rx, bool iCase = true) {
			setCommandRegex(rx, iCase);
		}

		void setCommandRegex(string const& rx, bool iCase = true) {
			m_rxCmdKey = iCase ? regex(rx, regex::icase) : regex(rx);
		}
		void setCommandRegex(regex const& rx) {
			m_rxCmdKey = rx;
		}
		auto const& lastCmd() {
			return m_lastCmd;
		}

		void add(string const& sKey, string const& rxParams, Cmd::func_t const& fnAction);
		void add(string const& sKey, Cmd::func_t const& fnAction);
		void add(string const& sKey, Cmd const& p_cmd);
		void setList(map_t const& list);

		bool execute(string const& sCommand);
		bool executeWithParams(string const& sKey, string const& sParams);
		bool executeIfName(string const& sKey, string const& sCommand);


	};


}//namespace...
