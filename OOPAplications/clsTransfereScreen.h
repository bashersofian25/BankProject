#pragma once
#include "clsScreen.h"
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <string>
class clsTransfereScreen : protected clsScreen
{

private:
	static void _PrintClientCard(clsBankClient Client) {
		cout << "---------------------\n";
		cout << "FullName   : " << Client.FullName()<<endl;
		cout << "Acc. Number: " << Client.AccountNumber()<<endl;
		cout << "Balance    : " << Client.AccountBalance<<endl;
		cout << "---------------------\n";
	}

	static bool _ConfirmTransfer() {
		cout << "Are you sure you want to complete this trasfer(y/n)? ";
		string ans = clsInputValidate::ReadString();
		if (ans == "y" || ans == "Y") {
			return true;
		}
		return false;
	}

	static void _CompleteTransFer(clsBankClient &From, clsBankClient &To, double Amount) {
		From.Withdraw(Amount);
		To.Deposit(Amount);
		_LogTransfer(From, To, Amount);
	}

	static void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("TransferLogs.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}
	static void _LogTransfer(clsBankClient &From, clsBankClient &To, double Amount) {
		clsDate currentDate;
		string date = currentDate.DateToString();
		string time = clsDate::getSystemTime();
		string Line = date+ "--" + time + "#//#" + From.AccountNumber() + "#//#" + To.AccountNumber() + "#//#" 
			+ to_string(Amount) + "#//#" +to_string(From.AccountBalance) + "#//#"
			+ to_string(To.AccountBalance) + "#//#" + CurrentUser.UserName;

		_AddDataLineToFile(Line);
	}


public:
	static void ShowTransferScreen() {
		_DrawScreenHeader("Transfer Screen");
		cout << "Please Enter Account Number To Transfer From: ";
		string FromAccountNumber = clsInputValidate::ReadString();
		clsBankClient FromClient = clsBankClient::Find(FromAccountNumber);

		while (FromClient.IsEmpty()) {
			cout << "Invalid Account Number, Please Try Again: ";
			FromAccountNumber = clsInputValidate::ReadString();
			FromClient = clsBankClient::Find(FromAccountNumber);
		}

		cout << "Client Card:\n";
		_PrintClientCard(FromClient);



		cout << "Please Enter Account Number To Trasfer To: ";

		string ToAccountNumber = clsInputValidate::ReadString();
		clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);

		while (ToClient.IsEmpty()) {
			cout << "Invalid Account Number, Please Try Again: ";
			ToAccountNumber = clsInputValidate::ReadString();
			ToClient = clsBankClient::Find(ToAccountNumber);
		}
		_PrintClientCard(ToClient);



		cout << "Enter Transfer Amount: ";
		double Amount = clsInputValidate::ReadDblNumber();

		while (Amount > FromClient.AccountBalance || Amount <= 0) {
			cout << "You can't transfer this Amount from the balance, Please try another amount: ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		bool confirmed = _ConfirmTransfer();

		if (confirmed) {

			_CompleteTransFer(FromClient, ToClient, Amount);
			cout << "Transfer Done Successfully!";
			return;
		}
		else {
			cout << "Proccess canceled!";
			return;
		}

	}
};

