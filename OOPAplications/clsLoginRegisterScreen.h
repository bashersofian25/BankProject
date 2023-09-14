#pragma once
#include "clsDate.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsUser.h"
#include "clsUtil.h"
#include <vector>
#include "Global.h"
class clsLoginRegisterScreen : protected clsScreen
{
    static const short _encryptionKey = 7;
    struct stLogin
    {
        string Date;
        string Time;
        string UserName;
        string PassWord;
        string Permission;
    };

    static stLogin _ConvertLinetoLogStr(string Line, string Seperator = "#//#")
    {
        stLogin myLogin;
        vector<string> vLog;

        vLog = clsString::Split(Line, Seperator);
        myLogin.Date = vLog[0];
        myLogin.Time = vLog[1];
        myLogin.UserName = vLog[2];
        myLogin.PassWord = vLog[3];
        myLogin.Permission = vLog[4];
        return myLogin;

    }
    static void _PrintLogRecordLine(stLogin Log) {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Log.UserName;
        cout << "| " << setw(25) << left << Log.Time;
        cout << "| " << setw(12) << left << Log.Date;
        cout << "| " << setw(20) << left << clsUtil::EncryptText(Log.PassWord, _encryptionKey);
        cout << "| " << setw(10) << left << Log.Permission;
    }

    static vector<stLogin> _GetLogsFromFile() {
        vector <stLogin> vLogs;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                stLogin Log = _ConvertLinetoLogStr(Line);

                vLogs.push_back(Log);
            }

            MyFile.close();

        }

        return vLogs;
    }
public:
	static void showLoginRegisterScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pLogsList)) {
            return;
        }

        vector <stLogin> vLogs = _GetLogsFromFile();
        string Title = "\t  Logs List";
        string SubTitle = "\t    (" + to_string(vLogs.size()) + ") Logs";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(25) << "Time";
        cout << "| " << left << setw(12) << "Date";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissons";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLogs.size() == 0)
            cout << "\t\t\t\tNo Logs Available On This System!";
        else

            for (stLogin Log : vLogs)
            {

                _PrintLogRecordLine(Log);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}
};

