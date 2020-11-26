#pragma once

/*ʵ�ֹ��ܣ�
- �ṩ�˵��������û�����
- ���ݽ��������̽��п���
- ���ļ��Ķ�д����*/

#include <iostream>
#include <string>
#include "Speaker.h"
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>		//�ڽ���������ͷ�ļ�
#include <numeric>		
#include <fstream>
#include <ctime>

using namespace std;

//������
class Speech_Manager
{
public:
	Speech_Manager();

	void InitSpeaker();			//��ʼ��ѡ���������

	void Show_Menu();			//չʾ�˵�����

	void StartSpeech();			//��ʼ�������������̿���

	void SpeechDraw();			//��ǩ����

	void SpeechContest();		//�������к���

	void ShowScore();			//��ʾ�������

	void SaveScore();			//�������������ļ���

	void GetScoreHistory();		//��ȡ�ļ��еļ�¼

	void ShowScoreHistory();	//չʾ�����¼

	void ClearScore();			//�����¼

	void ExitSystem();			//�˳�ϵͳ

	void CreateSpeaker();
	
	~Speech_Manager();

public:
	vector <int> v1;			//��һ�ֵ�������12�ˣ�
	vector <int> v2;			//�ڶ��ֵ�������6�ˣ�
	vector <int> vVictory;			//��������ǰ����3�ˣ�
	map <int, Speaker> m_Speaker;		//ѡ�ֱ�Ŷ�Ӧѡ�ֵ�����

	bool file_emply;			//�����¼���ļ��Ƿ�Ϊ�ձ�־

	map<int, vector<string>> m_Score;		//�����¼����


	int m_Index;


};