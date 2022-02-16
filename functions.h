#pragma once
#include <string>
#include <vector>

#include "cursor.cpp"

void print_text 
(int lines, int line_length, std::vector <std::pair <int, std::string>> buff_text, std::vector <int> &THICCNESS, std::vector <int> &LINEON, Cursor &cur);

void print_line 
(int line_number, int line_length, char mode, int percentage);

void print_curs 
(Cursor cur, int winx, int winy);

void clear_line  
(int line_number, int line_length);

int parse_command
(char x, Cursor &cur, int winx, int winy, int total_lines, std::vector <int> &THICCNESS, std::vector <int> &LINEON, std::vector <int> &buff_text_lines, std::vector <int> &buff_text_width);

void log(std::string str);
void logln(std::string str);
void clear_log();
