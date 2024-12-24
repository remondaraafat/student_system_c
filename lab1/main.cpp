#include <iostream>

using namespace std;
struct Employee{
    int id;
    string name;
    int salary;
};
void displayNum(int a=0){
cout<<"a value is "<<a<<endl;
}
void sum(int a,int b){
cout<<"sum a anb is "<<a+b<<endl;
}
void sum(float a,float b){
cout<<"sum a anb is "<<a+b<<endl;
}
string name="global";
int main()
{
    int num;
    cout << "enter number of employees" << endl;
    cin>> num;

    Employee* emp=new Employee[num];
    for(int i=0;i<num;i++){
        cout << "enter employee's "<<i+1<<" id" << endl;
        cin>> emp[i].id;
    cout << "enter employee's "<<i+1<<" name" << endl;
        cin>> emp[i].name;
        cout << "enter employee's "<<i+1<<" salary" << endl;
        cin>> emp[i].salary;

    }
    for(int i=0;i<num;i++){
         cout << "employee "<<i+1<<" data "<<"id: "<<emp[i].id<<"name: "<<emp[i].name<<"salary: " <<emp[i].salary<< endl;
    }
    //sum function
    displayNum();
    sum(1,3);
    sum(1,3.0);
//access global and class member and name space member
    string name="loca";
    std::cout<<"1- "<<name<<endl;
    std::cout<<"2- "<<::name<<endl;
    return 0;
}
