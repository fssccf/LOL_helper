#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	"lcu_riot/lcu_api.h"
#include	"utils.h"
#include	"item.h"
#include	<Windows.h>
#include	<shellapi.h>
#include	"resource.h"
#include	"pop_form.h"
#include	"game_resource.h"
#include	"MiscThread.h"
#include	"lcu_riot/config.h"
#include	"game_helper.h"
#include	"helper_setting.h"
#include	"timeout_ui.h"

#define	DYNAMIC_SKIN		//���붯̬����
#ifdef DYNAMIC_SKIN
#include	"dynamic_skin.h"
#endif // DYNAMIC_SKIN


// ����ͼ���Ψһ��ʶ��
#define TRAY_ICON_ID 1001
#define	MENUBAR_ONCLOSE	1002
#define	MENUBAR_COPYQQ	1003

class BasicForm : public ui::WindowImplBase
{
public:
	BasicForm();
	~BasicForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void InitWindow() override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;


	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	static const std::wstring kClassName;

	
private:	//������
	
	ui::CheckBox* _ui_accept;		//��ѡ�� 
	ui::CheckBox* _ui_nextgame;
	ui::CheckBox* _ui_searchqueue;
	ui::CheckBox* _ui_player_helper;//ս������
	ui::CheckBox* _ui_aram_helper;//���Ҷ�����
	ui::CheckBox* _ui_classic_helper;//ƥ������

	ui::VBox* tools_area;		//�������������
	ui::Control* summoner_icon;	//�û�ͷ��
	ui::CheckBox* _dynamic_skin;	//��̬���� ����ؼ�Ĭ�������ص�

	ui::Label* _ui_player_name;
	ui::Label* _ui_player_level;
	ui::Label* _ui_RANKED_SOLO_5x5;
	ui::Label* _ui_RANKED_FLEX_SR;
	ui::Label* _ui_RANKED_TFT;
	ui::Label* _ui_RANKED_TFT_TURBO;
	ui::Label* _ui_RANKED_TFT_DOUBLE_UP;
	ui::Label* display_game_status;

	ui::Button* _ui_close;
	ui::Button* _helper_settings;//�������� ��ť

	GAME_HELPER::Aram_helper	aram_helper;	//�����������
	GAME_HELPER::Classic_helper classic_helper;	//�����������

	// �Զ�����Ϣ��ID
	UINT myMessage = RegisterWindowMessage(L"ONLY_ONE");
	Pop_form* tools_windows;//lol���ִ���
	//����ͼ��
	NOTIFYICONDATA	m_trayIcon;

	//ʹ�õ��߳�
	std::mutex	ui_still_alive_lock;
	bool	still_alive = false;

private://������
	bool	OnSelected(ui::EventArgs* args);	//��ѡ�򱻵����Ĵ�����
	void	update_select_status();	//��ui'�ϸ�ѡ��ѡ��ʱ,���¸�ѡ�����ʾ�ı�
	bool	OnUiMyClose(ui::EventArgs* args);	//����ǵ�ui�� �رհ�ť ������ʱ ����һ������ͼ��ĺ���
	bool	OnHelperSettings(ui::EventArgs* args);//��ui�� �������ñ�����ʱ�Ĵ�����

	void	open_player_helper_tools();	//������ս������֮��,�����������������ս����
	//�ؼ���ʼ������
	void	init_all_controls();
	void	init_set_listen_controls();
	
	//�������ͼ��(��ʼ��)
	void	AddTrayIcon();
	//��������ͼ���ϵ��¼�
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled);

	//�������� ����
	//static std::wstring	add_str_status(const std::wstring& content,bool status);

	//�������������Ļص�����
	void	Receive_Datas1(GAME_STATUS gamestatus);
	void	Receive_Datas2(LCU_JSON_RESPONSE::LolSummonerInfo info);
	void	Receive_Datas3(LCU_JSON_RESPONSE::LolRankedData rank_Datas);

	void	set_current_player_icon(std::string icon_path);
	void	config_file_settings_to_ui();
#ifdef DYNAMIC_SKIN
	//�Զ�̬Ƥ���¼���Ĵ���
	//2023-7-16
	std::string	origin_dll_path;	//���غõ� Ƥ�� dll ��·��
	std::string	lol_game_path;	//lol\\game·��
	void	Receive_check(bool	check);
	void	Receive_download_dll_path(std::string	save_path);
	bool	Open_dynamic_skin(ui::EventArgs* args);
#endif // DYNAMIC_SKIN
};


