#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
using namespace std;

string status(int n);
class account{
    public:
int account_no;
float balance;
int no_deposits = 0;
int no_withdrawals = 0;
float interest_rate = 11;
float monthly_servicecharge_rate = 0.25;

virtual void makeDeposit(int x){
    balance = balance + x;
}

virtual void makeWithdrawal(int x){
    balance = balance - x;
}

virtual void calcInt(){
    float interest_amount = balance * interest_rate;
    int fin = balance + interest_amount;
    cout << "Monthly interest amount = "<< interest_amount<<endl;
    cout << "Total balance after adding monthly interest amount will be "<< fin<<endl;
}

virtual void monthlyProc(int x, int y){
    float m_s_c_fromDeposit = ((0.25/100)*x);
    float m_s_c_fromWithdrawal = ((0.25 / 100)*y);
    float monthly_service_charge = m_s_c_fromDeposit + m_s_c_fromWithdrawal;
    cout << "Monthly service charge = "<<monthly_service_charge<<endl;
    int fin = balance - monthly_service_charge;
    cout << "Your total balance after deducting service charge will be"<<fin<<endl;
}
void display(){
    cout<<account_no<<setw(10)<<" "<<no_deposits<<setw(10)<<" "<<no_withdrawals<<setw(10)<<" "<<balance<<endl;
}

};

class saving : public account {
public:
virtual void calcInt(){
    float interest_amount = balance * interest_rate;
    int fin = balance + interest_amount;
    cout << "Monthly interest amount = "<< interest_amount<<endl;
    cout << "Total balance after adding monthly interest amount will be "<< fin<<endl;
}

virtual void monthlyProc(int x, int y){
    float m_s_c_fromDeposit = ((0.25/100)*x);
    float m_s_c_fromWithdrawal = ((0.25 / 100)*y);
    float monthly_service_charge = m_s_c_fromDeposit + m_s_c_fromWithdrawal;
    cout << "Monthly service charge = "<<monthly_service_charge<<endl;
    int fin = balance - monthly_service_charge;
    cout << "Your total balance after deducting service charge will be"<<fin<<endl;
}
virtual void makeDeposit(int x){
    balance = balance + x;
}

virtual void makeWithdrawal(int x){
    balance = balance - x;
}


void display(){

    cout<<account_no<<setw(20)<<" "<<no_deposits<<setw(15)<<" "<<no_withdrawals<<setw(14)<<" "<<balance<<setw(9)<<" "<<status(account_no)<<endl;
}

void create(){
	cout<<"Enter the Account No: "<<endl;
	cin>>account_no;
	cout<<"Enter Initial Balance: "<<endl;;
	cin>>balance;cout<<endl;
	cout<<"Your Account Has Been Created Successfully!!!"<<endl<<endl;
}

void show(){
	cout<<"Account No : "<<account_no<<endl;
	cout<<"Number of Deposits : "<<no_deposits<<endl;
	cout<<"Number of Withdrawals : "<<no_withdrawals<<endl;
	cout<<"Total Balance : "<<balance<<endl<<endl;
}

void modify(){
    cout<<"Account No : "<<account_no<<endl;
	cout<<"Enter Modified Balance: "<<endl;
	cin>>balance;
	cout<<"Modified Successfully!!!!!"<<endl;
}

int return_account_no(){
    return account_no;
}

int return_balance(){
    return balance;
}
};

void store_account(){
    saving acc;
	ofstream Out;
	Out.open("Account.txt",ios::binary|ios::app);
	acc.create();
	Out.write((char *)(&acc), sizeof(saving));
	Out.close();
}

void store_modify_account(int a){
    int x=1;
	saving acc;
	fstream In;
    In.open("Account.txt",ios::binary|ios::in|ios::out);
	if(!In)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	while(!In.eof() && x==1)
	{
		In.read((char *) (&acc), sizeof(saving));
		if(acc.return_account_no()==a)
		{
			acc.show();
			cout<<"Enter The New Details of account: "<<endl;
			acc.modify();
			int pos=(-1)*static_cast<int>(sizeof(saving));
			In.seekp(pos,ios::cur);
		    In.write((char *) (&acc), sizeof(saving));
		    cout<<"Account Data Updated"<<endl;
		    x=x-1;
		  }
	}
	In.close();
	if(x==1)
		cout<<"Account No. Not Found "<<endl;
}

void delete_account(int a){  // int a ma chai hamile deko accnumber aayera basxa
    saving acc;
	ifstream in;
	ofstream out;
	in.open("Account.txt",ios::binary);
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	out.open("Temp.txt",ios::binary);
	in.seekg(0,ios::beg);
	while(in.read((char *) (&acc), sizeof(saving)))
	{
		if(acc.return_account_no()!=a)
		{
			out.write((char *) (&acc), sizeof(saving));
		}
	}
    in.close();
	out.close();
	remove("Account.txt");
	rename("Temp.txt","Account.txt");
	cout<<"Account Deleted .."<<endl;
}

void dispay_stats(){
    saving acc;
	ifstream in;
	in.open("Account.txt",ios::binary);
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	cout<<"                 ACCOUNT HOLDER LIST"<<endl;;
	cout<<"------------------------------------------------------------------------------------------"<<endl;
	cout<<"Account no.      No_Deposit      No_Withdraw     monthlyCharge    Int   Balance     Status"<<endl;//balance = -monthly charge + interest + deposit
	cout<<"------------------------------------------------------------------------------------------"<<endl;
	while(in.read((char *) (&acc), sizeof(saving)))
	{
		acc.display();
	}
	in.close();
}

