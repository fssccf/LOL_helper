#pragma	once
#include	"lcu_riot/lcu_api.h"
#include	<vector>
#include	"global_.h"

namespace GAME_HELPER
{
	enum class Status
	{
		CAN, CANOT, WAIT
	};

	//ս������ʵ��
	class Match_helper
	{
	public:
		Match_helper();//ս������ʵ��
		~Match_helper();//ս������ʵ��

	private:
	};
	class Helper_base
	{
	public:
		virtual bool run()=0;
		virtual void getconfig_for_configfiles() = 0;
	protected:
		raw_lcu_api& request = raw_lcu_api::getInstance();
	};

	//ƥ������,ʵ������Ӣ�� �Զ���������
	class Classic_helper:public	Helper_base
	{
	public:
		Classic_helper();
		~Classic_helper();
		bool	run()override;
		
	private:
		void	getconfig_for_configfiles()override;

		void	set_lock_champ(int champ);
		void	locking_champs(int champ_id = 0, bool completed = true);	//����Ӣ�� ���Ϊ0 �������ڸ����б����Ӣ��
		bool	check_is_have_champs(int champ_id = 0);	//����ǲ���ӵ�����Ӣ��		���Ϊ0 �ͼ���ǲ���ӵ�� lock_champ Ӣ��
		Status  check_is_selected_champs(int champ_id);	//����ǲ����Ѿ���������������
		LCU_JSON_RESPONSE::LolOwnerChampions	owner_champs;
		int		lock_champ = 0;
		bool	iscompleted = false;
		int		lock_timeout = 0;
	};

	//���Ҷ����� �ṩ ��Ӣ�� ����
	class Aram_helper :public	Helper_base
	{
	public:
		Aram_helper();
		~Aram_helper();
		bool	run()override;
	private:
		void	getconfig_for_configfiles()override;
		void	set_my_summoner_id();
		int		get_score_(int champ_id);
		std::vector<int>	get_all_bech_champs();	//��ȡ���б�սϯӢ��
		int64_t	get_now_select_champ();	//��ȡ�����ڵ�Ӣ��id
		
		int		wait_max_sec = 0;		//����һ�����,�����Ӣ��A �ĺø�ֵ��2����������������� ��������ѡ���Ӣ����B �øж���1 ��������п��ܻ�ѡ������Ӣ��, ������������� ��Ҫ���еȴ������� �м� ����л����õ� ��ѡ�� ����30�� 
		std::vector<std::pair<int,int>>	score_champs;	//Ӣ��id -- �øж�
		int		use_reroller = 1;
		int64_t	_my_summoner_id = 0;
	};
}
