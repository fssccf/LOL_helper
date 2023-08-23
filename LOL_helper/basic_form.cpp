#include "basic_form.h"
#pragma comment(lib, "Urlmon.lib") 
#include	<Shlobj.h>
#include	"global_.h"

const std::wstring BasicForm::kClassName = L"Basic";
BasicForm::BasicForm()
{
	//���Գ�ʼ��config_�����ļ�
	OutputDebugStringA("config_Settings_enable\n");
	if(!config_settings.load_config_file())
		config_settings.save_current_config();
}

BasicForm::~BasicForm()
{

}

std::wstring BasicForm::GetSkinFolder()
{
	return L"basic";
}

std::wstring BasicForm::GetSkinFile()
{
	return L"basic.xml";
}

std::wstring BasicForm::GetWindowClassName() const
{
	return kClassName;
}

void BasicForm::InitWindow()
{
	init_all_controls();
	init_set_listen_controls();
	config_file_settings_to_ui();
	StdClosure	wait_game_start = [this]() {
		do
		{
			std::string result;
			while (result.find("token") == std::string::npos) {
				result = GetProcessCommandLine("wmic process where caption='LeagueClientUx.exe' get commandline");
				if (result.find("token") == std::string::npos) {
					Sleep(2000);
					continue;
				}
			}
			raw_lcu_api::getInstance().set_game_commandline(result);
			Sleep(5000);
			if (raw_lcu_api::getInstance().init() == false) {
				Sleep(5000);
				continue;
			}
			nbase::ThreadManager::PostDelayedTask(kThreadNetwork, std::bind(&BasicForm::Receive_Datas2, this, raw_lcu_api::getInstance().get_summoner_datas()), nbase::TimeDelta::FromMilliseconds(1000));
			nbase::ThreadManager::PostDelayedTask(kThreadNetwork, std::bind(&BasicForm::Receive_Datas3, this, raw_lcu_api::getInstance().puuid_get_rank_datas()), nbase::TimeDelta::FromMilliseconds(1000));
			GAME_STATUS		forg_game_status=GAME_STATUS::Error;
			GAME_STATUS		game_Status = raw_lcu_api::getInstance().get_game_status();
			while (game_Status != GAME_STATUS::Error) {
				game_Status = raw_lcu_api::getInstance().get_game_status();
				if (game_Status!=forg_game_status)
				{
					nbase::ThreadManager::PostTask(kThreadNetwork, nbase::Bind(&BasicForm::Receive_Datas1, this, game_Status));
					forg_game_status = game_Status;
				}
				if (game_Status==GAME_STATUS::InProgress)
				{
					Sleep(5 * 1000);
				}else
					Sleep(1000);
			}
		} while (true);
	};
	nbase::ThreadManager::PostTask(kThreadLoopGetGameStatusThread, ToWeakCallback(wait_game_start));
}


