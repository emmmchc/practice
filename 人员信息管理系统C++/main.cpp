#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class Node
{
public:
	int val;
    string name;
    int age;
    string ID;
    string sex;
    string depart;
    int year;
    int month;
    int day;
    Node *next;
    Node *pre;
    Node()
    {
        next = NULL;
        pre = NULL;
		val = 0;
    }
};

class List  //管理整个链表
{
public:
    List();
    ~List();
    Node *GetHead(Node *head); //返回头元素指针
    Node *GetTail(Node *head); //返回尾元素指针

	void RemoveAt(string ID,Node *head); //移除指定下标值的元素
    void RemoveHead(Node *head);  //移除第一个元素
    void RemoveTail(Node *head);  //移除最后一个元素
	void RemoveAll(Node *head); //移除所有元素

    void AddHead(Node *head); //在表头添加元素或者链表.函数重载
    void AddTail(Node *head); //在表尾添加元素或者链表.函数重载

    int GetNext(Node* cur,Node *head); //返回下一个元素的位置
    int GetPrev(Node* cur,Node *head); //返回前一个元素位置
    Node *Find(string ID,Node *head);//返回等于指定值的元素
    Node *FindIndex(int pos,Node *head);//返回等于指定下标的元素

    void SetID(string ID,Node *head); //设定指定ID的元素值
    void SetName(string ID,Node *head);//设定指定姓名的元素值

    void InsertBefore(int pos,Node *head);//在指定位置前插入元素
    void InsertAfter(int pos,Node *head);//在指定位置后插入元素

    void HeadInsert(Node *head);//头插法
    void TailInsert(Node *head);//尾插法

    int GetCount(Node *head);//返回链表长度
    bool IsEmpty(Node *head);//判断链表是否为空
    void Show(Node *head);//遍历链表并输出
    void Stop();//按任意键返回菜单
    void ShowOne(Node *p);//显示一条记录
    void Save(Node *head);//保存数据到本地D盘根目录

    void AddTail(Node *p,Node *q);//函数重载，添加尾链表（实际可以通过改变参数位置进行链表的头合并或者尾合并）

    Node *stu;
	Node *tea;
};

class Set:public List
{
public:

    static bool SetInsert(Node *h, int n);
	static bool SetFind(Node *h, int a);
    static void SetPrint(Node *h);
    Node *And(Node *h1, Node *h2);


};

class _list
{
public:
	_list *head;
	_list *tail;
	_list *next;
	int num;
	_list()
	{
		head = tail = next = NULL;
	}
	virtual void store(int i) = 0;
	virtual int retrieve() = 0;
};

class Queue:public _list
{
public:
	void store(int i);
	int retrieve();
};

class Stack:public _list
{
public:
	void store(int i);
	int retrieve();
};

void Queue::store(int i)
{
	_list *item;
	item = new Queue;
	if(!item)
	{
		cout<<"分配失败"<<endl;
		exit(1);
	}
	item->num = i;
	if(tail)
		tail->next=item;
	tail = item;
	item->next = NULL;
	if(!head)
		head = tail;
}

