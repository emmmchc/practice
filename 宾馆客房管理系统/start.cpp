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
		while (menu(), cout << "请输入准确数字进行相应操作:", !(cin >> choice))	//控制输入
		{
			cin.sync(); //清除缓存区        
			cin.clear();    //清除错误状态
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
					type_in_room();	//录入房间信息
					break;
				}
				break;
			case 2:
				flag = 1;
				while (flag)
				{
					system("cls");
					check_in();		//顾客入住登记
					Stop();
					break;
				}
				break;
			case 3:
				flag = 1;
				while (flag)
				{
					system("cls");
					check_out();		//客人退房结算
					Stop();
					break;
				}
				break;
			case 4:
				flag = 1;
				while (flag)
				{
					system("cls");
					browse();		//客房信息浏览
					Stop();
					break;
				}
				break;
			case 5:
				flag = 1;
				while (flag)
				{
					system("cls");
					query();//客房信息查询：查询空房间情况、按姓名或房间号查询
					Stop();
					break;
				}
				break;
			case 6:
				flag = 1;
				while (flag)
				{
					system("cls");
					room_edit();//客房信息的删除、修改功能
					Stop();
					break;
				}
				break;
			case 7:
				flag = 0;//退出系统
				break;
			}
		system("cls");
	}
	sqlite3_close(dbopen);
	system("pause");
	return 0;
}

