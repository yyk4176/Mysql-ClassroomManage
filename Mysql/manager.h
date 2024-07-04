#pragma once
#include "mysql.h"
#include <iostream>
#include "TableData.h"
#include <vector>
#include <string>
#include <algorithm>

void printResult(MYSQL_RES* res, int rownum);
class Manager {
public:
	static TableEntity* getEntity() {
		std::string table;
		std::cout<< "�����������";
		std::cin >> table;
		std::string temp[5];
		if (table == "teacher")
		{
			std::cout<<"�������ʦID��";
			std::cin >> temp[0];
			std::cout << "�������ʦ������";
			std::cin >> temp[1];
			std::cout << "�������ʦְ�ƣ�";
			std::cin >> temp[2];
			TeacherRow* tr=new TeacherRow(atoi(temp[0].c_str()), temp[1], temp[2]);
			return tr;
		}
		else if (table == "course")
		{
			std::cout << "������γ�ID��";
			std::cin >> temp[0];
			std::cout << "������γ����ƣ�";
			std::cin >> temp[1];
			std::cout << "������γ�������";
			std::cin >> temp[2];
			std::cout << "�������ʦID��";
			std::cin >> temp[3];
			CourseRow* cr = new CourseRow(atoi(temp[0].c_str()), temp[1], atoi(temp[2].c_str()), atoi(temp[3].c_str()));
			return cr;
		}
		else if (table == "classroom")
		{
			std::cout << "���������ID��";
			std::cin >> temp[0];
			std::cout << "���������������";
			std::cin >> temp[1];
			std::cout << "������������ͣ�";
			std::cin >> temp[2];
			ClassroomRow* clr = new ClassroomRow(atoi(temp[0].c_str()), atoi(temp[1].c_str()), temp[2]);
			return clr;
		}
		else if (table == "schedule")
		{
			std::cout << "�޷��ֶ���ӿγ̰�����Ϣ" << std::endl;
			return nullptr;
		}
		else
		{
			std::cout<<"��������"<<std::endl;
			return nullptr;
		}
	}
	static void MADD(MYSQL mysql) {
		std::string sql = "insert into ";
		std::string tablename;

		TableEntity* tbe = getEntity();
		tablename = tbe->TableName;

		sql += tbe->TableName;
		sql += " values";
		mysql_query(&mysql, "set names GBK");
		if (tbe->TableName == "teacher")
		{
			sql += "('";
			sql+= std::to_string(((TeacherRow*)tbe)->TeacherID);
			sql += "','";
			sql += ((TeacherRow*)tbe)->Name;
			sql += "','";
			sql += ((TeacherRow*)tbe)->Title;
			sql += "')";
		}
		else if(tbe->TableName == "course")
		{
			sql += "(";
			sql += std::to_string(((CourseRow*)tbe)->CourseID);
			sql += ",'";
			sql += ((CourseRow*)tbe)->CourseName;
			sql += "',";
			sql += std::to_string(((CourseRow*)tbe)->Capacity);
			sql += ",";
			sql += std::to_string(((CourseRow*)tbe)->TeacherID);
			sql += ")";
		}
		else if (tbe->TableName == "classroom")
		{
			sql += "(";
			sql += std::to_string(((ClassroomRow*)tbe)->ClassroomID);
			sql += ",";
			sql += std::to_string(((ClassroomRow*)tbe)->Capacity);
			sql += ",'";
			sql += ((ClassroomRow*)tbe)->Type;
			sql += "')";
		}
		else {
			std::cout<<"empty tablename"<<std::endl;
			return;
		}
		//delete(tbe);
		std::cout << sql << std::endl;
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
	static void ReArrangement(MYSQL mysql) {//���°��ſγ�ʱ���
		if (mysql_query(&mysql, "delete from schedule"))//��տγ̰���
		{
			std::cout << "ɾ��ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
			return;
		}
		else
			std::cout << "ɾ���ɹ�" << std::endl;
		std::cout << "���°��ſγ�......" << std::endl;

		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		MYSQL_ROW row;
		mysql_query(&mysql, "set names GBK");

		std::vector<CourseRow> courses;//�γ̱�
		std::vector<ClassroomRow> classrooms;//���ұ�
		std::vector<ScheduleRow> schedules;//�γ̰��ű�
		std::string starttime[4] = { "08:00:00", "09:55:00", "13:30:00", "15:05:00" };
		std::string endtime[4] = { "09:35:00", "11:30:00", "15:05:00", "17:00:00" };

		mysql_query(&mysql, "select * from course");
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))//��ȡ�γ���Ϣ
			courses.push_back(CourseRow(atoi(row[0]), std::string(row[1]), atoi(row[2]), atoi(row[3])));

