#pragma once
#include "mysql.h"
#include <iostream>

void printResult(MYSQL_RES* res, int rownum);
class Manager {
public:
	static void MADD(MYSQL mysql, std::string table) {
		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		std::string input;
		std::string sql = "insert into ";
		sql += table;
		sql += " values(";
		std::string sqltemp = "select * from ";
		sqltemp += table;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sqltemp.c_str());
		res = mysql_store_result(&mysql);
		field = mysql_fetch_field(res);
		std::cout << "������" << field->name << "��";
		field = mysql_fetch_field(res);
		std::cin >> input;
		sql += "'";
		sql += input;
		sql += "'";
		while (field != nullptr){
			std::cout << "������" << field->name << "��";
			field = mysql_fetch_field(res);
			std::cin >> input;
			sql += ",'";
			sql += input;
			sql += "'";
		}
		sql += ")";
		//std::cout << sql;
		if (mysql_query(&mysql, sql.c_str()))
			std::cout << "���ʧ�ܣ�"<< mysql_error(&mysql) << std::endl;
		else
			std::cout << "��ӳɹ�" << std::endl;
	}
	static void MDelete(MYSQL mysql, std::string table, std::string ID) {
		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		std::string input;
		std::string sql = "delete from ";
		sql += table;
		sql += " where ";
		sql += table;
		sql += "ID";
		sql += " = ";
		sql += ID;
		//std::cout << sql;
		if (mysql_query(&mysql, sql.c_str()))
			std::cout << "ɾ��ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
		else
			std::cout << "ɾ���ɹ�" << std::endl;
	}
	static void MQuery(MYSQL mysql) {
		MYSQL_RES* res = nullptr;
		std::string sql;
		std::cout<<"����SQL��䣺";
		getline(std::cin, sql);
		mysql_query(&mysql, "set names GBK");
		if (mysql_query(&mysql, sql.c_str()))
		{
			std::cout << "����ʧ��" << ": " << mysql_error(&mysql) << std::endl;
			return;
		}
		else
		{
			std::cout << "�����ɹ�" << std::endl << std::endl;
			res = mysql_store_result(&mysql);
			if (res != nullptr)
				printResult(res, mysql_num_fields(res));
		}

	}
};
