#pragma once
#include "mysql.h"
#include <iostream>
#include "TableData.h"
#include <vector>
#include <string>
#include <algorithm>
struct TableEntity;
struct TeacherRow;
struct CourseRow;
struct ClassroomRow;
struct ScheduleRow;

void printResult(MYSQL_RES* res, int rownum);
class Manager {
public:
	static void ManagerAct(MYSQL mysql) {
		std::string input;
		while (1)
		{
			std::cout << "1.添加数据" << std::endl;
			std::cout << "2.删除数据" << std::endl;
			std::cout << "3.查询数据" << std::endl;
			std::cout << "4.高级SQL查询" << std::endl;
			std::cout << "5.重新安排课程" << std::endl;
			std::cout << "6.退出" << std::endl;
			std::cout << "请选择操作：";
			std::cin >> input;
			if (input == "1")
			{
				TableEntity* tbe = MADD(mysql);
				if (tbe != nullptr)
				{
					std::string input;
					std::cout << "检测到新增课程，是否为其安排教室？(y/n)：";
					std::cin >> input;
					if (input == "y") 
						Arrangement(mysql, tbe);
				}
			}
			else if (input == "2")
			{
				std::string table, ID;
				std::cout << "请输入表名：";
				std::cin >> table;
				std::cout << "请输入ID：";
				std::cin >> ID;
				MDelete(mysql, table, ID);
			}
			else if (input == "3")
			{
				MSearch(mysql);
			}
			else if (input == "4")
			{
				MQuery(mysql);
			}
			else if (input == "5")
			{
				ReArrangement(mysql);
			}
			else if (input == "6")
				break;
			else
				std::cout << "输入错误" << std::endl;
		}
	}

private:
	static void MSearch(MYSQL mysql) {
		std::string input;
		MYSQL_RES* res = nullptr;
		MYSQL_ROW row;
		while (1)
		{
			std::cout << "1.teacher \n2.course \n3.classroom \n4.schedule" << std::endl;
			std::cout << "选择待查询的表：";
			std::cin >> input;
			mysql_query(&mysql, "set names GBK");
			if (input == "1")
			{
				std::vector<TableEntity*> teacher;
				std::vector<TableEntity*> result;
				mysql_query(&mysql, "select * from teacher");
				res = mysql_store_result(&mysql);
				while (row = mysql_fetch_row(res))
					teacher.push_back(new TeacherRow(atoi(row[0]), std::string(row[1]), std::string(row[2])));
				showTable(teacher, "teacher");
				while (1)
				{
					std::cout<<"是否继续查询？(y/n)：";
					std::cin >> input;
					if (input == "y")
						break;
					else if (input == "n")
						return;
					else
						continue;
				}
				while (1)
				{
					std::cout<<"1.TeacherID\n2.TeacherName\n3.TeacherTitle\n4.退出\n请选择查询方式：";
					std::cin >> input;
					if (input == "1")
					{
						std::cout<<"请输入教师ID：";
						std::cin >> input;
						for(auto t : teacher)
						{
							if (((TeacherRow*)t)->TeacherID == atoi(input.c_str()))
								result.push_back(t);
						}
					}
					else if (input == "2")
					{
						std::cout << "请输入教师姓名：";
						std::cin >> input;
						for (auto t : teacher)
						{
							if (((TeacherRow*)t)->Name == input)
								result.push_back(t);
						}
					}
					else if (input == "3")
					{
						std::cout << "请输入教师职称：";
						std::cin >> input;
						for (auto t : teacher)
						{
							if (((TeacherRow*)t)->Title == input)
								result.push_back(t);
						}
					}
					else if (input == "4")
						break;
					else
					{
						std::cout << "输入错误" << std::endl;
						continue;
					}
					if (showTable(result, "teacher") == 0)
						break;
					teacher.assign(result.begin(), result.end());
					result.clear();
				}
				break;
			}
			else if (input == "2")
			{
				mysql_query(&mysql, "select * from course");
				res = mysql_store_result(&mysql);
				std::vector<TableEntity*> course;
				std::vector<TableEntity*> result;
				while (row = mysql_fetch_row(res))
					course.push_back(new CourseRow(atoi(row[0]), std::string(row[1]), atoi(row[2]), atoi(row[3])));
				showTable(course, "course");
				while (1) {
					std::cout << "是否继续查询？(y/n)：";
					std::cin >> input;
					if (input == "y")
						break;
					else if (input == "n")
						return;
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.CourseID\n2.CourseName\n3.Capacity\n4.TeacherID\n5.退出\n请选择查询方式：";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "请输入课程ID：";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->CourseID == atoi(input.c_str()))
								result.push_back(c);
						}
					}
					else if (input == "2")
					{
						std::cout << "请输入课程名称：";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->CourseName == input)
								result.push_back(c);
						}
					}
					else if (input == "3")
					{
						std::cout << "请输入课程容量：";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->Capacity == atoi(input.c_str()))
								result.push_back(c);
						}
					}
					else if (input == "4")
					{
						std::cout << "请输入教师ID：";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->TeacherID == atoi(input.c_str()))
								result.push_back(c);
						}
					}
					else if (input == "5")
						break;
					else
					{
						std::cout << "输入错误" << std::endl;
						continue;
					}
					if (showTable(result, "course") == 0)
						break;
					course.assign(result.begin(), result.end());
					result.clear();
					break;
				}
			}
			else if (input == "3")
			{
				mysql_query(&mysql, "select * from classroom");
				res = mysql_store_result(&mysql);
				std::vector<TableEntity*> classroom;
				std::vector<TableEntity*> result;
				while (row = mysql_fetch_row(res))
					classroom.push_back(new ClassroomRow(atoi(row[0]), atoi(row[1]), std::string(row[2])));
				showTable(classroom, "classroom");
				while (1)
				{
					std::cout << "是否继续查询？(y/n)：";
					std::cin >> input;
					if (input == "y")
						break;
					else if (input == "n")
						return;
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.ClassroomID\n2.Capacity\n3.Type\n4.退出\n请选择查询方式：";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "请输入教室ID：";
						std::cin >> input;
						for (auto cl : classroom)
						{
							if (((ClassroomRow*)cl)->ClassroomID == atoi(input.c_str()))
								result.push_back(cl);
						}
					}
					else if (input == "2")
					{
						std::cout << "请输入教室容量：";
						std::cin >> input;
						for (auto cl : classroom)
						{
							if (((ClassroomRow*)cl)->Capacity == atoi(input.c_str()))
								result.push_back(cl);
						}
					}
					else if (input == "3")
					{
						std::cout << "请输入教室类型：";
						std::cin >> input;
						for (auto cl : classroom)
						{
							if (((ClassroomRow*)cl)->Type == input)
								result.push_back(cl);
						}
					}
					else if (input == "4")
						break;
					else
					{
						std::cout << "输入错误" << std::endl;
						continue;
					}
					if (showTable(result, "classroom") == 0)
						break;
					classroom.assign(result.begin(), result.end());
					result.clear();
				}
				break;
			}
			else if (input == "4")
			{
				mysql_query(&mysql, "select * from schedule");
				res = mysql_store_result(&mysql);
				std::vector<TableEntity*> schedule;
				std::vector<TableEntity*> result;
				while (row = mysql_fetch_row(res))
					schedule.push_back(new ScheduleRow(atoi(row[0]), atoi(row[1]), atoi(row[2]), std::string(row[3]), std::string(row[4])));
				showTable(schedule, "schedule");
				while (1)
				{
					std::cout<<"是否继续查询？(y/n)：";
					std::cin >> input;
					if (input == "y")
						break;
					else if (input == "n")
						return;
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.ScheduleID\n2.ClassroomID\n3.CourseID\n4.StartTime\n5.EndTime\n6.退出\n请选择查询方式：";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "请输入课程安排ID：";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->ScheduleID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "2")
					{
						std::cout << "请输入教室ID：";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->ClassroomID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "3")
					{
						std::cout << "请输入课程ID：";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->CourseID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "4")
					{
						std::cout << "请输入开始时间：";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->StartTime == input)
								result.push_back(s);
						}
					}
					else if (input == "5")
					{
						std::cout << "请输入结束时间：";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->EndTime == input)
								result.push_back(s);
						}
					}
					else if (input == "6")
						break;
					else
					{
						std::cout << "输入错误" << std::endl;
						continue;
					}
					if (showTable(result, "schedule") == 0)
						break;
					schedule.assign(result.begin(), result.end());
					result.clear();
				}
				break;
			}
			else
			{
				std::cout << "输入错误" << std::endl;
				continue;
			}
		}
	}

	static int showTable(std::vector<TableEntity*> table, std::string tablename) {
		std::cout << "表名：" << tablename << std::endl;
		if (table.size() == 0)
		{
			std::cout << "没有数据！" << std::endl;
			return 0;
		}
		for (auto row : table)
		{
			row->printrow();
		}
		std::cout << std::endl;
		return 1;
	}

	static TableEntity* getEntity() {
		std::string table;
		std::cout<< "请输入表名：";
		std::cin >> table;
		std::string temp[5];
		if (table == "teacher")
		{
			std::cout<<"请输入教师ID：";
			std::cin >> temp[0];
			if (atoi(temp[0].c_str()) == 0)
			{
				std::cout << "ID格式错误！" << std::endl;
				return nullptr;
			}
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
			if (atoi(temp[0].c_str()) == 0 || atoi(temp[3].c_str()) == 0)
			{
				std::cout << "ID格式错误！" << std::endl;
				return nullptr;
			}
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
			if (atoi(temp[0].c_str()) == 0)
			{
				std::cout << "ID格式错误！" << std::endl;
			}
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

	static TableEntity* MADD(MYSQL mysql) {//添加数据
		std::string sql = "insert into ";
		std::string tablename;

		TableEntity* tbe = getEntity();
		
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
			return nullptr;
		}
		//std::cout << sql << std::endl;
		if (mysql_query(&mysql, sql.c_str()))
			std::cout << "添加失败："<< mysql_error(&mysql) << std::endl;
		else
			std::cout << "添加成功" << std::endl;
		if (tbe->TableName == "course")
			return tbe;
		else
			delete(tbe);
		return nullptr;
	}

	static void MDelete(MYSQL mysql, std::string table, std::string ID) {//删除数据
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

	static void MQuery(MYSQL mysql) {//查询数据
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

	static void Arrangement(MYSQL mysql, TableEntity* tbe) {//安排一节课程时间
		CourseRow* course = (CourseRow*)tbe;
		std::vector<ClassroomRow> classrooms;
		std::vector<ScheduleRow> schedules;
		std::string starttime[4] = { "08:00:00", "09:55:00", "13:30:00", "15:05:00" };
		std::string endtime[4] = { "09:35:00", "11:30:00", "15:05:00", "17:00:00" };

		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		MYSQL_ROW row;
		mysql_query(&mysql, "set names GBK");
		mysql_query(&mysql, "select * from classroom");
		res = mysql_store_result(&mysql);
		while (row = mysql_fetch_row(res))//获取教室信息
			classrooms.push_back(ClassroomRow(atoi(row[0]), atoi(row[1]), std::string(row[2])));
		std::sort(classrooms.begin(), classrooms.end(), &ClassroomRow::compare);//按教室容量排序

		for (int j = 0; j < classrooms.size(); j++)
		{
			if (course->Capacity == classrooms[j].Capacity)//对大小合适的教室安排课程
			{
				for (int day = 0; day < 5; day++)//一周5天
				{
					for (int time = 0; time < 4; time++) {//每天4个时间段
						if (classrooms[j].sparetime[day][time] == 0)//空闲时间段
						{
							classrooms[j].sparetime[day][time] = 1;
							course->flag = 1;
							schedules.push_back(ScheduleRow(schedules.size() + 1, classrooms[j].ClassroomID, course->CourseID,
								"2024-07-0" + std::to_string(day + 1) + " " + starttime[time], "2024-07-0" + std::to_string(day + 1) + " " + endtime[time]));
							break;
						}
					}
					if (course->flag == 1)
						break;
				}
				if (course->flag == 1)
					break;
			}
			else if (course->Capacity < classrooms[j].Capacity)//再安排课程容量小于教室容量的课程
			{
				for (int day = 0; day < 5; day++)
				{
					for (int time = 0; time < 4; time++) {
						if (classrooms[j].sparetime[day][time] == 0)
						{
							classrooms[j].sparetime[day][time] = 1;
							course->flag = 1;
							schedules.push_back(ScheduleRow(schedules.size() + 1, classrooms[j].ClassroomID, course->CourseID,
								"2024-07-0" + std::to_string(day + 1) + " " + starttime[time], "2024-07-0" + std::to_string(day + 1) + " " + endtime[time]));
							break;
						}
					}
					if (course->flag == 1)
						break;
				}
				if (course->flag == 1)
					break;
			}
		}
		if (course->flag == 0)
		{
			std::cout << "课程" << course->CourseName << "没有合适的教室" << std::endl;
			return;
		}
		std::string sql = "insert into schedule values(";
		sql += std::to_string(schedules[0].ScheduleID);
		sql += ",";
		sql += std::to_string(schedules[0].ClassroomID);
		sql += ",";
		sql += std::to_string(schedules[0].CourseID);
		sql += ",'";
		sql += schedules[0].StartTime;
		sql += "','";
		sql += schedules[0].EndTime;
		sql += "')";
		if (mysql_query(&mysql, sql.c_str()))
		{
			std::cout << "添加失败：" << mysql_error(&mysql) << std::endl;
			return;
		}
		else
			std::cout << "添加成功" << std::endl;

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