#pragma once
#include "mysql.h"
#include <iostream>
#include <string>

const int teacherrows = 3;
void printResult(MYSQL_RES* res,int rownum);
class Teacher {
public:
	Teacher(std::string id, std::string name, std::string title) {
		this->id = id;
		this->name = name;
		this->title = title;
	}
	~Teacher() {}
private:
	std::string id;
	std::string name;
	std::string title;
public:
	void TeacherInfo(MYSQL mysql) {
		MYSQL_RES* res = nullptr;
		std::string sql = "select * from teacher\n where TeacherID=";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		res = mysql_store_result(&mysql);
		printResult(res,teacherrows);
	}
	void TSearchCourseInfo(MYSQL mysql) {//查询课程信息
		std::string sql = "";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		MYSQL_RES* res = mysql_store_result(&mysql);
		printResult(res, teacherrows);
	}
	void TSearchEmptyClassroom(MYSQL mysql,std::string time) {//查询空教室
		std::string sql = "";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		MYSQL_RES* res = mysql_store_result(&mysql);
		printResult(res, teacherrows);
	}
};