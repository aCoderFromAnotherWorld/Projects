#include <iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string.h>

using namespace std;

/// <------ Declaration Section ------> ///
map<string, vector<string>> disease_map;  // Global map

class Time;
class Login;
class Patient;
class Doctor;
class HospitalManager;

int findIndex(HospitalManager &,int);
void release(int);
void resign(int);
string getTime(string, int *,int *);
void printDoc(vector<string>);
int isSubstring(string, string);
vector<string> recomend(string);
void program();

//////////////// CLASS ////////////////

///CLASS-01
class Login
{
    string pass = "12345";

public:
    bool match(string p);
    void change(string p);
    friend void program();
    
};

///CLASS-02
class Time
{
    int h, m;
    string t;
public:
    Time() {}
    Time(int, int, string);
    Time operator-(Time &e)
    {
        Time t;
        t.h = h - e.h;
        t.m = m - e.m;
        if(t.m<0) t.m+=60;
        if(t.h<0) {t.h+=12;t.h--;}
        return t;
    }
    void display();
};

///CLASS-03
class Doctor
{
    int id;
    string name;
    Time start_time;
    Time end_time;
    Time visiting_hour;
    string speciality;

public:
    Doctor() {}
    Doctor(int, string, Time , Time , string);
    string getName();
    string getSpeciality();
    void display();
    int getID();
    friend Time;
};

///CLASS-04
class Patient
{
    int id,age;
    string name;
    string bg;
    char gender;
    int doc_id;
    string contact;
    vector<string> vp;
    string disease;

public:
    Patient() {}
    Patient(int id, string name,int age, string bg, char gender,string disease,string contact, vector<string> vp);
    int getID();
    string getName();
    void display();
    friend class HospitalManager;
    friend void printDoc(vector<string>);
    friend vector<string> recomend(string);
};

///CLASS-05
class HospitalManager
{
    vector<Doctor> doc;
    vector<Patient> ptn;
    int countDoc = 100;
    int countPtn = 0;

public:
    void addPatient();
    void addDoctor();
    void displayDoc();
    void displayPtn();
    friend void release(HospitalManager &e, int id);
    friend void resign(HospitalManager &e, int id);
    friend int findIndex(HospitalManager &, int, char);
    friend int isSubstring(string, string);
    friend void searchPatient(HospitalManager &, string);
    friend vector<string> recomend(string);
    friend void printMap(HospitalManager &o, vector<string> v);
};

////////////// CLASS METHODS //////////

///// Class Login --->
bool Login::match(string p)
{
    if (p == pass)
        return true;
    else
        return false;
}

void Login::change(string p)
{
    this->pass = p;
    cout<<"\nPassword is successfully changed."<<endl;
}

///// Class Patient --->
Patient::Patient(int id, string name, int age, string bg, char gender, string disease, string contact, vector<string> vp)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->bg = bg;
    this->gender = gender;
    this->disease = disease;
    this->contact = contact;
    this->vp = vp;
}

void Patient::display()
{
    cout<<"-----------------------------\n";
    cout<<"Pateint's ID      : "<<id<<endl;
    cout<<"Pateint's Name    : "<<name<<endl;
    cout<<"Pateint's Age     : "<<age<<endl;
    cout<<"Pateint's BG      : "<<bg<<endl;
    cout<<"Pateint's Gender  : "<<gender<<endl;
    cout<<"Pateint's Disease : "<<disease<<endl;
    cout<<"Pateint's Contact : "<<contact<<endl;
    cout<<"Recomended Doctor : ";
    printDoc(recomend(disease));
    cout<<endl;
    cout<<"-----------------------------"<<endl;
}

int Patient::getID()
{
    return id;
}

string Patient::getName()
{
    return name;
}

///// Class Doctor --->
Doctor::Doctor(int id, string name, Time start, Time end, string speciality)
{
    //
    this->name = name;
    start_time = start;
    end_time = end;
    this->visiting_hour = end - start;
    this->id = id;
    this->speciality = speciality;
}

void Doctor::display()
{
    cout<<"-----------------------------\n";
    cout<<"Doctor's ID   : "<<id<<endl;
    cout<<"Name          : "<<name<<endl;
    cout<<"Speciality    : "<<speciality<<endl;
    cout<<"\nVisiting Hour : ";
    visiting_hour.display();
    cout <<" Hour"<<endl;
    cout<<"Visits From ";
    start_time.display();
    cout<<" To ";
    end_time.display();
    cout<<"\n-----------------------------\n\n";
}

int Doctor::getID()
{
    return id;
}

string Doctor::getName()
{
    return name;
}

string Doctor::getSpeciality()
{
    return speciality;
}

