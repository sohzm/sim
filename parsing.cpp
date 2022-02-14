#include <string>
#include <utility>
#include <locale.h>
#include <ncurses.h>
#include <fstream>

#include "functions.h"

int parse_command (
        char x, Cursor &cur, int winx, 
        int winy, int total_lines, 
        std::vector <int> &THICCNESS, 
        std::vector <int> &buff_text_lines
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

    // h j k l
        
    if (x == 'j') {
        if (cur.oy < winy - 3) {
            cur.oy++;
        }
        int temp_ovf = 0;
        int temp_index = buff_text_lines.size();
        while (temp_ovf < winy-3) {
            temp_index--;
            temp_ovf += buff_text_lines[temp_index];
        }
        temp_index++;
        if (cur.oy == winy-3 && cur.vu < temp_index) {
            cur.vu += 1;
            ret *= 5;
        }
        cur.y = cur.oy;
        if ( THICCNESS[cur.y]+4 < cur.x || THICCNESS[cur.y]+4 < cur.ox) 
            cur.x = 4+THICCNESS[cur.y];
        else cur.x = cur.ox;
    } else if (x == 'k') {
        if (cur.oy > 0) {
            cur.oy -= 1;
        }
        if (cur.oy == 0) {
            if (cur.vu > 0) {
                cur.vu -= 1;
                ret *= 5;
            }
        }
        cur.y = cur.oy;
        if (THICCNESS[cur.y]+4 < cur.x || THICCNESS[cur.y]+4 < cur.ox) 
            cur.x = 4+THICCNESS[cur.y];
        else cur.x = cur.ox;
    } else if (x == 'h') {
        if (cur.ox >= THICCNESS[cur.y]+4) {
            cur.ox = THICCNESS[cur.y]+4;
        }
        if (cur.ox > 4) {
            cur.ox -= 1;
        }
        cur.x = cur.ox;
    } else if (x == 'l') {
        if (cur.ox < THICCNESS[cur.y]+4) {
            cur.ox += 1;
        }
        if (THICCNESS[cur.y]+4 < cur.x || THICCNESS[cur.y]+4 < cur.ox) 
            cur.x = 4+THICCNESS[cur.y];
        else cur.x = cur.ox;

    // g G

    } else if (x == 'G') {
        int temp_ovf = 0;
        int temp_index = buff_text_lines.size();
        while (temp_ovf < winy-3) {
            temp_index--;
            temp_ovf += buff_text_lines[temp_index];
        }
        cur.vu = ++temp_index;
        cur.y = winy-3;
        cur.oy = winy-3;
    } else if (x == 'g') {
        x = getch();
        if (x == 'g') {
            cur.vu = 0;
            cur.oy = 0;
            cur.y = 0; 
        }

    // modes

    } else if (x == 'i') {
        cur.mode = 'i';
    } else if (x == 'n') {
        cur.mode = 'n';
    } else if (x == 'v') {
        cur.mode = 'v';
    }
    return 1;
}
