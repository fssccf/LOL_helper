#pragma once
#include	<windows.h>
#include    <string>
#include <codecvt>
#include <locale>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "shlobj.h" 
std::string to_string(long long num);

std::string get_commandline_exec(const char* cmd);


std::string wstring2string(std::wstring wstr);
std::wstring string2wstring(const std::string& str);
std::wstring StringToWString(const std::string& str);


std::string wstring_to_utf8(const std::wstring& wstr);

std::string timestamp2string(unsigned long long timestamp);


std::string GetProcessCommandLine(const std::string& cmdLine);
void CopyTextToClipboard(const std::wstring& text);

std::string	get_app_path();//����appdataĿ¼�� lol_helper·��,���������,�ʹ���
std::string get_app_path(std::string child_folder);	//��������������,�������child_folder��Ŀ¼,���������,�ʹ���

bool folderExists(const std::string& folderPath);