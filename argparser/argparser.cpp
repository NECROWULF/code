#include <iostream>
#include <vector>
#include <string>

#include "argparser.h"



namespace ArgumentParser{
    StringArgument& StringArgument::Default(std::string value){
        this->values.push_back(value);

        return *this;
    }

    StringArgument& StringArgument::StoreValue(std::string &str){
        store_value = &str;

        return *this;
    }

    StringArgument& StringArgument::MultiValue(int min_counter){
        this->is_multi_value = true;
        this->min_counter = min_counter;
        return *this;
    }

    StringArgument& StringArgument::Positional(){
        this->is_positional = true;
        return *this;
    }

    StringArgument& StringArgument::StoreValues(std::vector<std::string> &store_values){
        this->store_values = &store_values;

        return *this;
    }

    IntArgument& IntArgument::MultiValue(int min_counter){
        this->is_multi_value = true;
        this->min_counter = min_counter;
        return *this;
    }

    IntArgument& IntArgument::Positional(){
        this->is_positional = true;
        return *this;
    }

    IntArgument& IntArgument::StoreValues(std::vector<int> &store_values){
        this->store_values = &store_values;

        return *this;
    }

    IntArgument& IntArgument::StoreValue(int &n){
        store_value = &n;

        return *this;
    }

    Flag& Flag::Default(bool value){
        this->value = value;

        return *this;
    }

    Flag& Flag::StoreValue(bool &value){
        this->store_value = &value;

        return *this;
    }

    ArgParser::ArgParser(std::string name){
        this->name_ = name;
    }
    
    IntArgument& ArgParser::AddIntArgument(char short_name,std::string long_name, std::string description){
        IntArgument int_argument;
        int_argument.short_name = short_name;
        int_argument.long_name = long_name;
        int_argument.description = description;
        this->int_arguments_.push_back(int_argument);
        return int_arguments_[int_arguments_.size() - 1];
    }
    IntArgument& ArgParser::AddIntArgument(char short_name,std::string long_name){
        return AddIntArgument(short_name, long_name, "");
    }
    IntArgument& ArgParser::AddIntArgument(std::string long_name){
        return AddIntArgument(0, long_name, "");
    }
    IntArgument& ArgParser::AddIntArgument(std::string long_name, std::string description){
        return AddIntArgument(0, long_name, description);
    }

    StringArgument& ArgParser::AddStringArgument(char short_name, std::string long_name, std::string description){
        StringArgument string_argument;
        string_argument.short_name = short_name;
        string_argument.long_name = long_name;
        string_argument.description = description;
        this->string_arguments_.push_back(string_argument);

        return string_arguments_[string_arguments_.size()-1];
    }
    StringArgument& ArgParser::AddStringArgument(std::string long_name){
        return AddStringArgument(0,long_name, "");
    }
    StringArgument& ArgParser::AddStringArgument(char short_name, std::string long_name){
        return AddStringArgument(short_name,long_name, "");
    }


    std::string ArgParser::GetStringValue(std::string name){
        for(int i = 0; i < this->string_arguments_.size();++i){
            if(this->string_arguments_[i].long_name == name){
                return string_arguments_[i].values[0];
            }
        }
        return "";
    }


    int ArgParser::GetIntValue(std::string name, int index){
        for(int i = 0; i < this->int_arguments_.size();++i){
            if(this->int_arguments_[i].long_name == name){
                return this->int_arguments_[i].values[index];
            }
        }
        return 0;
    }
    int ArgParser::GetIntValue(std::string name){
        for(int i = 0; i < this->int_arguments_.size();++i){
            if(this->int_arguments_[i].long_name == name){

                return this->int_arguments_[i].values[0];
            }
        }
        return 0;
    }


    Flag& ArgParser::AddFlag(char short_name, std::string long_name, std::string description){
        Flag flag;
        flag.short_name = short_name;
        flag.long_name = long_name;
        flag.description = description;
        this->flags_.push_back(flag);
        return this->flags_[this->flags_.size() - 1];
    }
    Flag& ArgParser::AddFlag(std::string long_name, std::string description){
        return AddFlag(0,long_name,description);
    }

    Flag& ArgParser::AddFlag(char short_name, std::string long_name){
        return AddFlag(short_name, long_name, "");
    }


