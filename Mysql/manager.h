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
		std::cout<< "请输入表名：";
		std::cin >> table;
		std::string temp[5];
		if (table == "teacher")
		{
			std::cout<<"请输入教师ID：";
			std::cin >> temp[0];
			std::cout << "请输入教师姓名：";
			std::cin >> temp[1];
			std::cout << "请输入教师职称：";
			std::cin >> temp[2];
			TeacherRow* tr=new TeacherRow(atoi(temp[0].c_str()), temp[1], temp[2]);
			return tr;
		}
		else if (table == "course")
		{
			std::cout << "请输入课程ID：";
			std::cin >> temp[0];
			std::cout << "请输入课程名称：";
			std::cin >> temp[1];
			std::cout << "请输入课程容量：";
			std::cin >> temp[2];
			std::cout << "请输入教师ID：";
			std::cin >> temp[3];
			CourseRow* cr = new CourseRow(atoi(temp[0].c_str()), temp[1], atoi(temp[2].c_str()), atoi(temp[3].c_str()));
			return cr;
		}
		else if (table == "classroom")
		{
			std::cout << "请输入教室ID：";
			std::cin >> temp[0];
			std::cout << "请输入教室容量：";
			std::cin >> temp[1];
			std::cout << "请输入教室类型：";
			std::cin >> temp[2];
			ClassroomRow* clr = new ClassroomRow(atoi(temp[0].c_str()), atoi(temp[1].c_str()), temp[2]);
			return clr;
		}
		else if (table == "schedule")
		{
			std::cout << "无法手动添加课程安排信息" << std::endl;
			return nullptr;
		}
		else
		{
			std::cout<<"表名错误"<<std::endl;
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
			std::cout << "添加失败："<< mysql_error(&mysql) << std::endl;
		else
			std::cout << "添加成功" << std::endl;
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
			std::cout << "删除失败：" << mysql_error(&mysql) << std::endl;
		else
			std::cout << "删除成功" << std::endl;
	}
	static void MQuery(MYSQL mysql) {
		MYSQL_RES* res = nullptr;
		std::string sql;
		std::cout<<"输入SQL语句：";
		getline(std::cin, sql);
		mysql_query(&mysql, "set names GBK");
		if (mysql_query(&mysql, sql.c_str()))
		{
			std::cout << "操作失败" << ": " << mysql_error(&mysql) << std::endl;
			return;
		}
		else
		{
			std::cout << "操作成功" << std::endl << std::endl;
			res = mysql_store_result(&mysql);
			if (res != nullptr)
				printResult(res, mysql_num_fields(res));
		}
	}
	static void ReArrangement(MYSQL mysql) {//重新安排课程时间表
		if (mysql_query(&mysql, "delete from schedule"))//清空课程安排
		{
			std::cout << "删除失败：" << mysql_error(&mysql) << std::endl;
			return;
		}
		else
			std::cout << "删除成功" << std::endl;
		std::cout << "重新安排课程......" << std::endl;

		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		MYSQL_ROW row;
		mysql_query(&mysql, "set names GBK");

		std::vector<CourseRow> courses;//课程表
		std::vector<ClassroomRow> classrooms;//教室表
		std::vector<ScheduleRow> schedules;//课程安排表
		std::string starttime[4] = { "08:00:00", "09:55:00", "13:30:00", "15:05:00" };
		std::string endtime[4] = { "09:35:00", "11:30:00", "15:05:00", "17:00:00" };

		mysql_query(&mysql, "select * from course");
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))//获取课程信息
			courses.push_back(CourseRow(atoi(row[0]), std::string(row[1]), atoi(row[2]), atoi(row[3])));

		mysql_query(&mysql, "select * from classroom");
		res = mysql_store_result(&mysql);
		while(row = mysql_fetch_row(res))//获取教室信息
			classrooms.push_back(ClassroomRow(atoi(row[0]), atoi(row[1]), std::string(row[2])));
		std::sort(classrooms.begin(), classrooms.end(), &ClassroomRow::compare);//按教室容量排序

		for (int i = 0; i < courses.size(); i++)
		{
			for (int j = 0; j < classrooms.size(); j++)
			{
				if (courses[i].Capacity == classrooms[j].Capacity)//对大小合适的教室安排课程
				{
					for (int day = 0; day < 5; day++)//一周5天
					{
						for (int time = 0; time < 4; time++) {//每天4个时间段
							if (classrooms[j].sparetime[day][time] == 0)//空闲时间段
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
				else if(courses[i].Capacity < classrooms[j].Capacity)//再安排课程容量小于教室容量的课程
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
				std::cout << "课程" << courses[i].CourseName << "没有合适的教室" << std::endl;

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
				std::cout << "添加失败：" << mysql_error(&mysql) << std::endl;
				return;
			}
		}
		std::cout << "全部添加成功" << std::endl;
	}
};