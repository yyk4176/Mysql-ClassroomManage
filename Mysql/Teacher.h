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
	static Teacher* loadinfo(MYSQL mysql, std::string tid) {
		std::string sql = "select * from teacher where TeacherId = " + tid;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		MYSQL_RES* res = mysql_store_result(&mysql);
		if (res == nullptr)
		{
			std::cout<<"没有数据！"<<std::endl;
			return nullptr;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		Teacher* t = new Teacher(row[0], row[1], row[2]);
		return t;
	}

	void TeacherInfo(MYSQL mysql) {//查询个人信息
		MYSQL_RES* res = nullptr;
		std::string sql = "select * from teacher where TeacherID=";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		res = mysql_store_result(&mysql);
		printResult(res,teacherrows);
	}

	void TSearchCourseInfo(MYSQL mysql) {//查询课程信息
		std::string sql = "SELECT c.CourseID,c.CourseName,cl.ClassroomID,cl.Capacity,cl.Type,StartTime,EndTime FROM teacher t,course c,`schedule` s,classroom cl WHERE t.TeacherID=c.TeacherID AND s.CourseID=c.CourseID AND cl.ClassroomID=s.ClassroomID AND t.TeacherID=";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		if(mysql_query(&mysql, sql.c_str()))
			std::cout << "查询失败：" << mysql_error(&mysql) << std::endl;
		else
		{
			std::cout << "查询成功" << std::endl;
		MYSQL_RES* res = mysql_store_result(&mysql);
			printResult(res, mysql_num_fields(res));
		}
	}

	void TSearchEmptyClassroom(MYSQL mysql) {//查询空教室
		std::string sql = "SELECT ClassroomID FROM classroom WHERE NOT EXISTS (SELECT * FROM `schedule` WHERE classroom.ClassroomID=`schedule`.ClassroomID AND NOW() BETWEEN StartTime AND EndTime)";
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		MYSQL_RES* res = mysql_store_result(&mysql);
		printResult(res, mysql_num_fields(res));
	}

	void TeacherAct(MYSQL mysql)//教师操作
	{
		std::string sql;
		while (1)
		{
			std::cout << "1.查询个人信息" << std::endl;
			std::cout << "2.查询课程信息" << std::endl;
			std::cout << "3.查询空教室" << std::endl;
			std::cout << "4.退出" << std::endl;
			std::cout << "请选择操作：";
			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				TeacherInfo(mysql);
				break;
			case 2:
				TSearchCourseInfo(mysql);
				break;
			case 3:
				TSearchEmptyClassroom(mysql);
				break;
			case 4:
				return;
			default:
				std::cout << "输入错误，请重新输入" << std::endl;
				break;
			}
		}
	}
	
};