    bool ArgParser::GetFlag(std::string name){
        for(int i = 0; i < this->flags_.size(); ++i){
            if(this->flags_[i].long_name == name){
                return this->flags_[i].value;
            }
        }
        return false;
    }


    ArgParser& ArgParser::AddHelp(char short_command, std::string long_command, std::string description){
        short_help = std::string("-")+short_command;
        long_help = std::string("--")+long_command;
        help_description = description;
        return *this;
    }


    std::string ArgParser::HelpDescription(){
        std::string s = "";
        s +=  help_description + '\n';
        for(StringArgument argument : this->string_arguments_){
            s += argument.short_name + std::string("\t") + argument.long_name + std::string("=<string>") + '\t' + argument.description;
            if(argument.is_multi_value){
                s += std::string("\t[repeated, min args = ") + ToString(argument.min_counter)+ std::string("]");
            }
            if(argument.values.size()){
                s+=std::string("\t[defaut = ") + argument.values[0] + "]";
            }
            s += '\n';
        }
        for(IntArgument argument : this->int_arguments_){
            s += argument.short_name + std::string("\t") + std::string(argument.long_name) + std::string("=<int>") +std::string("\t") + std::string(argument.description) + '\n';
            if(argument.is_multi_value){
                s += std::string("\t[repeated, min args = ") + ToString(argument.min_counter) + std::string("]");
            }
            if(argument.values.size()){
                s += std::string("\t[defaut = ") + ToString(argument.values[0]) + std::string("]");
            }
            s += '\n';
        }
        for(Flag argument : this->flags_){
            s += argument.short_name + std::string("\t") + std::string(argument.long_name) + std::string("\t") + std::string(argument.description) + '\n';
            if(argument.value){
                s += std::string("\t[defaut = true") + ToString(argument.value) + std::string("]");
            }else{
                s += std::string("\t[defaut = false") + ToString(argument.value) + std::string("]"); 
            }
            s += '\n';
        }
        return s;
    }


    bool ArgParser::Parse(int argc, char** argv){
        std::vector<std::string> args;
        for(int i = 0; i < argc; ++i){
            args.push_back(FromCharptrToString(argv[i]));
        }
        return Parse(args);
    }

