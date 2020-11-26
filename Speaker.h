#pragma once

#include <iostream>

#include <string>

using namespace std;

/*选手类，选手的姓名和分数*/


class Speaker
{

public:

	string m_Name;
	double m_Score[2];			//比赛有两轮，存两轮的比赛结果
};