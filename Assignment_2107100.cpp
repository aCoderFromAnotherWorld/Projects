/*Submitted by - 2107100*/

#include <iostream>
#include<iomanip>
// #define MAX_SIZE 100
using namespace std;

//////////////////////// CLASS ////////////////////////

class EmployeeManager;

/// CLASS 1 ///
class Employee
{
    int id;
    string name;
    string position;
    float salary;

public:
    Employee(){ /*cout<<"Defalut ctor is called\n"*/;}
    Employee(int id, string name, string position, float salary);
    void display();
    ~Employee();
    friend class EmployeeManager;
    friend void promoteEmployee(EmployeeManager &e, int id);
};

/// CLASS 2 ///
class EmployeeManager
{
    int count = 0;
    Employee *emp = new Employee[count];

public:
    void add();
    void displayAll();
    void totalSalary();
    void remove(int id);
    friend void promoteEmployee(EmployeeManager &e, int idd);
};

///////////// Function or Methods ////////////////////

//Constructor
Employee::Employee(int id, string name,string position,float salary)
{
    this->id = id;
    this->name = name;
    this->position = position;
    this->salary = salary;
}

void Employee::display()
{
    cout<<left<<setw(8)<<id;
    cout<<left<<setw(14)<<name;
    cout<<left<<setw(14)<<position;
    cout<<left<<setw(11)<<salary;
    cout<<endl;
}

//Destructor
Employee::~Employee()
{
    // cout<<"Dtor is called\n";
}


void EmployeeManager::add()
{
    cout<<"----------    ADDING EMPLOYEE(S)   ----------\n\n";  
    cout<<"How many employees do you want to add: ";             
    int n;
    cin>>n;

    Employee *temp = new Employee[count];
    
    copy(emp, emp+count, temp);

    delete [] emp;

    emp = new Employee[count + n];

    copy(temp, temp+count, emp);

    for(int i = count;i < count + n ;i++)
    {
        int id;
        string name, position;
        float salary;
        cout<<"-----------------------\n";
        cout<<"Enter ID       : ";
        cin>>id;
        cin.ignore();
        cout<<"Enter Name     : ";
        getline(cin, name);
        cout<<"Enter Position : ";
        getline(cin,position);
        cout<<"Enter Salary   : ";
        cin>>salary;
        emp[i] = Employee(id, name, position, salary);
    }
    count += n;
    cout<<"\n\n";
    system("pause");
    system("cls");
    // cout<<"\n==============================================\n";
    cout<<"------  SUCCESSFULLY ADDED EMPLOYEE(S)  ------\n\n";
    // cout<<"=============================================\n\n";
    system("pause");
}

void EmployeeManager::displayAll()
{
    cout<<"\n==============================================\n";
    cout<<"--------   DETAILS OF ALL EMPLOYEES   --------\n";   
    cout<<"==============================================\n\n";
    cout<<"---------------------------------------\n";
    cout<<left<<setw(8)<<"ID";
    cout<<left<<setw(14)<<"NAME";
    cout<<left<<setw(14)<<"POSITION";
    cout<<left<<setw(11)<<"SALARY";
    cout<<"\n---------------------------------------\n";
    for(int i = 0;i<count;i++)
    {
        emp[i].display();
    }
    cout<<"\n\n";
    system("pause");
}

void EmployeeManager::totalSalary()
{
    float total=0;
    for(int i =0; i <count; i++)
    {
        total+=emp[i].salary;
    }
    cout<<"------ TOTAL SALARY PAID BY THE COMPANY ------\n\n";
    cout<<"The total salary paid by the company is: "<<total<<endl;
    cout<<"\n\n";
    system("pause");
}

void EmployeeManager::remove(int id)
{
    bool flag = false;
    for(int i = 0;i<count;i++)
    {
        if(id == emp[i].id)
        {
            emp[i].~Employee();
            for(int j=i;j<count-1;j++)
                emp[j] = emp[j+1];
            --count;
            flag = true;
            cout<<"Employee with id "<<id<<" is successfully removed\n\n\n";
        }
    }
    if(!flag)
        cout<<"Employee with id "<<id<< " is not found\n\n\n";
    system("pause");
}



/// Friend Function///
void promoteEmployee(EmployeeManager &e, int idd)
{
    bool flag = true;
    for (int i = 0; i < e.count; i++){
        if (e.emp[i].id == idd){
            flag = false;
            cout << "Enter promoted post: ";
            cin >>e.emp[i].position;
            cout << "Enter new salary: ";
            cin>>e.emp[i].salary;
            cout << "Mr. "<<e.emp[i].name<<" is promoted to " << e.emp[i].position << endl;
            break;
        }
    }
    if(flag){
        cout <<"ID is not found" << endl;
    }
    cout<<"\n\n";
    system("pause");
}

// Interface and operations for the program
void operations(EmployeeManager &e)
{
    int cmd;
    do{
        system("cls");
        cout<<"\n==============================================\n";
        cout<<"--------  EMPLOYEE MANAGEMENT SYSTEM  --------\n";   
        cout<<"==============================================\n\n";  
        cout<<"1: Add  employee\n";
        cout<<"2: Show details of all employees\n";
        cout<<"3: Promote an employee\n";
        cout<<"4: Show total salary paid\n";
        cout<<"5: Delete a record\n";
        cout<<"0: Exit\n";
        cout<<"\nEnter your choice: ";
        cin>>cmd;
        switch(cmd)
        {
            case 1:
                system("cls");
                e.add();
                break;
            case 2:
                system("cls");
                e.displayAll();
                break;
            case 3:
                system("cls");
                int idd;
                cout<<"------  PROMOTION  ------\n\n";   // PROMOTION //
                // cout<<"=============================================\n\n";
                cout<<"Enter an ID: ";
                cin>>idd;
                promoteEmployee(e,idd);
                break;
            case 4:
                system("cls");
                e.totalSalary();
                break;
            case 5:
                system("cls");
                int id;
                cout<<"------ DELETING A RECORD ------\n\n";
                cout<<"Enter an ID: ";
                cin>>id;
                e.remove(id);
                break;
            case 0:
                system("cls");
                cout<<"==============================="<<endl;
                cout<<"-----------THANK YOU-----------"<<endl;
                cout<<"----------===========----------"<<endl;
                cout<<"\n\nSYSTEM IS NOW SHUTTING DOWN....\n";
                cout<<"==============================="<<endl;
                break;
            default:
                cout<<"You request for a wrong query.\nPlease try again."<<endl;
        }
    }
    while(cmd!=0 && cmd != char(26));
    
}

int main()
{
    EmployeeManager e;
    operations(e);
    return 0;
}