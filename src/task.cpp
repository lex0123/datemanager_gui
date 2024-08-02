#include "task.h"
#include <iostream>
using namespace std;

string Classifier[]={"    learning   "," entertainment ","      rest     "};
string Priority[]={"       high      ","     medium     ","      low        "};
std::string format_date_time(const tm &A) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) <<A.tm_year << "-"
        << std::setw(2) << A.tm_mon << "-"
        << std::setw(2) << A.tm_mday<< " "
        << std::setw(2) << A.tm_hour << ":"
        << std::setw(2) << A.tm_min;
    return oss.str();
}
std::string format_task_info(const task& task) {
    std::stringstream ss;
    ss << "Don't forget that you need to complete " << task.name << " at ";
    ss << (task.doTime.tm_year) << '-' << (task.doTime.tm_mon) << '-';
    ss << task.doTime.tm_mday << " " << task.doTime.tm_hour << ':';
    ss << task.doTime.tm_min;
    return ss.str();
}
bool isValidTm(const  tm& time) {
    if (time.tm_year < 0) return false; // 年份从1900年开始计算
    if (time.tm_mon < 0 || time.tm_mon > 12) return false; // 月份范围是0-12
    if (time.tm_mday < 1 || time.tm_mday > 31) return false; // 日期范围是1-31
    if (time.tm_hour < 0 || time.tm_hour > 23) return false; // 小时范围是0-23
    if (time.tm_min < 0 || time.tm_min > 59) return false; // 分钟范围是0-59
    // 检查每个月的天数
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int monthDays = daysInMonth[time.tm_mon];

    
    if (time.tm_mon == 1) { 
        int year = time.tm_year + 1900;
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            monthDays = 29;
        }
    }

    if (time.tm_mday > monthDays) return false;
    return true;
}
bool time_equal (const tm &A,const tm &B)
{
    return (A.tm_year == B.tm_year
            &&A.tm_mon == B.tm_mon
            &&A.tm_mday == B.tm_mday
            &&A.tm_hour == B.tm_hour
            &&A.tm_min == B.tm_min);
}
bool time_less(const tm &A,const tm &B)
{
    if (A.tm_year < B.tm_year)return true;
    else if (A.tm_year > B.tm_year)return false;
    if (A.tm_mon < B.tm_mon)return true;
    else if (A.tm_mon > B.tm_mon)return false;
    if (A.tm_mday < B.tm_mday)return true;
    else if (A.tm_mday > B.tm_mday)return false;
    if (A.tm_hour < B.tm_hour)return true;
    else if (A.tm_hour > B.tm_hour)return false;
    if (A.tm_min < B.tm_min)return true;
    else return false;
}
void  sort_do_time(TaskList &List)
{
    sort(List.taskList.begin(), List.taskList.end(), [](const task&A,const task&B){return time_less(A.doTime,B.doTime);});
}
void  sort_notify_time(TaskList &List)
{
    sort(List.taskList.begin(), List.taskList.end(), [](const task&A,const task&B){return time_less(A.notifyTime,B.notifyTime);});
}
void  sort_classify(TaskList &List)
{
    sort(List.taskList.begin(), List.taskList.end(), [](const task&A,const task&B){return A.classify<B.classify;});
}
void  sort_priority(TaskList &List)
{
    sort(List.taskList.begin(), List.taskList.end(), [](const task&A,const task&B){return A.priority<B.priority;});
}
TaskList loadTasks(const  string& filename) {
    ifstream infile(filename);
    
    int n;
    task aTask;
    infile>>n;
    TaskList usertask(n);
    for(int i=0;i<usertask.TaskNum;i++)
    {
        getline(infile, usertask.taskList[i].name);
        getline(infile, usertask.taskList[i].name);
        infile>>usertask.taskList[i].id >>usertask.taskList[i].priority>>usertask.taskList[i].classify;
        infile>>usertask.taskList[i].notifyTime.tm_year>>usertask.taskList[i].notifyTime.tm_mon>>usertask.taskList[i].notifyTime.tm_mday>>usertask.taskList[i].notifyTime.tm_hour>>usertask.taskList[i].notifyTime.tm_min;
        infile>>usertask.taskList[i].doTime.tm_year>>usertask.taskList[i].doTime.tm_mon>>usertask.taskList[i].doTime.tm_mday>>usertask.taskList[i].doTime.tm_hour>>usertask.taskList[i].doTime.tm_min;
    }
    return usertask;
}

