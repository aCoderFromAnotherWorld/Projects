#include <iostream>
using namespace std;

class EmployeeManager;
class Employee
{
    int id;
    string name;
    string position;
    float salary;
public:
    void setData(int x, string s, string pos, float slry);
    void display();
    friend class EmployeeManager;
    friend void promoteEmployee(EmployeeManager &e, int id);
};

class EmployeeManager
{
    int count = 0;
    Employee *emp = new Employee[count+1];

public:
    void add();
    void displayAll();
    void total();
    friend void promoteEmployee(EmployeeManager &e, int idd);
};

void Employee::setData(int x, string s, string pos, float slry)
{
    this->id = x;
    this->name = s;
    this->position = pos;
    this->salary = slry;
    
}

void Employee::display()
{
    cout<<"ID:"<<id<<endl;
    cout<<"Name:"<<name<<endl;
    cout<<"Psition:"<<position<<endl;
    cout<<"Salary:"<<salary<<endl;
    cout<<endl;
}

void EmployeeManager::add()
{
    
    cout<<"How many employees do you want to add: ";
    int n;
    cin>>n;
    for(int i = 0;i<n;i++)
    {
        int id;
        string name, position;
        float salary;
        cout<<"Enter ID: ";
        cin>>id;
        cin.ignore();
        cout<<"Enter Name: ";
        getline(cin, name);
        cout<<"Enter Position: ";
        getline(cin,position);
        cout<<"Enter Salary: ";
        cin>>salary;
        emp[count].setData(id, name, position, salary);
        count++;
    }
}

void EmployeeManager::displayAll()
{
    for(int i = 0;i<count;i++)
    {
        emp[i].display();
    }
}

void EmployeeManager::total()
{
    float total=0;
    for(int i =0; i <count; i++)
    {
        total+=emp[i].salary;
    }
    cout<<"The total salary paid by the company is: "<<total<<endl;
}

void promoteEmployee(EmployeeManager &e, int idd)
{
    bool flag = true;
    for (int i = 0; i < e.count; i++){
        if (e.emp[i].id == idd){
            flag = false;
            cout << "Enter promoted post: ";
            cin >>e.emp[i].position;
            cout << "Mr. "<<e.emp[i].name<<" is promoted"<< endl;
            break;
        }
    }
    if(flag){
        cout <<"ID is not found" << endl;
    }
    cout<<endl;
    ;
}

int main()
{
    EmployeeManager e;
    int c;
    do{
        cout<<"1: Add  employee\n";
        cout<<"2: Show details of all employees\n";
        cout<<"3: Promote an employee\n";
        cout<<"4: Total Salary\n";
        cout<<"0: Exit\n";
        cout<<"\nEnter your choice: ";
        cin>>c;
        switch(c)
        {
            case 1:
                
                e.add();
                break;
            case 2:
                
                e.displayAll();
                break;
            case 3:
                
                int idd;
                cout<<"Enter an ID: ";
                cin>>idd;
                promoteEmployee(e,idd);
                break;
            case 4:
                
                e.total();
                break;
            case 0:
                cout<<"THANK YOU"<<endl;
                break;
            default:
                cout<<"You request for a wrong query.\nPlease try again."<<endl;
        }
    }
    while(c!=0);
    return 0;
}