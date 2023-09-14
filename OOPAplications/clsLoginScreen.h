#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsDate.h"
#include <iomanip>
#include "clsMainScreen.h"
#include <string>
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:
    static void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static void _RegisterLogin() {
        string date = clsDate::DateToString(clsDate::GetSystemDate());
        string time = clsDate::getSystemTime();
        string Line = date + "#//#" + time + "#//#" + CurrentUser.UserName + "#//#" + CurrentUser.Password + "#//#" + to_string(CurrentUser.Permissions);

        _AddDataLineToFile(Line);
    }
    static  bool _Login()
    {
        bool LoginFaild = false;
        short tries = 3;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                --tries;
                if (tries == 0) {
                    cout << "You are Blocked From The System!" << endl;
                    return false;
                }
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "you have " << tries << " to login\n\n";

            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);


        _RegisterLogin();
        clsMainScreen::ShowMainMenue();

    }
    

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");

        return _Login();
        

    }

};

