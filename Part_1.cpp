#include <iostream>
#include <string>
#include <stack>
using namespace std;

string total_str = "";

bool is_equal(char c) { return c == '='; }
bool is_op(char c) { return c == '+' || c == '*' || c == '-' || c == '/' || c == '$'; }
bool is_mult(char c) { return c == '*'; }
bool is_div(char c) { return c == '/'; }
void remove_spaces(string &str) // Removes spaces and adds $ at end
{
    for (auto i = str.begin(); i < str.end(); i++)
    {
        if (isspace(*i))
            str.erase(i, i + 1);
    }
    str += '$';
}
string convert_to_string(int num) // Converts postive num to strings
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

string get_string() // To give variable names
{
    static int a = 0;
    a++;
    return "t" + convert_to_string(a);
}

void Addition_Subtraction(string &str, int start) // For Addition & Subtraction
{
    string str1 = "", str2 = "";
    int initial = 0, final = 0, check = 0, check1 = 0;
    for (int i = start; i < str.length(); i++)
    {
        if (!is_op(str[i]))
        {
            if (!check)
                str1 += str[i];
            else
                str2 += str[i];
            if (initial == 0)
                initial = i;
        }
        else if ((str[i] == '+' || str[i] == '-' || str[i] == '$') && str2 == "")
        {
            check = 1;
            if (str[i] == '-')
                check1 = 1;
        }
        else
        {
            string my_str = get_string();
            check = 0;
            if (!check1)
                total_str += my_str + " = " + str1 + " + " + str2 + '\n';
            else
                total_str += my_str + " = " + str1 + " - " + str2 + '\n';
            final = i - 1;
            str.replace(initial, final - initial + 1, my_str);
            i = initial - 1;
            initial = 0, final = 0, check1 = 0, str1 = "", str2 = "";
        }
    }
}

void Multiplication_Division(string &str, int start) // For multiplication & division
{
    int check = 0, check1 = 0, initial = 0, final = 0;
    string str1 = "", str2 = "";
    for (int i = start; i < str.length(); i++)
    {
        if (!is_op(str[i]))
        {
            if (!check)
                str1 += str[i];
            else
                str2 += str[i];
            if (initial == 0)
                initial = i;
        }
        else if ((is_mult(str[i]) || is_div(str[i])) && str2 == "")
        {
            check = 1;
            if (is_div(str[i]))
                check1 = 1;
        }
        else if (str2 != "")
        {
            string my_str = get_string();
            check = 0;
            if (!check1)
                total_str += my_str + " = " + str1 + " * " + str2 + '\n';
            else if (str2 != "0")
                total_str += my_str + " = " + str1 + " / " + str2 + '\n';
            else // If division by zero error occured
                throw "Division by zero";
            final = i - 1;
            str.replace(initial, final - initial + 1, my_str);
            i = initial - 1;
            initial = 0, final = 0, check1 = 0, str1 = "", str2 = "";
        }
        else
            str1 = "", check = 0, initial = 0, final = 0, check1 = 0;
    }
}

void parse_str(string &str, int start)
{
    // First parse the string for multiplication & division
    // Each time replace the variable with the expression
    Multiplication_Division(str, start);

    // Then parse the whole thing again for addition & subtraction
    // Each time replace the variable with the expression
    Addition_Subtraction(str, start);

    // For remaining part of the string
    str.pop_back();
    for (int i = 0; i < str.length(); i++)
    {
        if (!is_equal(str[i]))
            total_str += str[i];
        else
            total_str += " = ";
    }
    total_str += '\n';
}

void check_equal(string str) // Checks whether equal is present or not
{
    remove_spaces(str); // Removes spaces and adds $
    int start_parsing = 0;
    int choice = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (is_equal(str[i]))
        {
            choice = 1;
            start_parsing = i + 1;
            break;
        }
    }
    if (choice) // If present, then passes to next function
        parse_str(str, start_parsing);
    else // Else stores in the total string
    {
        total_str += "print ";
        for (int i = 5; i < str.length() - 1; i++)
        {
            total_str += str[i];
        }
        total_str += '\n';
    }
}

int main()
{
#ifndef INPUT
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#else
#endif
    try
    {
        while (cin.peek() != EOF)
        {
            string str;
            getline(cin, str);
            check_equal(str);
        }
        cout << total_str;
    }
    catch (const char *msg)
    {
        cout << "ERROR !! Division by zero" << '\n';
    }
}