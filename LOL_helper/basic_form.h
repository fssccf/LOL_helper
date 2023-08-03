#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	"lcu_riot/lol_helper.h"
#include	"lcu_riot/utils.h"
#include	"item.h"
#include	<Windows.h>
#include	<shellapi.h>
#include	"resource.h"
#include	"utils.hpp"
#include	"pop_form.h"
#include	"game_resource.h"
#include	"MiscThread.h"

#define	DYNAMIC_SKIN		//���붯̬����
#ifdef DYNAMIC_SKIN
#include	"dynamic_skin.h"
#endif // DYNAMIC_SKIN


// ����ͼ���Ψһ��ʶ��
#define TRAY_ICON_ID 1001
#define	MENUBAR_ONCLOSE	1002
#define	MENUBAR_COPYQQ	1003

struct _UI_STATUS
{
	bool	_ui_accept_status = true;
	bool	_ui_nextgame_status = false;
	bool	_ui_searchqueue_status = false;
	bool	_ui_lockchampion_status = false;
	int		_ui_champion_id = 0;
	bool	_ui_player_help = true;
};

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
	
	

	//�ؼ���
	void	init_all_controls();
	void	init_set_listen_controls();

	ui::CheckBox* _ui_accept;		//��ѡ��
	ui::CheckBox* _ui_nextgame;
	ui::CheckBox* _ui_searchqueue;
	ui::CheckBox* _ui_lockchampion;
	ui::CheckBox* _ui_player_helper;//�Ծ�����
	ui::Label* _ui_selectchampion;	//�û�˫������ʾĿǰ����Ҫ�õ�Ӣ��,������ʾ��
	ui::VBox* tools_area;		//�������������
	ui::Control* summoner_icon;	//�û�ͷ��
	ui::CheckBox* _dynamic_skin;	//��̬���� ����ؼ�Ĭ�������ص�
	ui::Label* _download_R3nzdll;//���ؽ���

	bool	OnSelected(ui::EventArgs* args);
	void	update_select_status();
	bool	OnSelectedChampion(ui::EventArgs* args);
	bool	OnUiMyClose(ui::EventArgs* args);

	void	open_player_helper_tools();

	ui::Label* _ui_player_name;
	ui::Label* _ui_player_level;
	ui::Label* _ui_RANKED_SOLO_5x5;
	ui::Label* _ui_RANKED_FLEX_SR;
	ui::Label* _ui_RANKED_TFT;
	ui::Label* _ui_RANKED_TFT_TURBO;
	ui::Label* _ui_RANKED_TFT_DOUBLE_UP;
	ui::Label* display_game_status;
	ui::ListBox* _champion_list;
	ui::RichEdit* _ui_search_champion;

	ui::Button* _ui_close;
private:

	// �Զ�����Ϣ��ID
	UINT myMessage = RegisterWindowMessage(L"ONLY_ONE");


	//������Ҫ�Ľṹ������
	_UI_STATUS	ui_datas;

	Pop_form* tools_windows;//lol���ִ���

	//����ͼ��
	NOTIFYICONDATA	m_trayIcon;
	//�������ͼ��(��ʼ��)
	void AddTrayIcon();
	//��������ͼ���ϵ��¼�
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled);

	std::vector<CHAMPION>	have_champions_copy;	
	std::vector<CHAMPION> have_champions_copy_sort;	
	//��������,ֻ��Ϊ����ѡ��idʹ��
	//�������� ����ṹ��Ϊ�����������Ƶ�,����������������ݾʹ���������Ӣ��id,���û�� �ʹ������Ǹ���
	// 
	// 
	//��������
	static std::wstring	add_str_status(std::wstring& content,bool status);
	RANK_LEVEL_ITEM get(const RANK_LEVEL& vec,std::string en)const ;

	bool	sort_champions_datas(ui::EventArgs* args);

	void	Receive_Datas1(GAME_STATUS gamestatus);
	void	Receive_Datas2(SUMMONER_INFO info);
	void	Receive_Datas3(RANK_LEVEL rank_Datas);
	void	Receive_Datas4(std::vector<CHAMPION> owner_datas);
	void	set_current_player_icon(std::string icon_path);

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


