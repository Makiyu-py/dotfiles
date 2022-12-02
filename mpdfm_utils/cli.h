#pragma once
#include <iostream>
#include "../include/asker/asker.hpp"

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
        return asker::confirm(question);
    }

    template <size_t options_size>
    string get_input_with_options(string (&options)[options_size])
    {
        return asker::selectList("Please pick from the options given below:", options);
    }
}