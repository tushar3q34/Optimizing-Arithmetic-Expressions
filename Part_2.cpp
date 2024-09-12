#include <iostream>
#include <string>
#include <map>
using namespace std;
/*
WORKING :
    1. Takes input statement by statement
    2. For each statement, 3 major cases possible
        a) Both numbers -> Calculates value and puts it in Values map
        b) One var -> Checks accordingly
        c) Two Var -> Checks accordingly
    3. If any new variable(like p1,p2...) is created, an old variable is
       mapped to it using Names map
    4. Final output is stored in my_str string
*/
map<string, int> Values;
map<string, string> Names;
string my_str = "";

class Optimize
{
    bool is_equal(char c) { return c == '='; }
    bool is_op(char c) { return c == '+' || c == '*' || c == '-' || c == '/' || c == '$'; }
    bool is_digit(char c) { return '0' <= c && c <= '9'; }
    void remove_spaces(string &str)
    {
        for (auto i = str.begin(); i < str.end(); i++)
        {
            if (isspace(*i))
                str.erase(i, i + 1);
        }
    }
    int str_to_num(string &str)
    {
        int num = 0;
        if (str[0] == '-')
        {
            for (int i = 1; i < str.length(); i++)
                num = num * 10 + (str[i] - '0');
            num *= (-1);
        }
        else
        {
            for (int i = 0; i < str.length(); i++)
                num = num * 10 + (str[i] - '0');
        }
        return num;
    }
    string num_to_str(int num)
    {
        string str = "";
        if (num > 0)
        {
            while (num != 0)
            {
                str = (char)(num % 10 + 48) + str;
                num /= 10;
            }
        }
        else if (num < 0)
        {
            num = num * (-1);
            while (num != 0)
            {
                str = (char)(num % 10 + 48) + str;
                num /= 10;
            }
            str = '-' + str;
        }
        else
            str = "0";
        return str;
    }

private:
    string str0, str1, str2, op;
    /*
    str0 -> Part before equal
    str1 -> Part after equal and before op
    str2 -> Part after op
    op -> Operator
    */
public:
    // Optimize is constructor function -> Divides str into str0,str1,str2,op
    Optimize(string str)
    {
        remove_spaces(str);
        int choice = 0;
        str0 = "", str1 = "", str2 = "", op = "";
        for (int i = 0; i < str.length(); i++)
        {
            if (!is_equal(str[i]) && !is_op(str[i]))
            {
                if (choice == 0)
                    str0 += str[i];
                else if (choice == 1)
                    str1 += str[i];
                else
                    str2 += str[i];
            }
            else if (is_equal(str[i]))
                choice = 1;
            else
            {
                choice = 2;
                op += str[i];
            }
        }
        if (str2 != "" && str1 != "") // If both str1 & str2 non empty
        {
            if (is_digit(str1[0]) && is_digit(str2[0])) // If both numbers
                Calculate();
            else if (is_digit(str1[0]) || is_digit(str2[0])) // If one is number
                One_Var();
            else
                Both_Var(); // If both are variables
        }
        else if (str2 == "" && str1 != "") // If no op but equal sign is there
        {
            if (!is_digit(str1[0])) // If str1 is a variable
            {
                if (Names.find(str1) != Names.end())
                {
                    Names[str0] = Names[str1];
                    my_str.replace(my_str.find(Names[str0]), Names[str0].length(), str0);
                }
                else
                    Values[str0] = Values[str1];
            }
            else // If str1 is a number
            {
                Values[str0] = str_to_num(str1);
            }
        }
        else // If print statement
        {
            string_with_no_equal(str);
        }
    }
    void string_with_no_equal(string &str) // For print statements
    {
        string s;
        for (int i = 5; i < str.length(); i++)
        {
            s += str[i];
        }
        if (Names.find(s) != Names.end())
        {
            cout << my_str;
            cout << "print " << s << '\n';
            my_str = "";
        }
        else
        {
            cout << my_str;
            cout << "print " << Values[s] << '\n';
            my_str = "";
        }
    }
    void Both_Var() // If both str1 & str2 are variables
    {
        if (Values.find(str1) != Values.end() && Values.find(str2) != Values.end())
        {
            // Both have values
            str1 = num_to_str(Values[str1]);
            str2 = num_to_str(Values[str2]);
            Calculate();
        }
        else
        {
            // Since both of them are not numbers, we need to add a
            // statement in my_str about them and thus we first
            // reduce them to their known values/names(if any)
            // and then add a statement to my_str
            if (Names.find(str1) != Names.end())
                str1 = Names[str1];
            if (Names.find(str2) != Names.end())
                str2 = Names[str2];
            if (Values.find(str1) != Values.end())
                str1 = num_to_str(Values[str1]);
            if (Values.find(str2) != Values.end())
                str2 = num_to_str(Values[str2]);
            add_to_my_str();
        }
    }
    void One_Var() // If one of them is number
    {
        if (is_digit(str1[0]))
        {
            if (Values.find(str2) != Values.end())
            {
                str2 = num_to_str(Values[str2]);
                Calculate();
            }
            else
            {
                if (Names.find(str2) != Names.end())
                    str2 = Names[str2];
                add_to_my_str();
            }
        }
        else
        {
            if (Values.find(str1) != Values.end())
            {
                str1 = num_to_str(Values[str1]);
                Calculate();
            }
            else
            {
                if (Names.find(str1) != Names.end())
                    str1 = Names[str1];
                add_to_my_str();
            }
        }
    }
    void add_to_my_str() // For adding statements to my_str
    {
        static int a = 1;
        string s = "p" + num_to_str(a);
        Names[str0] = s;
        my_str += s + " = " + str1 + " " + op + " " + str2 + "\n";
        a++;
    }
    void Calculate() // For calculation
    {
        int num;
        if (op == "*")
            num = str_to_num(str1) * str_to_num(str2);
        else if (op == "+")
            num = str_to_num(str1) + str_to_num(str2);
        else if (op == "-")
            num = str_to_num(str1) - str_to_num(str2);
        else
        {
            if (str_to_num(str2) != 0)
                num = str_to_num(str1) / str_to_num(str2);
            else
                throw "Division by zero";
        }
        Values[str0] = num;
    }
};

int main()
{
#ifndef INPUT_OUTPUT
    freopen("output1.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);
#else
#endif
    try
    {
        while (cin.peek() != EOF)
        {
            string str;
            getline(cin, str);
            if (str != "ERROR !! Division by zero")
                Optimize Obj(str);
            else
                break;
        }
        if (my_str != "")
            cout << my_str;
    }
    catch (const char *msg)
    {
        cout << "ERROR !! Division by zero" << '\n';
    }
}