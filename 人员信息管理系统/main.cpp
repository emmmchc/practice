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

class List  //������������
{
public:
    List();
    ~List();
    Node *GetHead(Node *head); //����ͷԪ��ָ��
    Node *GetTail(Node *head); //����βԪ��ָ��

	void RemoveAt(string ID,Node *head); //�Ƴ�ָ���±�ֵ��Ԫ��
    void RemoveHead(Node *head);  //�Ƴ���һ��Ԫ��
    void RemoveTail(Node *head);  //�Ƴ����һ��Ԫ��
	void RemoveAll(Node *head); //�Ƴ�����Ԫ��

    void AddHead(Node *head); //�ڱ�ͷ���Ԫ�ػ�������.��������
    void AddTail(Node *head); //�ڱ�β���Ԫ�ػ�������.��������

    int GetNext(Node* cur,Node *head); //������һ��Ԫ�ص�λ��
    int GetPrev(Node* cur,Node *head); //����ǰһ��Ԫ��λ��
    Node *Find(string ID,Node *head);//���ص���ָ��ֵ��Ԫ��
    Node *FindIndex(int pos,Node *head);//���ص���ָ���±��Ԫ��

    void SetID(string ID,Node *head); //�趨ָ��ID��Ԫ��ֵ
    void SetName(string ID,Node *head);//�趨ָ��������Ԫ��ֵ

    void InsertBefore(int pos,Node *head);//��ָ��λ��ǰ����Ԫ��
    void InsertAfter(int pos,Node *head);//��ָ��λ�ú����Ԫ��

    void HeadInsert(Node *head);//ͷ�巨
    void TailInsert(Node *head);//β�巨

    int GetCount(Node *head);//����������
    bool IsEmpty(Node *head);//�ж������Ƿ�Ϊ��
    void Show(Node *head);//�����������
    void Stop();//����������ز˵�
    void ShowOne(Node *p);//��ʾһ����¼
    void Save(Node *head);//�������ݵ�����D�̸�Ŀ¼

