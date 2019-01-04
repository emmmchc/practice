#include "room_and_customer.h"
#include "sqlite3.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

//�ͷ�����
string kind = "";

//����Ԥ����Ҫ�ķ���
int day_indeed = 0;

extern sqlite3 *dbopen;

//��ͣ����
void Stop()
{
	getchar();
	cout << "�����������";
	if (getchar())
		system("cls");
}

//�˵�
void menu()//�˵�
{
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "|                      ������ݿͷ�����ϵͳ                         |" << endl;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << " 1.�ͷ���Ϣ¼��            2.������ס�Ǽ�             3.�����˷�����" << endl;
	cout << " 4.�ͷ���Ϣ���            5.�ͷ���Ϣ��ѯ             6.�ͷ���Ϣ�༭" << endl;
	cout << " 7.�˳�ϵͳ " << endl;
}

//�˷�����
void check_out()
{
	string name, id;
	cout << "����Ҫ�˷��Ŀ������������֤����:\n";
	cin >> name >> id;
	cout << "����ÿ���ʵס���� :\n";
	cin >> day_indeed;
	CheckOut(name, id);
}

//��ס�Ǽ�
void check_in()
{
	string	room_kind;
	int kind;
	cout << "��ѡ��Ԥ�����������:\n";
	cout << "1.���˼�/��100Ԫ\n2.˫�˼�/��200Ԫ\n3.���˼�/��300Ԫ\n4.�׷�/��400Ԫ\n";
	cin >> kind;
	int *p = &kind;
	string strSql = "";
	strSql += "select * from room where kind = ";
	if (kind == 1)
		strSql += "'���˼�';";
	else if (kind == 2)
		strSql += "'˫�˼�';";
	else if (kind == 3)
		strSql += "'���˼�';";
	else if (kind == 4)
		strSql += "'�׷�';";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), SearchRoom, p, 0);
}

