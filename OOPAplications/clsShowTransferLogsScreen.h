#pragma once
#include "clsScreen.h"
#include <iostream>
#include <iomanip>

class clsShowTransferLogsScreen : protected clsScreen
{
private:
    struct stTransfer
    {
        string DateAndTime;
        string FromAccNumber;
        string ToAccNumber;
        string Ammount;
        string FromNewBalance;
        string ToNewBalance;
        string UserName;

    };

    static stTransfer _ConvertLinetoLogStr(string Line, string Seperator = "#//#")
    {
        stTransfer myTransfer;
        vector<string> vTransfer;

        vTransfer = clsString::Split(Line, Seperator);
        myTransfer.DateAndTime = vTransfer[0];
        myTransfer.FromAccNumber= vTransfer[1];
        myTransfer.ToAccNumber = vTransfer[2];
        myTransfer.Ammount = vTransfer[3];
        myTransfer.FromNewBalance= vTransfer[4];
        myTransfer.ToNewBalance = vTransfer[5];
        myTransfer.UserName = vTransfer[6];
        return myTransfer;

    }
    static void _PrintLogRecordLine(stTransfer Log) {

        cout << setw(8) << left << "" << "| " << setw(20) << left << Log.DateAndTime;
        cout << "| " << setw(7) << left << Log.FromAccNumber;
        cout << "| " << setw(7) << left << Log.ToAccNumber;
        cout << "| " << setw(15) << left << Log.Ammount;
        cout << "| " << setw(15) << left << Log.FromNewBalance;
        cout << "| " << setw(15) << left << Log.ToNewBalance;
        cout << "| " << setw(7) << left << Log.UserName;
    }

    static vector<stTransfer> _GetLogsFromFile() {
        vector <stTransfer> vTransfers;

        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                if(Line.length() != 0) {
                    stTransfer Log = _ConvertLinetoLogStr(Line);
                    vTransfers.push_back(Log);
                }
                
            }

            MyFile.close();

        }

        return vTransfers;
    }
public:

    static void ShowTransferLogs() {
        vector <stTransfer> vTransfers = _GetLogsFromFile();
        string Title = "\t  Transfer Logs Screen";
        string SubTitle = "\t    (" + to_string(vTransfers.size()) + ") Transfer(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(20) << "Date and Time";
        cout << "| " << left << setw(7) << "s.Acc";
        cout << "| " << left << setw(7) << "d.Acc";
        cout << "| " << left << setw(15) << "Ammount";
        cout << "| " << left << setw(15) << "s.Balance";
        cout << "| " << left << setw(15) << "d.Balance";
        cout << "| " << left << setw(7) << "Username";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________\n" << endl;

        if (vTransfers.size() == 0)
            cout << "\t\t\t\tNo Transfers Have Been Done Yet!";
        else

            for (stTransfer &Transfer : vTransfers)
            {

                _PrintLogRecordLine(Transfer);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________\n" << endl;
    }

};

