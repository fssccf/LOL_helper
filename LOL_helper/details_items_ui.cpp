#include "details_items_ui.h"


Details_Item::Details_Item()
{
}


Details_Item::~Details_Item()
{
}

void Details_Item::InitSubControls(const PLAYER_HISTORY_MATCHDATA& data)
{
	game_mode = dynamic_cast<ui::Label*>(FindSubControl(L"game_mode"));
	game_date = dynamic_cast<ui::Label*>(FindSubControl(L"game_date"));
	create_date = dynamic_cast<ui::Label*>(FindSubControl(L"create_date"));
	game_win = dynamic_cast<ui::Label*>(FindSubControl(L"game_win"));
	player_kda = dynamic_cast<ui::Label*>(FindSubControl(L"player_kda"));
	use_champ = dynamic_cast<ui::Control*>(FindSubControl(L"use_champ"));
	player_dealtandvision_detailinfo = dynamic_cast<ui::Label*>(FindSubControl(L"player_dealtandvision_detailinfo"));

	if (data.isRank)
		game_mode->SetText(L"��λ��");
	else
		game_mode->SetText(StringToWString(data.gameMode));
	create_date->SetText(StringToWString(timestamp2string(data.gameCreation)));
	game_date->SetText(L"�Ծ�ʱ��:" + std::to_wstring(data.gameDuration / 60) + L"����");
	game_win->SetText(data.participants.win ? L"ʤ��" : L"ʧ��");
	game_win->SetStateTextColor(ui::ControlStateType::kControlStateNormal,data.participants.win ? L"blue" : L"red");

	std::string kda = std::to_string(data.participants.kills) + "/";
	kda.append(std::to_string(data.participants.deaths) + "/");
	kda.append(std::to_string(data.participants.assists)+" ");
	
	kda.append("Lv:" + std::to_string(data.participants.champLevel));
	kda.append(" ����:" + std::to_string(data.participants.goldEarned));
	player_kda->SetText(StringToWString(kda));

	std::string	dealt = "��Ӣ���˺�:" + std::to_string(data.participants.totalDamageDealtToChampions);
	dealt.append(" ��Ұ:" + std::to_string(data.participants.visionScore));
	player_dealtandvision_detailinfo->SetText(StringToWString(dealt));

	nbase::ThreadManager::PostTask(kThreadNetwork, nbase::Bind(&Details_Item::SetBkImg, this, GAME_RESOURCES::GAME_RES::getInstance().getIconsPath(GAME_RESOURCES::CHAMPION_ICONS, data.participants.championId)));
}

bool Details_Item::OnRemove(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent->Remove(this);
}
void	Details_Item::SetBkImg(std::string path) {
	if (!path.empty())
	{
		use_champ->SetBkImage(string2wstring(path));
	}
}