//¼��ͷ�
void type_in_room()
{
	int	n = 0;
	string room_id;
	int kind;
	cout << "��������ʼ¼��ͷ���Ϣ��\n\n";
	while (1)
	{
		cout << "���뷿���(����):";
		cin >> room_id;
		cout << "����ͷ�����:(1�����˼䣬2����˫�˼䣬3�������˼䣬4�����׷�)";
		cin >> kind;
		bool check = AddRoom(room_id, kind);
		if (check)
			cout << "\n¼��ɹ�!�Ƿ������(y/n)";
		else
			cout << "\n�ͷ��ų�ͻ,¼��ʧ�ܣ��Ƿ������(y/n)";
		char ch;
		cin >> ch;
		while ((ch != 'Y') && (ch != 'y') && (ch != 'N') && (ch != 'n'))
		{
			cout << "�������,����������!" << endl;
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

//�ͷ��༭
void room_edit()
{
	int edit;
	cout << "1.�ͷ���Ϣɾ��" << endl;
	cout << "2.�ͷ���Ϣ�޸�" << endl;
	cout << "��������Ӧ���ֽ��в���:";
	cin >> edit;
	cin.clear();
	cin.ignore();
	if (edit == 1)
	{
		int flag = 1;
		string room_id_delete;
		cout << "����Ҫɾ���ķ����";
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
		cout << "����Ҫ�޸ĵķ����:";
		cin >> room_id_edit;
		cin.clear();
		cin.ignore();
		cout << "�����µķ����:";
		cin >> room_id;
		cout << "����ͷ�����(1�����˼䣬2����˫�˼䣬3�������˼䣬4�����׷�):";
		cin >> kind;
		bool check = EditRoom(room_id, room_id_edit, kind, "��");
		if (check)
			cout << "\n�������!\n";
		else
			cout << "\n�޸�ʧ��!\n";
	}
}

//����ͷ���Ϣ
void browse()
{
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	cout << "�ͷ���\t\t�ͷ�����\t�ͷ��۸�(\\��)\t�Ƿ�շ�" << endl;
	char* cErrMsg;
	sqlite3_exec(dbopen, "select * from room;", AllRoom, 0, &cErrMsg);
	cout << "\n��ס�ͷ�������Ϣ" << endl;
	sqlite3_exec(dbopen, "select * from room where is_empty = '��';", PrintInformation, 0, 0);
}

//��Ϣ��ѯ
void query()
{
	int query;
	cout << "1.�շ����ѯ" << endl;
	cout << "2.�˿���Ϣ��ѯ" << endl;
	cout << "������׼ȷ���ֽ�����Ӧ����:";
	cin >> query;
	cin.clear();
	cin.ignore();
	if (query == 1)
	{
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
		cout << "ʣ��շ�������:" << endl;
		string strSql = "";
		strSql += "select * from room where is_empty = '��';";
		sqlite3_exec(dbopen, strSql.c_str(), EmptyRoom, 0, 0);
	}
	else if (query == 2)
	{
		system("cls");
		cout << "1.��������ѯ" << endl;
		cout << "2.�����֤��ѯ" << endl;
		cout << "������׼ȷ���ֽ�����Ӧ����:";
		int customer_choice;
		cin >> customer_choice;
		cin.clear();
		cin.ignore();
		if (customer_choice == 1)
		{
			int flag = 1;
			string name;
			cout << "������˿͵�����:" << endl;
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
			cout << "������˿͵����֤:" << endl;
			cin >> id;
			cin.clear();
			cin.ignore();
			QueryInformation(id);
		}
	}
}

//��ӿ�����Ϣ
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

//��ӿͷ�
bool AddRoom(string room_id, int kind)
{
	string strSql = "";
	strSql += "insert OR FAIL into room(room_id,kind,price,is_empty)";
	strSql += "values('";
	strSql += room_id;
	strSql += "',";
	if (kind == 1)
		strSql += "'���˼�',100,'��'";
	else if (kind == 2)
		strSql += "'˫�˼�',200,'��'";
	else if (kind == 3)
		strSql += "'���˼�',300,'��'";
	else if (kind == 4)
		strSql += "'�׷�',400,'��'";
	strSql += ");";
	char* cErrMsg;
	int nRes = sqlite3_exec(dbopen, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}

//���¿ͷ���Ϣ
bool EditRoom(string new_room_id, string room_id, int kind, string is_empty)
{
	string strSql = "";
	strSql += "update OR FAIL room set ";
	strSql += "room_id = '";
	strSql += new_room_id;
	strSql += "',kind = ";
	if (kind == 1)
	{
		strSql += "'���˼�',price = 100,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 2)
	{
		strSql += "'˫�˼�',price = 200,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 3)
	{
		strSql += "'���˼�',price = 300,is_empty = '";
		strSql += is_empty;
		strSql += "' where room_id = '";
	}
	else if (kind == 4)
	{
		strSql += "'�׷�',price = 400,is_empty = '";
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

//ɾ���ͷ�
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

//��ѯָ�����ֻ������֤�Ŀ���
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

//����ָ�����ֺ����֤�Ŀ���
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

//����ָ���ͷ�id�Ŀ�����Ϣ��ɾ��
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

//��ӡ���пշ���
static int AllRoom(void *NotUsed, int column, char **pValue, char **pName)
{
	for (int i = 0; i < column; i++)
	{
		cout << pValue[i] << "\t\t";
	}
	cout << endl;
	return 0;
}

//ɾ��ָ���ͷ�id�ķ���
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
	return 1;	//����1�������һ��
}

//��ӡ���пͷ���Ϣ
static int PrintInformation(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 0;
	cout << pValue[i] << "�ſͷ�:" << endl;
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

//��ӡ������Ϣ
static int PrintCustomer(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 1;
	//cout<<column<<endl;
	cout << "����:" << pValue[i] << endl;
	cout << "���֤:" << pValue[i + 1] << endl;
	cout << "Ԥ������:" << pValue[i + 2] << endl << endl;
	i = i + 4;
	return 1;
}

//��ӡ�շ���id
static int EmptyRoom(void *NotUsed, int column, char **pValue, char **pName)
{
	int i = 0;
	cout << pValue[i] << endl;
	i = i + 4;
	return 0;
}

//�˷�����������
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
	if (kind == "���˼�")
		kind1 = 1;
	else if (kind == "˫�˼�")
		kind1 = 2;
	else if (kind == "���˼�")
		kind1 = 3;
	else if (kind == "�׷�")
		kind1 = 4;
	EditRoom(room_id1, room_id1, kind1, "��");
	stringstream tmp;
	tmp << pValue[0];
	int room_id;
	tmp >> room_id;

	stringstream tmp1;
	tmp1 << pValue[3];
	int pay;
	tmp1 >> pay;

	int room_kind;
	if (kind == "���˼�")
		room_kind = 1;
	else if (kind == "˫�˼�")
		room_kind = 2;
	else if (kind == "���˼�")
		room_kind = 3;
	else if (kind == "�׷�")
		room_kind = 4;
	cout << "���˵ķ������" << room_id << ":Ϊ"<< kind <<",ÿ��" << room_kind * 100 << "Ԫ\n";
	cout << "�ÿ���Ԥ������" << pay << "Ԫ\nʵ������" << day_indeed * room_kind * 100 << "Ԫ\n";
	int cost = pay - day_indeed * room_kind * 100;
	if (cost > 0)
		cout << "Ӧ�˸��ÿ��� " << cost << " Ԫ\n";
	if (cost < 0)
		cout << "Ӧ���ոÿ���ס���� " << -cost << " Ԫ\n";

	return 1;
}

//Ϊȫ�ֱ���kind(�ͷ�������)��ֵ
static int GetRoomKind(void *NotUsed, int column, char **pValue, char **pName)
{
	kind = pValue[0];
	return 1;
}

//ɾ��ָ���ͷ�id�Ŀ�����Ϣ
static int DelCustomer(void *NotUsed, int column, char **pValue, char **pName)
{
	string room_id = pValue[0];
	string strSql = "";
	strSql += "delete from customer where room_id = ";
	strSql += room_id;
	strSql += " ;";
	//cout << strSql << endl;
	sqlite3_exec(dbopen, strSql.c_str(), 0, 0, 0);
	return 1;	//����1�������һ��
}

//��ӡ����ס������˵���Ϣ
static int QICallBack(void *NotUsed, int column, char **pValue, char **pName)
{
	cout << pValue[1] << "��ס����Ϣ����:\n";
	cout << "�����Ϊ:" << pValue[0] << endl;
	cout << "���֤��Ϊ:" << pValue[2] << endl;
	cout << "Ԥ������Ϊ:" << pValue[3] << endl;
	return 1;
}

//���ҿշ��䲢¼�������Ϣ
static int SearchRoom(void *NotUsed, int column, char **pValue, char **pName)//
{
	int *kind = NULL;
	kind = (int *)NotUsed;
	int i = 0;
	if (pValue[i] && strcmp(pValue[i + 3], "��") == 0)
	{
		//cout << "pValue[]=" << pValue[i] << " " << pValue[i + 3] << endl;
		//system("pause");
		string room_id = pValue[i];
		EditRoom(room_id, room_id, *kind, "��");
		string name;
		string id;
		int day, need_pay;
		cout << "�������������:\n";
		cin >> name;
		cout << "������������֤:\n";
		cin >> id;
		cout << "������ס������:\n";
		cin >> day;
		need_pay = day * (*kind) * 100;
		cout << "��Ҫ��ȡ����:" << need_pay << endl;
		AddCustomer(room_id, name, id, need_pay);
		cout << "�Ǽǳɹ�~" << endl;
		return 1;
	}
	i = i + 4;
	return 0;
}