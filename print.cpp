#include <string>
#include <utility>
#include <locale.h>
#include <ncurses.h>
#include <fstream>

#include "functions.h"

void print_text (
        int lines, int line_length, 
        std::vector <std::pair <int, std::string>> buff_text, 
        std::vector <int> &THICCNESS, std::vector <int> &LINEON,
        Cursor &cur
    )
{
    int buff_pos = 0;
    bool bool_once = true;
    int lastll = 0;
    bool print = true;
    int buff_line = 0;
    int last_line = -1;
    int that_line = -1;
    for (int64_t i = 0; i < lines; i++) {
        if (buff_line == cur.oline - cur.vf && bool_once) {
            cur.line = i;
            bool_once = false;
        }
        if (buff_line != lastll) {
            lastll = buff_line;
            cur.lastline = i;
            cur.lastline_lines = 1 + (buff_text[buff_line].second.length()%(line_length-4));
        }
        LINEON[i] = buff_line;
        cur.vl = buff_line+cur.vf;
        THICCNESS[i] = -1;
        move(i, 0);
        clrtoeol();
        if (buff_line < buff_text.size() && last_line != buff_text[buff_line].first) {
            attron(COLOR_PAIR(4));
            mvwprintw(stdscr, i, 0, "%3d", buff_text[buff_line].first);
            attroff(COLOR_PAIR(4));
            last_line = buff_text[buff_line].first;
        } else {
            mvwprintw(stdscr, i, 0, "   ");
        }
        for (int64_t j = 4; j < line_length; j ++) {
            char c;
            if (buff_line < buff_text.size()) c = buff_text[buff_line].second[buff_pos];
            else {
                c = '\n';
                THICCNESS[i] = 0;
                buff_pos = 0;
                buff_line++;
                break;
            }
            if (c == '\n') {
                THICCNESS[i] = j-5;
                buff_pos = 0;
                buff_line++;
                break;
            }
            mvwprintw(stdscr, i, j, "%c", c);
            buff_pos++;
        }
        if (THICCNESS[i] == -1) {
            THICCNESS[i] = line_length-5;
        }
        if (buff_line != 0 && buff_line < buff_text.size() && buff_text[buff_line-1].second == "\n") {
            THICCNESS[i] = 0;
        }
    }
}

void print_line
(int line_number, int line_length, char mode, int percentage)
{
    if (mode == 'n') {
        attron(A_REVERSE | COLOR_PAIR(1));
        mvwprintw(stdscr, line_number, 0, "%s", " NORMAL ");
        attroff(COLOR_PAIR(1));
    }
    if (mode == 'i') {
        attron(A_REVERSE | COLOR_PAIR(2));
        mvwprintw(stdscr, line_number, 0, "%s", " INSERT ");
        attroff(COLOR_PAIR(2));
    }
    if (mode == 'v') {
        attron(A_REVERSE | COLOR_PAIR(3));
        mvwprintw(stdscr, line_number, 0, "%s", " VISUAL ");
        attroff(COLOR_PAIR(3));
    }

    attroff(A_REVERSE);
    for (int64_t i = 8; i < line_length - 5; i++) {
        mvwprintw(stdscr, line_number, i, "%ls", L"═");
    }
    if (percentage > 100) percentage = 100;
    attron(A_REVERSE | COLOR_PAIR(6));
    mvwprintw(stdscr, line_number, line_length-6, " %3d%% ", percentage);
    attroff(A_REVERSE | COLOR_PAIR(6));
    for (int64_t i = 0; i < line_number; i++) {
        // ║ │
        mvwprintw(stdscr, i, 3, "%ls", L" ");
    }
}

void clear_line  (int line_number, int line_length) 
{
    for (int64_t i = 0; i < line_length; i++) {
        mvwprintw(stdscr, line_number, i, "%ls", L" ");
    }
}

void print_curs (Cursor cur, int winx, int winy) {
    log(std::to_string(cur.opos)+"opos");
    cur.line += cur.opos/(winx - 4);
    cur.pos = 4 + cur.opos%(winx - 4);
    if (cur.line > winy - 2) cur.line = winy - 2;
    if (cur.pos < 4) cur.pos = 4;
    attron(A_REVERSE);
    mvwprintw(stdscr, cur.line, cur.pos, "%c", mvinch(cur.line, cur.pos));
    attroff(A_REVERSE);
}
