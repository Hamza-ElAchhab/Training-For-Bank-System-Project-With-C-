#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string FileNamee = "ClinetsFile.txt";

float ReadNumber()
{
    float Number = 0;
    cout << "Pleas enter Balance : ";
    cin >> Number;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "Invalid Number , Enter a valid one : " << endl;
        cin >> Number;
    }
    return Number;
}

struct st_Information
{
    string AcountNum;
    string PinCode;
    string Name;
    string Phone;
    float balance;
    bool isD;
};
st_Information ReadInfoClient()
{
    st_Information sInfo1;

    cout << "\n__________ Read Info : __________\n\n";
    cout << "Enter Acount Number : ";
    getline(cin >> ws, sInfo1.AcountNum);

    cout << "Enter Pin Code      : ";
    getline(cin, sInfo1.PinCode);

    cout << "Enter Your Name     : ";
    getline(cin, sInfo1.Name);

    cout << "Enter Your Phone    : ";
    getline(cin, sInfo1.Phone);

    sInfo1.balance = ReadNumber();
    cout << "\n---------------------------------\n";

    return sInfo1;
}

string Join_Structer(st_Information sInfo, string sep = "#//#")
{
    string str = "";

    str += sInfo.AcountNum + sep;
    str += sInfo.Phone + sep;
    str += sInfo.Name + sep;
    str += sInfo.Phone + sep;
    str += to_string(sInfo.balance);

    return str;
}

void Add_Record_To_File(string FileName, string Record)
{
    fstream file;
    file.open(FileName, ios::out | ios::app);

    if (file.is_open())
    {
        file << Record << endl;

        file.close();
    }
}

vector<string> ft_split(string str, string delm)
{
    vector<string> vStrings;
    string Word = "";
    int Pos = 0;

    while ((Pos = str.find(delm)) != str.npos)
    {
        Word = str.substr(0, Pos);

        if (Word != "")
        {
            vStrings.push_back(Word);
        }

        str = str.erase(0, (Pos + delm.length()));
    }

    if (str != "")
    {
        vStrings.push_back(str);
    }

    return vStrings;
}

st_Information Fill_ClinetData_ToStructer(string str)
{
    vector<string> vStrings = ft_split(str, "#//#");
    st_Information Info;

    Info.AcountNum = vStrings[0];
    Info.PinCode = vStrings[1];
    Info.Name = vStrings[2];
    Info.Phone = vStrings[3];
    Info.balance = stoi(vStrings[4]);

    return Info;
}

void PrintClientInfo(st_Information Info)
{
    cout << setw(30) << Info.AcountNum << "| " << setw(14) << Info.Phone << "| " << setw(19) << Info.Name << "| " << setw(19)
        << Info.Phone << "|       " << Info.balance << endl;
}

void Add_Client()
{
    char cr = 'y';

    do
    {
        system("cls");
        Add_Record_To_File(FileNamee, Join_Structer(ReadInfoClient()));

        cout << "\nYou Want To Add More : ";
        cin >> cr;

    } while (toupper(cr) == 'Y');
}

vector<st_Information> Load_Data_FromFile_ToVector(string FileName)
{
    vector <st_Information> vST;

    fstream file;
    file.open(FileNamee, ios::in);
    string Record = "";
    st_Information Info;

    if (file.is_open())
    {

        while (getline(file, Record))
        {
            Info = Fill_ClinetData_ToStructer(Record);
            vST.push_back(Info);
        }

        file.close();
    }

    return vST;
}

void PrintAllData(vector<st_Information> vST)
{
    cout << "\n\t\t\t\t\t\tThere are (" << vST.size() << ") Client(s) : \n";
    cout << "\n\t\t__________________________________________________________________________________________\n";
    cout << "\n\t\tAcount Number:|      Pin Cide:|         Name:      |        Phone:      |        Balance: \n";
    cout << "\t\t__________________________________________________________________________________________\n";

    for (st_Information& i : vST)
    {
        PrintClientInfo(i);
    }

    cout << "\t\t__________________________________________________________________________________________\n";
}

