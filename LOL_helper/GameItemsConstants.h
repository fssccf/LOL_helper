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
	{"UNRANKED","û�ж�λ"}
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


static Factory<std::string>	F_rank_class(rank_class_dict);
static Factory<std::string>	F_rank_tiers(rank_tiers_dict);
static Factory<std::string>	F_game_mode(GAME_MODE);
static Factory<std::string>	F_game_type(GAME_TYPE);
