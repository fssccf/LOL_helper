#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	"game_resource.h"

// �� ui::ListContainerElement �м̳����п��ù���
class Champ_Item_Ui : public ui::ListContainerElement
{
public:
	Champ_Item_Ui();
	~Champ_Item_Ui();

	// �ṩ�ⲿ��������ʼ�� item ����
	void InitSubControls(const CHAMP_INFO data);

private:
	bool OnRemove(ui::EventArgs* args);
	void	SetBkImg(std::string path);
private:
	ui::Label* champ_name;	//��Ϸģʽ
	ui::Control* champ_icon;	//Ӣ��ͷ��
};

