#pragma	once
#include	<Windows.h>
#include	<string>
#include	<regex>
#include	<vector>
#include	<TlHelp32.h>
#include	<mutex>
#include "lcu_riot/struct.h"
#include	"lcu_riot/request_utils.h"


enum class CHAMP_TYPE
{
	love, hate, normal
};
struct ARAM_CHAMPION
{
	CHAMP_TYPE	_type;
	int	champ_id;
	int	score;
};
class Aram_Helper
{
public:
	Aram_Helper();
	~Aram_Helper();
	std::string	output_config_json();//��������
	bool	input_config_json();//�������� ���ؽ������
	void	use_reroll();		//ʹ������
	void	get_current_select_champion();	//��ȡ����ѡ���Ӣ��
	void	get_all_bach_champ();	//��ȡ���б�սϯӢ��
	void	set_champ_type();		//����Ӣ�۵ķ��� ���� ϲ�� һ����ϲ�� �� һ��
	void	change_champ_score();	//����Ӣ�۵����ȼ�

private:
	std::vector<CHAMPION>	bach_champions;

};
