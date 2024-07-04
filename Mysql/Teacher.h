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
};