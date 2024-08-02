#ifndef Gui_H
#define Gui_H

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <iostream>
#include <iomanip>
#include <gtkmm/window.h>
#include "user.h"
#include "task.h"
#include <atomic>
#include <thread>
int newTask(const  std::string& filename,const task& atask);
class LoginWindow : public Gtk::Window {
public:
    LoginWindow();
    void on_login_clicked();

private:
    Gtk::Box m_vbox;
    Gtk::Entry m_username_entry;
    Gtk::Entry m_password_entry;
    Gtk::Button m_login_button;
    void show_message(const Glib::ustring &message);

};
class RegisterWindow : public Gtk::Window {
public:
    RegisterWindow();
    void on_register_clicked();
private:
    Gtk::Box m_vbox;
    Gtk::Entry m_username_entry;
    Gtk::Entry m_password_entry;
    Gtk::Entry m_confirm_password_entry;
    Gtk::Button m_register_button;
    void show_message(const Glib::ustring &message);

};
class WelcomeScreen : public Gtk::Window {
public:
    WelcomeScreen();
   
    void on_registration_complete() {
        show_all(); // 显示 WelcomeScreen
    }
     void on_login_complete() {
        show_all(); // 显示 WelcomeScreen
    }
    
private:
    Gtk::Button m_login_button;
    Gtk::Button m_register_button;
    Gtk::Box m_vbox;

    void on_login_clicked();
    void on_register_clicked();
    void show_message(const Glib::ustring &message);

};
class TaskColumns : public Gtk::TreeModel::ColumnRecord {
public:
    TaskColumns() {
        add(task_id);
        add(task_name);
        add(reminder_time);
        add(due_time);
        add(classify);
        add(priority);
    }

    Gtk::TreeModelColumn<int> task_id;
    Gtk::TreeModelColumn<Glib::ustring> task_name;
    Gtk::TreeModelColumn<Glib::ustring> reminder_time;
    Gtk::TreeModelColumn<Glib::ustring> due_time;
    Gtk::TreeModelColumn<Glib::ustring> classify;
    Gtk::TreeModelColumn<Glib::ustring> priority;
};
class TaskDialog : public Gtk::Dialog {
public:

    sigc::signal<void(const task&)> signal_task_created;
    
    task atask;
    TaskDialog(Gtk::Window& parent);

    task get_task() const ;
private:
    void show_message(const Glib::ustring &message);
    bool signal_emitted;
    Gtk::Box* create_time_box(const Glib::ustring& label_text,
    Gtk::ComboBoxText& combo_year,
    Gtk::ComboBoxText& combo_month, 
    Gtk::ComboBoxText& combo_day, 
    Gtk::ComboBoxText& combo_hour,
    Gtk::ComboBoxText& combo_minute) ;
    void on_response(int response_id);
    void on_combo_year_month_changed(Gtk::ComboBoxText& combo_year, Gtk::ComboBoxText& combo_month, Gtk::ComboBoxText& combo_day);
    Gtk::Entry entry_name;
    Gtk::ComboBoxText combo_priority;
    Gtk::ComboBoxText combo_classify;
    Gtk::ComboBoxText combo_notify_year;
    Gtk::ComboBoxText combo_notify_month;
    Gtk::ComboBoxText combo_notify_day;
    Gtk::ComboBoxText combo_notify_hour;
    Gtk::ComboBoxText combo_notify_minute;
    Gtk::ComboBoxText combo_do_year;
    Gtk::ComboBoxText combo_do_month;
    Gtk::ComboBoxText combo_do_day;
    Gtk::ComboBoxText combo_do_hour;
    Gtk::ComboBoxText combo_do_minute;
};
class DeleteTaskDialog : public Gtk::Dialog {
public:
    
