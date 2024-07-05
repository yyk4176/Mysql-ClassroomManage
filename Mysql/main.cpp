#include <iostream>
#include <iomanip>
#include "mysql.h"
#include <string>
#include "Teacher.h"
#include "manager.h"

using namespace std;

void printResult(MYSQL_RES* res, int rownum)
{
	MYSQL_ROW row;
	MYSQL_FIELD* field = nullptr;
	field = mysql_fetch_fields(res);
	if(mysql_num_rows(res) == 0)
	{
		cout << "û�����ݣ�" << endl;
		return;
	}
	cout<<"��ѯ������£�"<<endl;
	for (int i = 0; i < rownum; i++)
	{
		cout << field[i].name << "  ";
	}
	cout << endl;
	while (row = mysql_fetch_row(res))
	{
		for (int i = 0; i < rownum; i++)
		{
			cout << row[i] << "  ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "1q2w3e4r5t6y7u", "classroommanagesystem", 3306, nullptr, 0))
	{//�������ݿ�
		cout << "���ݿ�����ʧ��" << mysql_errno(&mysql) << endl;
		return -1;
	}
	cout << "���ݿ����ӳɹ�" << endl << endl;
	MYSQL_RES* res = nullptr;
	MYSQL_ROW row;

	string uid, password;
	while (1)
	{
		cout << "������ID��";
		cin >> uid;
		cout << "���������룺";
		cin >> password;

		if (uid == "manager" && password == "root")
		{
			cout << "����Ա��¼�ɹ�" << endl;
			Manager::ManagerAct(mysql);
			break;
		}
		else if (uid == "manager" && password != "root")
		{
			cout << "��¼ʧ��" << endl;
			continue;
		}
		mysql_query(&mysql, "set names GBK");
		string selectuser = "select * from teacher where TeacherID = " + uid;
		mysql_query(&mysql, selectuser.c_str());
		res = mysql_store_result(&mysql);
		if(res != nullptr)
		{
			row = mysql_fetch_row(res);
			if (row != nullptr)
			{
				cout << "��ʦ��¼�ɹ�" << endl;
				Teacher* t = Teacher::loadinfo(mysql, uid);
				t->TeacherAct(mysql);
				break;
			}
			cout << "��¼ʧ��" << endl;

		}
		else
			cout << "��¼ʧ��" << endl;
	}

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�����
	mysql_close(&mysql);

	return 0;
}