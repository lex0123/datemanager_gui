#include "gui.h"
#include "user.h"
#include "task.h"
#include <cstdlib> 
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int newTask(const  std::string& filename,const task& atask)
{
    task aTask=atask;
    TaskList check=loadTasks(filename);
    for(int i=0;i<check.TaskNum;i++)
    {
        if (check.taskList[i].name==aTask.name)
        return 1;
    };
    if (!isValidTm(aTask.notifyTime)) {
        return 2;
    };
    for(int i=0;i<check.TaskNum;i++) {
        if (time_equal(aTask.doTime,check.taskList[i].doTime)) {
            std::cout << "You have a task to handle during this time period,the task's name is" <<' '<<check.taskList[i].name
                 << std::endl;
            return 3;
        }
    }
    if (!isValidTm(aTask.doTime)) {
        std::cerr << "Invalid do time format." << std::endl;
        return 4;
    }
    // 打开文件进行读写
    std::fstream file(filename,std::ios::in|std::ios::out);
    if (!file) {
        std::cerr << "Unable to open the file: " << filename <<  std::endl;
        return 5;
    }
    TaskList list=loadTasks(filename);
    list.TaskNum++;
    aTask.id=list.TaskNum;
    list.taskList.push_back(aTask);
    std::ofstream  outfile(filename,std::ofstream::trunc);
    pthread_mutex_lock( &mutex);
    outfile<<list.TaskNum<<std::endl;
    for(int i=0;i<list.TaskNum;i++)
    {
        outfile<<list.taskList[i].name<<std::endl;
        outfile<<list.taskList[i].id <<'\t'<<list.taskList[i].priority<<'\t'<<list.taskList[i].classify<<std::endl;
        outfile<<list.taskList[i].notifyTime.tm_year<<'\t'<<list.taskList[i].notifyTime.tm_mon<<'\t';
        outfile<<list.taskList[i].notifyTime.tm_mday<<'\t'<<list.taskList[i].notifyTime.tm_hour<<'\t';
        outfile<<list.taskList[i].notifyTime.tm_min<<std::endl;
        outfile<<list.taskList[i].doTime.tm_year<<'\t'<<list.taskList[i].doTime.tm_mon<<'\t'<<list.taskList[i].doTime.tm_mday<<'\t';
        outfile<<list.taskList[i].doTime.tm_hour<<'\t'<<list.taskList[i].doTime.tm_min<<std::endl;
    }
    outfile.close();
    pthread_mutex_unlock( &mutex);
    return 0;
}
LoginWindow::LoginWindow(): m_vbox(Gtk::ORIENTATION_VERTICAL,10){
    set_title("Login Window");
    set_default_size(300, 200);
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER);
    m_username_entry.set_placeholder_text("Username");
    m_username_entry.set_size_request(200, 30); // 设置用户名输入框大小
    m_password_entry.set_placeholder_text("Password");
    m_password_entry.set_visibility(false);
    m_password_entry.set_placeholder_text("Password");
    m_password_entry.set_visibility(false);
    m_password_entry.set_size_request(200, 30); // 设置密码输入框大小
    m_login_button.set_label("Login");
    m_login_button.signal_clicked().connect(sigc::mem_fun(*this, &LoginWindow::on_login_clicked));
    m_vbox.pack_start(m_username_entry, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_password_entry, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_login_button,Gtk::PACK_SHRINK);
    add(m_vbox);
    show_all_children();
}

void LoginWindow::on_login_clicked() {
    std::string username= m_username_entry.get_text() ;
    std::string password= m_password_entry.get_text() ;
    std::string fileName="user.txt";
    if (loginUser(fileName,username,password))
    {
        show_message("Login successful!");
         MyTask *task=new MyTask(username);
         task->show_all();
    }
    else 
    {
        show_message("Invalid username or password!");
        m_password_entry.set_text("");
        m_username_entry.set_text("");
    }

}
void RegisterWindow::show_message(const Glib::ustring &message) {
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}
void LoginWindow::show_message(const Glib::ustring &message) {
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}
RegisterWindow::RegisterWindow() :m_vbox(Gtk::ORIENTATION_VERTICAL,10){
    set_title("Register Window");
    set_default_size(300, 250);
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER);
    

    m_username_entry.set_placeholder_text("Username");
    m_password_entry.set_placeholder_text("Password");
    m_password_entry.set_visibility(false);
    m_confirm_password_entry.set_placeholder_text("Confirm Password");
    m_confirm_password_entry.set_visibility(false);

    m_register_button.set_label("Register");
    m_register_button.signal_clicked().connect(sigc::mem_fun(*this, &RegisterWindow::on_register_clicked));

    m_vbox.pack_start(m_username_entry, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_password_entry, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_confirm_password_entry, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_register_button, Gtk::PACK_SHRINK);

    add(m_vbox);
    show_all_children();
}

