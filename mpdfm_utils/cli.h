#pragma once
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>

using namespace std;

namespace cli_util
{
    string strip_str(const string &inpt)
    {
        auto start_it = inpt.begin();
        auto end_it = inpt.rbegin();
        while (isspace(*start_it))
            ++start_it;
        while (isspace(*end_it))
            ++end_it;
        
        try
        {
            return string(start_it, end_it.base());
        }
        catch ( const length_error& e ) // out of range = str w only spaces = empty
        {
            return "";
        }
    }

    string get_input()
    {
        static string input;
        getline(cin, input);
        input = strip_str(input);

        return input;
    }

    bool get_input_by_bool(string question)
    {
        cout << question << endl;
        cout << "( y / n )> ";

        string input = get_input();
        // this converts the input string to lowercase for some reason
        transform(input.begin(), input.end(), input.begin(), ::tolower);;

        if (!(input.length() == 1 && (input == "y" || input == "n")))
        {
            throw invalid_argument("Input '" + input + "' is invalid.");
        }

        return input == "y";
    }

    template <size_t options_size>
    int get_input_with_options(string (&options)[options_size], int default_option=0)
    {
        cout << "Please pick from the options given below:\n\n";

        stringstream choices_str;
        choices_str << "\n( ";

        for (size_t i = 0; i < options_size; i++)
        {
            cout << i;
            if (i == default_option)
                cout << " - default";
            cout << ")  " << options[i] << endl;

            choices_str << i << ( (i == options_size - 1) ? " )" : " / " );
        }

        choices_str << "> ";

        cout << choices_str.str();

        string input = get_input();
        if (input.empty()) return default_option;

        int option_chosen;
        try
        {
            option_chosen = stoi(input);
        }
        catch ( const invalid_argument& e )
        {
            throw invalid_argument("Input '" + input + "' is invalid.");
        }

        if (option_chosen >= options_size)
        {
            throw invalid_argument("Input '" + input + "' is invalid.");
        }

        return option_chosen;
    }
}