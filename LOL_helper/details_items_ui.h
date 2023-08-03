#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include "lcu_riot/utils.h"
#include	"game_resource.h"


// �� ui::ListContainerElement �м̳����п��ù���
class Details_Item : public ui::ListContainerElement
{
public:
	Details_Item();
	~Details_Item();

	// �ṩ�ⲿ��������ʼ�� item ����
	void InitSubControls(const PLAYER_HISTORY_MATCHDATA &data);

private:
	bool OnRemove(ui::EventArgs* args);
	void	SetBkImg(std::string path);
private:
	ui::Label* game_mode;	//��Ϸģʽ
	ui::Label* create_date;	//������Ϸʱ��
	ui::Label* game_date;	//��Ϸ����ʱ��

	ui::Label* game_win;	//Ӯ�˻�������
	ui::Label* player_kda;	//ս��
	ui::Label* player_dealtandvision_detailinfo;	//�˺�����Ұ�÷�
	ui::Control* use_champ;	//Ӣ��ͷ��
};

