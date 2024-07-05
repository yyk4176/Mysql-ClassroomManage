#pragma once
#include <string>
#include <iomanip>	

struct TableEntity {
public:
	std::string TableName;
	int rownum;
	virtual void printrow() = 0;
};

struct TeacherRow :public TableEntity {
public:
	int TeacherID;
	std::string Name;
	std::string Title;
	TeacherRow(int TeacherID, std::string Name, std::string Title)
	{
		TableName = "teacher";
		this->TeacherID = TeacherID;
		this->Name = Name;
		this->Title = Title;
		rownum = 3;
	}
	void printrow() override {
		std::cout << std::setw(5) << TeacherID << std::setw(7) << Name << std::setw(7) << Title << std::endl;
	}
};

struct CourseRow :public TableEntity {
	int CourseID;
	std::string CourseName;
	int Capacity;
	int TeacherID;
	int flag;
	CourseRow(int CourseID, std::string CourseName, int Capacity, int TeacherID)
	{
		TableName = "course";
		this->CourseID = CourseID;
		this->CourseName = CourseName;
		this->Capacity = Capacity;
		this->TeacherID = TeacherID;
		rownum = 4;
		flag = 0;
	}
	void printrow() override {
		std::cout << std::setw(5) << CourseID << std::setw(20) << CourseName << std::setw(5) << Capacity << std::setw(5) << TeacherID << std::endl;
	}
};

struct ClassroomRow :public TableEntity {
	int ClassroomID;
	int Capacity;
	std::string Type;
	int sparetime[5][4] = { 0 };
	static bool compare(ClassroomRow& a, ClassroomRow& b) {
		return a.Capacity < b.Capacity;
	}
	ClassroomRow(int ClassroomID, int Capacity, std::string Type)
	{
		TableName = "classroom";
		this->ClassroomID = ClassroomID;
		this->Capacity = Capacity;
		this->Type = Type;
		rownum = 3;
	}
	void printrow() override {
		std::cout << std::setw(5) << ClassroomID << std::setw(5) << Capacity << std::setw(7) << Type << std::endl;
	}
};

struct ScheduleRow :public TableEntity {
	int ScheduleID;
	int ClassroomID;
	int CourseID;
	std::string StartTime;
	std::string EndTime;
	ScheduleRow(int ScheduleID, int ClassroomID, int CourseID, std::string StartTime, std::string EndTime)
	{
		TableName = "schedule";
		this->ScheduleID = ScheduleID;
		this->ClassroomID = ClassroomID;
		this->CourseID = CourseID;
		this->StartTime = StartTime;
		this->EndTime = EndTime;
		rownum = 5;
	}
	void printrow() override{
		std::cout << std::setw(3) << ScheduleID << std::setw(5) << ClassroomID << std::setw(6) << CourseID << std::setw(20) << StartTime << std::setw(20) << EndTime << std::endl;
	}
};