void show_tasks(TaskList &List)
{
    int choice;
    cout << "1. Display in chronological order:" <<  endl;
    cout << "2. Display in order by ID:" <<  endl;
    cout << "Enter choice: " <<  endl;
    cin>>choice;
    if(choice==1) {
        sort_do_time(List);
    }
    else if(choice==2){
        sort(List.taskList.begin(), List.taskList.end(), [](const task &task1, const task &task2) {
            return task1.id<task2.id;
        });
    }
    else {
        cout<<"Invalid choice!"<<endl;
        return;
    }
    cout<<"task id |"<<setw(30)<<setfill(' ')<<"task   name        "<<setw(10)<<"|    priority     |"<<setw(10)<<"    classify   |  "<<setw(12)<<"reminder time"<<setw(10)<<"   |     do time      |"<<endl;
    for(int i=0;i<List.TaskNum;i++)
    {
        cout<<List.taskList[i].id<<"       |  "<<setw(25)<<setfill(' ')<< left<<List.taskList[i].name<<"   |"<<Priority[List.taskList[i].priority-1]<<"|"<<Classifier[List.taskList[i].classify-1]<<"|";
        cout<<" "<<List.taskList[i].notifyTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_min<<" |";
        cout<<" "<<List.taskList[i].doTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_min<<" |"<<endl;
    }
}
void  DelTask(TaskList &List,string &filename)
{
    int n;
    cout<<"task id |"<<setw(30)<<setfill(' ')<<"task   name        "<<setw(10)<<"|    priority     |"<<setw(10)<<"    classify   |  "<<setw(12)<<"reminder time"<<setw(10)<<"   |     do time      |"<<endl;
    for(int i=0;i<List.TaskNum;i++)
    {
        cout<<List.taskList[i].id<<"       |  "<<setw(25)<<setfill(' ')<< left<<List.taskList[i].name<<"   |"<<Priority[List.taskList[i].priority-1]<<"|"<<Classifier[List.taskList[i].classify-1]<<"|";
        cout<<" "<<List.taskList[i].notifyTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_min<<" |";
        cout<<" "<<List.taskList[i].doTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_min<<" |"<<endl;
    }
    cout<<"Please input task id:"<<endl;
    cin>>n;
    sort(List.taskList.begin(),List.taskList.end(),[](const task &A,const task &B){return A.id<B.id;});
    if(n>=0&&n<=List.TaskNum)List.taskList.erase(List.taskList.begin()+n-1);
    else {cout<<"Error!Invalid id!";return;}
    List.TaskNum--;
    ofstream  outfile(filename,ofstream::trunc);
    outfile<<List.TaskNum<<endl;
    for(int i=0;i<List.TaskNum;i++)
    {
        if (List.taskList[i].id>n)List.taskList[i].id--;
        outfile<<List.taskList[i].id <<'\t'<< List.taskList[i].name<<'\t'<<List.taskList[i].priority<<'\t'<<List.taskList[i].classify<<endl;
        outfile<<List.taskList[i].notifyTime.tm_year<<'\t'<<List.taskList[i].notifyTime.tm_mon<<'\t';
        outfile<<List.taskList[i].notifyTime.tm_mday<<'\t'<<List.taskList[i].notifyTime.tm_hour<<'\t';
        outfile<<List.taskList[i].notifyTime.tm_min<<endl;
        outfile<<List.taskList[i].doTime.tm_year<<'\t'<<List.taskList[i].doTime.tm_mon<<'\t'<<List.taskList[i].doTime.tm_mday<<'\t';
        outfile<<List.taskList[i].doTime.tm_hour<<'\t'<<List.taskList[i].doTime.tm_min<<endl;
    }
    cout<<"Your task has been deleted and the task id has changed, please recheck"<<endl;
    cout<<"task id |"<<setw(30)<<setfill(' ')<<"task   name        "<<setw(10)<<"|    priority     |"<<setw(10)<<"    classify   |  "<<setw(12)<<"reminder time"<<setw(10)<<"   |     do time      |"<<endl;
    for(int i=0;i<List.TaskNum;i++)
    {
        cout<<List.taskList[i].id<<"       |  "<<setw(25)<<setfill(' ')<< left<<List.taskList[i].name<<"   |"<<Priority[List.taskList[i].priority-1]<<"|"<<Classifier[List.taskList[i].classify-1]<<"|";
        cout<<" "<<List.taskList[i].notifyTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].notifyTime.tm_min<<" |";
        cout<<" "<<List.taskList[i].doTime.tm_year<<"-"<< setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mon<<"-"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_mday<<' '<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_hour<<":"<<  setw(2)<<setfill('0')<<right<<List.taskList[i].doTime.tm_min<<" |"<<endl;
    }
    outfile.close();
}