void RegisterWindow::on_register_clicked() {
    if (m_password_entry.get_text() == m_confirm_password_entry.get_text()) {
        
        std::string username=m_username_entry.get_text();
        std::string password=m_password_entry.get_text();
        std::string fileName="user.txt";
        if (username==""){show_message("Invalid name!");return;}
        int m=registerUser(fileName,username,password);
        if(m==1){
            m_username_entry.set_text("");
            m_password_entry.set_text("");
            m_confirm_password_entry.set_text("");
            show_message("The username already exists,Please input again!");
        }
        else if (m==2)
        {
            m_password_entry.set_text("");
            m_confirm_password_entry.set_text("");
            show_message("Error! The size of password must be greater than 4\n Please input password again");
        }
        else if (m==0)
        {
            show_message("Register successful!");
            close();
            
        }
    } else {
        show_message("Passwords don't match.");
    }
}

WelcomeScreen::WelcomeScreen() :m_vbox(Gtk::ORIENTATION_VERTICAL,10) {
    set_title("welcome");
    set_default_size(300, 200);
    set_border_width(10);
    set_position(Gtk::WIN_POS_CENTER);

    m_login_button.set_label("Login");
    m_login_button.set_size_request(200,50);
    m_register_button.set_label("Register");
    m_register_button.set_size_request(200,50);


    m_login_button.signal_clicked().connect(sigc::mem_fun(*this, &WelcomeScreen::on_login_clicked));
    m_register_button.signal_clicked().connect(sigc::mem_fun(*this, &WelcomeScreen::on_register_clicked));
    m_vbox.pack_start(m_login_button, Gtk::PACK_SHRINK);
    m_vbox.pack_start(m_register_button, Gtk::PACK_SHRINK);

    add(m_vbox);
    show_all_children();
}
void WelcomeScreen::on_login_clicked() {
    
    LoginWindow *login_window = new LoginWindow();
    login_window->show_all();
  
}

void WelcomeScreen::on_register_clicked() {

    RegisterWindow *register_window = new RegisterWindow();
    register_window->show_all();
    
}

