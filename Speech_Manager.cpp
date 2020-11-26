#include "Speech_Manager.h"

Speech_Manager::Speech_Manager()
{
	//����ʱ���캯����ʼ��
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
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void Speech_Manager::ExitSystem()
{
	cout << "�˳�����ӭ�´�ʹ�ã�" << endl;
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
		string speaker= "ѡ��";
		speaker += Id[i];

		Speaker sp;

		sp.m_Name = speaker;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;					//�����ÿ�
		}



		this->v1.push_back(i + 10001);			//�����һ�α�����ǩ�����ʮ����ѡ�ֵı��

		this->m_Speaker.insert(make_pair(i + 10001, sp));			//map�����д����Ӧ��ż�ѡ����Ϣ

	}


}

void Speech_Manager::StartSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	SpeechDraw();
	//2������
	SpeechContest();
	//3����ʾ�������
	ShowScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	SpeechDraw();
	//2������
	SpeechContest();
	//3����ʾ���ս��
	ShowScore();
	//4���������
	SaveScore();


	/*���ñ��������»���������ݣ���������޷���ʾ�������ݵ�bug  */
	this->InitSpeaker();
	this->CreateSpeaker();
	this->GetScoreHistory();	


	cout << "�������������" << endl;
	system("pause");
	system("cls");
}

void Speech_Manager::SpeechDraw()
{

	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	int num = 0;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			num++;
			if (num == 1)
				cout << "��һ�飺";

			if (num == 7)
				cout << "�ڶ��飺";

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
	cout << "------------- ��" << this->m_Index << "����ʽ������ʼ��------------- " << endl;

	multimap<double, int, greater<double>> gourpScore;			//��ʱ���������Խ������򣬱��ں���ȡǰ����

	int num=0;		//���ڼ�¼��������������һ��


	vector<int> v_Src;		//����ѡ������
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

		//ʮ����ί���
		deque<double> deq;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;	//�������60~100(С��)
		//cout << score << " ";
			deq.push_back(score);
		}
		//cout << endl;

		sort(deq.begin(), deq.end(), greater<double>());	//����,�Ӵ�С����

		deq.pop_back();		//ȥ����ͷ�
		deq.pop_front();	//ȥ����߷�

		double sum = accumulate(deq.begin(), deq.end(), 0.0f);		//�ܷ�
		double avg = sum / (double)deq.size();	//ƽ����

		//cout << "ƽ���֣� " << avg << "����: " << this->m_Speaker[*it].m_Name << endl;

		//��ƽ���ַ���map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;		//*it��ֵ����ѡ�ֱ�� Ҳ����map������keyֵ
		 
		gourpScore.insert(make_pair(avg, *it));		//key�ǵ÷֣�value��ѡ�ֱ��

		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << " С��������Σ�" << endl;

			for (multimap<double, int, greater<double>> ::iterator it = gourpScore.begin(); it != gourpScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name << "������ " << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			cout << endl;

			int count = 0;		//��¼ǰ��

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
	
	cout << "------------- ��" << this->m_Index << "�ֱ������  ------------- " << endl;
	system("pause");


}

void Speech_Manager::ShowScore()
{
	cout << "---------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_Speaker[*it].m_Name << " �÷֣� " << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->Show_Menu();
}

void Speech_Manager::SaveScore()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//�����ʽ���ļ���׷�ӷ�ʽд�ļ�, csv��ʽ�ļ����ü��±���excel���

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ","
			<< m_Speaker[*it].m_Name << "," << m_Speaker[*it].m_Score[1] << ",";
	}

	ofs << endl;

	ofs.close();
	cout << "�����¼�ɹ�:" << endl;

	this->file_emply = false;			//�ļ���־λ����
}

void Speech_Manager::GetScoreHistory()
{
	
	ifstream ifs;

	ifs.open("speech.csv", ios::in );	//���������󣬶��ļ�
	if (!ifs.is_open())
	{
		this->file_emply = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->file_emply = true;
		//cout << "�ļ�Ϊ�գ�" << endl;
		ifs.close();
		return;
	}


	this->file_emply = false;		//�ļ���Ϊ��

	ifs.putback(ch);		//ǰ������ļ��Ƿ�Ϊ��ʱ���ߵ��ַ��Ż���

	string data;
	int index = 0;		//Ĭ��0��쿪ʼ

	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;		//��Ų鵽��','��λ��
		int start = 0;		//���ҵ���ʼλ��

		vector<string> v;


		while (true)
		{
			pos = data.find(",",start); //��0��ʼ����','��λ��

			if (pos == -1)
			{
				//û�ҵ�
				break;
			}

			string temp = data.substr(start, pos - start);		//��ȡ�Ӵ�
			//cout << temp << endl;;

			v.push_back(temp);

			start = pos + 1;		//pos�����ŵ�λ�ã�+1�Ƕ���
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
		cout << "�ļ������ڣ������ļ�Ϊ��" << endl;
	}

	else
	{

		for (int i = 0; i < this->m_Score.size(); i++)
		{
			cout << "��" << i + 1 << "�� " << endl <<
				"�ھ���ţ�" << this->m_Score[i][0] << " ѡ�֣�" << this->m_Score[i][1] << " " << " �÷֣� " << this->m_Score[i][2] << endl <<
				"�Ǿ���ţ�" << this->m_Score[i][3] << " ѡ�֣�" << this->m_Score[i][4] << " " << " �÷֣� " << this->m_Score[i][5] << endl <<
				"������ţ�" << this->m_Score[i][6] << " ѡ�֣�" << this->m_Score[i][7] << " �÷֣� " << this->m_Score[i][8] << " " << endl;
		}
	}
	system("pause");
	system("cls");
}

void Speech_Manager::ClearScore()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{ 
		ofstream ofs("speech.csv", ios::trunc);				//��ģʽ ios::trunc ������ļ�������ɾ���ļ������´���
		ofs.close();

		this->InitSpeaker();				//���³�ʼ������
		
		this->CreateSpeaker();				//���´���ѡ��

		this->GetScoreHistory();			//���»�ȡ�����¼


		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}