///// Class HospitalManager --->
void HospitalManager::addPatient()
{
    countPtn++;
    int age;
    string name, bg, disease, contact;
    char gender;
    cout<<"\n------------------------------\n";
    cin.ignore();
    cout<<"Enter Patient's Name   : ";
    getline(cin, name);
    cout<<"Enter Patient's Age    : ";
    cin>>age;
    cin.ignore();
    cout<<"Patient's Blood Group  : ";
    cin>>bg;
    cout<<"Patient's Gender       : ";
    cin>>gender;
    cin.ignore();
    cout<<"Patient's Contact No   : ";
    cin>>contact;
    cin.ignore();
    cout<<"Patient's Disease Type : ";
    cin>>disease;
    vector<string> vp = recomend(disease);
    Patient p(countPtn, name, age, bg, gender, disease, contact, vp);
    ptn.push_back(p);
}

void HospitalManager::addDoctor()
{
    countDoc++;
    string name, speciality;
    string time;
    string t;
    int h,m;
    cout<<"\n------------------------------\n";
    cin.ignore();
    cout<<"Enter Doctor Name    : ";
    getline(cin, name);
    cout<<"Doctor's Speciality  : ";
    cin>>speciality;
    cout<<"Starting Time (H,M)  : ";
    cin.ignore();
    getline(cin, time);
    t.clear();
    t = getTime(time, &h, &m);
    Time st(h,m, t);
    cout<<"Ending Time (H,M)    : ";
    getline(cin, time);
    t.clear();
    t = getTime(time, &h, &m);
    Time en(h,m, t);
    Doctor d(countDoc, name, st, en, speciality);
    disease_map[speciality].push_back(name);
    doc.push_back(d);
}

void HospitalManager::displayDoc()
{
    system("cls");
    if(countDoc > 100)
    {
        // cout<<"======================================\n";
        cout<<"------- DISPLAYING DOCTOR(S) ---------\n\n";
        // cout<<"======================================\n";

        for(auto it=doc.begin();it!=doc.end();it++)
        {
            (*it).display();
        }
        cout<<"\n"<<endl;
    }
    else
        cout<<"There is no Doctor yet!\n";
}

void HospitalManager::displayPtn()
{
    system("cls");
    if(countPtn)
    {
        // cout<<"======================================\n";
        cout<<"------- DISPLAYING PATIENT(S) --------\n\n";
        // cout<<"======================================\n";

        for(auto it=ptn.begin();it!=ptn.end();it++)
        {
            (*it).display();
        }
        cout<<"\n"<<endl;
    }
    else
        cout<<"There is no Doctor yet!\n";
}

///// Class Time --->
Time::Time(int h, int m, string t)
{
    this->h = h;
    this->m = m;
    this->t = t;
}

void Time::display()
{
    cout<<h<<":"<<m <<" "<<t;
    if(!t.empty())  cout<<"M";
}

//////////// FRIEND FUNCTION ///////////
void release(HospitalManager &e, int id)
{
    int n = findIndex(e, id, 'p');
    if(n == -100)
        cout<<"\nPatient is not found!\n";
    else{
        cout<<"\nPatient Mr. "<< e.ptn.at(n).getName() <<" is released.\n";
        e.ptn.erase(e.ptn.begin()+n);
        e.countPtn--;
    }
}

void resign(HospitalManager &e, int id)
{
    int n = findIndex(e, id, 'd');
    if(n == -100)
        cout<<"\nDoctor is not found!\n";
    else
    {
        string nm = e.doc.at(n).getName();
        string sp = e.doc[n].getSpeciality();

        cout<<"\nDoctor "<< nm <<" is resigned.\n";
        e.doc.erase(e.doc.begin()+n);

        auto it= disease_map.find(sp);
        if(it != disease_map.end() )
        {
            vector<string>& nmm = it->second;
            auto itt = find(nmm.begin(), nmm.end(), nm);
            if(itt!=nmm.end())
                nmm.erase(itt);
        }
        e.countDoc--;
    }
    

    
}

vector<string> recomend(string dis)
{
    return disease_map[dis];
}

int findIndex(HospitalManager &e,int id, char p)
{
    if(p == 'p')
    {
        for(int it = 0; it <= e.ptn.size(); it++)
        {
            if( id == e.ptn[it].getID())
                return it;
        }
    }

    else if(p == 'd')
    {
        for(int it = 0; it <= e.doc.size(); it++)
        {
            if( id == e.doc[it].getID())
                return it;
        }
    }
    return -100;
}

void printDoc(vector<string> v)
{
    if(!v.empty())
        for(int i = 0; i<v.size();i++)
        {
            if(i!=v.size()-1)
                cout<<v[i]<<", ";
            else    cout<<v[i];
        }
    else cout<<"N/A";
}

