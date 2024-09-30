#include "Commands.h"
#include "Utils.h"

namespace Tools {

	using namespace std;

	bool Cmd::apply(const string& p_sParams) const {
		if (!m_fnAction) return false;

		params_t listParams;

		if (m_rxParams._Empty()) {
			return m_fnAction(listParams);
		} else {
			smatch result;
			if (regex_search(p_sParams, result, m_rxParams)) {
				auto size = result.size();
				if (size == 1) {
					listParams.push_back(result[0].str());
				}
				else for (int i = 1; i < result.size(); i++) {
					listParams.push_back(result[i].str());
				}
				return m_fnAction(listParams);
			}
			else return false;
		}

	}

	void Commands::add(string const& sKey, string const& rxParams, Cmd::func_t const& fnAction) {
		if (sKey.empty()) return;
		m_listCmd[sKey] = Cmd(rxParams, fnAction);
	}

	void Commands::add(string const& sKey, Cmd::func_t const& fnAction) {
		this->add(sKey, "", fnAction);
	}

	void Commands::add(string const& sKey, Cmd const& p_cmd) {
		if (sKey.empty()) return;
		m_listCmd[sKey] = p_cmd;
	}

	void Commands::setList(map_t const& list) {
		m_listCmd = list;
	}

	bool Commands::execute(string const& sCommand) {
		return executeIfName("", sCommand);
	}

	bool Commands::executeIfName(string const& sKey, string const& sCommand) {
		
		m_lastCmd = "";

		smatch result;
		if (!regex_search(sCommand, result, m_rxCmdKey)) return false;

		string sCmd = (result.length() > 1) ? result[1] : result[0];

		if (!sKey.empty() && sCmd != sKey) return false;

		string sParams = (result.length() > 2) ? result[2] : result.suffix();
		return executeWithParams(sCmd, sParams);
	}

	bool Commands::executeWithParams(string const& sKey, string const& sParams) {
		if (m_listCmd.find(sKey) == m_listCmd.end()) return false;
		m_lastCmd = sKey;
		return m_listCmd[sKey].apply(sParams);
	}

}//namespace...