void deposit(int a){
    int deposit;
	int x=1;
	saving acc;
	fstream File;
    File.open("Account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!"<<endl<<endl;
		return;
	}
	while(!File.eof() && x==1)
	{
		File.read((char *) (&acc), sizeof(saving));
		if(acc.return_account_no()==a)
		{
			acc.show();
				cout<<"To Deposit Amount"<<endl;
				cout<<"------------------"<<endl<<endl;
				cout<<"Enter The amount to be deposited: ";
				cin>>deposit;
				acc.makeDeposit(deposit);
				acc.no_deposits += 1;
            int position=(-1)*static_cast<int>(sizeof(acc));
			File.seekp(position,ios::cur);
			File.write((char *) (&acc), sizeof(saving));
			cout<<"Amount Successfully Deposited!!!"<<endl<<endl;
			x=x-1;
		}
	}
File.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;

}

void withdraw(int a){
    int withdraw;
	int x=1;
	saving acc;
	fstream File;
    File.open("Account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	while(!File.eof() && x==1)
	{
		File.read((char *) (&acc), sizeof(saving));
		if(acc.return_account_no()==a)
		{
		    string y = status(a);
			acc.show();
			if(y == "INACTIVE"){
                    cout<<"Account must have more than 25$ to withdraw again!!!"<<endl<<endl;
				}else{
				cout<<"To Withdraw Amount"<<endl;
				cout<<"-------------------"<<endl<<endl;
				cout<<"Enter The amount to be withdrawn: ";
				cin>>withdraw;cout<<endl;
				int a = acc.return_balance()-withdraw;
				if(a<0){
                    cout<<"Insufficient Balance"<<endl<<endl;
				}else if(a<25){
                    cout<<"Your Account will be In active if you withdraw."<<endl<<endl;
                    cout<<"Do you want to continue? Yes(1)/No(2)"<<endl;
                    int b;
                    cin>>b;
                    if (b == 1){
                        acc.makeWithdrawal(withdraw);
                        acc.no_withdrawals += 1;
                        cout<<"Amount Successfully Withdrawn!!!"<<endl<<endl;
                    }else if(b == 2){
                        return;
                    }else{
                        cout<<"Enter Valid Data"<<endl;
                    }
				}else{
				acc.makeWithdrawal(withdraw);
				acc.no_withdrawals += 1;
				cout<<"Amount Successfully Withdrawn!!!"<<endl<<endl;
				}
				}
            int position=(-1)*static_cast<int>(sizeof(acc));
			File.seekp(position,ios::cur);
			File.write((char *) (&acc), sizeof(saving));

			x=x-1;
		}
	}
File.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;

}
void display_from_file(int a){
	saving acc;
	int x=1;
	ifstream in;
	in.open("Account.txt",ios::binary);
	if(!in)
	{
		cout<<"File could not be open !!"<<endl;
		return;
	}
	cout<<"Account Details: "<<endl;
    	while(in.read((char *) (&acc), sizeof(saving)))
	{
		if(acc.return_account_no()==a)
		{
			acc.show();
			x=x-1;
		}
	}
    in.close();
	if(x==1)
		cout<<"Account No. Not Found"<<endl;
}

string status(int a){
    int i=1;
    saving acc;
    string b;
    ifstream in;
    in.open("Account.txt", ios::binary|ios::in);
    while(!in.eof() && i==1){
    in.read((char *) (&acc), sizeof(saving));
    if(acc.return_account_no() == a){
            int a = acc.return_balance();
        if(a<25){
            b = "INACTIVE";
        }else{
            b = "ACTIVE";
        }
        i=i-1;
    }
    }
    in.close();
    if(i==1)
		cout<<"Account no. Not Found "<<endl;
return b;
}

int main(){
int choice,user,num;
cout<<"             Bank Of Cyber Technicians"<<endl;
cout<<"            DhaniNagar,Switzerland,Nepal"<<endl;
cout<<"               9840000001,9840000002"<<endl<<endl;
cout<<"Are you Admin(1) or Customer(2)?"<<endl;
cin>>user;cout<<endl;
if (user == 1){
do{
    cout<<"List of Functions : "<<endl;
    cout<<"-------------------"<<endl;
    cout<<"1. Modify Account                2. Delete Account"<<endl;
    cout<<"3. View Stats                    4. Exit"<<endl<<endl;
    cout<<"Enter from 1 to 4: ";
    cin>>choice;
    cout<<endl;
    switch(choice){
        case 1:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            store_modify_account(num);
            break;
        case 2:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            delete_account(num);
            break;
        case 3:
            dispay_stats();
            break;
        case 4:
            cout<<"Good Work!!!!!"<<endl<<endl;

            break;
        default:
            cout<<"Enter valid number:"<<endl<<endl;
    }
}while(choice != 4);
}else if (user == 2){
do{
    cout<<"List of Functions : "<<endl;
    cout<<"-------------------"<<endl;
    cout<<"1. Add Account                   2. Withdraw"<<endl;
    cout<<"3. Deposit                       4. View Balance"<<endl;
    cout<<"5. Exit"<<endl<<endl;
    cout<<"Enter from 1 to 5: ";
    cin>>choice;
    cout<<endl;
    switch(choice){
        case 1:
            store_account();
            break;
        case 2:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            withdraw(num);
            break;
        case 3:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            deposit(num);
            break;
        case 4:
            cout<<"Enter Account no: "<<endl;
            cin>>num;cout<<endl;
            display_from_file(num);
            break;
        case 5:
            cout<<"Thank you for visiting Bank of Cyber Technicians"<<endl<<endl;
            break;
        default:
            cout<<"Enter valid number:"<<endl<<endl;
    }
}while(choice != 5);
}else{
cout<<"Enter Valid Data!!!"<<endl;
}
return 0;
}

