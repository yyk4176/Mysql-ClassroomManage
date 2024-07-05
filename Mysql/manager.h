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
	static void ManagerAct(MYSQL mysql) {
		std::string input;
		while (1)
		{
			std::cout << "1.添加数据" << std::endl;
			std::cout << "2.删除数据" << std::endl;
			std::cout << "3.查询数据" << std::endl;
			std::cout << "4.修改数据" << std::endl;
			std::cout << "5.高级SQL查询" << std::endl;
			std::cout << "6.重新安排课程" << std::endl;
			std::cout << "7.退出" << std::endl;
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
				MDelete(mysql);
			}
			else if (input == "3")
			{
				MSearch(mysql);
			}
			else if(input == "4")
			{
				MAlter(mysql);
			}
			else if (input == "5")
			{
				MQuery(mysql);
			}
			else if (input == "6")
			{
				ReArrangement(mysql);
			}
			else if (input == "7")
				break;
			else
				std::cout << "输入错误" << std::endl;
		}
	}

private:
	static void MAlter(MYSQL mysql)
	{
		std::vector<TableEntity*>* table = MSearch(mysql);
		std::string tablename = (*table)[0]->TableName;
		if (table->size() == 1)
		{
			if (tablename == "teacher")
			{
				std::string input;
				std::cout << "1.修改教师姓名" << std::endl;
				std::cout << "2.修改教师职称" << std::endl;
				std::cout << "3.退出" << std::endl;
				std::cout << "请选择操作：";
				std::cin >> input;
				if (input == "1")
				{
					std::string name;
					std::cout << "请输入新的教师姓名：";
					std::cin >> name;
					std::string sql = "update teacher set Name='";
					sql += name;
					sql += "' where TeacherID=";
					sql += std::to_string(((TeacherRow*)(*table)[0])->TeacherID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "2")
				{
					std::string title;
					std::cout << "请输入新的教师职称：";
					std::cin >> title;
					std::string sql = "update teacher set Title='";
					sql += title;
					sql += "' where TeacherID=";
					sql += std::to_string(((TeacherRow*)(*table)[0])->TeacherID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "3")
					return;
				else
					std::cout << "输入错误" << std::endl;
			}
			else if (tablename == "course")
			{
				std::string input;
				std::cout << "1.修改课程名称" << std::endl;
				std::cout << "2.修改课程容量" << std::endl;
				std::cout << "3.修改教师ID" << std::endl;
				std::cout << "4.退出" << std::endl;
				std::cout << "请选择操作：";
				std::cin >> input;
				if (input == "1")
				{
					std::string name;
					std::cout << "请输入新的课程名称：";
					std::cin >> name;
					std::string sql = "update course set CourseName='";
					sql += name;
					sql += "' where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "2")
				{
					std::string capacity;
					std::cout << "请输入新的课程容量：";
					std::cin >> capacity;
					std::string sql = "update course set Capacity=";
					sql += capacity;
					sql += " where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "3")
				{
					std::string teacherid;
					std::cout << "请输入新的教师ID：";
					std::cin >> teacherid;
					std::string sql = "update course set TeacherID=";
					sql += teacherid;
					sql += " where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "4")
					return;
				else
					std::cout << "输入错误" << std::endl;
			}
			else if (tablename == "classroom")
			{
				std::string input;
				std::cout << "1.修改教室容量" << std::endl;
				std::cout << "2.修改教室类型" << std::endl;
				std::cout << "3.退出" << std::endl;
				std::cout << "请选择操作：";
				std::cin >> input;
				if (input == "1")
				{
					std::string capacity;
					std::cout << "请输入新的教室容量：";
					std::cin >> capacity;
					std::string sql = "update classroom set Capacity=";
					sql += capacity;
					sql += " where ClassroomID=";
					sql += std::to_string(((ClassroomRow*)(*table)[0])->ClassroomID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "2")
				{
					std::string type;
					std::cout << "请输入新的教室类型：";
					std::cin >> type;
					std::string sql = "update classroom set Type='";
					sql += type;
					sql += "' where ClassroomID=";
					sql += std::to_string(((ClassroomRow*)(*table)[0])->ClassroomID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "3")
					return;
				else
					std::cout << "输入错误" << std::endl;
			}
			else if (tablename == "schedule")
			{
				std::cout<<"1.修改教室ID\n2.修改开始时间\n3.修改结束时间\n4.退出\n请选择操作：";
				std::string input;
				std::cin >> input;
				if (input == "1")
				{
					std::string classroomid;
					std::cout << "请输入新的教室ID：";
					std::cin >> classroomid;
					std::string testsql = "SELECT a.* FROM `schedule` a, `schedule` b WHERE a.ClassroomID = b.ClassroomID AND a.StartTime = b.StartTime AND a.ClassroomID = ";
					testsql += classroomid;
					testsql += " AND a.starttime = '";
					testsql += ((ScheduleRow*)(*table)[0])->StartTime;
					testsql += "'";
					mysql_query(&mysql, testsql.c_str());
					MYSQL_RES* res = mysql_store_result(&mysql);
					if (mysql_num_rows(res) > 0)
					{
						std::cout << "该教室已有课程安排！" << std::endl;
						return;
					}
					std::string sql = "update schedule set ClassroomID=";
					sql += classroomid;
					sql += " where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "2")
				{
					std::string starttime;
					std::string testsql="SELECT a.* FROM `schedule` a, `schedule` b WHERE a.ClassroomID = b.ClassroomID AND a.StartTime = b.StartTime AND a.ClassroomID = ";
					std::cout << "请输入新的开始时间：";
					std::cin >> starttime;
					testsql+= std::to_string(((ScheduleRow*)(*table)[0])->ClassroomID);
					testsql+=" AND a.starttime = '";
					testsql+=starttime;
					testsql+="'";
					mysql_query(&mysql, testsql.c_str());
					MYSQL_RES* res = mysql_store_result(&mysql);
					if (mysql_num_rows(res) > 0)
					{
						std::cout << "该时间该教室已有课程安排！" << std::endl;
						return;
					}
					std::string sql = "update schedule set StartTime='";
					sql += starttime;
					sql += "' where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "3")
				{
					std::string endtime;
					std::string testsql = "SELECT a.* FROM `schedule` a, `schedule` b WHERE a.ClassroomID = b.ClassroomID AND a.StartTime = b.StartTime AND a.ClassroomID = ";
					std::cout << "请输入新的结束时间：";
					std::cin >> endtime;
					testsql += std::to_string(((ScheduleRow*)(*table)[0])->ClassroomID);
					testsql += " AND a.endtime = '";
					testsql += endtime;
					testsql += "'";
					mysql_query(&mysql, testsql.c_str());
					MYSQL_RES* res = mysql_store_result(&mysql);
					if (mysql_num_rows(res) > 0)
					{
						std::cout << "该时间该教室已有课程安排！" << std::endl;
						return;
					}
					std::string sql = "update schedule set EndTime='";
					sql += endtime;
					sql += "' where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "修改失败：" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "修改成功" << std::endl;
				}
				else if (input == "4")
					return;
				else
					std::cout << "输入错误" << std::endl;
			}
			else
			{
				std::cout << "输入错误" << std::endl;
			}
		}
	}

	static std::vector<TableEntity*>* MSearch(MYSQL mysql) {
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
						return new std::vector<TableEntity*>(teacher);
					else
						continue;
				}
				while (1)
				{
					std::cout<<"1.TeacherID\n2.TeacherName\n3.TeacherTitle\n4.确定并退出\n请选择查询方式：";
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
						return new std::vector<TableEntity*>(teacher);
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
						return new std::vector<TableEntity*>(course);
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.CourseID\n2.CourseName\n3.Capacity\n4.TeacherID\n5.确定并退出\n请选择查询方式：";
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
						return new std::vector<TableEntity*>(course);
					else
					{
						std::cout << "输入错误" << std::endl;
						continue;
					}
					if (showTable(result, "course") == 0)
						break;
					course.assign(result.begin(), result.end());
					result.clear();
				}
				break;
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
						return new std::vector<TableEntity*>(classroom);
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.ClassroomID\n2.Capacity\n3.Type\n4.确定并退出\n请选择查询方式：";
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
						return new std::vector<TableEntity*>(classroom);
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
						return new std::vector<TableEntity*>(schedule);
					else
						continue;
				}
				while (1)
				{
					std::cout << "1.ScheduleID\n2.ClassroomID\n3.CourseID\n4.StartTime\n5.EndTime\n6.确定并退出\n请选择查询方式：";
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
						return new std::vector<TableEntity*>(schedule);
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
		return nullptr;
	}

	static int showTable(std::vector<TableEntity*> table, std::string tablename) {
		std::cout << "表名：" << tablename << std::endl;
		if (table.size() == 0)
		{
			std::cout << "没有数据！" << std::endl;
			return 0;
		}
		if (tablename == "teacher")
		{
			std::cout<<std::setw(5)<<"ID"<<std::setw(7)<<"Name"<<std::setw(7)<<"Title"<<std::endl;
		}
		else if(tablename=="course")
		{
			std::cout << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(10) << "Capacity" << std::setw(10) << "TeacherID" << std::endl;
		}
		else if (tablename == "classroom")
		{
			std::cout << std::setw(5) << "ID" << std::setw(10) << "Capacity" << std::setw(10) << "Type" << std::endl;
		}
		else if (tablename == "schedule")
		{
			std::cout << std::setw(3) << "ID" << std::setw(12) << "ClassroomID" << std::setw(10) << "CourseID" << std::setw(20) << "StartTime" << std::setw(20) << "EndTime" << std::endl;
		}
		else
		{
			std::cout << "表名错误" << std::endl;
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

	static void MDelete(MYSQL mysql) {//删除数据
		
		std::vector<TableEntity*>* table = MSearch(mysql);

		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		std::string input;
		showTable(*table, (*table)[0]->TableName);
		std::cout << "是否删除以上数据？(y/n)：";
		std::cin >> input;
		if (input == "y")
		{
			for (auto tbe : *table)
			{
				std::string sql = "delete from ";
				sql += tbe->TableName;
				sql += " where ";
				sql += tbe->TableName;
				sql += "ID";
				sql += " = ";
				sql += std::to_string(tbe->getID());
				if (mysql_query(&mysql, sql.c_str()))
					std::cout << "删除失败：" << mysql_error(&mysql) << std::endl;

			}
		}
		
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