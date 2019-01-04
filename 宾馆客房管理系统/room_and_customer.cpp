#include "room_and_customer.h"
#include "sqlite3.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//客房种类
string kind = "";

//客人预订需要的费用
int day_indeed = 0;

extern sqlite3 *dbopen;

//暂停函数
void Stop()
{
	getchar();
	cout << "按任意键继续";
	if (getchar())
		system("cls");
}

//菜单
void menu()//菜单
{
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "|                      虚拟宾馆客房管理系统                         |" << endl;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << " 1.客房信息录入            2.客人入住登记             3.客人退房结算" << endl;
	cout << " 4.客房信息浏览            5.客房信息查询             6.客房信息编辑" << endl;
	cout << " 7.退出系统 " << endl;
}

//退房结算
void check_out()
{
	string name, id;
	cout << "输入要退房的客人姓名和身份证号码:\n";
	cin >> name >> id;
	cout << "输入该客人实住天数 :\n";
	cin >> day_indeed;
	CheckOut(name, id);
}

//入住登记
void check_in()
{
	string	room_kind;
	int kind;
	cout << "请选择预定房间的种类:\n";
	cout << "1.单人间/天100元\n2.双人间/天200元\n3.三人间/天300元\n4.套房/天400元\n";
	cin >> kind;
	int *p = &kind;
	string strSql = "";
	strSql += "select * from room where kind = ";
	if (kind == 1)
		strSql += "'单人间';";
	else if (kind == 2)
		strSql += "'双人间';";
	else if (kind == 3)
		strSql += "'三人间';";
	else if (kind == 4)
		strSql += "'套房';";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), SearchRoom, p, 0);
}

//录入客房
void type_in_room()
{
	int	n = 0;
	string room_id;
	int kind;
	cout << "接下来开始录入客房信息！\n\n";
	while (1)
	{
		cout << "输入房间号(整数):";
		cin >> room_id;
		cout << "输入客房种类:(1代表单人间，2代表双人间，3代表三人间，4代表套房)";
		cin >> kind;
		bool check = AddRoom(room_id, kind);
		if (check)
			cout << "\n录入成功!是否继续？(y/n)";
		else
			cout << "\n客房号冲突,录入失败！是否继续？(y/n)";
		char ch;
		cin >> ch;
		while ((ch != 'Y') && (ch != 'y') && (ch != 'N') && (ch != 'n'))
		{
			cout << "输入错误,请重新输入!" << endl;
			cin.clear();
			cin.ignore();
			cin >> ch;
		}
		if ((ch == 'Y') || (ch == 'y'))
		{
			continue;
		}
		else if (ch == ('N' | 'n'))
			break;
	}
}

//客房编辑
void room_edit()
{
	int edit;
	cout << "1.客房信息删除" << endl;
	cout << "2.客房信息修改" << endl;
	cout << "请输入相应数字进行操作:";
	cin >> edit;
	cin.clear();
	cin.ignore();
	if (edit == 1)
	{
		int flag = 1;
		string room_id_delete;
		cout << "输入要删除的房间号";
		cin >> room_id_delete;
		cin.clear();
		cin.ignore();
		DeleteRoom(room_id_delete);
	}
	else if (edit == 2)
	{
		int flag = 1;
		string room_id_edit;
		string room_id;
		int kind;
		cout << "输入要修改的房间号:";
		cin >> room_id_edit;
		cin.clear();
		cin.ignore();
		cout << "输入新的房间号:";
		cin >> room_id;
		cout << "输入客房种类(1代表单人间，2代表双人间，3代表三人间，4代表套房):";
		cin >> kind;
		bool check = EditRoom(room_id, room_id_edit, kind, "是");
		if (check)
			cout << "\n操作完成!\n";
		else
			cout << "\n修改失败!\n";
	}
}

//浏览客房信息
void browse()
{
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "客房号\t\t客房类型\t客房价格(\\天)\t是否空房" << endl;
	char* cErrMsg;
	sqlite3_exec(dbopen, "select * from room;", AllRoom, 0, &cErrMsg);
	cout << "\n入住客房客人信息" << endl;
	sqlite3_exec(dbopen, "select * from room where is_empty = '否';", PrintInformation, 0, 0);
}

