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
		cout << "没有数据！" << endl;
		return;
	}
	cout<<"查询结果如下："<<endl;
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
	{//连接数据库
		cout << "数据库连接失败" << mysql_errno(&mysql) << endl;
		return -1;
	}
	cout << "数据库连接成功" << endl << endl;
	MYSQL_RES* res = nullptr;
	MYSQL_ROW row;

	Teacher teacher("10", "田悦", "教授");
	teacher.TeacherInfo(mysql);

	Manager::MQuery(mysql);


	return 0;
	char sql[1024]{ 0 };
	sprintf_s(sql, 1024, "select * from customer");
	mysql_query(&mysql, "set names GBK");
	///< 调用查询接口
	if (mysql_real_query(&mysql, sql, (unsigned int)strlen(sql)))
	{
		cout << "查询失败" << ": " << mysql_errno(&mysql) << endl;
	}
	else
	{
		cout << "查询成功" << endl << endl;

		///< 装载结果集
		res = mysql_store_result(&mysql);

		if (nullptr == res)
		{
			cout << "装载数据失败" << ": " << mysql_errno(&mysql) << endl;
		}
		else
		{
			///< 取出结果集中内容
			while (row = mysql_fetch_row(res))
			{
				cout << row[0] << "  " << row[1] << endl;
			}
		}
	}

	///< 释放结果集
	mysql_free_result(res);

	///< 关闭数据库连接
	mysql_close(&mysql);

	system("pause");

	return 0;
}