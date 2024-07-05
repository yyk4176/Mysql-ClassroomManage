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
			std::cout<<"û�����ݣ�"<<std::endl;
			return nullptr;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		Teacher* t = new Teacher(row[0], row[1], row[2]);
		return t;
	}

	void TeacherInfo(MYSQL mysql) {//��ѯ������Ϣ
		MYSQL_RES* res = nullptr;
		std::string sql = "select * from teacher where TeacherID=";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		res = mysql_store_result(&mysql);
		printResult(res,teacherrows);
	}

	void TSearchCourseInfo(MYSQL mysql) {//��ѯ�γ���Ϣ
		std::string sql = "SELECT c.CourseID,c.CourseName,cl.ClassroomID,cl.Capacity,cl.Type,StartTime,EndTime FROM teacher t,course c,`schedule` s,classroom cl WHERE t.TeacherID=c.TeacherID AND s.CourseID=c.CourseID AND cl.ClassroomID=s.ClassroomID AND t.TeacherID=";
		sql+= id;
		mysql_query(&mysql, "set names GBK");
		if(mysql_query(&mysql, sql.c_str()))
			std::cout << "��ѯʧ�ܣ�" << mysql_error(&mysql) << std::endl;
		else
		{
			std::cout << "��ѯ�ɹ�" << std::endl;
		MYSQL_RES* res = mysql_store_result(&mysql);
			printResult(res, mysql_num_fields(res));
		}
	}

	void TSearchEmptyClassroom(MYSQL mysql) {//��ѯ�ս���
		std::string sql = "SELECT ClassroomID FROM classroom WHERE NOT EXISTS (SELECT * FROM `schedule` WHERE classroom.ClassroomID=`schedule`.ClassroomID AND NOW() BETWEEN StartTime AND EndTime)";
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, sql.c_str());
		MYSQL_RES* res = mysql_store_result(&mysql);
		printResult(res, mysql_num_fields(res));
	}

	void TeacherAct(MYSQL mysql)//��ʦ����
	{
		std::string sql;
		while (1)
		{
			std::cout << "1.��ѯ������Ϣ" << std::endl;
			std::cout << "2.��ѯ�γ���Ϣ" << std::endl;
			std::cout << "3.��ѯ�ս���" << std::endl;
			std::cout << "4.�˳�" << std::endl;
			std::cout << "��ѡ�������";
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
				std::cout << "�����������������" << std::endl;
				break;
			}
		}
	}
	
};