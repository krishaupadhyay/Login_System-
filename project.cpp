#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>
using namespace std;
class invalidinput : public exception
{
    const char *what() const noexcept override
    {
        return "You entered wrong input. Please enter 0 or 1";
    }
};
class User
{
private:
    string Username;
    string Password;

public:
    User() {};
    User(string name, string pass) : Username(name), Password(pass) {}

    string getpass()
    {
        return Password;
    }

    string getUsername()
    {
        return Username;
    }
};
bool safeInput(int &num)
{
    cin >> num; // If the user types something invalid (like a or @),
                // cin goes into a fail state, and this line fails.
    if (cin.fail())
    {
        cin.clear();             // Clear error flag
        cin.ignore(10000, '\n'); // Discard invalid input
        return false;
    }

    return true;
}

class Usermanager
{
private:
    vector<User> users;

public:
    //::::::::::::::::::::::::::::::::::::::::::::USERMANAGER CONSTRUCTOR::::::::::::::::::::::::::::::::::::::::::::::::
    Usermanager()
    {
        Load_from_file(); // Load users from on startup
    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::LOAD_FROM_FILE::::::::::::::::::::::::::::::::::::::::::::::::::::
    void Load_from_file()
    {

        ifstream fin("DataBase.txt");
        if (!fin)
        {
            cerr << "Error: Could not open file for reading." << endl;
            return;
        }
        string uname, pword;
        while (getline(fin, uname) && getline(fin, pword))
        { // get each line from file and store previous data in vector
            users.push_back(User(uname, pword));
        }

        fin.close();
    }

    //::::::::::::::::::::::::::::::::::::::::::::REGISTER USER::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void register_User()
    {

        string pass, name;
        cout << "Enter Username-";
        cin >> name;
        // cin >> name;
        cout << "Enter password-";
        cin >> pass;
        if (!check_password(pass))
        {
            cout << "password invalid!" << endl;
            cout << "It must contain at least 8 characters,";
            cout << "one uppercase letter,";
            cout << "one lowercase letter,";
            cout << "one digit,";
            cout << "one special character." << endl;
            cout << "TRY AGAIN--" << endl;
            return;
        }
        cout << endl;
        // cin >> pass;
        if (!users.empty())
        {
            for (int i = 0; i < users.size(); i++)
            {
                if (users[i].getUsername() == name)
                {
                    cout << "User Allready Exist " << endl;
                    cout << "If you have already account then press 0 for login page or 1 for exit" << endl;

                    while (true)
                    {
                        int n;
                        cin >> n;
                        try
                        {
                            if (cin.fail() || (n != 0 && n != 1))
                            {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                throw invalidinput();
                            }
                            if (n == 0)
                            {
                                Login();
                                return; // Add return to exit the function
                            }
                            else if (n == 1)
                            {
                                cout << "Thank you..." << endl;
                                return; // Add return to exit the function
                            }
                        }
                        catch (exception &e)
                        {
                            cout << e.what() << endl;
                            continue; // Continue the loop to ask for input again
                        }
                    }
                }
            }
        }

        users.push_back(User(name, pass));
        savetofile(name, pass);
        cout << "Register User succesfully" << endl;
    }
    //:::::::::::::::::::::::::::::::::::::::::::CHECK PASSWORD:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    bool check_password(string const &pass)
    {
        if (pass.size() < 8)
        {
            return false;
        }

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

        for (char ch : pass)
        {
            if (islower(ch))
            {
                hasLower = true;
            }
            else if (isupper(ch))
            {
                hasUpper = true;
            }
            else if (isdigit(ch))
            {
                hasDigit = true;
            }
            else
            {
                hasSpecial = true;
            }
        }
        return hasUpper && hasLower && hasDigit && hasSpecial; // if all are true then it will return true otherwise false
    }

    //::::::::::::::::::::::::::::::::::::::::::::::::::LOGIN USER::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void Login()
    {
        cout << "\n========== Login System ==========\n";
        string pass;
        string id;
        cout << "Enter Username-";
        cin >> id;
        // cin >> name; 
        cout << "Enter password-";
        cin >> pass;
        bool flag1 = false;
        // cin >> pass;
        bool flag2 = false;
        for (int i = 0; i < users.size(); i++)
        {

            if (users[i].getUsername() == id)
            {
                flag1 = true;
                if (users[i].getpass() == pass)
                {
                    flag2 = true;
                    cout << "===============Login SucessFull==============" << endl;
                }
            }
        }
        if (!flag1)
        {
            cout << "Invalid Username Try Again!!!" << endl;
            cout << "If you don't have account then click 0 for register of sign-up or 1 for exit" << endl;
         
             
            while (true)
            {
                int n;
                cin >> n;
                try
                {
                    if (cin.fail() || (n != 0 && n != 1))
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        throw invalidinput();
                    }
                    if (n == 0)
                    {
                       register_User();
                        return; // Add return to exit the function
                    }
                    else if (n == 1)
                    {
                        cout << "Thank you..." << endl;
                        return; // Add return to exit the function
                    }
                }
                catch (exception &e)
                {
                    cout << e.what() << endl;
                    continue; // Continue the loop to ask for input again
                }
            }
        }
    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::SHOW USER LIST ::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void Show_Userlist()
    {
        cout << "----------------User List--------------" << endl;
        for (int i = 0; i < users.size(); i++)
        {

            cout << "[" << i + 1 << "]" << users[i].getUsername() << endl;
        }
        if (users.empty())
        {
            cout << "No User Detail Exist........" << endl;
        }
    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::SEARCH USER::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void Search_User()
    {
        string name;
        bool flag = false;
        cout << "Enter username which your looking for..." << endl;

        cout << "Enter Username-";
        cin >> name;

        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == name)
            {
                flag = true;
                cout << "User Found" << endl;
            }
        }
        if (!flag)
        {
            cout << "User not found........" << endl;
        }
    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::DELETE USER::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void Delete_User()
    {
        string name,pass;
        cout << "Enter Username whose Account you want to delete" << endl;
        cin >> name;
        cout << "Enter Password whose Account you want to delete" << endl;
        cin >> pass;
        
        bool flag = false;
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == name&&users[i].getpass()==pass)
            {
                flag = true;
                delete_from_file(users[i].getUsername(), users[i].getpass());

                users.erase(users.begin() + i);

                cout << "User delete Sucessfully!!" << endl;
                break;
            }
        }
        if (!flag)
        {
            cout << "User not found........" << endl;
        }
    }

    //::::::::::::::::::::::::::::::::::::::::::::SAVE_TO_FILE:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    void savetofile(string const id, string const pass)
    {
        ofstream fout("DataBase.txt", ios::app);
        if (!fout)
        {
            cerr << "Error: Could not open file for reading." << endl;
            return;
        }
        fout << id << endl;

        fout << pass << endl;
        // for(auto &i: users){
        //     fout<<"ID:"<<i.getUsername()<<endl;
        //     fout<<"Pass:"<<i.getpass()<<endl;
        // }
        fout.close();
    }
    //:::::::::::::::::::::::::::::::::::::::::::::::DELETE_TO_FILE:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    void delete_from_file(string id, string pass)
    {
        ifstream fin("DataBase.txt");
        if (!fin)
        {
            cerr << "Error: Could not open file for reading." << endl;
            return;
        }
        vector<string> lines;
        string uname, pword;
        // Step 1: Read all lines
        while (getline(fin, uname) && getline(fin, pword))
        {
            if (uname == id && pword == pass)
            {
                // Step 2: Skip the both line to delete
                continue;
            }
            lines.push_back(uname);
            lines.push_back(pword);
        }

        fin.close();
        // Step 3: Write back remaining lines
        ofstream fout("DataBase.txt");
        if (!fout)
        {
            cerr << "Error: Could not open file for reading." << endl;
            return;
        }
        for (const auto &i : lines)
        {

            fout << i << endl;
        }
        fout.close();

        // cout<<"user delete succesfully"<<endl;
    }

    bool safeInput(int &num)
    {
        cin >> num; // If the user types something invalid (like a or @),
                    // cin goes into a fail state, and this line fails.
        if (cin.fail())
        {
            cin.clear();             // Clear error flag
            cin.ignore(10000, '\n'); // Discard invalid input
            return false;
        }

        return true;
    }
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::MAIN::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main()
{
    Usermanager u;
    int choice;
    do
    {
        cout << "---------Hey! Welcome in our Login page-----------------" << endl;
        cout << "1: Register User" << endl;
        cout << "2:Login" << endl;
        cout << "3:Show User List" << endl;
        cout << "4:Search User" << endl;
        cout << "5:Delete User" << endl;
        cout << "6:Exit" << endl;
        cout << "Enter your choice" << endl;
        try
        {
            if (!safeInput(choice))
            {
                cout << "Invalid input. Please enter a number." << endl;
                continue;
            }
        }
        catch (exception &w)
        {
            cout << w.what() << endl;
        }

        if (choice == 6)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            u.register_User();
            break;
        case 2:
            u.Login();
            break;
        case 3:
            u.Show_Userlist();
            break;
        case 4:
            u.Search_User();
            break;
        case 5:
            u.Delete_User();
            break;
        default:

            cout << "invalid choice!!" << endl;
            break;
        }

    } while (1);

    return 0;
}