#include <string>
#include <ctype.h>
#include <stdlib.h>
#include <utility>
#include <locale.h>
#include <ncurses.h>
#include <fstream>

#include "functions.h"

int parse_command (
        char x, Cursor &cur, int winx, 
        int winy, int total_lines, 
        std::vector <int> &THICCNESS, 
        std::vector <int> &LINEON, 
        std::vector <int> &buff_text_lines,
        std::vector <int> &buff_text_width
     )
{
    int ret = 1;
    if (x == ':') {
        char str[90];
        scanw("%s", str);
        clear_line(winy-1, winx);
        if (std::string(str) == "q") {
            endwin();
            exit(0);
        }
    }

    if (x == 'j') {
        if (cur.oline < total_lines - 1) {
            cur.oline++;
            cur.opos = cur.maxx;
            if (cur.opos > buff_text_width[cur.oline]) {
                cur.opos = buff_text_width[cur.oline];
            }
        }
        if (cur.vl < total_lines - 1 && cur.line >= cur.lastline) {
            int temp_count = 0;
            int temp_index = cur.vl+2;
            while (1) {
                temp_index--;
                temp_count += buff_text_lines[temp_index];
                if (temp_index < 0) break;
                if (temp_count == winy - 2) {
                    break;
                }
                if (temp_count > winy - 2) {
                    temp_index++;
                    break;
                }
            }
            cur.vf = temp_index;
        }
    } else if (x == 'k') {
        if (cur.oline > 0) {
            cur.oline--;
            cur.opos = cur.maxx;
            if (cur.opos > buff_text_width[cur.oline] - 2) {
                cur.opos = buff_text_width[cur.oline] - 2;
            }
        }
        if (cur.vl > 0 && cur.line == 0 && cur.vf != 0) {
            cur.vf--;
        }
    } else if (x == 'h') {
        if (cur.opos > 0) {
            cur.opos--;
            cur.maxx = cur.opos;
        }
    } else if (x == 'l') {
        if (cur.opos < buff_text_width[cur.oline] - 2) {
            cur.opos++;
            cur.maxx = cur.opos;
        }
    } else if (x == 'G') {
        int temp_count = 0;
        int temp_index = total_lines;
        while (1) {
            temp_index--;
            temp_count += buff_text_lines[temp_index];
            if (temp_index < 0) break;
            if (temp_count == winy - 2) {
                break;
            }
            if (temp_count > winy - 2) {
                temp_index++;
                break;
            }
        }
        cur.vf = temp_index;
        cur.oline = cur.vf;
    } else if (x == 'g') {
        x = getch();
        if (x == 'g') {
            cur.vf = 0;
            cur.oline = 0;
        }

    // modes

    } else if (x == '0') {
        cur.maxx = 0;
        cur.opos = 0;
    } else if (x == '$') {
        cur.maxx = buff_text_width[cur.oline] - 2;
        cur.opos = cur.maxx;
    } else if (x == 'i') {
        cur.mode = 'i';
    } else if (x == 'n') {
        cur.mode = 'n';
    } else if (x == 'v') {
        cur.mode = 'v';
    }
    return 1;
}
