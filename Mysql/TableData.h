#pragma once
#include <string>

struct TeacherRow {
	int TeacherID;
	std::string Name;
	std::string Title;
};

struct CourseRow {
	int CourseID;
	std::string CourseName;
	int Capacity;
	int TeacherID;
	int flag = 0;
	CourseRow(int CourseID, std::string CourseName, int Capacity, int TeacherID) : CourseID(CourseID), CourseName(CourseName), Capacity(Capacity), TeacherID(TeacherID) {}
};

struct ClassroomRow {
	int ClassroomID;
	int Capacity;
	std::string Type;
	int sparetime[5][4] = { 0 };
	static bool compare(ClassroomRow& a, ClassroomRow& b) {
		return a.Capacity < b.Capacity;
	}
	ClassroomRow(int ClassroomID, int Capacity, std::string Type) : ClassroomID(ClassroomID), Capacity(Capacity), Type(Type) {}
};

struct ScheduleRow {
	int ScheduleID;
	int ClassroomID;
	int CourseID;
	std::string StartTime;
	std::string EndTime;
	ScheduleRow(int ScheduleID, int ClassroomID, int CourseID, std::string StartTime, std::string EndTime) : ScheduleID(ScheduleID), ClassroomID(ClassroomID), CourseID(CourseID), StartTime(StartTime), EndTime(EndTime) {}
};