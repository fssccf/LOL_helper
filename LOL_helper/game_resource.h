#pragma	once
#include	<curl/curl.h>
#include	<string>
#include "shlobj.h" 
#include <fstream>
#include	"lcu_riot/request_utils.h"
#include	"lcu_riot/json.hpp"
//��������������������Ϸ�ļ�
//���� ͷ��,Ӣ��Ԥ��
//���ȳ�ʼ��,������ȡһ���ļ���appdata��,Ȼ���½�Ŀ¼
//��һЩö��ֵ,������ʶ ͷ�� | Ӣ�� 
//�ô�����������Ѿ�������,��ô�ͷ���·��,��������ھ�����
using json = nlohmann::json;

namespace GAME_RESOURCES
{
	enum DOWN_TYPE
	{
		ICONS, CHAMPION_ICONS
	};
	class GAME_RES
	{
	public:
		GAME_RES(const GAME_RES&) = delete;
		GAME_RES& operator=(const GAME_RES&) = delete;

		static GAME_RES& getInstance() {
			static GAME_RES instance;
			return instance;
		}
		std::string	getIconsPath(DOWN_TYPE type, int id);

	private:
		GAME_RES();
		~GAME_RES();
		static bool folderExists(const std::string& folderPath);
		bool	download(DOWN_TYPE type, std::string child_url, std::string save_name);


	private:
		std::string	AppdataFolder;
		std::string	MyFolder;
	};

}