void PrintCardOfClinet(st_Information info)
{
    cout << "\nClinet Info : ";
    cout << "\n_________________________\n";
    cout << "Acount Num : " << info.AcountNum << endl;
    cout << "Pin Code   : " << info.PinCode << endl;
    cout << "Name       : " << info.Name << endl;
    cout << "Phone      : " << info.Phone << endl;
    cout << "Balance    : " << info.balance << endl;
    cout << "_________________________\n";
}

string ReadAcountNum()
{
    system("cls");

    string Acount = "";
    cout << "Enter Acount Number : ";
    getline(cin >> ws, Acount);

    return Acount;
}

bool IsClientExists_get_it(string AcountNum, st_Information& info)
{
    vector<st_Information> vClients = Load_Data_FromFile_ToVector(FileNamee);

    for (st_Information& i : vClients)
    {
        if (i.AcountNum == AcountNum)
        {
            info = i;
            return true;
        }
    }
    return false;
}

void FindClinet()
{
    char a = 'y';
    do
    {
        st_Information info;

        if (IsClientExists_get_it(ReadAcountNum(), info))
        {
            PrintCardOfClinet(info);
        }
        else
        {
            cout << endl << "Noo Clinet with this Acount Number !!!";
        }

        cout << "\n\n Do Want to Find Another Clinet : ";
        cin >> a;

    } while (toupper(a) == 'Y');
}

void Sava_VectorData_ToFile(vector<st_Information> vData)
{
    fstream file;
    file.open(FileNamee, ios::out);

    if (file.is_open())
    {
        string Line;

        for (st_Information& i : vData)
        {
            if (i.isD != true)
            {
                Line = Join_Structer(i);
                file << Line << endl;
            }
        }

        file.close();
    }
}

void MarkForDelete(string AcountNum, vector<st_Information> &vST)
{
    for (st_Information& i : vST)
    {
        if (i.AcountNum == AcountNum)
        {
            i.isD = true;
            return;
        }
    }
}

bool DeleteClient()
{
    string AcountNum = ReadAcountNum();
    st_Information info;
    char c;
    vector<st_Information> vData = Load_Data_FromFile_ToVector(FileNamee);

    if (IsClientExists_get_it(AcountNum, info))
    {
        PrintCardOfClinet(info);
        cout << "\nAre You Sure : ";
        cin >> c;

        if (towupper(c) == 'Y')
        {
            MarkForDelete(AcountNum, vData);
            Sava_VectorData_ToFile(vData);
        }

        cout << endl << "Clinet Deleted Successfully.\n";
        return true;
    }
    else
    {
        cout << endl << "Noo Clinet with this Acount Number !!!\n";
        return false;
    }
}

st_Information GetNewClientInfo(string AcountNum)
{
    st_Information sInfo1;
    sInfo1.AcountNum = AcountNum;

    cout << "\n__________ Read Info : __________\n\n";
    cout << "Enter Pin Code      : ";
    getline(cin >> ws, sInfo1.PinCode);

    cout << "Enter Your Name     : ";
    getline(cin, sInfo1.Name);

    cout << "Enter Your Phone    : ";
    getline(cin, sInfo1.Phone);

    sInfo1.balance = ReadNumber();
    cout << "\n---------------------------------\n";

    return sInfo1;
}

void UpDateClient()
{
    vector<st_Information> vData = Load_Data_FromFile_ToVector(FileNamee);
    string AcountNum = ReadAcountNum();
    st_Information info;
    char a = 'b';

    if (IsClientExists_get_it(AcountNum, info))
    {
        PrintCardOfClinet(info);

        cout << endl << "Are You Sure : ";
        cin >> a;
        if (toupper(a) == 'Y')
        {
            cout << "\n\nUpDating : \n";
            for (st_Information& s : vData)
            {
                if (s.AcountNum == AcountNum)
                {
                    s = GetNewClientInfo(AcountNum);
                    break;
                }
            }

            Sava_VectorData_ToFile(vData);
            cout << "\nUpDated Successfully\n";
        }

    }
    else
    {
        cout << "\nClient Does not exists\n";
    }
}




int main()
{

    //Add_Client();




    return 0;
}