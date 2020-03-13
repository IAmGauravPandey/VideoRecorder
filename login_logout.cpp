#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int main ()
{
    string userName;
    string userPassword;
    int loginAttempt = 0;
    vector<pair<string,string>>userInfo;
    userInfo.pb({"inkers","inkers"});
    userInfo.pb({"gaurav","gaurav"});
    bool login=false;
    while (loginAttempt < 5)
    {
        if(login){
            string input;
            cin>>input;
            if(input=="y" or input=="yes" or input=="Y"){
                cout<<"Thank You for using our service.\n";
                return 0;
            }
            cout<<"You are logged in.\nPress y to logout.\n";
            continue;
        }
        cout << "Please enter your user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;
        bool found=false;
        for(auto user:userInfo){
            if(user.first==userName and user.second==userPassword){
                found=true;break;
            }
        }
        if(found){
            cout<<"Welcome "<<userName<<"\n";
            cout << "Thank you for logging in.\n";
            cout<<"Press y to logout\n";
            login=true;
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 5)
    {
            cout << "Too many login attempts! The program will now terminate.\n";
            return 0;
    }
}