LRESULT BasicForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT BasicForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_USER && wParam == TRAY_ICON_ID) {
		return OnTrayIcon(uMsg, wParam, lParam, false);
	}
	if (uMsg == myMessage) {
		Post2UI([this]() {
			this->ActiveWindow();
			::SetForegroundWindow(m_hWnd);
			::BringWindowToTop(m_hWnd);
			});
		//ɾ������ͼ��
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		//��ʾ������
		ShowWindow(SW_SHOWNORMAL);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

bool	BasicForm::OnSelected(ui::EventArgs* args) {
	if (args->Type == ui::kEventSelect || args->Type == ui::kEventUnSelect)
	{
		update_select_status();
		ui::CheckBox* c = static_cast<ui::CheckBox*>((args->pSender));
		auto	str = c->GetText();
		add_str_status(str, c->IsSelected());
		c->SetText(str);
	}
	return	true;
}

void	BasicForm::init_all_controls() {
	tools_area = static_cast<ui::VBox*>(FindControl(L"tools_area"));
	_ui_accept = static_cast<ui::CheckBox*>(FindControl(L"_ui_accept"));
	_ui_nextgame = static_cast<ui::CheckBox*>(FindControl(L"_ui_nextgame"));
	_ui_searchqueue = static_cast<ui::CheckBox*>(FindControl(L"_ui_searchqueue"));
	summoner_icon = dynamic_cast<ui::Control*>(FindControl(L"summoner-icon"));

	_ui_player_name = static_cast<ui::Label*>(FindControl(L"player_name"));
	_ui_player_level = static_cast<ui::Label*>(FindControl(L"player_level"));
	_ui_RANKED_SOLO_5x5 = static_cast<ui::Label*>(FindControl(L"RANKED_SOLO_5x5"));
	_ui_RANKED_FLEX_SR = static_cast<ui::Label*>(FindControl(L"RANKED_FLEX_SR"));
	_ui_RANKED_TFT = static_cast<ui::Label*>(FindControl(L"RANKED_TFT"));
	_ui_RANKED_TFT_TURBO = static_cast<ui::Label*>(FindControl(L"RANKED_TFT_TURBO"));
	_ui_RANKED_TFT_DOUBLE_UP = static_cast<ui::Label*>(FindControl(L"RANKED_TFT_DOUBLE_UP"));

	display_game_status = static_cast<ui::Label*>(FindControl(L"display_game_status"));
	_ui_close = dynamic_cast<ui::Button*>(FindControl(L"closebtn1"));
	_helper_settings = dynamic_cast<ui::Button*>(FindControl(L"helper_settings"));
	
	_ui_player_helper = dynamic_cast<ui::CheckBox*>(FindControl(L"matching_helper"));
	_ui_aram_helper = dynamic_cast<ui::CheckBox*>(FindControl(L"aram_helper"));
	_ui_classic_helper = dynamic_cast<ui::CheckBox*>(FindControl(L"classic_helper"));

#ifdef DYNAMIC_SKIN
	//_download_R3nzdll = dynamic_cast<ui::Label*>(FindControl(L"_download_progress"));
	_dynamic_skin = dynamic_cast<ui::CheckBox*>(FindControl(L"_dynamic_skin"));
	nbase::ThreadManager::PostDelayedTask(kThreadNetwork, nbase::Bind(&BasicForm::Receive_check, this, dynamic_skin_host_my::check_Allow()), nbase::TimeDelta::FromSeconds(1));
#endif // DYNAMIC_SKIN
}

void	BasicForm::init_set_listen_controls() {
	_ui_accept->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_accept->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));

	//�Զ���һ��
	_ui_nextgame->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_nextgame->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));


	//�Զ��������
	_ui_searchqueue->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_searchqueue->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));


	//�Զ�����
	_ui_accept->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_accept->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));


	//ս������
	_ui_player_helper->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_player_helper->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));

	//���Ҷ�����
	_ui_aram_helper->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_aram_helper->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));

	//ƥ������
	_ui_classic_helper->AttachSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));
	_ui_classic_helper->AttachUnSelect(std::bind(&BasicForm::OnSelected, this, std::placeholders::_1));

	_ui_close->AttachClick(std::bind(&BasicForm::OnUiMyClose, this, std::placeholders::_1));

	_helper_settings->AttachClick(std::bind(&BasicForm::OnHelperSettings, this, std::placeholders::_1));
}

std::wstring	BasicForm::add_str_status(const std::wstring& content, bool status) {
	std::wstring	ret(content);
	if (content.find(L"-") == std::wstring::npos) {
		ret += L"-";
	}
	else {
		ret = content.substr(0, content.find(L"-") + 1);
	}

	if (status)
	{
		ret += L"����";
	}
	else
		ret += L"�ر�";
	return	ret;
}

