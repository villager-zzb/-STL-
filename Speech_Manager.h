#pragma once

/*实现功能：
- 提供菜单界面与用户交互
- 对演讲比赛流程进行控制
- 与文件的读写交互*/

#include <iostream>
#include <string>
#include "Speaker.h"
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>		//内建函数对象头文件
#include <numeric>		
#include <fstream>
#include <ctime>

using namespace std;

//管理类
class Speech_Manager
{
public:
	Speech_Manager();

	void InitSpeaker();			//初始化选手相关容器

	void Show_Menu();			//展示菜单界面

	void StartSpeech();			//开始比赛，比赛流程控制

	void SpeechDraw();			//抽签函数

	void SpeechContest();		//比赛进行函数

	void ShowScore();			//显示比赛结果

	void SaveScore();			//保存比赛结果到文件中

	void GetScoreHistory();		//获取文件中的记录

	void ShowScoreHistory();	//展示往届记录

	void ClearScore();			//清除记录

	void ExitSystem();			//退出系统

	void CreateSpeaker();
	
	~Speech_Manager();

public:
	vector <int> v1;			//第一轮的容器（12人）
	vector <int> v2;			//第二轮的容器（6人）
	vector <int> vVictory;			//比赛结束前三（3人）
	map <int, Speaker> m_Speaker;		//选手编号对应选手的容器

	bool file_emply;			//往届记录的文件是否为空标志

	map<int, vector<string>> m_Score;		//往届记录容器


	int m_Index;


};