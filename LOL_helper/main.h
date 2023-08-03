#pragma once
#include	<base/base.h>
#include	<duilib/UIlib.h>
#include	"MiscThread.h"


/** @class MainThread
* @brief ���̣߳�UI�̣߳��࣬�̳� nbase::FrameworkThread
* @copyright (c) 2015, NetEase Inc. All rights reserved
* @date 2015/1/1
*/
class MainThread : public nbase::FrameworkThread
{
public:
	MainThread() : nbase::FrameworkThread("MainThread") {}
	virtual ~MainThread() {}

private:
	/**
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;
	void	check_only();

private:
	std::unique_ptr<MiscThread>	misc_thread_;	// ר�Ŵ������µ��߳�
	std::unique_ptr<MiscThread>	misc_thread_loop;	// ר�Ŵ���ѭ�����µ��߳�
	std::unique_ptr<MiscThread>	network_thread_;	// ר�Ŵ���ѭ�����µ��߳�

};