void	BasicForm::Receive_Datas1(GAME_STATUS gamestatus) {
	StdClosure	closure = [this, gamestatus]() {
		if (gamestatus != GAME_STATUS::ChampSelect && config_settings.configs.matching_helper && tools_windows != NULL)
		{
			std::lock_guard<std::mutex> lock(ui_still_alive_lock);
			still_alive = false;
			tools_windows->Close();
			tools_windows = NULL;
		}

		switch (gamestatus)
		{
		case GAME_STATUS::Error:
			display_game_status->SetText(L"�ȴ���Ϸ������");
			break;
		case GAME_STATUS::None:
			display_game_status->SetText(L"��Ϸ����");
			break;
		case GAME_STATUS::Lobby:
			display_game_status->SetText(L"������");
			if (config_settings.configs.searchqueue_status == true && tools_windows == NULL)
				raw_lcu_api::getInstance().search_queue();
			break;
		case GAME_STATUS::Matchmaking:
			display_game_status->SetText(L"ƥ����");
			break;
		case GAME_STATUS::ReadyCheck:
			display_game_status->SetText(L"�ҵ��Ծ�");
			if (config_settings.configs.accept_status == true)
				if (config_settings.configs.accept_timeout!=0)
				{
					nbase::ThreadManager::PostDelayedTask(kThreadNetwork,[]() {
						raw_lcu_api::getInstance().accept_game();
						}, nbase::TimeDelta::FromSeconds(config_settings.configs.accept_timeout));
				}else
					raw_lcu_api::getInstance().accept_game();

			break;
		case GAME_STATUS::ChampSelect:
			display_game_status->SetText(L"ѡӢ����");
			if (config_settings.configs.matching_helper)
			{//ս������
				open_player_helper_tools();
			}
			if (config_settings.configs.aram_helper || config_settings.configs.classic_helper)
			{
				const auto response = raw_lcu_api::getInstance().get_current_game_mode();
				std::string	game_mode = response.map.game_mode;
				//��ȡ�˿���Ϸģʽ   ���Ҷ�����  
				if (game_mode._Equal("ARAM")) {
					nbase::ThreadManager::PostTask(kThreadHelperWorkThread, [this]() {
						aram_helper.run();
						});
				}
				if (game_mode._Equal("CLASSIC")&&response.game_data.queue.is_ranked==false)
				{
					nbase::ThreadManager::PostTask(kThreadHelperWorkThread, [this]() {
						classic_helper.run();
						});
				}
			}
			break;
		case GAME_STATUS::InProgress:
			display_game_status->SetText(L"��Ϸ��");
			break;
		case GAME_STATUS::PreEndOfGame:
			display_game_status->SetText(L"��Ϸ��������");
			break;
		case GAME_STATUS::WaitingForStats:
			display_game_status->SetText(L"�ȴ�����ҳ��");
			break;
		case GAME_STATUS::EndOfGame:
			display_game_status->SetText(L"��Ϸ����");
			if (config_settings.configs.nextgame_status == true)
				raw_lcu_api::getInstance().auto_next_game();
			break;
		case GAME_STATUS::Reconnect:
			display_game_status->SetText(L"�ȴ���������");
			break;
		default:
			break;
		}
	};
	Post2UI(closure);//Global network request Thread
}

void	BasicForm::Receive_Datas2(LCU_JSON_RESPONSE::LolSummonerInfo info) {
	StdClosure	closure = [this, info]() {
		_ui_player_name->SetText(string2wstring(info.display_name));
		_ui_player_level->SetText(std::to_wstring(info.summoner_level));
		nbase::ThreadManager::PostTask(kThreadNetwork, nbase::Bind(&BasicForm::set_current_player_icon, this, GAME_RESOURCES::GAME_RES::getInstance().getIconsPath(GAME_RESOURCES::ICONS, info.profile_icon_id)));;//Global network request Thread
	};
	Post2UI(closure);
}

void	BasicForm::Receive_Datas3(LCU_JSON_RESPONSE::LolRankedData rank_Datas) {
	StdClosure	closure = [this, rank_Datas]() {
		auto	SOLO_5x5 = rank_Datas.queue_map.ranked_solo_5_x5;
		if (!SOLO_5x5.tier.empty()) {
			std::wstring	n = StringToWString(F_ClassicRank_tiers.GetSecond(SOLO_5x5.tier)) + StringToWString(SOLO_5x5.division) + L" " + std::to_wstring(SOLO_5x5.league_points);
			_ui_RANKED_SOLO_5x5->SetText(n);
		}
		auto	FLEX_SR = rank_Datas.queue_map.ranked_flex_sr;
		if (!FLEX_SR.tier.empty()) {
			std::wstring	n = StringToWString(F_ClassicRank_tiers.GetSecond(FLEX_SR.tier)) + L" " + StringToWString(FLEX_SR.division) + L" " + std::to_wstring(FLEX_SR.league_points);
			_ui_RANKED_FLEX_SR->SetText(n);
		}
		auto	TFT = rank_Datas.queue_map.ranked_tft;
		if (!TFT.tier.empty()) {
			std::wstring	n = StringToWString(F_ClassicRank_tiers.GetSecond(TFT.tier)) + StringToWString(TFT.division) + L" " + std::to_wstring(TFT.league_points);
			_ui_RANKED_TFT->SetText(n);
		}
		auto	TFT_TURBO = rank_Datas.queue_map.ranked_tft_turbo;
		if (!TFT_TURBO.tier.empty()) {
			std::wstring	n = StringToWString(F_ClassicRank_tiers.GetSecond(TFT_TURBO.tier)) + StringToWString(TFT_TURBO.division) + L" " + std::to_wstring(TFT_TURBO.league_points);
			_ui_RANKED_TFT_TURBO->SetText(n);
		}
		auto	TFT_DOUBLE_UP = rank_Datas.queue_map.ranked_tft_double_up;
		if (!TFT_DOUBLE_UP.tier.empty()) {
			std::wstring	n = StringToWString(F_ClassicRank_tiers.GetSecond(TFT_DOUBLE_UP.tier)) + L" " + StringToWString(TFT_DOUBLE_UP.division) + L" " + std::to_wstring(TFT_DOUBLE_UP.league_points);
			_ui_RANKED_SOLO_5x5->SetText(n);
		}
	};
	Post2UI(closure);//Global network request Thread
}