MyTask::MyTask(std::string username):file(username){
        running=true;
        dispatcher.connect([this]() {

        this->show_message(this->message);
        });
        list=loadTasks(file);
        m_thread=std::thread(std::bind(&MyTask::CheckReminders, this));
        set_title("Task List");
        set_position(Gtk::WIN_POS_CENTER);
        Glib::ustring remindertime;
        Glib::ustring dotime;
        refTreeModel = Gtk::ListStore::create(columns);
        treeView.set_model(refTreeModel);
        Glib::ustring s[7]={"s","Task ID","Task Name","Reminder Time","Due Time","Classify","Priority"};
        treeView.append_column(s[1], columns.task_id);
        treeView.append_column(s[2], columns.task_name);
        treeView.append_column(s[3], columns.reminder_time);
        treeView.append_column(s[4], columns.due_time);
        treeView.append_column(s[5], columns.classify);
        treeView.append_column(s[6], columns.priority);

        auto* col_task_id = treeView.get_column(0);
        if (col_task_id) {
            col_task_id->set_min_width(100);
            col_task_id->set_spacing(10);
        }

        auto* col_task_name = treeView.get_column(1);
        if (col_task_name) {
            col_task_name->set_min_width(200);
            col_task_name->set_spacing(10);
        }

        auto* col_reminder_time = treeView.get_column(2);
        if (col_reminder_time) {
            col_reminder_time->set_min_width(200);
            col_reminder_time->set_spacing(10);
        }

        auto* col_due_time = treeView.get_column(3);
        if (col_due_time) {
            col_due_time->set_min_width(200);
            col_due_time->set_spacing(10);
        }

        auto* col_classify = treeView.get_column(4);
        if (col_classify) {
            col_classify->set_min_width(125);
            col_classify->set_spacing(10);
        }

        auto* col_priority = treeView.get_column(5);
        if (col_priority) {
            col_priority->set_min_width(125);
            col_priority->set_spacing(10);
        }
        for (int i = 0; i <list.TaskNum; ++i) {
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
                 attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
    }
    
        // 创建按钮
        show_sort_button.set_label("Sort");
        add_task_button.set_label("Add task");
        delte_task_button.set_label("delte task");
        show_all_task_button.set_label("Refresh");
        show_unfinished_work_button.set_label("Show upcoming work");
        show_overdue_work_button.set_label("Show overdue work");
        add_task_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::add_Task));
        delte_task_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::del_Task));
        show_unfinished_work_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::show_unfinish_work));
        show_all_task_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::show_all_task));
        show_overdue_work_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::show_overdue_work));
        show_sort_button.signal_clicked().connect(sigc::mem_fun(*this, &MyTask::show_sort));
        // 将按钮添加到按钮容器中
        buttonBox.pack_start(add_task_button);
        buttonBox.pack_start(delte_task_button);
        buttonBox.pack_start(show_all_task_button);
        buttonBox.pack_start(show_unfinished_work_button);
        buttonBox.pack_start(show_overdue_work_button);
        buttonBox.pack_start(show_sort_button);
        // 将 TreeView 添加到滚动窗口
        scrolledWindow.add(treeView);
        scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        for (int year = 2000; year <= 2048; ++year) {
            combo_year.append(std::to_string(year));
        }
        combo_year.set_active(24);
        combo_year.signal_changed().connect(sigc::mem_fun(*this, &MyTask::on_combo_changed));

        for (int month = 1; month <= 12; ++month) {
            combo_month.append(Glib::ustring::format(std::setw(2), std::setfill(L'0'), month));
        }
        combo_month.signal_changed().connect(sigc::mem_fun(*this, &MyTask::on_combo_changed));
        combo_year.set_active(6);
        // 创建日历控件并连接信号
        calendar.signal_day_selected().connect(sigc::mem_fun(*this, &MyTask::on_calendar_day_selected));

        // 创建一个水平布局容器，将下拉选择框添加到该布局中
        hbox.pack_start(combo_year, Gtk::PACK_SHRINK);
        hbox.pack_start(combo_month, Gtk::PACK_SHRINK);
    

        // 创建一个垂直布局容器，将下拉选择框容器、日历、滚动窗口和按钮容器添加到该布局中
        vbox.pack_start(hbox, Gtk::PACK_SHRINK);
        vbox.pack_start(calendar, Gtk::PACK_SHRINK);
        vbox.pack_start(scrolledWindow);
        vbox.pack_start(buttonBox, Gtk::PACK_SHRINK);

        // 添加垂直布局容器到窗口并显示
        add(vbox);
        show_all_children();
    }
void  MyTask::show_message(const Glib::ustring &message) {
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}
void MyTask::CheckReminders() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        pthread_mutex_lock( &mutex);
        TaskList List= loadTasks(file);   
        pthread_mutex_unlock( &mutex);
        sort_notify_time(List);
        std::time_t currentTime = std::time(nullptr);
        std::tm* localTime = std::localtime(&currentTime);
        int i=0;
        tm givenTime = {};
        for (;i<List.TaskNum;i++)
        {
            givenTime.tm_year = List.taskList[i].notifyTime.tm_year-1900; // 年份从1900开始
            givenTime.tm_mon = List.taskList[i].notifyTime.tm_mon-1;            // 0-based, 7月是6
            givenTime.tm_mday = List.taskList[i].notifyTime.tm_mday;          // 日期
            givenTime.tm_hour = List.taskList[i].notifyTime.tm_hour;
            givenTime.tm_min = List.taskList[i].notifyTime.tm_min;           // 分钟
            if (time_less(givenTime,*localTime)) {
                i++;
            } else if (time_equal(givenTime,*localTime)) 
            {
                message=format_task_info(List.taskList[i]);
               
                dispatcher.emit();
                std::this_thread::sleep_for(std::chrono::seconds(30));
            }
        }
    }
}
void MyTask::on_calendar_day_selected() {
        guint year, month, day;
        calendar.get_date(year, month, day);
        combo_year.set_active_text(std::to_string(year));
        combo_month.set_active_text(Glib::ustring::format(std::setfill(L'0'), std::setw(2), month + 1));
        show_task_day(year,month,day);
    }
void  MyTask::on_combo_changed() {
        Glib::ustring selected_year = combo_year.get_active_text();
        Glib::ustring selected_month = combo_month.get_active_text();
        if (selected_year.empty() || selected_month.empty()) {
            return;
        }
        guint year=std::stoi(selected_year), month=std::stoi(selected_month)-1, day=1;
        calendar.select_month(month,year);
        calendar.select_day(day);
        show_task_day(year,month,day);
    }