void searchPatient(HospitalManager &obj, string name)
{
    int flag = -1;
    if(obj.countPtn)
        for(int i=0 ;i <obj.countPtn;i++)
        {
            flag =  isSubstring(name, obj.ptn.at(i).getName());
            if(flag != -1)
            {
                system("cls");
                cout<<"-------- DISPLAYING DETAILS --------\n";
                obj.ptn[i].display();
                break;
            }
        }
    
    if(flag == -1)
        cout<<"\nThere is no such Patient admitted\n";
}

void printMap(HospitalManager &o, vector < string > v)
{
    int flag = 0;
    if(!v.empty())
    for(int i=0;i< v.size() ; i++)
    {
        for(int j = 0; j < o.doc.size(); j++)
        {
            if(o.doc[j].getName() == v[i])
            {
                if(!flag)
                {
                    system("cls");
                    cout<<"------------ Details ------------\n\n";
                    flag = 1;
                }
                o.doc[j].display();
            }
        }
    }
    else
        cout<<"\nThere is no Doctor found!\n\n";

}

//////////// GENERAL FUNCTION ///////////
int isSubstring(string s1, string s2)
{
    if (s2.find(s1) != string::npos)
        return s2.find(s1);
    return -1;
}

string getTime(string str, int *x,int *y)
{
    string t;
    char *strn = (char *) str.c_str();
    char s[] = ": ";
    int flag = 0;

    char *ptr = strtok(strn,s);
    while(ptr!=NULL)
    {
        if(flag == 0){
            *x = atoi(ptr);
            flag++;
        }
        else if(flag == 1)
        {
            *y = atoi(ptr);
            flag++;
        }
        else if(flag == 2)
        {
            t = *ptr;
            for (auto & c: t) t = toupper(c);
            flag++;
        }
        ptr = strtok(NULL, s);
    }
    delete ptr;
    return t;
}

void program()
{
    HospitalManager hm;
    int command, id;
    Login p;
    string pass;
    string str;

    do
    {
        system("cls");
        cout<<"======================================\n";
        cout<<"----- HOSPITAL MANAGEMENT SYSTEM -----\n";
        cout<<"======================================\n\n";

        cout<<"1: Appoint a Doctor\n"
            <<"2: Admit a Patient\n"
            <<"3: Show Details of Doctors\n"
            <<"4: Show Details of Patients\n"
            <<"5: Search Doctors by Speciality\n"
            <<"6: Search Patient by name\n"
            <<"7: Release a Patient\n"
            <<"8: Resign a Doctor\n"
            <<"9: Change Password\n"
            <<"0: Exit\n";
        cout<<"Enter your choice : ";
        cin>>command;

        switch(command)
        {
            case 1:
                hm.addDoctor();
                // cin.ignore();
                cout<<"\n\nDoctor is successfully added\n";
                system("pause");
                break;
            case 2:
                hm.addPatient();
                cin.ignore();
                cout<<"\n\nPatient is successfully added\n";
                system("pause");
                break;
            case 3:
                hm.displayDoc();
                cin.ignore();
                getchar();
                break;
            case 4:
                hm.displayPtn();
                cin.ignore();
                getchar();
                break;
            case 5:
                cout<<"Enter Speciality: ";
                cin>>str;
                printMap(hm, disease_map[str]);
                cin.ignore();
                getchar();
                break;
            case 6:
                cout<<"Enter Name: ";
                cin.ignore();
                getline(cin, pass);
                searchPatient(hm, pass);
                getchar();
                break;
            case 7:
                cout<<"Enter ID: ";
                cin>>id;
                release(hm, id);
                cin.ignore();
                getchar();
                break;
            case 8:
                cout<<"Enter ID: ";
                cin>>id;
                resign(hm, id);
                cin.ignore();
                getchar();
                break;
            case 9:
                cout<<"Enter Old Password: ";
                cin>>pass;
                cin.ignore();
                if(p.match(pass))
                {
                    cout<<"Enter New Password: ";
                    cin>>pass;
                    p.change(pass);
                }
                else{
                    cout<<"\nYou have entered wrong password!\n";
                }
                cin.ignore();
                getchar();
                break;
            case 0:
                system("cls");
                cout<<"------ THANK YOU -------\n\n\n";
                break;
            default:
                cout<<"\n\nYou have entered a wrong input!\nPlease try again.\n";
                cin.ignore();
                getchar();
        }
    }while(command != 0);
}

//////////// MAIN FUNCTION ///////////
int main()
{
label:
    system("cls");
    cout<<"Enter Password: ";
    string pass;
    cin>>pass;
    Login password;
    if(password.match(pass))
        program();
    else
    {
        cout<<"You haved entered a wrong password.\nPlease try again.";
        cin.ignore();
        getchar();
        goto label;
    }

    return 0;
}