    bool ArgParser::Parse(std::vector<std::string> args){
        int size = args.size();
        for(int i = 0; i < size; ++i){
            if(IsMultyCommand(args[i])){
                for(int j = 1; j < args[i].length() - 1; ++j){
                    args.push_back(std::string("-")+args[i][j]);
                }
                args[i] = std::string("-")+args[i][args[i].length() - 1];
            }
        }

        if(args[1] == short_help || args[1] == long_help){
            return Help();
        }

        for(int argument_index = 1; argument_index < args.size(); ++argument_index){
            if(args[argument_index][0] == '-'){
            bool search = true;
            bool is_short = (args[argument_index][1] != '-');
            std::string command = "";
            std::string name = "";
            Set(args[argument_index], command, name);
            bool is_flag = false;
            if(name == ""){
                for(int i = 0; i < this->flags_.size(); ++i){
                    if(
                        is_short? CheckShortCommand(command, this->flags_[i].short_name) 
                        : CheckLongCommand(command, this->flags_[i].long_name)
                    ){
                        is_flag = true;
                        this->flags_[i].value = true;
                        break;
                    }
                }
                if(!is_flag){
                    name = args[++argument_index];
                }
            }
            if(!is_flag){
                if(is_short){
                    for(int i = 0; i < this->string_arguments_.size(); ++i){
                        if(CheckShortCommand(command, this->string_arguments_[i].short_name)){
                            search = false;
                            
                            if(string_arguments_[i].has_value){
                                string_arguments_[i].values.push_back(name);
                            }else{
                                string_arguments_[i].has_value = true;
                                if(string_arguments_[i].values.size()){
                                    string_arguments_[i].values[0] = name;
                                }else{
                                    string_arguments_[i].values.push_back(name);
                                }
                            }
                            
                        }
                    }
                    if(search){
                        for(int i = 0; i < this->int_arguments_.size(); ++i){
                            if(CheckShortCommand(command, this->int_arguments_[i].short_name)){
                                search = false;
                                int_arguments_[i].values.push_back(ToInt(name));
                            }
                        }
                    }
                    if(search){
                        for(int i = 0; i < this->flags_.size(); ++i){
                            if(CheckShortCommand(command, this->flags_[i].short_name)){
                                search = false;
                                flags_[i].value = true;
                            }
                        }
                    }
                }else{
                    for(int i = 0; i < this->string_arguments_.size(); ++i){
                        if(CheckLongCommand(command, this->string_arguments_[i].long_name)){
                            search = false;
                            if(string_arguments_[i].has_value){
                                string_arguments_[i].values.push_back(name);
                            }else{
                                string_arguments_[i].has_value = true;
                                if(string_arguments_[i].values.size()){
                                    string_arguments_[i].values[0] = name;
                                }else{
                                    string_arguments_[i].values.push_back(name);
                                }
                            }
                        }
                    }
                    if(search){
                        for(int i = 0; i < this->int_arguments_.size(); ++i){
                            if(CheckLongCommand(command, this->int_arguments_[i].long_name)){
                                search = false;
                                int_arguments_[i].values.push_back(ToInt(name));
                            }
                        }
                    }
                    if(search){
                        for(int i = 0; i < this->flags_.size(); ++i){
                            if(CheckLongCommand(command, this->flags_[i].long_name)){
                                search = false;
                                flags_[i].value = true;
                            }
                        }
                    }
                }
                    if(search) return false;
                }

            }else{
                bool search = true;
                for(int i = 0; i < this->string_arguments_.size(); ++i){
                    if(this->string_arguments_[i].is_positional){
                        search = false;
                        if(string_arguments_[i].has_value){
                            string_arguments_[i].values.push_back(args[argument_index]);
                        }else{
                            string_arguments_[i].has_value = true;
                            if(string_arguments_[i].values.size()){                                        
                                string_arguments_[i].values[0] = args[argument_index];
                            }else{
                                string_arguments_[i].values.push_back(args[argument_index]);
                            }
                        }            
                    }
                }
                if(search){
                    for(int i = 0; i < this->int_arguments_.size(); ++i){
                        if(this->int_arguments_[i].is_positional){
                            search = false;
                            if(int_arguments_[i].has_value){
                                int_arguments_[i].values.push_back(ToInt(args[argument_index]));
                            }else{
                                int_arguments_[i].has_value = true;
                                if(int_arguments_[i].values.size()){                                        
                                    int_arguments_[i].values[0] = ToInt(args[argument_index]);
                                }else{
                                    int_arguments_[i].values.push_back(ToInt(args[argument_index]));
                                }
                            } 
                        }
                    }
                }
                if(search) return false;
            }
        }

        for(IntArgument argument:this->int_arguments_){
            if(argument.min_counter > argument.values.size())return false;
            if(argument.store_values != nullptr) *argument.store_values = argument.values;
        }
        for(StringArgument argument:this->string_arguments_){
            if(argument.min_counter > argument.values.size())return false;
            if(argument.store_value != nullptr) *argument.store_value = argument.values[0];
        }
        for(Flag flag:this->flags_){
            if(flag.store_value != nullptr){
                (*flag.store_value) = flag.value;
                
            }
        }


        return true;
    }

    bool ArgParser::Help(){
        std::cout<<HelpDescription()<<std::endl;
        return true;
    }

    std::string FromCharptrToString(char* c){
        std::string s = "";
        while(*c!='\0'){
            s+=*c;
            ++c;
        }
        return s;
    }
    bool CheckLongCommand(std::string command, std::string name){
        return command == "--"+name; 
    }
    bool CheckShortCommand(std::string command, char name){
        return command == std::string("-")+name;
    }
    int ToInt(std::string s){
        int n = 0;
        for(char c: s){
            n = 10*n + c - '0';
        }
        return n;
    }
    void Set(std::string arg, std::string &command, std::string &name){
        bool b = false;
        for(char c: arg){
            if(c=='='){
                b = true;
            }else{
                if(b){
                    name += c;
                }else{
                    command += c;
                }
            }
        }
    }
    bool IsMultyCommand(std::string command){
        return command[0]=='-' && command[1] != '-' && command.length() > 2 && command[2] != '=';
    }
    std::string ToString(int n){
        std::string s = "";
        while(n > 0){
            s = char(n%10+'0')+s;
            n/=10;
        }
        return s;
    }
}