    void AddTail(Node *p,Node *q);//�������أ����β����ʵ�ʿ���ͨ���ı����λ�ý��������ͷ�ϲ�����β�ϲ���

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
		cout<<"����ʧ��"<<endl;
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
		cout<<"��"<<endl;
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
		cout<<"����ʧ��"<<endl;
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
		cout<<"��"<<endl;
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
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"�ڴ����ʧ��"<<endl;
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

void List::HeadInsert(Node *head)//��ͷ����Ӽ�¼
{
    Node *p = head->next;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"�ڴ����ʧ��"<<endl;
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
    cout<<"����������:";
    cin>>name1;
    cout<<"����������:";
    cin>>age1;
    if(head==tea)
        cout<<"�����빤��:";
    else
        cout<<"������ѧ��:";
    cin>>ID1;
    cout<<"�������Ա�(��/Ů):";
    cin>>sex1;
    if(head==tea)
        cout<<"����������ѧԺ:";
    else
        cout<<"������Ժϵ:";
    cin>>depart1;
    cout<<"�������������(yyyy mm dd):";
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
        s->next = p;        // ���½�����head��
    }
    else
    {
        head->next = s;
        s->next = NULL;
        s->pre = head;
    }
    char ch;
    cout<<"\n�������,�Ƿ��ٴ�ִ�иò���?(Y/N):";
    cin>>ch;
    while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
    {
        cout<<"�������,����������!"<<endl;
        cout<<"�Ƿ��ٴ�ִ�иò���?(Y/N):";
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

void List::TailInsert(Node *head)//��β����Ӽ�¼
{
    Node *p = head->next;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"�ڴ����ʧ��"<<endl;
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
    cout<<"����������:";
    cin>>name1;
    cout<<"����������:";
    cin>>age1;
    if(head==tea)
        cout<<"�����빤��:";
    else
        cout<<"������ѧ��:";
    cin>>ID1;
    cout<<"�������Ա�(��/Ů):";
    cin>>sex1;
    if(head==tea)
        cout<<"����������ѧԺ:";
    else
        cout<<"������Ժϵ:";
    cin>>depart1;
    cout<<"�������������(yyyy mm dd):";
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
    cout<<"\n�������,�Ƿ��ٴ�ִ�иò���?(Y/N):";
    cin>>ch;
    while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
    {
        cout<<"�������,����������!"<<endl;
        cout<<"�Ƿ��ٴ�ִ�иò���?(Y/N):";
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

void List::SetID(string ID,Node *head)//ͨ��ID����ָ����¼���޸�
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
        cout << "��¼Ϊ��" <<endl;
    else
    {
        while (p->ID!=ID)
        {
            p = p->next;
            i++;
            if(i>GetCount(head))
                {
                    cout << "�޸ü�¼" <<endl;
                    return;
                }
        }
        if(i == GetCount(head))
        {
            cout<<"�����޸���������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ��޸ģ�(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"����������:";
                cin>>name1;
                cout<<"����������:";
                cin>>age1;
                if(head==tea)
                    cout<<"�����빤��:";
                else
                    cout<<"������ѧ��:";
                cin>>ID1;
                cout<<"�������Ա�(��/Ů):";
                cin>>sex1;
                cout<<"������Ժϵ:";
                cin>>depart1;
                cout<<"�������������(yyyy mm dd):";
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
            cout<<"�����޸���������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ��޸ģ�(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"����������:";
                cin>>name1;
                cout<<"����������:";
                cin>>age1;
                if(head==tea)
                    cout<<"�����빤��:";
                else
                    cout<<"������ѧ��:";
                cin>>ID1;
                cout<<"�������Ա�(��/Ů):";
                cin>>sex1;
                cout<<"������Ժϵ:";
                cin>>depart1;
                cout<<"�������������(yyyy mm dd):";
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

void List::SetName(string name,Node *head)//ͨ����������ָ����¼���޸�
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
        cout << "��¼Ϊ��" <<endl;
    else
    {
        while (p->name!=name)
        {
            p = p->next;
            i++;
            if(i>GetCount(head))
                {
                    cout << "�޸ü�¼" <<endl;
                    return;
                }
        }
        if(i == GetCount(head))
        {
            cout<<"�����޸���������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ��޸ģ�(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"����������:";
                cin>>name1;
                cout<<"����������:";
                cin>>age1;
                if(head==tea)
                    cout<<"�����빤��:";
                else
                    cout<<"������ѧ��:";
                cin>>ID1;
                cout<<"�������Ա�(��/Ů):";
                cin>>sex1;
                cout<<"������Ժϵ:";
                cin>>depart1;
                cout<<"�������������(yyyy mm dd):";
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
            cout<<"�����޸���������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ��޸ģ�(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                cout<<"����������:";
                cin>>name1;
                cout<<"����������:";
                cin>>age1;
                if(head==tea)
                    cout<<"�����빤��:";
                else
                    cout<<"������ѧ��:";
                cin>>ID1;
                cout<<"�������Ա�(��/Ů):";
                cin>>sex1;
                cout<<"������Ժϵ:";
                cin>>depart1;
                cout<<"�������������(yyyy mm dd):";
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

void List::RemoveAt(string ID,Node *head)//ɾ��ָ��ID�ļ�¼
{
    int i = 0;
    Node *p = head;
    if (IsEmpty(head))
    {
        cout<<"�޼�¼"<<endl;
    }
    else
    {
       while (p->ID!=ID)
        {
            p = p->next;
            i++;
            if (i>GetCount(head))
                {
                    cout<<"û�и�����¼��"<<endl;
                    return;
                }
        }
        if (i == GetCount(head))
        {
            cout<<"����ɾ����������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ�ɾ����(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                p->pre->next = NULL;
                delete p;
				cout<<"ɾ���ɹ���"<<endl;
            }
            else if(ch==('N'|'n'))
                system("cls");

        }
        else
        {
            cout<<"����ɾ����������:"<<endl;
            ShowOne(p);
            cout<<"\n�Ƿ�ɾ����(Y/N):";
            char ch;
            cin>>ch;
            while((ch!='Y')&&(ch!='y')&&(ch!='N')&&(ch!='n'))
            {
                cout<<"�������,����������!"<<endl;
                cin.clear();
                cin.ignore();
                cin>>ch;
            }
            if((ch=='Y')|(ch=='y'))
            {
                p->pre->next = p->next;
                p->next->pre = p->pre;
                delete p;
				cout<<"ɾ���ɹ���"<<endl;
            }
            else if(ch==('N'|'n'))
                system("cls");
        }
    }
}

void List::RemoveHead(Node *head)//ɾ��ͷ��¼
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

void List::RemoveTail(Node *head)//ɾ��β��¼
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

void List::RemoveAll(Node *head)//ɾ��ȫ����¼
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

void List::InsertAfter(int pos,Node *head)//�ڵ�ǰ�ڵ�����������
{
    Node *p;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"����λ�ô���!"<<endl;
    }
    else
    {
        while (i < pos)
        {
            p = p->next;
            i++;
        }
        if (i == GetCount(head))      //��������һ��Ԫ�غ������data
        {
            TailInsert(head);
        }
        else
        {
            s = new Node;
            if(s==NULL)
            {
                cout<<"�ڴ����ʧ��"<<endl;
                exit(1);
            }
            cout<<"����������:";
            cin>>name1;
            cout<<"����������:";
            cin>>age1;
            if(head==tea)
                cout<<"�����빤��:";
            else
                cout<<"������ѧ��:";
            cin>>ID1;
            cout<<"�������Ա�(��/Ů):";
            cin>>sex1;
            if(head==tea)
                cout<<"����������ѧԺ:";
            else
                cout<<"������Ժϵ:";
            cin>>depart1;
            cout<<"�������������(yyyy mm dd):";
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
    cout<<"\n�������"<<endl;
    Stop();
}

void List::InsertBefore(int pos,Node *head)//�ڵ�ǰ�ڵ�ǰ���������
{
    Node *p;
    Node *s = new Node;
    if(s==NULL)
    {
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"����λ�ô���!"<<endl;
    }
    else
    {
        while(i < pos)
        {
            p = p->next;
            i++;
        }
        if (i == 1)      // ����ڵ�һ��Ԫ��ǰ�����data
        {
            HeadInsert(p);
        }
        else
        {
            s = new Node;
            if(s==NULL)
            {
                cout<<"�ڴ����ʧ��"<<endl;
                exit(1);
            }
            cout<<"����������:";
            cin>>name1;
            cout<<"����������:";
            cin>>age1;
            if(head==tea)
            cout<<"�����빤��:";
            else
                cout<<"������ѧ��:";
            cin>>ID1;
            cout<<"�������Ա�(��/Ů):";
            cin>>sex1;
            if(head==tea)
                cout<<"����������ѧԺ:";
            else
                cout<<"������Ժϵ:";
            cin>>depart1;
            cout<<"�������������(yyyy mm dd):";
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
    cout<<"\n�������"<<endl;
    Stop();
}

Node *List::FindIndex(int pos,Node *head)//����ָ��λ�õļ�¼
{
    Node *p = head->next;
    while (pos-1)
    {
        if(p==NULL)
        {
            cout<<"�޲�ѯ���"<<endl;
            return NULL;
        }
        p = p->next;
        pos--;
    }
    return p;
}

Node *List::Find(string ID,Node *head)//��ѧ�š����Ų���
{
    Node *p = head->next;
    while (p)
    {
        if(p->ID == ID)
            return p;
        p = p->next;
    }
    cout<<"�޲�ѯ���"<<endl;
    return NULL;
}

int List::GetNext(Node* cur,Node *head)//���غ�һ����¼��λ��
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

int List::GetPrev(Node* cur,Node *head)//����ǰһ����¼��λ��
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

Node *List::GetHead(Node *head)//����ͷԪ��ָ��
{
    Node *p = head->next;
    return p;
}

Node *List::GetTail(Node *head)//����βԪ��ָ��
{
    Node *p = head->next;
    if(p==NULL)
        return NULL;
    while(p->next)
        p = p->next;
    return p;
}

void List::ShowOne(Node *p)//��ӡһ����¼
{
    cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
    cout<<"����:"<<p->name<<endl;
    cout<<"����:"<<p->age<<endl;
    cout<<"ѧ��:"<<p->ID<<endl;
    cout<<"�Ա�:"<<p->sex<<endl;
    cout<<"Ժϵ:"<<p->depart<<endl;
    cout<<"��������:"<<p->year<<"��"<<p->month<<"��"<<p->day<<"��"<<endl;
}

void List::Show(Node *head)//��ӡȫ����¼
{
    Node *p = head->next;
	if(head==stu && (GetCount(head)==GetCount(stu)))
		cout<<"��ǰ�ܹ���"<<GetCount(head)<<"��ѧ����¼"<<endl<<endl;
	else if(head==tea && (GetCount(head)==GetCount(tea)))
		cout<<"��ǰ�ܹ���"<<GetCount(head)<<"����ְ����¼"<<endl<<endl;
	else
		cout<<"��ǰ�ܹ���"<<GetCount(head)<<"����¼"<<endl<<endl;
	while(p!=NULL)
    {
        cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*"<<endl;
		cout<<"����:"<<p->name<<endl;
		cout<<"����:"<<p->age<<endl;
		cout<<"ѧ��:"<<p->ID<<endl;
		cout<<"�Ա�:"<<p->sex<<endl;
		cout<<"Ժϵ:"<<p->depart<<endl;
		cout<<"��������:"<<p->year<<"��"<<p->month<<"��"<<p->day<<"��"<<endl;
		p = p->next;
	}
	cout << endl;
}

void List::Stop()//���ز˵�
{
    getchar();
    cout<<"�����������";
    if(getchar())
        system("cls");
}

int List::GetCount(Node *head)//������
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

bool List::IsEmpty(Node *head)//�����Ƿ�Ϊ��
{
    if(head->next==NULL)
        return true;
    else
        return false;
}

void List::Save(Node *head)//�������ݵ�����
{
    Node *p = head->next;
    if(head==stu)
    {
        ofstream fStudent("D://ѧ����Ϣ.txt",ios::out);
        fStudent<<"����\t\t����\tѧ��\t\t�Ա�\tԺϵ\t\t��������"<<endl;
        while(p)
        {
            fStudent<<p->name<<"\t\t"<<p->age<<"\t"<<p->ID<<"\t\t"<<p->sex<<"\t"<<p->depart<<"\t\t"<<p->year<<"��"<<p->month<<"��"<<p->day<<"��"<<endl;
            p = p->next;
        }
        fStudent.close();
    }
    else
    {
        ofstream fTeacher("D://��ְ����Ϣ.txt",ios::out);
        fTeacher<<"����\t\t����\t����\t\t�Ա�\t����ѧԺ\t\t��������"<<endl;
        while(p)
        {
            fTeacher<<p->name<<"\t\t"<<p->age<<"\t"<<p->ID<<"\t\t"<<p->sex<<"\t"<<p->depart<<"\t\t"<<p->year<<"��"<<p->month<<"��"<<p->day<<"��"<<endl;
            p = p->next;
        }
        fTeacher.close();
    }
    cout<<"����ɹ�!"<<endl;
    Stop();
}

void List::AddTail(Node *p,Node *q)//�������أ����β����ʵ�ʿ���ͨ���ı����λ�ý��������ͷ�ϲ�����β�ϲ���
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

Node* operator+(Node &k1,Node &k2);//����
Node* operator-(Node &k1,Node &k2);//�

void menu()//���ܲ˵�
{
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << "|                      ��Ա��Ϣ����                         |" << endl;
    cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    cout << " 1.ѧ���Ǽ�                2.ѧ���༭              3.ѧ��ɾ��" << endl;
    cout << " 4.ѧ������                5.ѧ������              6.ѧ������" << endl;
    cout << " 7.ѧ������                                                  " <<endl;
	cout << " 8.��ʦ�Ǽ�                9.��ʦ�༭             10.��ʦɾ��" << endl;
    cout << "11.��ʦ����               12.��ʦ����             13.��ʦ����" << endl;
    cout << "14.��ʦ����                                                  " << endl;
	cout << "15.����                   16.����                 17.ջ      " << endl;
	cout << "18.����ϲ�               19.�˳�ϵͳ                        " << endl;
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
        cout << "������׼ȷ���ֽ�����Ӧ����:";
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
					cout<<"1.ͷ�巨"<<endl;
					cout<<"2.β�巨"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
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
					cout<<"1.��ѧ�Ž��������޸�"<<endl;
					cout<<"2.���������������޸�"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"����ѧ��:"; cin>>ID; L.SetID(ID,L.stu); L.Stop();break;
						case 2:
						cout<<"��������:";  cin>>name; L.SetName(name,L.stu); L.Stop();break;
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
					cout<<"1.ɾ��ָ����¼"<<endl;
					cout<<"2.ɾ����һ����¼"<<endl;
					cout<<"3.ɾ�����һ����¼"<<endl;
					cout<<"4.ɾ��ȫ����¼"<<endl;
					cout<<"5.������һ��"<<endl;
					cout <<"�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<6)
						switch(num)
						{
						case 1:cout<<"������ѧ��:"; cin>>ID; L.RemoveAt(ID,L.stu);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.stu)<<"��ѧ����¼"<<endl;L.Stop();break;
						case 2:L.RemoveHead(L.stu);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.stu)<<"��ѧ����¼"<<endl;L.Stop();break;
						case 3:L.RemoveTail(L.stu);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.stu)<<"��ѧ����¼"<<endl;L.Stop();break;
						case 4:L.RemoveAll(L.stu);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.stu)<<"��ѧ����¼"<<endl;L.Stop();break;
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
					cout<<"����:��ǰ����"<<L.GetCount(L.stu)<<"����¼!"<<endl;
					cout<<"������Ҫ�����λ��(����):";
					cin>>pos;
					if(pos<=0||pos>L.GetCount(L.stu))
					{
						cout<<"�������!"<<endl;
						L.Stop();
					 }
					else
					{
						Node *p;
						p = L.FindIndex(pos,L.stu);
						L.ShowOne(p);
						cout<<"\n1.��ǰ����"<<endl;
						cout<<"2.������"<<endl;
						cout<<"3.����"<<endl;
						while(flag)
						{
							cout <<"�������Ӧ���ֽ�����Ӧ����:";
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
					cout<<"1.��ѧ�Ų���"<<endl;
					cout<<"2.��λ�ò���"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"����ѧ��:"; cin>>ID;
						p=L.Find(ID,L.stu);
						if(p)
						{
							L.ShowOne(p);
							if(p==L.GetHead(L.stu) && p==L.GetTail(L.stu))
							{
								cout<<"\nǰһ����¼λ��:��"<<endl;
								cout<<"��һ����¼λ��:��"<<endl<<endl;
							}
							else if(p==L.GetHead(L.stu))
							{
								cout<<"\nǰһ����¼λ��:��"<<endl;
								cout<<"��һ����¼λ��:"<<L.GetNext(p,L.stu)<<endl<<endl;
							}
							else if(p==L.GetTail(L.stu))
							{
								cout<<"\nǰһ����¼λ��:"<<L.GetPrev(p,L.stu)<<endl;
								cout<<"��һ����¼λ��:��"<<endl<<endl;
							}
							else
							{
								cout<<"\nǰһ����¼λ��:"<<L.GetPrev(p,L.stu)<<endl;
								cout<<"��һ����¼λ��:"<<L.GetNext(p,L.stu)<<endl<<endl;
							}
						}
						L.Stop();break;
						case 2:
						cout<<"����λ��:"; Node *p; cin>>pos;
						if(pos<=0||pos>L.GetCount(L.stu))
							cout<<"�������!"<<endl;
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
					cout<<"1.ͷ�巨"<<endl;
					cout<<"2.β�巨"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
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
					cout<<"1.�����Ž��������޸�"<<endl;
					cout<<"2.���������������޸�"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"���빤��:"; cin>>ID; L.SetID(ID,L.tea);L.Stop(); break;
						case 2:
						cout<<"��������:";  cin>>name; L.SetName(name,L.tea);L.Stop(); break;
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
					cout<<"1.ɾ��ָ����¼"<<endl;
					cout<<"2.ɾ����һ����¼"<<endl;
					cout<<"3.ɾ�����һ����¼"<<endl;
					cout<<"4.ɾ��ȫ����¼"<<endl;
					cout<<"5.������һ��"<<endl;
					cout <<"�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<6)
						switch(num)
						{
						case 1:cout<<"�����빤��:"; cin>>ID; L.RemoveAt(ID,L.tea);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.tea)<<"����ְ����¼"<<endl;L.Stop();break;
						case 2:L.RemoveHead(L.tea);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.tea)<<"����ְ����¼"<<endl;L.Stop();break;
						case 3:L.RemoveTail(L.tea);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.tea)<<"����ְ����¼"<<endl;L.Stop();break;
						case 4:L.RemoveAll(L.tea);cout<<"�������!"<<endl;cout<<"��ǰ����"<<L.GetCount(L.tea)<<"����ְ����¼"<<endl;L.Stop();break;
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
					cout<<"����:��ǰ����"<<L.GetCount(L.tea)<<"����¼!"<<endl;
					cout<<"������Ҫ�����λ��(����):";
					cin>>pos;
					if(pos<=0||pos>L.GetCount(L.tea))
					{
						cout<<"�������!"<<endl;
						L.Stop();
					 }
					else
					{
						Node *p;
						p = L.FindIndex(pos,L.tea);
						L.ShowOne(p);
						cout<<"\n1.��ǰ����"<<endl;
						cout<<"2.������"<<endl;
						cout<<"3.����"<<endl;
						while(flag)
						{
							cout <<"�������Ӧ���ֽ�����Ӧ����:";
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
					cout<<"1.�����Ų���"<<endl;
					cout<<"2.��λ�ò���"<<endl;
					cout<<"3.������һ��"<<endl;
					cout << "�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:
						cout<<"���빤��:"; cin>>ID;
						p=L.Find(ID,L.tea);
						if(p)
						{
							L.ShowOne(p);
							if(p==L.GetHead(L.tea) && p==L.GetTail(L.tea))
							{
								cout<<"\nǰһ����¼λ��:��"<<endl;
								cout<<"��һ����¼λ��:��"<<endl<<endl;
							}
							else if(p==L.GetHead(L.tea))
							{
								cout<<"\nǰһ����¼λ��:��"<<endl;
								cout<<"��һ����¼λ��:"<<L.GetNext(p,L.tea)<<endl<<endl;
							}
							else if(p==L.GetTail(L.tea))
							{
								cout<<"\nǰһ����¼λ��:"<<L.GetPrev(p,L.tea)<<endl;
								cout<<"��һ����¼λ��:��"<<endl<<endl;
							}
							else
							{
								cout<<"\nǰһ����¼λ��:"<<L.GetPrev(p,L.tea)<<endl;
								cout<<"��һ����¼λ��:"<<L.GetNext(p,L.tea)<<endl<<endl;
							}
						}
						L.Stop();break;
						case 2:
						cout<<"����λ��:"; Node *p; cin>>pos;
						if(pos<=0||pos>L.GetCount(L.tea))
							cout<<"�������!"<<endl;
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
                        cout<<"�ڴ����ʧ��"<<endl;
                        exit(1);
                    }
					h1->next = NULL;
					Node *h2 = new Node;
					if(h2==NULL)
                    {
                        cout<<"�ڴ����ʧ��"<<endl;
                        exit(1);
                    }
					h2->next = NULL;
					cout << "����1Ԫ�أ���-1��β����";
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						S.SetInsert(h1, t);
					}
					cout << "����2Ԫ�أ���-1��β����";
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						S.SetInsert(h2, t);
					}
					cout << "����1��";
					S.SetPrint(h1);
					cout << "����2��";
					S.SetPrint(h2);
					cout << "������";
					S.SetPrint(S.And(h1,h2));
					cout << "������";
					{
					    Node &k1 = *h1;
                        Node &k2 = *h2;
                        S.SetPrint(k1+k2);
					}
					cout << "����1�뼯��2�Ĳ��";
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
					cout << "���ӣ���-1��β����";
					int count=0;
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						p->store(t);
						count++;
					}
					cout<<"����:"<<endl;
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
					cout << "��ջ����-1��β����";
					int count=0;
					while (1)
					{
						cin >> t;
						if (t == -1)
							break;
						p->store(t);
						count++;
					}
					cout<<"��ջ:"<<endl;
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
					cout<<"1.��ְ����¼��ӵ�ѧ����(ע��:����ϲ�����ֻ��ִ��һ��)"<<endl;
					cout<<"2.ѧ����¼��ӵ���ְ����(ע��:����ϲ�����ֻ��ִ��һ��)"<<endl;
					cout<<"3.������һ��"<<endl;
					cout <<"�������Ӧ���ֽ�����Ӧ����:";
					cin>>num;
					if(num>0 && num<4)
						switch(num)
						{
						case 1:L.AddTail(L.stu,L.tea);cout<<"�������!"<<endl;L.Stop();break;
						case 2:L.AddTail(L.tea,L.stu);cout<<"�������!"<<endl;L.Stop();break;
						case 3:system("cls");flag=0;break;
						}
				}
				break;
                }
			case 19:
                {
                  system("cls");cout<<"���˳�����ӭ�ٴ�ʹ��~~"<<endl;exit(0);
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
        cout<<"�ڴ����ʧ��"<<endl;
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
        cout<<"�ڴ����ʧ��"<<endl;
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