//信息查询
void query()
{
	int query;
	cout << "1.空房间查询" << endl;
	cout << "2.顾客信息查询" << endl;
	cout << "请输入准确数字进行相应操作:";
	cin >> query;
	cin.clear();
	cin.ignore();
	if (query == 1)
	{
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
		cout << "剩余空房间如下:" << endl;
		string strSql = "";
		strSql += "select * from room where is_empty = '是';";
		sqlite3_exec(dbopen, strSql.c_str(), EmptyRoom, 0, 0);
	}
	else if (query == 2)
	{
		system("cls");
		cout << "1.按姓名查询" << endl;
		cout << "2.按身份证查询" << endl;
		cout << "请输入准确数字进行相应操作:";
		int customer_choice;
		cin >> customer_choice;
		cin.clear();
		cin.ignore();
		if (customer_choice == 1)
		{
			int flag = 1;
			string name;
			cout << "请输入顾客的姓名:" << endl;
			cin >> name;
			cin.clear();
			cin.ignore();
			QueryInformation(name);
		}
		if (customer_choice == 2)
		{
			system("cls");
			int flag = 1;
			string id;
			cout << "请输入顾客的身份证:" << endl;
			cin >> id;
			cin.clear();
			cin.ignore();
			QueryInformation(id);
		}
	}
}

//添加客人信息
void AddCustomer(string room_id, string name, string id, int need_pay)
{
	string strSql = "";
	strSql += "insert OR FAIL into customer(room_id,name,id,need_pay)";
	strSql += "values('";
	strSql += room_id;
	strSql += "', '";
	strSql += name;
	strSql += "', '";
	strSql += id;
	strSql += "', ";

	stringstream tmp;
	tmp << need_pay;
	string need_pay1 = tmp.str();

	strSql += need_pay1;
	strSql += ");";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), 0, 0, 0);
}

//添加客房
bool AddRoom(string room_id, int kind)
{
	string strSql = "";
	strSql += "insert OR FAIL into room(room_id,kind,price,is_empty)";
	strSql += "values('";
	strSql += room_id;
	strSql += "',";
	if (kind == 1)
		strSql += "'单人间',100,'是'";
	else if (kind == 2)
		strSql += "'双人间',200,'是'";
	else if (kind == 3)
		strSql += "'三人间',300,'是'";
	else if (kind == 4)
		strSql += "'套房',400,'是'";
	strSql += ");";
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}

//更新客房信息
bool EditRoom(string new_room_id, string room_id, int kind, string is_empty)
{
	string strSql = "";
	strSql += "update OR FAIL room set ";
	strSql += "room_id = '";
	strSql += new_room_id;
	strSql += "',kind = ";
	if (kind == 1)
	{
		strSql += "'单人间',price = 100,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 2)
	{
		strSql += "'双人间',price = 200,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 3)
	{
		strSql += "'三人间',price = 300,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 4)
	{
		strSql += "'套房',price = 400,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	strSql += room_id;
	strSql += "';";
	//cout << strSql << endl;
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}

//删除客房
bool DeleteRoom(string room_id1)
{
	string strSql = "";
	strSql += "select ";
	strSql += room_id1;
	strSql += " from room;";
	//cout << strSql << endl;
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), DelRoom, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}

//查询指定名字或者身份证的客人
void  QueryInformation(string str)
{
	string strSql = "";
	strSql += "select * from customer where name='";
	strSql += str;
	strSql += "' or id='";
	strSql += str;
	strSql += "';";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), QICallBack, 0, 0);
}

//挑出指定名字和身份证的客人
void CheckOut(string name, string id)
{
	string strSql = "";
	strSql += "select * from customer where name='";
	strSql += name;
	strSql += "' and id='";
	strSql += id;
	strSql += "';";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), CheckOutCallBack, 0, 0);

}

//挑出指定客房id的客人信息并删除
bool DeleteCustomer(string room_id)
{
	string strSql = "";
	strSql += "select ";
	strSql += room_id;
	strSql += " from room;";
	//cout << strSql << endl;
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), DelCustomer, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}

//打印所有空房间
static int AllRoom(void *NotUsed, int column, char **pValue, char **pName)
{
	for (int i = 0; i < column; i++)
	{
		cout << pValue[i] << "\t\t";
	}
	cout << endl;
	return 0;
}

//删除指定客房id的房间
static int DelRoom(void *NotUsed, int column, char **pValue, char **pName)
{
	string room_id = pValue[0];
	string strSql = "";
	strSql += "delete from room where room_id = ";
	strSql += room_id;
	strSql += " ;";
	//cout << strSql << endl;
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), 0, 0, &cErrMsg);
	return 1;	//返回1代表调用一次
}