void MyTask::show_task_day(int year,int month,int day)
{
    sort_do_time(list);
    refTreeModel->clear();
    Glib::ustring remindertime;
    Glib::ustring dotime;
    for (int i = 0; i <list.TaskNum; ++i) {
        if((list.taskList[i].doTime.tm_year==year)
        &&(list.taskList[i].doTime.tm_mon==(month+1))
        &&(list.taskList[i].doTime.tm_mday==day)){
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
                 attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
        }        
    }
}

void MyTask::add_task(int id, const Glib::ustring& name,
     const Glib::ustring& reminder, const Glib::ustring& due, 
     const Glib::ustring& attr,const Glib::ustring& priority) {
        Gtk::TreeModel::Row row = *(refTreeModel->append());
        row[columns.task_id] = id;
        row[columns.task_name] = name;
        row[columns.reminder_time] = reminder;
        row[columns.due_time] = due;
        row[columns.classify] = attr;
        row[columns.priority] = priority;
    }
void  MyTask::new_task(const task &atask){

    int m=newTask(file,atask);
    if (m==1){
        show_message("You have a same task!Please modify!");
    }
    if (m==2){
        show_message("Invalid notify time format!Please modify!");
    }
    if (m==3){
        show_message("You have a task to handle at this time!Please modify!");
    }
    if (m==4){
        show_message("You have a same task!Please modify!");
    }
    if (m==5)
    {
        show_message("Unable to load task!Please try again!");
    }
    if (m==0)
    {
    show_message("Add task successful!");
    Glib::ustring remindertime = format_date_time(atask.notifyTime);
    Glib::ustring dotime = format_date_time(atask.doTime);
    add_task(atask.id, atask.name, remindertime, dotime, attribute[atask.classify], priority[atask.priority]);
    }
};

void MyTask::add_Task(){
        TaskDialog dialog(*this);
        dialog.signal_task_created.connect(sigc::mem_fun(*this, &MyTask::new_task));
        int result = dialog.run();
        show_all_task();
    };
void MyTask::del_Task(){
        DeleteTaskDialog dialog(*this,list.TaskNum);
        dialog.signal_task_deleted.connect(sigc::mem_fun(*this, &MyTask::del_task));
        int result =dialog.run();
        show_all_task();
    }
