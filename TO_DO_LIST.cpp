#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
class todolist
{
    public:
    vector<string> tasks;
    void addtask();
    void deletetask();
    void displaytask();
    void savetask();
    void loadtask();
    void marktask();
    todolist() {loadtask();};
};
void todolist :: addtask()
{
    string add;
    cin.ignore();
    cout<<" Enter the task you want to add: ";
    getline(cin,add);

    tasks.push_back(add);
    cout<<"Task added successfully!\n";
    savetask();
}
void todolist::deletetask()
{
    if(tasks.empty())
    {
        cout<<"No tasks to delete!\n";
        return;
    }
    int del;
    displaytask();
    cout<<"Enter the task number to delete: ";
    cin>>del;

    if(del < 1 || del> tasks.size())
    {
        cout<<"INvalid task number!\n";
        return;
    }
    tasks.erase(tasks.begin() + del - 1);
    cout<<"Task deleted successfully!\n";
    savetask();
}
void todolist::displaytask()
{
    if(tasks.empty())
    {
        cout<<"No tasks to display!\n";
        return;
    }
    cout<<"tasks:\n";
    for(size_t i=0;i<tasks.size();i++)
    {
        cout<< i+1 <<"."<<tasks[i]<<endl;
    }
}
void todolist::savetask()
{
    ofstream file("todolist.txt");
    for(const string &task : tasks)
    {
        file<<task<<endl;
    }
    file.close(); 
}
void todolist::loadtask()
{
    ifstream file("todolist.txt");
    string line;
    tasks.clear();
    while(getline(file,line))
    {
        tasks.push_back(line);
    }
    file.close();
}
void todolist::marktask()
{
    if(tasks.empty())
    {
        cout<<"NO tasks to mark as completed.\n";
        return;
    }
    int index;
    displaytask();
    cout<<"Enter the  task number to mark as completed:";
    cin>>index;
    
    if(index < 1 || index > tasks.size())
    {
        cout<<"Invalid task number!\n";
        return;
    }
    tasks[index-1] += " [COMPLETED]";
    cout << "Task marked as completed!\n";
    savetask();
}
int main()
{
    todolist list;
    int ch;
    do
    {
        cout<<"1. Add Task \n";
        cout<<"2. Display all Tasks \n";
        cout<<"3. Mark a task as completed \n";
        cout<<"4. Delete a Task \n";
        cout<<"5. Save tasks To File \n";
        cout<<"6. Load TasksFrom File \n";
        cout<<"7. Exit \n";
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: list.addtask();
                    break;
            case 2: list.displaytask();
                    break;
            case 3: list.marktask();
                    break;
            case 4: list.deletetask();
                    break;
            case 5: list.savetask();
                    break;
            case 6: list.loadtask();
                    break;
            case 7: return 0;
            default: cout<<"Invalid choice \n";
        }
    } while (true);
    
}