int Queue::retrieve()
{
	int i;
	_list *p;
	if(!head)
	{
		cout<<"空"<<endl;
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

void Stack::store(int i)
{
	_list *item;
	item = new Stack;
	if(!item)
	{
		cout<<"分配失败"<<endl;
		exit(1);
	}
	item->num = i;
	if(head)
		item->next = head;
	head = item;
	if(!tail)
		tail = head;
}

int Stack::retrieve()
{
	int i;
	_list *p;
	if(!head)
	{
		cout<<"空"<<endl;
		return 0;
	}
	i = head->num;
	p = head;
	head = head->next;
	delete p;
	return i;
}

bool Set::SetInsert(Node *h, int n)
{
	Node *p = h->next;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"内存分配失败"<<endl;
        return false;
    }
	s->val = n;
    if (p != NULL)
    {
        while(p->next)
            p=p->next;
        p->next = s;
        s->pre = p;
        s->next = NULL;
    }
    else
    {
        h->next = s;
        s->next = NULL;
        s->pre = h;
    }
	return true;
}

bool Set::SetFind(Node *h, int a)
{
    while (h->next != NULL)
    {
        if (h->next->val == a)
            return true;
        h = h->next;
    }
    return false;
}

void Set::SetPrint(Node *h)
{
    while (h->next != NULL)
    {
        cout << h->next->val << ' ';
        h= h->next;
    }
    cout << endl;
}

Node *Set::And(Node *h1, Node *h2)
{
    Node *h3 = new Node;
    if(h3==NULL)
    {
        cout<<"内存分配失败"<<endl;
        return h3;
    }
    h3->next = NULL;
    while (h1->next != NULL)
    {
        if (SetFind(h2, h1->next->val))
            SetInsert(h3, h1->next->val);
        h1 = h1->next;
    }
    return h3;
}

List::List() {
	stu = new Node;
	if(stu==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
	stu->val=0;
	stu->name="";
	stu->age=0;
	stu->ID="";
	stu->sex="";
	stu->depart="";
	stu->year=0;
	stu->month=0;
	stu->age=0;
	stu->next = NULL;
	stu->pre = NULL;
	tea = new Node;
	if(tea==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
	tea->val=0;
	tea->name="";
	tea->age=0;
	tea->ID="";
	tea->sex="";
	tea->depart="";
	tea->year=0;
	tea->month=0;
	tea->age=0;
	tea->next = NULL;
	tea->pre = NULL;
}

List::~List()
{
	Node* p = stu;
	while(p!=NULL)
	{
		p=stu;
		stu=stu->next;
	    delete p;
	}
	stu=NULL;

	Node* q = tea;
	while(q!=NULL)
	{
		q=tea;
		tea=tea->next;
	    delete q;
	}
	tea=NULL;
}

void List::HeadInsert(Node *head)//从头部添加记录
{
    Node *p = head->next;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;
    cout<<"请输入姓名:";
    cin>>name1;
    cout<<"请输入年龄:";
    cin>>age1;
    if(head==tea)
        cout<<"请输入工号:";
    else
        cout<<"请输入学号:";
    cin>>ID1;
    cout<<"请输入性别(男/女):";
    cin>>sex1;
    if(head==tea)
        cout<<"请输入所属学院:";
    else
        cout<<"请输入院系:";
    cin>>depart1;
    cout<<"请输入出生年月(yyyy mm dd):";
    cin>>year1>>month1>>day1;
    s->name = name1;
    s->age = age1;
    s->ID = ID1;
    s->sex = sex1;
    s->depart = depart1;
    s->year = year1;
    s->month = month1;
    s->day = day1;
    if (p != NULL)
    {
        s->pre = p->pre;
        p->pre->next = s;
        s->next = p;        // 将新结点插入head后
    }
    else
    {
        head->next = s;
        s->next = NULL;
        s->pre = head;
    }
    char ch;
    cout<<"\n操作完成,是否再次执行该操作?(Y/N):";
    cin>>ch;
    while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
    {
        cout<<"输入错误,请重新输入!"<<endl;
        cout<<"是否再次执行该操作?(Y/N):";
        cin.clear();
        cin.sync();
        cin>>ch;
    }
    if((ch=='Y')|(ch=='y'))
    {
        HeadInsert(head);
    }
    else if(ch==('N'|'n'))
        system("cls");
}

void List::TailInsert(Node *head)//从尾部添加记录
{
    Node *p = head->next;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;
    cout<<"请输入姓名:";
    cin>>name1;
    cout<<"请输入年龄:";
    cin>>age1;
    if(head==tea)
        cout<<"请输入工号:";
    else
        cout<<"请输入学号:";
    cin>>ID1;
    cout<<"请输入性别(男/女):";
    cin>>sex1;
    if(head==tea)
        cout<<"请输入所属学院:";
    else
        cout<<"请输入院系:";
    cin>>depart1;
    cout<<"请输入出生年月(yyyy mm dd):";
    cin>>year1>>month1>>day1;
    s->name = name1;
    s->age = age1;
    s->ID = ID1;
    s->sex = sex1;
    s->depart = depart1;
    s->year = year1;
    s->month = month1;
    s->day = day1;
    if (p != NULL)
    {
        while(p->next)
            p=p->next;
        p->next = s;
        s->pre = p;
        s->next = NULL;
    }
    else
    {
        head->next = s;
        s->next = NULL;
        s->pre = head;
    }

    char ch;
    cout<<"\n操作完成,是否再次执行该操作?(Y/N):";
    cin>>ch;
    while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
    {
        cout<<"输入错误,请重新输入!"<<endl;
        cout<<"是否再次执行该操作?(Y/N):";
        cin.clear();
        cin.sync();
        cin>>ch;
    }
    if((ch=='Y')|(ch=='y'))
    {
        TailInsert(head);
    }
    else if(ch==('N'|'n'))
        system("cls");
}

void List::SetID(string ID,Node *head)//通过ID查找指定记录并修改
{
    int i = 0;
    Node *p = head;
    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;
    if (IsEmpty(head))
        cout << "记录为空" <<endl;
    else
    {
        while (p->ID!=ID)
        {
            p = p->next;
            i++;
            if(i>GetCount(head))
                {
                    cout << "无该记录" <<endl;
                    return;
                }
        }
        if(i == GetCount(head))
        {
            cout<<"您将修改如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否修改？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"请输入姓名:";
                cin>>name1;
                cout<<"请输入年龄:";
                cin>>age1;
                if(head==tea)
                    cout<<"请输入工号:";
                else
                    cout<<"请输入学号:";
                cin>>ID1;
                cout<<"请输入性别(男/女):";
                cin>>sex1;
                cout<<"请输入院系:";
                cin>>depart1;
                cout<<"请输入出生年月(yyyy mm dd):";
                cin>>year1>>month1>>day1;
                p->name = name1;
                p->age = age1;
                p->ID = ID1;
                p->sex = sex1;
                p->depart = depart1;
                p->year = year1;
                p->month = month1;
                p->day = day1;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
        else
        {
            cout<<"您将修改如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否修改？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"请输入姓名:";
                cin>>name1;
                cout<<"请输入年龄:";
                cin>>age1;
                if(head==tea)
                    cout<<"请输入工号:";
                else
                    cout<<"请输入学号:";
                cin>>ID1;
                cout<<"请输入性别(男/女):";
                cin>>sex1;
                cout<<"请输入院系:";
                cin>>depart1;
                cout<<"请输入出生年月(yyyy mm dd):";
                cin>>year1>>month1>>day1;
                p->name = name1;
                p->age = age1;
                p->ID = ID1;
                p->sex = sex1;
                p->depart = depart1;
                p->year = year1;
                p->month = month1;
                p->day = day1;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
     }
}

void List::SetName(string name,Node *head)//通过姓名查找指定记录并修改
{
    int i = 0;
    Node *p = head;
    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;
    if (IsEmpty(head))
        cout << "记录为空" <<endl;
    else
    {
        while (p->name!=name)
        {
            p = p->next;
            i++;
            if(i>GetCount(head))
                {
                    cout << "无该记录" <<endl;
                    return;
                }
        }
        if(i == GetCount(head))
        {
            cout<<"您将修改如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否修改？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"请输入姓名:";
                cin>>name1;
                cout<<"请输入年龄:";
                cin>>age1;
                if(head==tea)
                    cout<<"请输入工号:";
                else
                    cout<<"请输入学号:";
                cin>>ID1;
                cout<<"请输入性别(男/女):";
                cin>>sex1;
                cout<<"请输入院系:";
                cin>>depart1;
                cout<<"请输入出生年月(yyyy mm dd):";
                cin>>year1>>month1>>day1;
                p->name = name1;
                p->age = age1;
                p->ID = ID1;
                p->sex = sex1;
                p->depart = depart1;
                p->year = year1;
                p->month = month1;
                p->day = day1;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
        else
        {
            cout<<"您将修改如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否修改？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"请输入姓名:";
                cin>>name1;
                cout<<"请输入年龄:";
                cin>>age1;
                if(head==tea)
                    cout<<"请输入工号:";
                else
                    cout<<"请输入学号:";
                cin>>ID1;
                cout<<"请输入性别(男/女):";
                cin>>sex1;
                cout<<"请输入院系:";
                cin>>depart1;
                cout<<"请输入出生年月(yyyy mm dd):";
                cin>>year1>>month1>>day1;
                p->name = name1;
                p->age = age1;
                p->ID = ID1;
                p->sex = sex1;
                p->depart = depart1;
                p->year = year1;
                p->month = month1;
                p->day = day1;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
     }
}

void List::RemoveAt(string ID,Node *head)//删除指定ID的记录
{
    int i = 0;
    Node *p = head;
    if (IsEmpty(head))
    {
        cout<<"无记录"<<endl;
    }
    else
    {
       while (p->ID!=ID)
        {
            p = p->next;
            i++;
            if (i>GetCount(head))
                {
                    cout<<"没有该条记录！"<<endl;
                    return;
                }
        }
        if (i == GetCount(head))
        {
            cout<<"您将删除如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否删除？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                p->pre->next = NULL;
                delete p;
				cout<<"删除成功！"<<endl;
            }
            else if(ch==('N'|'n'))
                system("cls");

        }
        else
        {
            cout<<"您将删除如下数据:"<<endl;
            ShowOne(p);
            cout<<"\n是否删除？(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"输入错误,请重新输入!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                p->pre->next = p->next;
                p->next->pre = p->pre;
                delete p;
				cout<<"删除成功！"<<endl;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
    }
}

void List::RemoveHead(Node *head)//删除头记录
{
    Node *p = head->next;
    if(!p)
        ;
    else if(p->next==NULL)
        head->next = NULL;
    else
    {
        head->next = p->next;
        p->next->pre = head;
    }
}

void List::RemoveTail(Node *head)//删除尾记录
{
    Node *p = head->next;
    if(!p)
        ;
    else if(p->next==NULL)
        p->pre->next = NULL;
    else
    {
        while(p->next)
            p = p->next;
        p->pre->next = NULL;
    }
}

void List::RemoveAll(Node *head)//删除全部记录
{
    Node *p1,*p2;
    p1 = head->next;
    p2 = head->next;
    head->next = NULL;
    while(p1)
    {
        p1 = p1->next;
        delete p2;
        p2 = p1;
    }
}

void List::InsertAfter(int pos,Node *head)//在当前节点后面插入数据
{
    Node *p;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
    p = head;
    int i = 0;

    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;

    if (pos<1 || pos>GetCount(head) + 1)
    {
        cout<<"插入位置错误!"<<endl;
    }
    else
    {
        while (i < pos)
        {
            p = p->next;
            i++;
        }
        if (i == GetCount(head))      //如果在最后一个元素后面插入data
        {
            TailInsert(head);
        }
        else
        {
            s = new Node;
            if(s==NULL)
            {
                cout<<"内存分配失败"<<endl;
                exit(1);
            }
            cout<<"请输入姓名:";
            cin>>name1;
            cout<<"请输入年龄:";
            cin>>age1;
            if(head==tea)
                cout<<"请输入工号:";
            else
                cout<<"请输入学号:";
            cin>>ID1;
            cout<<"请输入性别(男/女):";
            cin>>sex1;
            if(head==tea)
                cout<<"请输入所属学院:";
            else
                cout<<"请输入院系:";
            cin>>depart1;
            cout<<"请输入出生年月(yyyy mm dd):";
            cin>>year1>>month1>>day1;
            s->name = name1;
            s->age = age1;
            s->ID = ID1;
            s->sex = sex1;
            s->depart = depart1;
            s->year = year1;
            s->month = month1;
            s->day = day1;
            s->next = p->next;
            p->next->pre = s;
            p->next = s;
            s->pre = p;
        }
    }
    cout<<"\n操作完成"<<endl;
    Stop();
}

void List::InsertBefore(int pos,Node *head)//在当前节点前面插入数据
{
    Node *p;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"内存分配失败"<<endl;
        exit(1);
    }
    p = head;
    string name1;
    int age1;
    string ID1;
    string sex1;
    string depart1;
    int year1;
    int month1;
    int day1;
    int i = 0;
    if (pos<1 || pos>GetCount(head) + 1)
    {
        cout<<"插入位置错误!"<<endl;
    }
    else
    {
        while(i < pos)
        {
            p = p->next;
            i++;
        }
        if (i == 1)      // 如果在第一个元素前面插入data
        {
            HeadInsert(p);
        }
        else
        {
            s = new Node;
            if(s==NULL)
            {
                cout<<"内存分配失败"<<endl;
                exit(1);
            }
            cout<<"请输入姓名:";
            cin>>name1;
            cout<<"请输入年龄:";
            cin>>age1;
            if(head==tea)
            cout<<"请输入工号:";
            else
                cout<<"请输入学号:";
            cin>>ID1;
            cout<<"请输入性别(男/女):";
            cin>>sex1;
            if(head==tea)
                cout<<"请输入所属学院:";
            else
                cout<<"请输入院系:";
            cin>>depart1;
            cout<<"请输入出生年月(yyyy mm dd):";
            cin>>year1>>month1>>day1;
            s->name = name1;
            s->age = age1;
            s->ID = ID1;
            s->sex = sex1;
            s->depart = depart1;
            s->year = year1;
            s->month = month1;
            s->day = day1;
            s->pre = p->pre;
            s->next = p;
            p->pre->next = s;
            p->pre = s;
        }
    }
    cout<<"\n操作完成"<<endl;
    Stop();
}

Node *List::FindIndex(int pos,Node *head)//返回指定位置的记录
{
    Node *p = head->next;
    while (pos-1)
    {
        if(p==NULL)
        {
            cout<<"无查询结果"<<endl;
            return NULL;
        }
        p = p->next;
        pos--;
    }
    return p;
}

Node *List::Find(string ID,Node *head)//按学号、工号查找
{
    Node *p = head->next;
    while (p)
    {
        if(p->ID == ID)
            return p;
        p = p->next;
    }
    cout<<"无查询结果"<<endl;
    return NULL;
}

int List::GetNext(Node* cur,Node *head)//返回后一条记录的位置
{
    int key=1;
    Node *p = cur;
    if(p->next==NULL)
        key = GetCount(head)+1;
    else
        while(p->next)
        {
            key++;
            p = p->next;
        }
    key = GetCount(head)-key+2;
    return key;
}

int List::GetPrev(Node* cur,Node *head)//返回前一条记录的位置
{
    int key=1;
    Node *p = cur;
    if(p->next==NULL)
        key = GetCount(head)-1;
    else
    {
        while(p->next)
        {
            key++;
            p = p->next;
        }
		 key = GetCount(head)-key;
    }
    return key;
}

Node *List::GetHead(Node *head)//返回头元素指针
{
    Node *p = head->next;
    return p;
}

Node *List::GetTail(Node *head)//返回尾元素指针
{
    Node *p = head->next;
    if(p==NULL)
        return NULL;
    while(p->next)
        p = p->next;
    return p;
}

void List::ShowOne(Node *p)//打印一条记录
{
    cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
    cout<<"姓名:"<<p->name<<endl;
    cout<<"年龄:"<<p->age<<endl;
    cout<<"学号:"<<p->ID<<endl;
    cout<<"性别:"<<p->sex<<endl;
    cout<<"院系:"<<p->depart<<endl;
    cout<<"出生年月:"<<p->year<<"年"<<p->month<<"月"<<p->day<<"日"<<endl;
}

void List::Show(Node *head)//打印全部记录
{
    Node *p = head->next;
	if(head==stu && (GetCount(head)==GetCount(stu)))
		cout<<"当前总共有"<<GetCount(head)<<"条学生记录"<<endl<<endl;
	else if(head==tea && (GetCount(head)==GetCount(tea)))
		cout<<"当前总共有"<<GetCount(head)<<"条教职工记录"<<endl<<endl;
	else
		cout<<"当前总共有"<<GetCount(head)<<"条记录"<<endl<<endl;
	while(p!=NULL)
    {
        cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
		cout<<"姓名:"<<p->name<<endl;
		cout<<"年龄:"<<p->age<<endl;
		cout<<"学号:"<<p->ID<<endl;
		cout<<"性别:"<<p->sex<<endl;
		cout<<"院系:"<<p->depart<<endl;
		cout<<"出生年月:"<<p->year<<"年"<<p->month<<"月"<<p->day<<"日"<<endl;
		p = p->next;
	}
	cout << endl;
}

void List::Stop()//返回菜单
{
    getchar();
    cout<<"按任意键继续";
    if(getchar())
        system("cls");
}

int List::GetCount(Node *head)//链表长度
{
    int count = 0;
    Node *Tmp = head->next;
    while(Tmp != NULL)
    {
        count++;
        Tmp = Tmp->next;
    }
    return count;
}

bool List::IsEmpty(Node *head)//链表是否为空
{
    if(head->next==NULL)
        return true;
    else
        return false;
}

void List::Save(Node *head)//保存数据到本地
{
    Node *p = head->next;
    if(head==stu)
    {
        ofstream fStudent("D://学生信息.txt",ios::out);
        fStudent<<"姓名\t\t年龄\t学号\t\t性别\t院系\t\t出生年月"<<endl;
        while(p)
        {
            fStudent<<p->name<<"\t\t"<<p->age<<"\t"<<p->ID<<"\t\t"<<p->sex<<"\t"<<p->depart<<"\t\t"<<p->year<<"年"<<p->month<<"月"<<p->day<<"日"<<endl;
            p = p->next;
        }
        fStudent.close();
    }
    else
    {
        ofstream fTeacher("D://教职工信息.txt",ios::out);
        fTeacher<<"姓名\t\t年龄\t工号\t\t性别\t所属学院\t\t出生年月"<<endl;
        while(p)
        {
            fTeacher<<p->name<<"\t\t"<<p->age<<"\t"<<p->ID<<"\t\t"<<p->sex<<"\t"<<p->depart<<"\t\t"<<p->year<<"年"<<p->month<<"月"<<p->day<<"日"<<endl;
            p = p->next;
        }
        fTeacher.close();
    }
    cout<<"保存成功!"<<endl;
    Stop();
}

void List::AddTail(Node *p,Node *q)//函数重载，添加尾链表（实际可以通过改变参数位置进行链表的头合并或者尾合并）
{
	Node *tail;
	Node *head;
	tail = GetTail(p);
	head = GetHead(q);
	if(!tail)
    {
        p->next = head;
        head->pre = p;
    }
    else
    {
        tail->next = head;
        head->pre = tail;
    }
}

Node* operator+(Node &k1,Node &k2);//并集
Node* operator-(Node &k1,Node &k2);//差集

void menu()//功能菜单
{
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "|                      人员信息管理                         |" << endl;
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << " 1.学生登记                2.学生编辑              3.学生删除" << endl;
    cout << " 4.学生插入                5.学生遍历              6.学生查找" << endl;
    cout << " 7.学生保存                                                  " <<endl;
	cout << " 8.教师登记                9.教师编辑             10.教师删除" << endl;
    cout << "11.教师插入               12.教师遍历             13.教师查找" << endl;
    cout << "14.教师保存                                                  " << endl;
	cout << "15.集合                   16.队列                 17.栈      " << endl;
	cout << "18.链表合并               19.退出系统                        " << endl;
}

int main()
{
    Set S;
    List L;
    int num = 0;
	int flag=1;
    while(1)
    {
        menu();
        cout << "请输入准确数字进行相应操作:";
        cin>>num;
        if(num>0 && num<23)
            switch(num)
            {
            case 1:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					cout<<"1.头插法"<<endl;
					cout<<"2.尾插法"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:L.HeadInsert(L.stu);break;
						case 2:L.TailInsert(L.stu);break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
            case 2:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					string name;
					cout<<"1.按学号进行搜索修改"<<endl;
					cout<<"2.按姓名进行搜索修改"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"输入学号:"; cin>>ID; L.SetID(ID,L.stu); L.Stop();break;
						case 2:
						cout<<"输入姓名:";  cin>>name; L.SetName(name,L.stu); L.Stop();break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
            case 3:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					cout<<"1.删除指定记录"<<endl;
					cout<<"2.删除第一个记录"<<endl;
					cout<<"3.删除最后一个记录"<<endl;
					cout<<"4.删除全部记录"<<endl;
					cout<<"5.返回上一级"<<endl;
					cout <<"请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<6)
						switch(num)
						{
						case 1:cout<<"请输入学号:"; cin>>ID; L.RemoveAt(ID,L.stu);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.stu)<<"条学生记录"<<endl;L.Stop();break;
						case 2:L.RemoveHead(L.stu);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.stu)<<"条学生记录"<<endl;L.Stop();break;
						case 3:L.RemoveTail(L.stu);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.stu)<<"条学生记录"<<endl;L.Stop();break;
						case 4:L.RemoveAll(L.stu);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.stu)<<"条学生记录"<<endl;L.Stop();break;
						case 5:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 4:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					int pos;
					cout<<"提醒:当前共有"<<L.GetCount(L.stu)<<"条记录!"<<endl;
					cout<<"输入需要插入的位置(整数):";
					cin>>pos;
					if(pos<=0||pos>L.GetCount(L.stu))
					{
						cout<<"输入错误!"<<endl;
						L.Stop();
					 }
					else
					{
						Node *p;
						p = L.FindIndex(pos,L.stu);
						L.ShowOne(p);
						cout<<"\n1.向前插入"<<endl;
						cout<<"2.向后插入"<<endl;
						cout<<"3.返回"<<endl;
						while(flag)
						{
							cout <<"请输入对应数字进行相应操作:";
							cin>>num;
							switch(num)
							{
                            case 1:
                            L.InsertBefore(pos,L.stu); flag=0; L.Stop();break;
                            case 2:
                            L.InsertAfter(pos,L.stu); flag=0; L.Stop();break;
                            case 3:
                            system("cls"); flag=0; break;
							}
							if(flag)
								cin>>num;
						}
					  }
					flag = 0;
				}
				break;
                }
			case 5:
                {
					system("cls");L.Show(L.stu);L.Stop(); break;
                }
			case 6:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					int pos;
					Node *p;
					cout<<"1.按学号查找"<<endl;
					cout<<"2.按位置查找"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"输入学号:"; cin>>ID;
						p=L.Find(ID,L.stu);
						if(p)
						{
							L.ShowOne(p);
							if(p==L.GetHead(L.stu) && p==L.GetTail(L.stu))
							{
								cout<<"\n前一条记录位置:无"<<endl;
								cout<<"后一条记录位置:无"<<endl<<endl;
							}
							else if(p==L.GetHead(L.stu))
							{
								cout<<"\n前一条记录位置:无"<<endl;
								cout<<"后一条记录位置:"<<L.GetNext(p,L.stu)<<endl<<endl;
							}
							else if(p==L.GetTail(L.stu))
							{
								cout<<"\n前一条记录位置:"<<L.GetPrev(p,L.stu)<<endl;
								cout<<"后一条记录位置:无"<<endl<<endl;
							}
							else
							{
								cout<<"\n前一条记录位置:"<<L.GetPrev(p,L.stu)<<endl;
								cout<<"后一条记录位置:"<<L.GetNext(p,L.stu)<<endl<<endl;
							}
						}
						L.Stop();break;
						case 2:
						cout<<"输入位置:"; Node *p; cin>>pos;
						if(pos<=0||pos>L.GetCount(L.stu))
							cout<<"输入错误!"<<endl;
						else
						{
							p = L.FindIndex(pos,L.stu);
							L.ShowOne(p);
						}
						L.Stop();break;
						case 3:system("cls"); flag=0; break;
						}
				}
				break;
                }
			case 7:
                {
					system("cls");L.Save(L.stu);break;
                }
			case 8:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					cout<<"1.头插法"<<endl;
					cout<<"2.尾插法"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:L.HeadInsert(L.tea);break;
						case 2:L.TailInsert(L.tea);break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 9:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					string name;
					cout<<"1.按工号进行搜索修改"<<endl;
					cout<<"2.按姓名进行搜索修改"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"输入工号:"; cin>>ID; L.SetID(ID,L.tea);L.Stop(); break;
						case 2:
						cout<<"输入姓名:";  cin>>name; L.SetName(name,L.tea);L.Stop(); break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 10:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					cout<<"1.删除指定记录"<<endl;
					cout<<"2.删除第一个记录"<<endl;
					cout<<"3.删除最后一个记录"<<endl;
					cout<<"4.删除全部记录"<<endl;
					cout<<"5.返回上一级"<<endl;
					cout <<"请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<6)
						switch(num)
						{
						case 1:cout<<"请输入工号:"; cin>>ID; L.RemoveAt(ID,L.tea);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.tea)<<"条教职工记录"<<endl;L.Stop();break;
						case 2:L.RemoveHead(L.tea);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.tea)<<"条教职工记录"<<endl;L.Stop();break;
						case 3:L.RemoveTail(L.tea);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.tea)<<"条教职工记录"<<endl;L.Stop();break;
						case 4:L.RemoveAll(L.tea);cout<<"操作完成!"<<endl;cout<<"当前还有"<<L.GetCount(L.tea)<<"条教职工记录"<<endl;L.Stop();break;
						case 5:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 11:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					int pos;
					cout<<"提醒:当前共有"<<L.GetCount(L.tea)<<"条记录!"<<endl;
					cout<<"输入需要插入的位置(整数):";
					cin>>pos;
					if(pos<=0||pos>L.GetCount(L.tea))
					{
						cout<<"输入错误!"<<endl;
						L.Stop();
					 }
					else
					{
						Node *p;
						p = L.FindIndex(pos,L.tea);
						L.ShowOne(p);
						cout<<"\n1.向前插入"<<endl;
						cout<<"2.向后插入"<<endl;
						cout<<"3.返回"<<endl;
						while(flag)
						{
							cout <<"请输入对应数字进行相应操作:";
							cin>>num;
							switch(num)
							{
                            case 1:
                            L.InsertBefore(pos,L.tea); flag=0; break;
                            case 2:
                            L.InsertAfter(pos,L.tea); flag=0; break;
                            case 3:
                            system("cls"); flag=0; break;
							}
							if(flag)
								cin>>num;
						}
					  }
					flag = 0;
				}
				break;
                }
			case 12:
                {
					system("cls");L.Show(L.tea);L.Stop();break;
                }
			case 13:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					int pos;
					Node *p;
					cout<<"1.按工号查找"<<endl;
					cout<<"2.按位置查找"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout << "请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"输入工号:"; cin>>ID;
						p=L.Find(ID,L.tea);
						if(p)
						{
							L.ShowOne(p);
							if(p==L.GetHead(L.tea) && p==L.GetTail(L.tea))
							{
								cout<<"\n前一条记录位置:无"<<endl;
								cout<<"后一条记录位置:无"<<endl<<endl;
							}
							else if(p==L.GetHead(L.tea))
							{
								cout<<"\n前一条记录位置:无"<<endl;
								cout<<"后一条记录位置:"<<L.GetNext(p,L.tea)<<endl<<endl;
							}
							else if(p==L.GetTail(L.tea))
							{
								cout<<"\n前一条记录位置:"<<L.GetPrev(p,L.tea)<<endl;
								cout<<"后一条记录位置:无"<<endl<<endl;
							}
							else
							{
								cout<<"\n前一条记录位置:"<<L.GetPrev(p,L.tea)<<endl;
								cout<<"后一条记录位置:"<<L.GetNext(p,L.tea)<<endl<<endl;
							}
						}
						L.Stop();break;
						case 2:
						cout<<"输入位置:"; Node *p; cin>>pos;
						if(pos<=0||pos>L.GetCount(L.tea))
							cout<<"输入错误!"<<endl;
						else
						{
							p = L.FindIndex(pos,L.tea);
							L.ShowOne(p);
						}
						L.Stop();break;
						case 3:system("cls"); flag=0; break;
						}
				}
				break;
                }
			case 14:
                {
					system("cls");L.Save(L.tea);break;
                }
			case 15:
                {
				flag = 1;
				while(flag)
				{
					int t;
					Node *h1 = new Node;
					if(h1==NULL)
                    {
                        cout<<"内存分配失败"<<endl;
                        exit(1);
                    }
					h1->next = NULL;
					Node *h2 = new Node;
					if(h2==NULL)
                    {
                        cout<<"内存分配失败"<<endl;
                        exit(1);
                    }
					h2->next = NULL;
					cout << "集合1元素（以-1结尾）：";
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						S.SetInsert(h1, t);
					}
					cout << "集合2元素（以-1结尾）：";
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						S.SetInsert(h2, t);
					}
					cout << "集合1：";
					S.SetPrint(h1);
					cout << "集合2：";
					S.SetPrint(h2);
					cout << "交集：";
					S.SetPrint(S.And(h1,h2));
					cout << "并集：";
					{
					    Node &k1 = *h1;
                        Node &k2 = *h2;
                        S.SetPrint(k1+k2);
					}
					cout << "集合1与集合2的差集：";
					{
                        Node &k1 = *h1;
                        Node &k2 = *h2;
                        S.SetPrint(k1-k2);
					}
					flag = 0;
					L.Stop();
					break;
				}
				break;
                }
			case 16:
                {
				flag = 1;
				while(flag)
				{
					int t;
					_list *p;
					Queue q;
					p = &q;
					cout << "进队（以-1结尾）：";
					int count=0;
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						p->store(t);
						count++;
					}
					cout<<"出队:"<<endl;
					while(count)
					{
						cout<<p->retrieve()<<"	";
						count--;
					}
					flag = 0;
					L.Stop();
					break;
				}
				break;
                }
			case 17:
                {
				flag = 1;
				while(flag)
				{
					int t;
					_list *p;
					Stack obj;
					p = &obj;
					cout << "进栈（以-1结尾）：";
					int count=0;
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						p->store(t);
						count++;
					}
					cout<<"出栈:"<<endl;
					while(count)
					{
						cout<<p->retrieve()<<"	";
						count--;
					}
					flag = 0;
					L.Stop();
					break;
				}
				break;
                }
            case 18:
                {
				flag = 1;
				while(flag)
				{
					system("cls");
					string ID;
					cout<<"1.教职工记录添加到学生后(注意:链表合并操作只能执行一次)"<<endl;
					cout<<"2.学生记录添加到教职工后(注意:链表合并操作只能执行一次)"<<endl;
					cout<<"3.返回上一级"<<endl;
					cout <<"请输入对应数字进行相应操作:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:L.AddTail(L.stu,L.tea);cout<<"操作完成!"<<endl;L.Stop();break;
						case 2:L.AddTail(L.tea,L.stu);cout<<"操作完成!"<<endl;L.Stop();break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 19:
                {
                  system("cls");cout<<"已退出，欢迎再次使用~~"<<endl;exit(0);
                }
            }
    }
    return 0;
}

Node* operator+(Node &k1,Node &k2)
{
    Node *h3 = new Node;
    Node *h1 = &k1;
    Node *h2 = &k2;
    if(h3==NULL)
    {
        cout<<"内存分配失败"<<endl;
        return h3;
    }
    h3->next = NULL;
    while (h1->next != NULL)
    {
        Set::SetInsert(h3, h1->next->val);
        h1 = h1->next;
    }
    while (h2->next != NULL)
    {
        if (!Set::SetFind(h3, h2->next->val))
            Set::SetInsert(h3, h2->next->val);
        h2 = h2->next;
    }
    return h3;
}

Node* operator-(Node &k1,Node &k2)
{

    Node *h1 = &k1;
    Node *h2 = &k2;
    Node *h3 = new Node;
    if(h3==NULL)
    {
        cout<<"内存分配失败"<<endl;
        return h3;
    }
    h3->next = NULL;
    while (h1->next != NULL)
    {
        if (!Set::SetFind(h2, h1->next->val))
            Set::SetInsert(h3, h1->next->val);
        h1 = h1->next;
    }
    return h3;
}

