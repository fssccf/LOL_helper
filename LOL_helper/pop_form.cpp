#include "pop_form.h"

const std::wstring Pop_form::kClassName = L"basic";


std::wstring Pop_form::GetSkinFolder()
{
	return L"basic";
}

std::wstring Pop_form::GetSkinFile()
{
	return L"secondui.xml";
}

std::wstring Pop_form::GetWindowClassName() const
{
	return kClassName;
}

void Pop_form::InitWindow()
{
	_list = dynamic_cast<ui::ListBox*>(FindControl(L"list"));
	init_set_listen_controls();
	nbase::ThreadManager::PostTask(kThreadMain, std::bind(&Pop_form::Recv_info, this, helper::getInstance().getChatRoomPlayerIdList()));
}

LRESULT Pop_form::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void Pop_form::Recv_info(std::vector<TEAM_SUMMONER_INFO> info)
{
	for (const auto& i : info)
	{
		std::string out = i.puuid + "    " + i.summonerId + "\n";
		OutputDebugStringA(out.c_str());

		MATCH_ITEMS::NEED_DATAS	need;
		need.player_name = helper::getInstance().getDisplayName(i.summonerId);
		need.rank_datas = helper::getInstance().puuid_get_rank_datas(i.puuid);
		auto top_ = helper::getInstance().get_top_champions(i.summonerId, 6);
		if (top_.size()<6)
		{
			for (int i = top_.size(); i < 6; i++) {
				CHAMPION_TOP	t;
				t.championId = 0;
				top_.push_back(t);
			}
		}
		
		{
			need.top1 = top_.at(0).championId;
			need.top2 = top_.at(1).championId;
			need.top3 = top_.at(2).championId;
			need.top4 = top_.at(3).championId;
			need.top5 = top_.at(4).championId;
			need.top6 = top_.at(5).championId;
		}
		Match_Items* item = new Match_Items;
		ui::GlobalManager::FillBoxWithCache(item, L"basic/matchitem.xml");
		item->InitSubControls(need);
		//item->AttachDoubleClick(nbase::Bind(&BasicForm::OnSelectedChampion, this, std::placeholders::_1));
		_list->Add(item);
	}
}

LRESULT Pop_form::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	return __super::HandleMessage(uMsg, wParam, lParam);
}


//�ؼ���
void	Pop_form::init_all_controls() {
	_list = dynamic_cast<ui::ListBox*>(FindControl(L"list"));
}
void	Pop_form::init_set_listen_controls() {

}

