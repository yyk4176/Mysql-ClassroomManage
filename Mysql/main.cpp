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

	/*Teacher t1("1", "����", "����");
	t1.TSearchEmptyClassroom(mysql);*/
	Manager::ReArrangement(mysql);

	// �ͷŽ����
	mysql_free_result(res);

	// �ر����ݿ�����
	mysql_close(&mysql);

	system("pause");

	return 0;
}