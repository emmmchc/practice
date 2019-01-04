#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>
#include "room_and_customer.h"
using namespace std;
sqlite3 * dbopen = NULL;
int main()
{
	int nRes = sqlite3_open("manage.db", &dbopen);
	if (nRes != SQLITE_OK)
	{
		cout << "Open database fail: " << sqlite3_errmsg(dbopen);
		sqlite3_close(dbopen);
		return 0;
	}
	int choice;
	int flag = 1;
	while (flag)
	{
		while (menu(), cout << "������׼ȷ���ֽ�����Ӧ����:", !(cin >> choice))	//��������
		{
			cin.sync(); //���������        
			cin.clear();    //�������״̬
			while (cin.get() != '\n')
			{
				system("cls");
				continue;
			}
		}
		if (choice > 0 && choice < 8)
			switch (choice)
			{
			case 1:
				flag = 1;
				while (flag)
				{
					system("cls");
					type_in_room();	//¼�뷿����Ϣ
					break;
				}
				break;
			case 2:
				flag = 1;
				while (flag)
				{
					system("cls");
					check_in();		//�˿���ס�Ǽ�
					Stop();
					break;
				}
				break;
			case 3:
				flag = 1;
				while (flag)
				{
					system("cls");
					check_out();		//�����˷�����
					Stop();
					break;
				}
				break;
			case 4:
				flag = 1;
				while (flag)
				{
					system("cls");
					browse();		//�ͷ���Ϣ���
					Stop();
					break;
				}
				break;
			case 5:
				flag = 1;
				while (flag)
				{
					system("cls");
					query();//�ͷ���Ϣ��ѯ����ѯ�շ���������������򷿼�Ų�ѯ
					Stop();
					break;
				}
				break;
			case 6:
				flag = 1;
				while (flag)
				{
					system("cls");
					room_edit();//�ͷ���Ϣ��ɾ�����޸Ĺ���
					Stop();
					break;
				}
				break;
			case 7:
				flag = 0;//�˳�ϵͳ
				break;
			}
		system("cls");
	}
	sqlite3_close(dbopen);
	system("pause");
	return 0;
}

