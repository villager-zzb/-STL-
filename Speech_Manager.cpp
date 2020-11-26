#include "Speech_Manager.h"

Speech_Manager::Speech_Manager()
{
	//启动时构造函数初始化
	this->InitSpeaker();
	this->CreateSpeaker();
	this->GetScoreHistory();
}

Speech_Manager::~Speech_Manager()
{

}

void Speech_Manager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void Speech_Manager::ExitSystem()
{
	cout << "退出，欢迎下次使用：" << endl;
	system("pause");
	exit(0);
}

void Speech_Manager::InitSpeaker()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;

	this->m_Score.clear();		
}

void Speech_Manager::CreateSpeaker()
{
	string Id = "ABCDEFGHIJKL";

	for (int i = 0; i < 12; i++)
	{
		string speaker= "选手";
		speaker += Id[i];

		Speaker sp;

		sp.m_Name = speaker;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;					//分数置空
		}



		this->v1.push_back(i + 10001);			//存入第一次比赛抽签结果的十二名选手的编号

		this->m_Speaker.insert(make_pair(i + 10001, sp));			//map容器中存入对应编号即选手信息

	}


}

void Speech_Manager::StartSpeech()
{
	//第一轮比赛
	//1、抽签
	SpeechDraw();
	//2、比赛
	SpeechContest();
	//3、显示晋级结果
	ShowScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	SpeechDraw();
	//2、比赛
	SpeechContest();
	//3、显示最终结果
	ShowScore();
	//4、保存分数
	SaveScore();


	/*重置比赛，重新获得往届数据，避免出现无法显示本届数据的bug  */
	this->InitSpeaker();
	this->CreateSpeaker();
	this->GetScoreHistory();	


	cout << "本届比赛结束了" << endl;
	system("pause");
	system("cls");
}

void Speech_Manager::SpeechDraw()
{

	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	int num = 0;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			num++;
			if (num == 1)
				cout << "第一组：";

			if (num == 7)
				cout << "第二组：";

			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

void Speech_Manager::SpeechContest()
{
	cout << "------------- 第" << this->m_Index << "轮正式比赛开始：------------- " << endl;

	multimap<double, int, greater<double>> gourpScore;			//临时的容器，以降序排序，便于后面取前三名

	int num=0;		//用于记录参赛人数，六人一组


	vector<int> v_Src;		//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (vector<int> ::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//十个评委打分
		deque<double> deq;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;	//随机分数60~100(小数)
		//cout << score << " ";
			deq.push_back(score);
		}
		//cout << endl;

		sort(deq.begin(), deq.end(), greater<double>());	//排序,从大到小降序

		deq.pop_back();		//去除最低分
		deq.pop_front();	//去除最高分

		double sum = accumulate(deq.begin(), deq.end(), 0.0f);		//总分
		double avg = sum / (double)deq.size();	//平均分

		//cout << "平均分： " << avg << "姓名: " << this->m_Speaker[*it].m_Name << endl;

		//将平均分放入map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;		//*it的值就是选手编号 也就是map容器的key值
		 
		gourpScore.insert(make_pair(avg, *it));		//key是得分，value是选手编号

		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << " 小组比赛名次：" << endl;

			for (multimap<double, int, greater<double>> ::iterator it = gourpScore.begin(); it != gourpScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name << "分数： " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			cout << endl;

			int count = 0;		//记录前三

			for (multimap<double, int, greater<double>> ::iterator it = gourpScore.begin(); it != gourpScore.end() && count < 3; it++,count ++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);

				}
				else
				{
					vVictory.push_back((*it).second);
				}

			}


			gourpScore.clear();
		}

	}
	
	cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
	system("pause");


}

void Speech_Manager::ShowScore()
{
	cout << "---------第" << this->m_Index << "轮晋级选手信息如下：-----------" << endl;
	vector<int>v;

	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << " 姓名： " << m_Speaker[*it].m_Name << " 得分： " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();
}

void Speech_Manager::SaveScore()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//输出方式打开文件，追加方式写文件, csv格式文件可用记事本和excel表打开

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Name << "," << m_Speaker[*it].m_Score[1] << ",";
	}

	ofs << endl;

	ofs.close();
	cout << "保存记录成功:" << endl;

	this->file_emply = false;			//文件标志位更新
}

void Speech_Manager::GetScoreHistory()
{
	
	ifstream ifs;

	ifs.open("speech.csv", ios::in );	//输入流对象，读文件
	if (!ifs.is_open())
	{
		this->file_emply = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->file_emply = true;
		//cout << "文件为空！" << endl;
		ifs.close();
		return;
	}


	this->file_emply = false;		//文件不为空

	ifs.putback(ch);		//前面测试文件是否为空时读走的字符放回来

	string data;
	int index = 0;		//默认0界届开始

	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;		//存放查到的','的位置
		int start = 0;		//查找的起始位置

		vector<string> v;


		while (true)
		{
			pos = data.find(",",start); //从0开始查找','的位置

			if (pos == -1)
			{
				//没找到
				break;
			}

			string temp = data.substr(start, pos - start);		//截取子串
			//cout << temp << endl;;

			v.push_back(temp);

			start = pos + 1;		//pos即逗号的位置，+1是逗号
		}

		this->m_Score.insert(make_pair(index, v)); 

		index++;

	}
	ifs.close();


}

void Speech_Manager::ShowScoreHistory()
{
	if (this->file_emply)
	{
		cout << "文件不存在，或者文件为空" << endl;
	}

	else
	{

		for (int i = 0; i < this->m_Score.size(); i++)
		{
			cout << "第" << i + 1 << "届 " << endl <<
				"冠军编号：" << this->m_Score[i][0] << " 选手：" << this->m_Score[i][1] << " " << " 得分： " << this->m_Score[i][2] << endl <<
				"亚军编号：" << this->m_Score[i][3] << " 选手：" << this->m_Score[i][4] << " " << " 得分： " << this->m_Score[i][5] << endl <<
				"季军编号：" << this->m_Score[i][6] << " 选手：" << this->m_Score[i][7] << " 得分： " << this->m_Score[i][8] << " " << endl;
		}
	}
	system("pause");
	system("cls");
}

void Speech_Manager::ClearScore()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{ 
		ofstream ofs("speech.csv", ios::trunc);				//打开模式 ios::trunc 即如果文件存在则删除文件并重新创建
		ofs.close();

		this->InitSpeaker();				//重新初始化属性
		
		this->CreateSpeaker();				//重新创建选手

		this->GetScoreHistory();			//重新获取往届记录


		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}