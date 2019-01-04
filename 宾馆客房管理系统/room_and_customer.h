#ifndef ROOM_AND_CUSTOMER_H
#define ROOM_AND_CUSTOMER_H

#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//�������ݿ��һЩ�ص�����
static int QICallBack(void *NotUsed, int column, char **pValue, char **pName);
static int DelRoom(void *NotUsed, int column, char **pValue, char **pName);
static int AllRoom(void *NotUsed, int column, char **pValue, char **pName);
static int SearchRoom(void *NotUsed, int column, char **pValue, char **pName);
static int PrintCustomer(void *NotUsed, int column, char **pValue, char **pName);
static int PrintInformation(void *NotUsed, int column, char **pValue, char **pName);
static int EmptyRoom(void *NotUsed, int column, char **pValue, char **pName);
static int CheckOutCallBack(void *NotUsed, int column, char **pValue, char **pName);
static int GetRoomKind(void *NotUsed, int column, char **pValue, char **pName);
static int DelCustomer(void *NotUsed, int column, char **pValue, char **pName);


void menu();//�˵�
void Stop();//��ͣ
void type_in_room();//¼��ͷ�
void room_edit();//�ͷ��༭
void check_out();//�˷�����
void check_in();//��ס�Ǽ�
void browse();//����ͷ���Ϣ
void query();//��Ϣ��ѯ

//�����������ܺ�����һЩ�Ӻ���
bool EditRoom(string new_room_id, string room_id, int kind, string is_empty);
bool DeleteRoom(string room_id);
bool DeleteCustomer(string room_id);
void CheckOut(string name, string id);
void QueryInformation(string str);
void AddCustomer(string room_id, string name, string id, int need_pay);
bool AddRoom(string room_id, int kind);
#endif