    sigc::signal<void, int> signal_task_deleted;
    DeleteTaskDialog(Gtk::Window& parent,int size) :
        Gtk::Dialog("Delete Task", parent, true) {
        set_position(Gtk::WIN_POS_CENTER);
        add_button("Cancel", Gtk::RESPONSE_CANCEL);
        add_button("OK", Gtk::RESPONSE_OK);

        Gtk::Box* content = get_content_area();

        // Task ID
        Gtk::Box* id_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* id_label = Gtk::manage(new Gtk::Label("Task ID:"));
        id_box->pack_start(*id_label, Gtk::PACK_SHRINK);
        for (int id =1;id<=size;id++) {
            combo_task_id.append(std::to_string(id));
        }
        id_box->pack_start(combo_task_id);
        content->pack_start(*id_box, Gtk::PACK_SHRINK);
        
        show_all_children();
        ifemit=false;
        signal_response().connect(sigc::mem_fun(*this, &DeleteTaskDialog::on_response));
    }
    int get_task_id() const {
        if (combo_task_id.get_active_text()=="")return  -1;
        return std::stoi(combo_task_id.get_active_text());
    }
private:
    void on_response(int response_id) {
        if (response_id == Gtk::RESPONSE_OK&&!ifemit)
         {
            ifemit=true;
            signal_task_deleted.emit(get_task_id());
        }
        close();
    }
    bool ifemit;

    Gtk::ComboBoxText combo_task_id;
};

class MyTask : public Gtk::Window {    
protected:
    Glib::Dispatcher dispatcher;
    void new_task(const task& atask);
    void CheckReminders();
    // int get_days_in_month(int year, int month);
    // void update_days();
    void on_combo_changed();
    void on_calendar_day_selected() ;
    void show_task_day(int,int,int);
private:
    Glib::ustring message;
    std::atomic<bool> running;
    std::thread m_thread;
    void show_message(const Glib::ustring &message);
    TaskColumns columns;
    Glib::RefPtr<Gtk::ListStore> refTreeModel;
    Gtk::TreeView treeView;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::Box hbox{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Box buttonBox{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button  add_task_button,delte_task_button,show_all_task_button,show_unfinished_work_button,
    show_overdue_work_button,show_sort_button;
    Gtk::ComboBoxText combo_year, combo_month;
    Gtk::Calendar calendar;
    std::string file;
    TaskList list;
    Glib::ustring attribute[3] ={"Learning","Entertainment","Rest"};
    Glib::ustring priority[3] ={"High","Medium","Low"};
public:
    MyTask(std::string filename=""); 
    ~MyTask(){running=false;if (m_thread.joinable())
m_thread.join();}
    void add_Task();
    void add_task(int id, const Glib::ustring& name,
    const Glib::ustring& reminder, const Glib::ustring& due, 
    const Glib::ustring& attr,const Glib::ustring& priority) ;
    void del_Task(); 
    void del_task(int id);
    void show_unfinish_work();
    void show_all_task() ;
    void show_sort();
    void sort_Task(int);
    void show_overdue_work();
    
    
};


class sortTaskDialog : public Gtk::Dialog {
public:
    sigc::signal<void, int> signal_task_sort;
    sortTaskDialog(Gtk::Window& parent) :
        Gtk::Dialog("Sort", parent, true) {
        set_position(Gtk::WIN_POS_CENTER);
        add_button("Cancel", Gtk::RESPONSE_CANCEL);
        add_button("OK", Gtk::RESPONSE_OK);
        Gtk::Box* content = get_content_area();
        // Task ID
        Gtk::Box* id_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        Gtk::Label* id_label = Gtk::manage(new Gtk::Label("Sort by:"));
        id_box->pack_start(*id_label, Gtk::PACK_SHRINK);
        for (int i=0;i<5;i++)
        {
        combo_sort.append(selection[i]);
        }
        id_box->pack_start(combo_sort);
        content->pack_start(*id_box, Gtk::PACK_SHRINK);
        show_all_children();
        ifemit=false;
        signal_response().connect(sigc::mem_fun(*this, &sortTaskDialog::on_response));
    }

    int get_task_id() const {
        for(int i=0;i<5;i++)
        {
            if (combo_sort.get_active_text()==selection[i])return i;
        }
        return 5;
    }
private:
    std::string selection[5]={"Classify","Priority","Do_Time","Notification time","ID"};
    void on_response(int response_id) {
        if (response_id == Gtk::RESPONSE_OK&&!ifemit)
         {
            ifemit=true;
            signal_task_sort.emit(get_task_id());
        }
        close();
    }
    bool ifemit;
    Gtk::ComboBoxText combo_sort;
};
#endif