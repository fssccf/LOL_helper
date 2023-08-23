#pragma	once

#include	<iostream>
#include    <map>
#include	"factory.h"


//������Ϸ�ĳ�������,����Դ


//mapid https://static.developer.riotgames.com/docs/lol/maps.json
//gamemode https://static.developer.riotgames.com/docs/lol/gameModes.json
//gametype https://static.developer.riotgames.com/docs/lol/gameTypes.json
static const std::map<std::string, std::string>   rank_class_dict = {
	{"RANKED_SOLO_5x5","����/˫��"},
	{"RANKED_FLEX_SR","������� 5v5"},
	{"RANKED_TFT","�ƶ�֮��"},
	{"RANKED_TFT_TURBO","�ƶ�֮�Ŀ�ģʽ"},
	{"RANKED_TFT_DOUBLE_UP","�ƶ�֮��˫����ս"}
}; //��λ�ȼ���ģʽ

static const std::map<std::string, std::string>   rank_tiers_dict = {
	{"CHALLENGER","��ǿ����"},
	{"GRANDMASTER","������ʦ"},
	{"MASTER","������ʦ"},
	{"IRON","���ͺ���"},
	{"DIAMOND","����ʯ"},
	{"EMERALD","�������"},
	{"PLATINUM","���󲬽�"},
	{"GOLD","��ҫ�ƽ�"},
	{"SILVER","��������"},
	{"BRONZE","Ӣ�»�ͭ"},
	{"UNRANKED","û�ж�λ"},

    {"Grey","��"},
    {"Green","��"},
    {"Blue","��"},
    {"Purple","��"},
    {"Hyper","��"}
};

static const std::map<std::string, std::string>   GAME_MODE = {
	{"CLASSIC","����ģʽ"},
	{"ARAM","���ش��Ҷ�"},
	{"CHERRY","���꾺����"},
	{"TUTORIAL_MODULE_1","���ֽ̳�1"},
	{"TUTORIAL_MODULE_2","���ֽ̳�2"},
	{"TUTORIAL_MODULE_3","���ֽ̳�3"},
	{"PRACTICETOOL","ѵ��ģʽ"}
};
static const std::map<std::string, std::string >GAME_TYPE = {
	{"MATCHED_GAME","ƥ��ģʽ"},
	{"CUSTOM_GAME","�Զ���"},
	{"TUTORIAL_GAME","��Ϸ�̳�"}
};


static const std::map<int, std::string> GAME_CLASS = {
    {0, "�Զ���"},
    {72, "��ѩ��1v1"},
    {73, "��ѩ��2v2"},
    {75, "˫������"},
    {76, "����ģʽ"},
    {78, "����ģʽ"},
    {83, "������ս����ģʽ"},
    {98, "˫������"},
    {100, "����ARAM"},
    {310, "������"},
    {313, "���н���"},
    {317, "����֧��"},
    {325, "ȫ���"},
    {400, "ѡ��"},
    {420, "��˫"},
    {430,"ƥ��"},
    {440, "���"},
    {450, "���Ҷ�"},
    {600, "��ɱ�̿�"},
    {610, "������ϵ"},
    {700, "�Ծ�"},
    {720, "ARAM�Ծ�"},
    {820, "�����˻�"},
    {830, "�����˻�"},
    {840, "�����˻�"},
    {850, "һ���˻�"},
    {900, "�Ҷ�ģʽ"},
    {910, "����"},
    {920, "����������"},
    {940, "����ս"},
    {950, "ĩ��ͶƱ"},
    {960, "ĩ��"},
    {980, "�ǹ��ػ���"},
    {990, "�ǹ��ػ���"},
    {1000, "PROJECT: Hunters"},
    {1010, "ѩ���Ҷ�"},
    {1020, "ȫԱӢ��"},
    {1030, "�µ�������"},
    {1040, "�µ����±�"},
    {1050, "�µ�����Ա"},
    {1060, "�µ�������"},
    {1070, "�µ���ǿϮ"},
    {1090, "�ƶ�ƥ��"},
    {1100, "�ƶ���λ"},
    {1110, "�ƶ���ѧ"},
    {1111, "�ƶ�����"},
    {1130,"�ƶ���"},
    {1160,"�ƶ�˫����ս"},
    {1300, "�漣ģʽ"},
    {1400, "�ռ�������"},
    {1700, "���꾺����"},
    {1900, "URF"},
    {2000, "��ѧ 1"},
    {2010, "��ѧ 2"},
    {2020, "��ѧ 3"},
};//����ȫͳ��,����ֻ����ʱ��Ϊ�ж���Ϸ���͵�ѡ��
//��Դ:https://github.com/RiotGames/developer-relations/issues/574

static Factory<std::string>	F_rank_class(rank_class_dict);
static Factory<std::string>	F_ClassicRank_tiers(rank_tiers_dict);
static Factory<std::string>	F_game_mode(GAME_MODE);
static Factory<std::string>	F_game_type(GAME_TYPE);
static Factory<int> F_game_class(GAME_CLASS);