void MyTask::del_task(int id)
{
    sort(list.taskList.begin(),list.taskList.end(),
    [](const task &A,const task &B){return A.id<B.id;});
    if(id>= 1&&id<=list.TaskNum)
    list.taskList.erase(list.taskList.begin()+id-1);
    else show_message("Error!Invalid id!");
    list.TaskNum--;
    std::ofstream  outfile(file,std::ofstream::trunc);
    pthread_mutex_lock( &mutex);
    outfile<<list.TaskNum<<std::endl;
    for(int i=0;i<list.TaskNum;i++)
    {
        outfile<<list.taskList[i].name<<std::endl;
        if (list.taskList[i].id>id)list.taskList[i].id--;
        outfile<<list.taskList[i].id <<'\t'<<list.taskList[i].priority<<'\t'<<list.taskList[i].classify<<std::endl;
        outfile<<list.taskList[i].notifyTime.tm_year<<'\t'<<list.taskList[i].notifyTime.tm_mon<<'\t';
        outfile<<list.taskList[i].notifyTime.tm_mday<<'\t'<<list.taskList[i].notifyTime.tm_hour<<'\t';
        outfile<<list.taskList[i].notifyTime.tm_min<<std::endl;
        outfile<<list.taskList[i].doTime.tm_year<<'\t'<<list.taskList[i].doTime.tm_mon<<'\t'<<list.taskList[i].doTime.tm_mday<<'\t';
        outfile<<list.taskList[i].doTime.tm_hour<<'\t'<<list.taskList[i].doTime.tm_min<<std::endl;
    }
    show_message("Your task has been deleted and the tasks id has changed");
    outfile.close();
    pthread_mutex_unlock( &mutex);

}
void MyTask::show_overdue_work(){
    refTreeModel->clear();
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    std::tm Local=*localTime;
    Glib::ustring remindertime;
    Glib::ustring dotime;
    Local.tm_year+=1900;
    Local.tm_mon+=1;
    sort_do_time(list);
    for (int i = 0; i <list.TaskNum; ++i) {
        if(time_less(list.taskList[i].doTime,Local))
        {
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
                 attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
        }
        else break;
    }
}
void MyTask::show_unfinish_work(){
    refTreeModel->clear();
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    std::tm Local=*localTime;
    Local.tm_year+=1900;
    Local.tm_mon+=1;
    Glib::ustring dotime;
    Glib::ustring remindertime;
    sort_do_time(list);
    for (int i = 0; i <list.TaskNum; ++i) {
        if(time_less(list.taskList[i].doTime,Local)){continue;}
        else 
        {
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
                 attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
        }

    }
}
void MyTask::show_all_task() {
   refTreeModel->clear();

   list = loadTasks(file);

    Glib::ustring remindertime;
    Glib::ustring dotime;
    for (int i = 0; i <list.TaskNum; ++i) {
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
                 attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
    }
};
void MyTask::show_sort()
{
    sortTaskDialog dialog(*this);
    dialog.signal_task_sort.connect(sigc::mem_fun(*this, &MyTask::sort_Task));
    int result =dialog.run();
    refTreeModel->clear();
    Glib::ustring remindertime;
    Glib::ustring dotime;
    for (int i = 0; i <list.TaskNum; ++i) {
        dotime = format_date_time(list.taskList[i].doTime);
        remindertime = format_date_time(list.taskList[i].notifyTime);
        add_task(list.taskList[i].id,list.taskList[i].name, remindertime, dotime,
        attribute[list.taskList[i].classify-1], priority[list.taskList[i].priority-1]);
    }
}
void MyTask::sort_Task(int select)
{
    if (select==0) sort_classify(list);
    else if(select==1)sort_priority(list);
    else if(select==2)sort_do_time(list);
    else if(select==3)sort_notify_time(list);
    else std::sort(list.taskList.begin(), list.taskList.end(), [](const task&A,const task&B)
    {return A.id<B.id;});
}
task TaskDialog::get_task() const {
        task task1;
        task1.name = entry_name.get_text();

        task1.priority = combo_priority.get_active_row_number() + 1;
        task1.classify = combo_classify.get_active_row_number() + 1;
        task1.notifyTime.tm_year = std::stoi(combo_notify_year.get_active_text());
        task1.notifyTime.tm_mon = std::stoi(combo_notify_month.get_active_text());
        task1.notifyTime.tm_mday = std::stoi(combo_notify_day.get_active_text());
        task1.notifyTime.tm_hour = std::stoi(combo_notify_hour.get_active_text());
        task1.notifyTime.tm_min = std::stoi(combo_notify_minute.get_active_text());
        task1.doTime.tm_year = std::stoi(combo_do_year.get_active_text());
        task1.doTime.tm_mon = std::stoi(combo_do_month.get_active_text());
        task1.doTime.tm_mday = std::stoi(combo_do_day.get_active_text());
        task1.doTime.tm_hour = std::stoi(combo_do_hour.get_active_text());
        task1.doTime.tm_min = std::stoi(combo_do_minute.get_active_text());

        return task1;
    }
TaskDialog::TaskDialog(Gtk::Window& parent) :
        Gtk::Dialog("Add Task", parent, true),
        combo_priority(),
        combo_classify(),
        combo_notify_year(),
        combo_notify_month(),
        combo_notify_day(),
        combo_notify_hour(),
        combo_notify_minute(),
        combo_do_year(),
        combo_do_month(),
        combo_do_day(),
        combo_do_hour(),
        combo_do_minute() {
        bool signal_emitted=false;
        set_position(Gtk::WIN_POS_CENTER);
        add_button("Cancel", Gtk::RESPONSE_CANCEL);
        add_button("OK", Gtk::RESPONSE_OK);
        Gtk::Box* content = get_content_area();
        // Task Name
        Gtk::Box* name_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* name_label = Gtk::manage(new Gtk::Label("Task Name:"));
        name_box->pack_start(*name_label, Gtk::PACK_SHRINK);
        name_box->pack_start(entry_name);
        content->pack_start(*name_box, Gtk::PACK_SHRINK);
        // Priority
        Gtk::Box* priority_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* priority_label = Gtk::manage(new Gtk::Label("Priority:"));
        priority_box->pack_start(*priority_label, Gtk::PACK_SHRINK);
        combo_priority.append("High");
        combo_priority.append("Medium");
        combo_priority.append("Low");
        combo_priority.set_active(1);
        priority_box->pack_start(combo_priority);
        content->pack_start(*priority_box, Gtk::PACK_SHRINK);
        // Classify
        Gtk::Box* classify_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* classify_label = Gtk::manage(new Gtk::Label("Classify:"));
        classify_box->pack_start(*classify_label, Gtk::PACK_SHRINK);
        combo_classify.append("Learning");
        combo_classify.append("Entertainment");
        combo_classify.append("Rest");
        combo_classify.set_active(1);
        classify_box->pack_start(combo_classify);
        content->pack_start(*classify_box, Gtk::PACK_SHRINK);

        // Notify Time
        content->pack_start(*create_time_box("Notify Time:", combo_notify_year, combo_notify_month, combo_notify_day, combo_notify_hour, combo_notify_minute), Gtk::PACK_SHRINK);

        // Do Time
        content->pack_start(*create_time_box("Do Time:", combo_do_year, combo_do_month, combo_do_day, combo_do_hour, combo_do_minute), Gtk::PACK_SHRINK);
        
        show_all_children();
        signal_response().connect(sigc::mem_fun(*this, &TaskDialog::on_response));        
    }
