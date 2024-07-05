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
			std::cout << "1.�������" << std::endl;
			std::cout << "2.ɾ������" << std::endl;
			std::cout << "3.��ѯ����" << std::endl;
			std::cout << "4.�޸�����" << std::endl;
			std::cout << "5.�߼�SQL��ѯ" << std::endl;
			std::cout << "6.���°��ſγ�" << std::endl;
			std::cout << "7.�˳�" << std::endl;
			std::cout << "��ѡ�������";
			std::cin >> input;
			if (input == "1")
			{
				TableEntity* tbe = MADD(mysql);
				if (tbe != nullptr)
				{
					std::string input;
					std::cout << "��⵽�����γ̣��Ƿ�Ϊ�䰲�Ž��ң�(y/n)��";
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
				std::cout << "�������" << std::endl;
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
				std::cout << "1.�޸Ľ�ʦ����" << std::endl;
				std::cout << "2.�޸Ľ�ʦְ��" << std::endl;
				std::cout << "3.�˳�" << std::endl;
				std::cout << "��ѡ�������";
				std::cin >> input;
				if (input == "1")
				{
					std::string name;
					std::cout << "�������µĽ�ʦ������";
					std::cin >> name;
					std::string sql = "update teacher set Name='";
					sql += name;
					sql += "' where TeacherID=";
					sql += std::to_string(((TeacherRow*)(*table)[0])->TeacherID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "2")
				{
					std::string title;
					std::cout << "�������µĽ�ʦְ�ƣ�";
					std::cin >> title;
					std::string sql = "update teacher set Title='";
					sql += title;
					sql += "' where TeacherID=";
					sql += std::to_string(((TeacherRow*)(*table)[0])->TeacherID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "3")
					return;
				else
					std::cout << "�������" << std::endl;
			}
			else if (tablename == "course")
			{
				std::string input;
				std::cout << "1.�޸Ŀγ�����" << std::endl;
				std::cout << "2.�޸Ŀγ�����" << std::endl;
				std::cout << "3.�޸Ľ�ʦID" << std::endl;
				std::cout << "4.�˳�" << std::endl;
				std::cout << "��ѡ�������";
				std::cin >> input;
				if (input == "1")
				{
					std::string name;
					std::cout << "�������µĿγ����ƣ�";
					std::cin >> name;
					std::string sql = "update course set CourseName='";
					sql += name;
					sql += "' where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "2")
				{
					std::string capacity;
					std::cout << "�������µĿγ�������";
					std::cin >> capacity;
					std::string sql = "update course set Capacity=";
					sql += capacity;
					sql += " where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "3")
				{
					std::string teacherid;
					std::cout << "�������µĽ�ʦID��";
					std::cin >> teacherid;
					std::string sql = "update course set TeacherID=";
					sql += teacherid;
					sql += " where CourseID=";
					sql += std::to_string(((CourseRow*)(*table)[0])->CourseID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "4")
					return;
				else
					std::cout << "�������" << std::endl;
			}
			else if (tablename == "classroom")
			{
				std::string input;
				std::cout << "1.�޸Ľ�������" << std::endl;
				std::cout << "2.�޸Ľ�������" << std::endl;
				std::cout << "3.�˳�" << std::endl;
				std::cout << "��ѡ�������";
				std::cin >> input;
				if (input == "1")
				{
					std::string capacity;
					std::cout << "�������µĽ���������";
					std::cin >> capacity;
					std::string sql = "update classroom set Capacity=";
					sql += capacity;
					sql += " where ClassroomID=";
					sql += std::to_string(((ClassroomRow*)(*table)[0])->ClassroomID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "2")
				{
					std::string type;
					std::cout << "�������µĽ������ͣ�";
					std::cin >> type;
					std::string sql = "update classroom set Type='";
					sql += type;
					sql += "' where ClassroomID=";
					sql += std::to_string(((ClassroomRow*)(*table)[0])->ClassroomID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "3")
					return;
				else
					std::cout << "�������" << std::endl;
			}
			else if (tablename == "schedule")
			{
				std::cout<<"1.�޸Ľ���ID\n2.�޸Ŀ�ʼʱ��\n3.�޸Ľ���ʱ��\n4.�˳�\n��ѡ�������";
				std::string input;
				std::cin >> input;
				if (input == "1")
				{
					std::string classroomid;
					std::cout << "�������µĽ���ID��";
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
						std::cout << "�ý������пγ̰��ţ�" << std::endl;
						return;
					}
					std::string sql = "update schedule set ClassroomID=";
					sql += classroomid;
					sql += " where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "2")
				{
					std::string starttime;
					std::string testsql="SELECT a.* FROM `schedule` a, `schedule` b WHERE a.ClassroomID = b.ClassroomID AND a.StartTime = b.StartTime AND a.ClassroomID = ";
					std::cout << "�������µĿ�ʼʱ�䣺";
					std::cin >> starttime;
					testsql+= std::to_string(((ScheduleRow*)(*table)[0])->ClassroomID);
					testsql+=" AND a.starttime = '";
					testsql+=starttime;
					testsql+="'";
					mysql_query(&mysql, testsql.c_str());
					MYSQL_RES* res = mysql_store_result(&mysql);
					if (mysql_num_rows(res) > 0)
					{
						std::cout << "��ʱ��ý������пγ̰��ţ�" << std::endl;
						return;
					}
					std::string sql = "update schedule set StartTime='";
					sql += starttime;
					sql += "' where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "3")
				{
					std::string endtime;
					std::string testsql = "SELECT a.* FROM `schedule` a, `schedule` b WHERE a.ClassroomID = b.ClassroomID AND a.StartTime = b.StartTime AND a.ClassroomID = ";
					std::cout << "�������µĽ���ʱ�䣺";
					std::cin >> endtime;
					testsql += std::to_string(((ScheduleRow*)(*table)[0])->ClassroomID);
					testsql += " AND a.endtime = '";
					testsql += endtime;
					testsql += "'";
					mysql_query(&mysql, testsql.c_str());
					MYSQL_RES* res = mysql_store_result(&mysql);
					if (mysql_num_rows(res) > 0)
					{
						std::cout << "��ʱ��ý������пγ̰��ţ�" << std::endl;
						return;
					}
					std::string sql = "update schedule set EndTime='";
					sql += endtime;
					sql += "' where ScheduleID=";
					sql += std::to_string(((ScheduleRow*)(*table)[0])->ScheduleID);
					if (mysql_query(&mysql, sql.c_str()))
						std::cout << "�޸�ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
					else
						std::cout << "�޸ĳɹ�" << std::endl;
				}
				else if (input == "4")
					return;
				else
					std::cout << "�������" << std::endl;
			}
			else
			{
				std::cout << "�������" << std::endl;
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
			std::cout << "ѡ�����ѯ�ı�";
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
					std::cout<<"�Ƿ������ѯ��(y/n)��";
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
					std::cout<<"1.TeacherID\n2.TeacherName\n3.TeacherTitle\n4.ȷ�����˳�\n��ѡ���ѯ��ʽ��";
					std::cin >> input;
					if (input == "1")
					{
						std::cout<<"�������ʦID��";
						std::cin >> input;
						for(auto t : teacher)
						{
							if (((TeacherRow*)t)->TeacherID == atoi(input.c_str()))
								result.push_back(t);
						}
					}
					else if (input == "2")
					{
						std::cout << "�������ʦ������";
						std::cin >> input;
						for (auto t : teacher)
						{
							if (((TeacherRow*)t)->Name == input)
								result.push_back(t);
						}
					}
					else if (input == "3")
					{
						std::cout << "�������ʦְ�ƣ�";
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
						std::cout << "�������" << std::endl;
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
					std::cout << "�Ƿ������ѯ��(y/n)��";
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
					std::cout << "1.CourseID\n2.CourseName\n3.Capacity\n4.TeacherID\n5.ȷ�����˳�\n��ѡ���ѯ��ʽ��";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "������γ�ID��";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->CourseID == atoi(input.c_str()))
								result.push_back(c);
						}
					}
					else if (input == "2")
					{
						std::cout << "������γ����ƣ�";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->CourseName == input)
								result.push_back(c);
						}
					}
					else if (input == "3")
					{
						std::cout << "������γ�������";
						std::cin >> input;
						for (auto c : course)
						{
							if (((CourseRow*)c)->Capacity == atoi(input.c_str()))
								result.push_back(c);
						}
					}
					else if (input == "4")
					{
						std::cout << "�������ʦID��";
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
						std::cout << "�������" << std::endl;
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
					std::cout << "�Ƿ������ѯ��(y/n)��";
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
					std::cout << "1.ClassroomID\n2.Capacity\n3.Type\n4.ȷ�����˳�\n��ѡ���ѯ��ʽ��";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "���������ID��";
						std::cin >> input;
						for (auto cl : classroom)
						{
							if (((ClassroomRow*)cl)->ClassroomID == atoi(input.c_str()))
								result.push_back(cl);
						}
					}
					else if (input == "2")
					{
						std::cout << "���������������";
						std::cin >> input;
						for (auto cl : classroom)
						{
							if (((ClassroomRow*)cl)->Capacity == atoi(input.c_str()))
								result.push_back(cl);
						}
					}
					else if (input == "3")
					{
						std::cout << "������������ͣ�";
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
						std::cout << "�������" << std::endl;
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
					std::cout<<"�Ƿ������ѯ��(y/n)��";
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
					std::cout << "1.ScheduleID\n2.ClassroomID\n3.CourseID\n4.StartTime\n5.EndTime\n6.ȷ�����˳�\n��ѡ���ѯ��ʽ��";
					std::cin >> input;
					if (input == "1")
					{
						std::cout << "������γ̰���ID��";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->ScheduleID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "2")
					{
						std::cout << "���������ID��";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->ClassroomID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "3")
					{
						std::cout << "������γ�ID��";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->CourseID == atoi(input.c_str()))
								result.push_back(s);
						}
					}
					else if (input == "4")
					{
						std::cout << "�����뿪ʼʱ�䣺";
						std::cin >> input;
						for (auto s : schedule)
						{
							if (((ScheduleRow*)s)->StartTime == input)
								result.push_back(s);
						}
					}
					else if (input == "5")
					{
						std::cout << "���������ʱ�䣺";
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
						std::cout << "�������" << std::endl;
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
				std::cout << "�������" << std::endl;
				continue;
			}
		}
		return nullptr;
	}

	static int showTable(std::vector<TableEntity*> table, std::string tablename) {
		std::cout << "������" << tablename << std::endl;
		if (table.size() == 0)
		{
			std::cout << "û�����ݣ�" << std::endl;
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
			std::cout << "��������" << std::endl;
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
		std::cout<< "�����������";
		std::cin >> table;
		std::string temp[5];
		if (table == "teacher")
		{
			std::cout<<"�������ʦID��";
			std::cin >> temp[0];
			if (atoi(temp[0].c_str()) == 0)
			{
				std::cout << "ID��ʽ����" << std::endl;
				return nullptr;
			}
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
			if (atoi(temp[0].c_str()) == 0 || atoi(temp[3].c_str()) == 0)
			{
				std::cout << "ID��ʽ����" << std::endl;
				return nullptr;
			}
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
			if (atoi(temp[0].c_str()) == 0)
			{
				std::cout << "ID��ʽ����" << std::endl;
			}
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

	static TableEntity* MADD(MYSQL mysql) {//�������
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
			std::cout << "���ʧ�ܣ�"<< mysql_error(&mysql) << std::endl;
		else
			std::cout << "��ӳɹ�" << std::endl;
		if (tbe->TableName == "course")
			return tbe;
		else
			delete(tbe);
		return nullptr;
	}

	static void MDelete(MYSQL mysql) {//ɾ������
		
		std::vector<TableEntity*>* table = MSearch(mysql);

		MYSQL_RES* res = nullptr;
		MYSQL_FIELD* field = nullptr;
		std::string input;
		showTable(*table, (*table)[0]->TableName);
		std::cout << "�Ƿ�ɾ���������ݣ�(y/n)��";
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
					std::cout << "ɾ��ʧ�ܣ�" << mysql_error(&mysql) << std::endl;

			}
		}
		
	}

	static void MQuery(MYSQL mysql) {//��ѯ����
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

	static void Arrangement(MYSQL mysql, TableEntity* tbe) {//����һ�ڿγ�ʱ��
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
		while (row = mysql_fetch_row(res))//��ȡ������Ϣ
			classrooms.push_back(ClassroomRow(atoi(row[0]), atoi(row[1]), std::string(row[2])));
		std::sort(classrooms.begin(), classrooms.end(), &ClassroomRow::compare);//��������������

		for (int j = 0; j < classrooms.size(); j++)
		{
			if (course->Capacity == classrooms[j].Capacity)//�Դ�С���ʵĽ��Ұ��ſγ�
			{
				for (int day = 0; day < 5; day++)//һ��5��
				{
					for (int time = 0; time < 4; time++) {//ÿ��4��ʱ���
						if (classrooms[j].sparetime[day][time] == 0)//����ʱ���
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
			else if (course->Capacity < classrooms[j].Capacity)//�ٰ��ſγ�����С�ڽ��������Ŀγ�
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
			std::cout << "�γ�" << course->CourseName << "û�к��ʵĽ���" << std::endl;
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
			std::cout << "���ʧ�ܣ�" << mysql_error(&mysql) << std::endl;
			return;
		}
		else
			std::cout << "��ӳɹ�" << std::endl;

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