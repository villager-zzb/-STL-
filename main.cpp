
/*����
* ѧУ����һ���ݽ�����������12���˲μӡ����������֣���һ��Ϊ��̭�����ڶ���Ϊ������
* ������ʽ�����������ÿ��6���ˣ�ѡ��ÿ��Ҫ������飬���б���
* ÿ��ѡ�ֶ��ж�Ӧ�ı�ţ��� 10001 ~ 10012 
* ��һ�ַ�Ϊ����С�飬ÿ��6���ˡ� ���尴��ѡ�ֱ�Ž��г�ǩ��˳���ݽ���
* ��С���ݽ������̭����������������ѡ�֣�ǰ����������������һ�ֵı�����
* �ڶ���Ϊ������ǰ����ʤ��
* ÿ�ֱ���������Ҫ**��ʾ����ѡ�ֵ���Ϣ***/

/* ��ʵ�ֹ��ܣ�
* ��ʼ�ݽ����������������������̣�ÿ�������׶���Ҫ���û�һ����ʾ���û���������������һ���׶�
* �鿴�����¼���鿴֮ǰ����ǰ���������ÿ�α��������¼���ļ��У��ļ���.csv��׺������
* ��ձ�����¼�����ļ����������
* �˳��������򣺿����˳���ǰ����*/


#include "Speech_Manager.h"

using namespace std;



int main()
{
	Speech_Manager m;

	//��������
	//for (map<int, Speaker> ::iterator it = m.m_Speaker.begin(); it != m.m_Speaker.end(); it++)
	//{
	//	cout << it->first << it->second.m_Name << it->second.m_Score[0] << endl;
	//}


	int Choice;

	while (true)
	{
		m.Show_Menu();

		srand((unsigned int)time(NULL));			//���������


		cout << "������ѡ��" << endl;

		cin >> Choice;

		switch (Choice)
		{
		case 1:			//��ʼ����
			m.StartSpeech();
			break;

		case 2:			//�鿴�����¼
			m.ShowScoreHistory();
			break;

		case 3:			//�������
			m.ClearScore();
			break;

		case 0:			//�˳�ϵͳ
			m.ExitSystem();
			break;
		default:
			cout << "�����������������룺" << endl; 
			system("pause");
			system("cls");
			break;
		}
	}

	

	system("pause");
	return 0;
}