void TaskDialog::show_message(const Glib::ustring &message) {
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.run();
}
void TaskDialog::on_response(int response_id) {
        if (response_id == Gtk::RESPONSE_OK&&!signal_emitted) {
            signal_emitted=true;
            task new_task=get_task();
            if (new_task.name==""){show_message("Invalid task name!");return;}
            signal_task_created.emit(new_task);
        }
        close();
    }
Gtk::Box* TaskDialog::create_time_box(const Glib::ustring& label_text, Gtk::ComboBoxText& combo_year, Gtk::ComboBoxText& combo_month, Gtk::ComboBoxText& combo_day, Gtk::ComboBoxText& combo_hour, Gtk::ComboBoxText& combo_minute) {
        Gtk::Box* time_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* label = Gtk::manage(new Gtk::Label(label_text));
        time_box->pack_start(*label, Gtk::PACK_SHRINK);
        // Year
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        for (int year = now->tm_year + 1850; year <= now->tm_year + 1950; ++year) {
            combo_year.append(std::to_string(year));
        }
        combo_year.set_active(50);
        combo_year.signal_changed().connect([this,&combo_year,&combo_month,&combo_day](){
            this->on_combo_year_month_changed(combo_year, combo_month, combo_day);
        });
        time_box->pack_start(combo_year, Gtk::PACK_SHRINK);

        // Month
        for (int month = 1; month <= 12; ++month) {
            combo_month.append(std::to_string(month));
        }
        combo_month.signal_changed().connect([this,&combo_year,&combo_month,&combo_day](){
            this->on_combo_year_month_changed(combo_year, combo_month, combo_day);
        });
        combo_month.set_active(now->tm_mon);
        time_box->pack_start(combo_month, Gtk::PACK_SHRINK);
        time_box->pack_start(combo_day, Gtk::PACK_SHRINK);
        combo_day.set_active(now->tm_mday-1);

        // Hour
        for (int hour = 0; hour <= 23; ++hour) {
            combo_hour.append(std::to_string(hour));
        }
        time_box->pack_start(combo_hour, Gtk::PACK_SHRINK);
        combo_hour.set_active(now->tm_hour);

        // Minute
        for (int minute = 0; minute <= 59; ++minute) {
            combo_minute.append(std::to_string(minute));
        }
        time_box->pack_start(combo_minute, Gtk::PACK_SHRINK);
        combo_minute.set_active(now->tm_min);

        return time_box;
    }
void TaskDialog::on_combo_year_month_changed(Gtk::ComboBoxText& combo_year, Gtk::ComboBoxText& combo_month, Gtk::ComboBoxText& combo_day)
{
    Glib::ustring selected_year = combo_year.get_active_text();
    Glib::ustring selected_month = combo_month.get_active_text();
        if (selected_year.empty() || selected_month.empty()) {
            return;
        }
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int month =  std::stoi(combo_month.get_active_text())-1;
    int day =daysInMonth[month];
    int year=std::stoi(combo_year.get_active_text());
    if (month == 1) { 
        if ((year % 4 == 0 && year % 100 != 0) ||(year % 400 == 0)) {
            day = 29;
        }
    }
    combo_day.remove_all();
    for (int i=1;i<=day;i++)
    {   
        combo_day.append(std::to_string(i));
    }
    combo_day.set_active(1);

    

}