void	BasicForm::set_current_player_icon(std::string icon_path) {
	StdClosure	closure = [this, icon_path]() {
		summoner_icon->SetBkImage(string2wstring(icon_path));
	};
	Post2UI(closure);//Global network request Thread
}

#ifdef DYNAMIC_SKIN
void	BasicForm::Receive_check(bool	check) {
	if (check == false)
	{
		_dynamic_skin->SetText(L"O No ���ع�����ʱ������");
	}
	else
	{
		_dynamic_skin->SetText(L"���չ���:��̬����");
		_dynamic_skin->AttachSelect(std::bind(&BasicForm::Open_dynamic_skin, this, std::placeholders::_1));
		_dynamic_skin->AttachUnSelect(std::bind(&BasicForm::Open_dynamic_skin, this, std::placeholders::_1));
		nbase::ThreadManager::PostDelayedTask(kThreadNetwork, nbase::Bind(&BasicForm::Receive_download_dll_path, this, dynamic_skin_host_my::download_dll()), nbase::TimeDelta::FromSeconds(1));
	}//���չ���:��̬����
}

bool	BasicForm::Open_dynamic_skin(ui::EventArgs* args) {
	if (args->Type == ui::kEventSelect || args->Type == ui::kEventUnSelect)
	{
		if (!origin_dll_path.empty())
		{
			if (args->Type == ui::kEventSelect) {
				if (!dynamic_skin_host_my::open_dynamic_skin(origin_dll_path)) {
					_dynamic_skin->Selected(false, false);
				}
				else
				{
					const TCHAR szOperation[] = _T("open");
					const TCHAR szAddress[] = _T("https://note.youdao.com/s/P8BuWoMJ");
					HINSTANCE hRslt = ShellExecute(NULL, szOperation,
						szAddress, NULL, NULL, SW_SHOWNORMAL);
				}
			}

			if (args->Type == ui::kEventUnSelect) {
				if (!dynamic_skin_host_my::close_dynamic_skin()) {
					_dynamic_skin->Selected(true, false);
				}
			}
		}
		else {
			_dynamic_skin->Selected(false, false);
		}
		ui::CheckBox* c = static_cast<ui::CheckBox*>((args->pSender));
		auto	str = c->GetText();
		add_str_status(str, c->IsSelected());
		c->SetText(str);
	}
	return	true;
}
void	BasicForm::Receive_download_dll_path(std::string	save_path) {
	if (!save_path.empty())
	{
		origin_dll_path = save_path;
	}
	else {
		_dynamic_skin->SetText(L"����ʧ��,�����´򿪳�����");
	}
}
#endif // DYNAMIC_SKIN

bool	BasicForm::OnUiMyClose(ui::EventArgs* args) {
	//SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	::ShowWindow(m_hWnd, SW_HIDE);
	AddTrayIcon();
	return true;
}


void BasicForm::AddTrayIcon() {
	// ��������ͼ��
	ZeroMemory(&m_trayIcon, sizeof(NOTIFYICONDATA));
	m_trayIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_trayIcon.hWnd = m_hWnd;
	m_trayIcon.uID = TRAY_ICON_ID;
	m_trayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_trayIcon.uCallbackMessage = WM_USER;
	m_trayIcon.hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	lstrcpy(m_trayIcon.szTip, L"LOL�Ծ�����");
	Shell_NotifyIcon(NIM_ADD, &m_trayIcon);
	ShowWindow(SW_HIDE);
}

void	BasicForm::update_select_status() {
	config_settings.configs.accept_status = _ui_accept->IsSelected();
	config_settings.configs.nextgame_status = _ui_nextgame->IsSelected();
	config_settings.configs.searchqueue_status = _ui_searchqueue->IsSelected();
	config_settings.configs.matching_helper = _ui_player_helper->IsSelected();
	config_settings.configs.aram_helper = _ui_aram_helper->IsSelected();
	config_settings.configs.classic_helper = _ui_classic_helper->IsSelected();
	config_settings.save_current_config();	//ÿ�θ��Ľ����checkbox���ؾ�����д��config�ļ���
}