		mysql_query(&mysql, "select * from classroom");
		res = mysql_store_result(&mysql);
		while(row = mysql_fetch_row(res))//��ȡ������Ϣ
			classrooms.push_back(ClassroomRow(atoi(row[0]), atoi(row[1]), std::string(row[2])));
		std::sort(classrooms.begin(), classrooms.end(), &ClassroomRow::compare);//��������������

		for (int i = 0; i < courses.size(); i++)
		{
			for (int j = 0; j < classrooms.size(); j++)
			{
				if (courses[i].Capacity == classrooms[j].Capacity)//�Դ�С���ʵĽ��Ұ��ſγ�
				{
					for (int day = 0; day < 5; day++)//һ��5��
					{
						for (int time = 0; time < 4; time++) {//ÿ��4��ʱ���
							if (classrooms[j].sparetime[day][time] == 0)//����ʱ���
							{
								classrooms[j].sparetime[day][time] = 1;
								courses[i].flag = 1;
								schedules.push_back(ScheduleRow(schedules.size() + 1, classrooms[j].ClassroomID, courses[i].CourseID,
									"2024-07-0" + std::to_string(day + 1) + " " + starttime[time], "2024-07-0" + std::to_string(day + 1) + " " + endtime[time]));
								break;
							}
						}
						if (courses[i].flag == 1)
							break;
					}
					if (courses[i].flag == 1)
						break;
				}
				else if(courses[i].Capacity < classrooms[j].Capacity)//�ٰ��ſγ�����С�ڽ��������Ŀγ�
				{
					for (int day = 0; day < 5; day++)
					{
						for (int time = 0; time < 4; time++) {
							if (classrooms[j].sparetime[day][time] == 0)
							{
								classrooms[j].sparetime[day][time] = 1;
								courses[i].flag = 1;
								schedules.push_back(ScheduleRow(schedules.size() + 1, classrooms[j].ClassroomID, courses[i].CourseID,
									"2024-07-0" + std::to_string(day + 1) + " " + starttime[time], "2024-07-0" + std::to_string(day + 1) + " " + endtime[time]));
								break;
							}
						}
						if (courses[i].flag == 1)
							break;
					}
					if (courses[i].flag == 1)
						break;
				}
			}
			if (courses[i].flag == 0)
				std::cout << "�γ�" << courses[i].CourseName << "û�к��ʵĽ���" << std::endl;

		}
		for (int i = 0; i < schedules.size(); i++)
		{
			std::string sql = "insert into schedule values(";
			sql += std::to_string(schedules[i].ScheduleID);
			sql += ",";
			sql += std::to_string(schedules[i].ClassroomID);
			sql += ",";
			sql += std::to_string(schedules[i].CourseID);
			sql += ",'";
			sql += schedules[i].StartTime;
			sql += "','";
			sql += schedules[i].EndTime;
			sql += "')";
			if (mysql_query(&mysql, sql.c_str()))
			{
				std::cout << "���ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
				return;
			}
		}
		std::cout << "ȫ����ӳɹ�" << std::endl;
	}
};