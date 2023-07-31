#pragma once

#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	"game_resource.h"
// �� ui::ListContainerElement �м̳����п��ù���
namespace MATCH_ITEMS {
	struct NEED_DATAS
	{
		std::wstring player_name;
		RANK_LEVEL	rank_datas;
		int	top1=0;	//Ӣ��id
		int	top2 = 0;	//Ӣ��id
		int	top3 = 0;	//Ӣ��id
		int	top4 = 0;	//Ӣ��id
		int	top5 = 0;	//Ӣ��id
		int	top6 = 0;	//Ӣ��id
	};
}

class Match_Items : public ui::ListContainerElement
{
public:
	Match_Items() {};
	~Match_Items() {};

	// �ṩ�ⲿ��������ʼ�� item ����
	void InitSubControls(MATCH_ITEMS::NEED_DATAS player_info);

private:
	bool OnRemove(ui::EventArgs* args);
private:
	MATCH_ITEMS::NEED_DATAS _info;


	ui::Label* team_player_name;		//�����

	ui::Label* team_player_rank_SOLO;	//��˫
	ui::Label* team_player_rank_FLEX;	//���
	ui::Label* team_player_rank_SOLO_last;	//��˫
	ui::Label* team_player_rank_FLEX_last;	//���


	ui::Control* top1;
	ui::Control* top2;
	ui::Control* top3;
	ui::Control* top4;
	ui::Control* top5;
	ui::Control* top6;


	ui::Label* label_title_;

};