void	BasicForm::config_file_settings_to_ui() {
	//�޸�ui����ĵ��״̬
	_ui_accept->Selected(config_settings.configs.accept_status, false);
	_ui_accept->SetText(add_str_status(_ui_accept->GetText(), _ui_accept->IsSelected()));

	_ui_nextgame->Selected(config_settings.configs.nextgame_status, false);
	_ui_nextgame->SetText(add_str_status(_ui_nextgame->GetText(), _ui_nextgame->IsSelected()));


	_ui_searchqueue->Selected(config_settings.configs.searchqueue_status, false);
	_ui_searchqueue->SetText(add_str_status(_ui_searchqueue->GetText(), _ui_searchqueue->IsSelected()));

	_ui_player_helper->Selected(config_settings.configs.matching_helper, false);
	_ui_player_helper->SetText(add_str_status(_ui_player_helper->GetText(), _ui_player_helper->IsSelected()));

	_ui_aram_helper->Selected(config_settings.configs.aram_helper, false);
	_ui_aram_helper->SetText(add_str_status(_ui_aram_helper->GetText(), _ui_aram_helper->IsSelected()));

	_ui_classic_helper->Selected(config_settings.configs.classic_helper, false);
	_ui_classic_helper->SetText(add_str_status(_ui_classic_helper->GetText(), _ui_classic_helper->IsSelected()));
}

bool BasicForm::OnHelperSettings(ui::EventArgs* args)
{
	if (GAME_STATUS::Error==raw_lcu_api::getInstance().get_game_status())
	{
		MessageBoxA(NULL,"δ��⵽��Ϸ","error",MB_OK);
		return	true;
	}
	Helper_Setting	*wnd = new Helper_Setting();
	wnd->Create(this->GetHWND(), L"��������", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	wnd->ShowModalFake(this->GetHWND(),false);
	wnd->CenterWindow();
	return true;
}


LRESULT BasicForm::OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL bHandled)
{
	//�����ͼ����˫�������ԭ
	if (lParam == WM_LBUTTONDBLCLK)		//WM_LBUTTONDBLCLK	WM_LBUTTONDOWN
	{
		Post2UI([this]() {//MainThread
			this->ActiveWindow();
			::SetForegroundWindow(m_hWnd);
			::BringWindowToTop(m_hWnd);
			});
		//ɾ������ͼ��
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		//��ʾ������
		ShowWindow(SW_SHOWNORMAL);
	}
	//�����ͼ���е����Ҽ��򵯳�����ʽ�˵�
	if (lParam == WM_RBUTTONDOWN)
	{
		//��ȡ�������
		POINT pt; GetCursorPos(&pt);
		//�һ�����ؿ���������һ������Ĳ˵���
		SetForegroundWindow(m_hWnd);
		//���̲˵�    win32����ʹ�õ���HMENU�������MFC�������ʹ��CMenu
		HMENU hMenu;
		//�������̲˵�
		hMenu = CreatePopupMenu();
		//��Ӳ˵�,�ؼ��������õ�һ����ʶ��  WM_ONCLOSE �������õ�
		AppendMenu(hMenu, MF_STRING, MENUBAR_COPYQQ, _T("qȺ:758843151"));
		AppendMenu(hMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(hMenu, MF_STRING, MENUBAR_ONCLOSE, _T("Exit"));
		//�����˵�,�����û���ѡ�˵���ı�ʶ������
		int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, m_hWnd, NULL);
		//�����ʶ����WM_ONCLOSE��ر�
		if (cmd == MENUBAR_ONCLOSE)
		{
			m_trayIcon.hIcon = NULL;
			Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
#ifdef DYNAMIC_SKIN
			dynamic_skin_host_my::close_dynamic_skin();
#endif //DYNAMIC_SKIN
			exit(0);
		}
		else if (cmd == MENUBAR_COPYQQ) {
			CopyTextToClipboard(L"758843151");
		}
	}
	bHandled = true;
	return 0;
}

void	BasicForm::open_player_helper_tools() {
	if (tools_windows == NULL)
	{
		std::lock_guard<std::mutex> lock(ui_still_alive_lock);
		still_alive = true;
		tools_windows = new Pop_form();
		tools_windows->Create(this->GetHWND(), NULL, WS_EX_OVERLAPPEDWINDOW & ~WS_EX_APPWINDOW, 0);
		tools_windows->ShowModalFake(this->GetHWND(), true);
		tools_windows->ShowWindow();
		StdClosure	setUiPos = [this]() {
			while (still_alive) {
				// ��ȡ����λ����Ϣ
				HWND hwnd = FindWindowA(NULL, "League of Legends");
				RECT rect;
				GetWindowRect(hwnd, &rect);
				ui::UiRect	pos;
				pos.top = rect.top;
				pos.left = rect.right;
				tools_windows->Recv_PosInfo(pos);
				Sleep(100);
			}
		};
		nbase::ThreadManager::PostTask(kThreadLoopGetGameUiPosThread, setUiPos);
	}
}