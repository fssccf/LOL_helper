#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	<Windows.h>
#include	"lcu_riot/config.h"
#include	"lock_champs_ui.h"
#include	"lova_champ_ui.h"
#include	"lcu_riot/lcu_api.h"
#include	"global_.h"
#include <commdlg.h>


class Helper_Setting : public ui::WindowImplBase
{
public:
	Helper_Setting();

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	virtual void InitWindow() override;
	void	AddSettingsConfig(Settings_Config Config);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const std::wstring kClassName;

private:
	bool	child_close_notify(ui::EventArgs* args);	//�Ӵ��ڹرպ�֪ͨ
	bool	OnBtnClicked(ui::EventArgs* args);
	bool	OnControlSelected(ui::EventArgs* Args);
	bool	isWhichReroller(ui::EventArgs* Args);
	void	saveToConfigJson();
	void	initAllSubControls();
	int		getIdByChampName(std::string champ_name);
	std::string	getNameByChampId(int champ_id);
	void	init_ui_for_config();
	void	foreg_get_configfiledatas();	//ǿ�ƴ�config_settings��ȡ����

	ui::Label* _ui_lockChamp;	//������ʶƥ����������Ҫ��������˭
	ui::Button* _ui_lockAotherChamp;//ѡ������Ӣ����Ϊ����Ӣ��
	ui::CheckBox* _ui_autoLock;	//�������Զ�����
	ui::RichEdit* _ui_autoLockTimeout;//������ʱ
	ui::RichEdit* _ui_acceptTimeout;//���ܶԾ���ʱ
	ui::RichEdit* _ui_arammaxtimeout;//aram�������ʱ��
	ui::Option* _ui_reroller1;	//����ʹ�ò���1	����ʹ��
	ui::Option* _ui_reroller2;	//����ʹ�ò���2	�оͲ�ʹ��
	ui::Option* _ui_reroller3;	//����ʹ�ò���3	���ǲ�ʹ��
	ui::Combo* _ui_lovaChampList;	//Ӣ��ϲ����ʾ�б�
	ui::Button* _ui_lovaAotherChamp;//ѡ������Ӣ��ϲ��
	ui::Button* _ui_loadConfig;//��������
	ui::Button* _ui_outputConfig;//��������
	ui::Button* _ui_saveConfig;//��������
	ui::Button* _ui_calcelConfig;//ȡ������

	Settings_Config	_config;
	std::vector<CHAMP_INFO>	all_champs;
};
