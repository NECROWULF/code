#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

namespace ArgumentParser {

struct StringArgument{
    char short_name = 0;
    std::string long_name;
    std::vector<std::string> values;
    std::string description;

    bool has_value = false;
    std::string* store_value = nullptr;
    std::vector<std::string>* store_values = nullptr;

    bool is_multi_value = false;
    int min_counter = 1;
    bool is_positional = false;

    StringArgument& Default(std::string value);
    StringArgument& StoreValue(std::string &str);
    StringArgument& MultiValue(int min_counter = 0);
    StringArgument& Positional();
    StringArgument& StoreValues(std::vector<std::string> &store_values);
};

struct IntArgument{
    char short_name = 0;
    std::string long_name;
    bool has_value = false;
    std::string description;

    std::vector<int> values;

    bool is_multi_value = false;
    int min_counter = 1;
    bool is_positional = false;

    int* store_value = nullptr;
    std::vector<int>* store_values = nullptr;

    IntArgument& MultiValue(int min_counter = 0);

    IntArgument& Positional();

    IntArgument& StoreValues(std::vector<int> &store_values);

    IntArgument& StoreValue(int &n);
    
};

struct Flag{
    char short_name = 0;
    std::string long_name;
    std::string description = "";
    bool value = false;
    bool* store_value = nullptr;

    Flag& Default(bool value);

    Flag& StoreValue(bool &value);
};



class ArgParser {
    public:
        #pragma region constructor
        ArgParser(std::string name);
        #pragma endregion
        
        #pragma region function from main
        IntArgument& AddIntArgument(char short_name,std::string long_name, std::string description);
        IntArgument& AddIntArgument(char short_name,std::string long_name);
        IntArgument& AddIntArgument(std::string long_name, std::string description);
        IntArgument& AddIntArgument(std::string long_name);
                
        StringArgument& AddStringArgument(char short_name,std::string long_name, std::string description);
        StringArgument& AddStringArgument(char short_name,std::string long_name);
        StringArgument& AddStringArgument(std::string long_name, std::string description);
        StringArgument& AddStringArgument(std::string long_name);

        std::string GetStringValue(std::string name);

        int GetIntValue(std::string name, int index);
        int GetIntValue(std::string name);

        Flag& AddFlag(std::string long_name, std::string description);
        Flag& AddFlag(char short_name, std::string long_name, std::string description);
        Flag& AddFlag(char short_name, std::string long_name);

        bool GetFlag(std::string name);

        ArgParser& AddHelp(char short_command, std::string long_command, std::string description);

        std::string HelpDescription();

        bool Parse(int argc, char** argv);
        bool Parse(std::vector<std::string>);

        bool Help();
        #pragma endregion
    private:
        std::string name_;
        std::vector<IntArgument> int_arguments_;
        std::vector<StringArgument> string_arguments_;
        std::vector<Flag> flags_;
        
        std::string short_help = "";
        std::string long_help = "";
        std::string help_description = "";

};
    std::string FromCharptrToString(char* c);
    bool CheckLongCommand(std::string command, std::string name);
    bool CheckShortCommand(std::string command, char name);
    int ToInt(std::string s);
    void Set(std::string arg, std::string &command, std::string &name);
    bool IsMultyCommand(std::string command);
    std::string ToString(int n);
} // namespace ArgumentParser
