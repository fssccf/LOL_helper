#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include "VirtualTileBox.h"
#include	"lcu_riot/struct.h"
#include	"champ_ui.h"

class Provider : public VirtualTileInterface
{
public:
	Provider();
	~Provider();

	virtual ui::Control* CreateElement() override;

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(ui::Control *control, int index) override;

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount() override;

public:
	void SetDatas(std::vector<CHAMP_INFO> info);

private:
	std::vector<CHAMP_INFO> m_vTasks;
	nbase::NLock  lock_;
};

