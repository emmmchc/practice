#ifndef ROOM_AND_CUSTOMER_H
#define ROOM_AND_CUSTOMER_H

#include "sqlite3.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//操作数据库的一些回调函数
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


void menu();//菜单
void Stop();//暂停
void type_in_room();//录入客房
void room_edit();//客房编辑
void check_out();//退房结算
void check_in();//入住登记
void browse();//浏览客房信息
void query();//信息查询

//以下是主功能函数的一些子函数
bool EditRoom(string new_room_id, string room_id, int kind, string is_empty);
bool DeleteRoom(string room_id);
bool DeleteCustomer(string room_id);
void CheckOut(string name, string id);
void QueryInformation(string str);
void AddCustomer(string room_id, string name, string id, int need_pay);
bool AddRoom(string room_id, int kind);
#endif