#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"lcu_riot/struct.h"
#include	"lcu_riot/lol_helper.h"
#include	"details_items_ui.h"
#include	"lcu_structs.hpp"
class Details_Pop : public ui::WindowImplBase
{
public:
	Details_Pop();
	~Details_Pop();

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
	bool	details_isinvalid();
	void	reset_info(int key);
	void	init_info(LCU_JSON_RESPONSE::LolChampSelect info);
	bool	init_set_listen_controls(ui::EventArgs* args);
private:
	void	set_info_to_ui(LCU_JSON_RESPONSE::MyTeam player);
	void	Recv_datas1(LCU_JSON_RESPONSE::LolMatchHistory	datas);
	void	add_items(int participantId);

	int		now_show_player_participantId = 0;


	LCU_JSON_RESPONSE::LolChampSelect	info_;
	std::map<int, LCU_JSON_RESPONSE::LolMatchHistory>	all_datas;//CellId --> ս��

	ui::Label* wind_title;
	ui::ListBox* Vlist;
	ui::VBox* main_box;
};