//打印所有客房信息
static int PrintInformation(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 0;
	cout << pValue[i] << "号客房:" << endl;
	string room_id = pValue[i];
	string strSql = "";
	strSql += "select * from customer where room_id = '";
	strSql += room_id;
	strSql += "';";
	//cout << strSql<< endl;
	sqlite3_exec(dbopen, strSql.c_str(), PrintCustomer, 0, 0);
	i = i + 3;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	return 0;
}

//打印客人信息
static int PrintCustomer(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 1;
	//cout<<column<<endl;
	cout << "客人:" << pValue[i] << endl;
	cout << "身份证:" << pValue[i + 1] << endl;
	cout << "预定费用:" << pValue[i + 2] << endl << endl;
	i = i + 4;
	return 1;
}

//打印空房间id
static int EmptyRoom(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 0;
	cout << pValue[i] << endl;
	i = i + 4;
	return 0;
}

//退房结算具体过程
static int CheckOutCallBack(void *NotUsed, int column, char **pValue, char **pName)
{

	string room_id1 = pValue[0];
	string strSql = "";
	strSql += "select kind from room where room_id='";
	strSql += room_id1;
	strSql += "';";
	sqlite3_exec(dbopen, strSql.c_str(), GetRoomKind, 0, 0);
	DeleteCustomer(room_id1);
	int kind1;
	if (kind == "单人间")
		kind1 = 1;
	else if (kind == "双人间")
		kind1 = 2;
	else if (kind == "三人间")
		kind1 = 3;
	else if (kind == "套房")
		kind1 = 4;
	EditRoom(room_id1, room_id1, kind1, "是");
	stringstream tmp;
	tmp << pValue[0];
	int room_id;
	tmp >> room_id;

	stringstream tmp1;
	tmp1 << pValue[3];
	int pay;
	tmp1 >> pay;

	int room_kind;
	if (kind == "单人间")
		room_kind = 1;
	else if (kind == "双人间")
		room_kind = 2;
	else if (kind == "三人间")
		room_kind = 3;
	else if (kind == "套房")
		room_kind = 4;
	cout << "客人的房间号是" << room_id << ":为"<< kind <<",每天" << room_kind * 100 << "元\n";
	cout << "该客人预付房费" << pay << "元\n实际消费" << day_indeed * room_kind * 100 << "元\n";
	int cost = pay - day_indeed * room_kind * 100;
	if (cost > 0)
		cout << "应退给该客人 " << cost << " 元\n";
	if (cost < 0)
		cout << "应补收该客人住房费 " << -cost << " 元\n";

	return 1;
}

//为全局变量kind(客房的种类)赋值
static int GetRoomKind(void *NotUsed, int column, char **pValue, char **pName)
{
	kind = pValue[0];
	return 1;
}

//删除指定客房id的客人信息
static int DelCustomer(void *NotUsed, int column, char **pValue, char **pName)
{
	string room_id = pValue[0];
	string strSql = "";
	strSql += "delete from customer where room_id = ";
	strSql += room_id;
	strSql += " ;";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), 0, 0, 0);
	return 1;	//返回1代表调用一次
}

//打印已入住房间客人的信息
static int QICallBack(void *NotUsed, int column, char **pValue, char **pName)
{
	cout << pValue[1] << "的住房信息如下:\n";
	cout << "房间号为:" << pValue[0] << endl;
	cout << "身份证号为:" << pValue[2] << endl;
	cout << "预付房费为:" << pValue[3] << endl;
	return 1;
}

//查找空房间并录入客人信息
static int SearchRoom(void *NotUsed, int column, char **pValue, char **pName)//
{
	int *kind = NULL;
	kind = (int *)NotUsed;
	int i = 0;
	if (pValue[i] && strcmp(pValue[i + 3], "是") == 0)
	{
		//cout << "pValue[]=" << pValue[i] << " " << pValue[i + 3] << endl;
		//system("pause");
		string room_id = pValue[i];
		EditRoom(room_id, room_id, *kind, "否");
		string name;
		string id;
		int day, need_pay;
		cout << "请输入客人姓名:\n";
		cin >> name;
		cout << "请输入客人身份证:\n";
		cin >> id;
		cout << "请输入住宿天数:\n";
		cin >> day;
		need_pay = day * (*kind) * 100;
		cout << "需要收取费用:" << need_pay << endl;
		AddCustomer(room_id, name, id, need_pay);
		cout << "登记成功~" << endl;
		return 1;
	}
	i = i + 4;
	return 0;
}