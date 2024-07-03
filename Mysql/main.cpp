#include <iostream>
#include "mysql.h"
#include <string>
#include "Teacher.h"
#include "manager.h"

using namespace std;

void printResult(MYSQL_RES* res, int rownum)
{
	MYSQL_ROW row;
	if(mysql_num_rows(res) == 0)
	{
		cout << "û�����ݣ�" << endl;
		return;
	}
	cout<<"��ѯ������£�"<<endl;
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

	Teacher teacher("10", "����", "����");
	teacher.TeacherInfo(mysql);

	Manager::MQuery(mysql);


	return 0;
	char sql[1024]{ 0 };
	sprintf_s(sql, 1024, "select * from customer");
	mysql_query(&mysql, "set names GBK");
	///< ���ò�ѯ�ӿ�
	if (mysql_real_query(&mysql, sql, (unsigned int)strlen(sql)))
	{
		cout << "��ѯʧ��" << ": " << mysql_errno(&mysql) << endl;
	}
	else
	{
		cout << "��ѯ�ɹ�" << endl << endl;

		///< װ�ؽ����
		res = mysql_store_result(&mysql);

		if (nullptr == res)
		{
			cout << "װ������ʧ��" << ": " << mysql_errno(&mysql) << endl;
		}
		else
		{
			///< ȡ�������������
			while (row = mysql_fetch_row(res))
			{
				cout << row[0] << "  " << row[1] << endl;
			}
		}
	}

	///< �ͷŽ����
	mysql_free_result(res);

	///< �ر����ݿ�����
	mysql_close(&mysql);

	system("pause");

	return 0;
}