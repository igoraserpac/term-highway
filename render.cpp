#include "render.hpp"

void print_frame(Frame f) {
    
    int color_index = 1; 
    map<string, int> color_pair_map; 

    for (const auto& color_entry : f.colors) {
        if (color_index >= COLOR_PAIRS) {
            break; 
        }

        string color_name = color_entry.first;
        int curses_color;

        if (color_name == "red") {
            curses_color = COLOR_RED;
        } else if (color_name == "blue") {
            curses_color = COLOR_BLUE;
        } else if (color_name == "green") {
            curses_color = COLOR_GREEN;
        } else if (color_name == "yellow") {
            curses_color = COLOR_YELLOW;
        } else if (color_name == "cyan") {
            curses_color = COLOR_CYAN;
        } else if (color_name == "magenta") {
            curses_color = COLOR_MAGENTA;
        } else {
            curses_color = COLOR_WHITE; 
        }

        init_pair(color_index, curses_color, COLOR_BLACK);
        color_pair_map[color_name] = color_index++;
    }

    
    for (int i = 0; i < f.f.size(); i++) {
        for (int j = 0; j < f.f[i].size(); j++) {
            
            int color_to_use = 0; 
            for (const auto& color_entry : f.colors) {
                const auto& positions = color_entry.second;
                if (find(positions.begin(), positions.end(), make_pair(i, j)) != positions.end()) {
                    color_to_use = color_pair_map[color_entry.first];
                    break;
                }
            }

            
            if (color_to_use > 0) {
                attron(COLOR_PAIR(color_to_use));
            }
            mvprintw(i, j, "%c", f.f[i][j]);
            if (color_to_use > 0) {
                attroff(COLOR_PAIR(color_to_use));
            }
        }
    }
}

Frame make_empty_frame(int x, int y){
    Frame f;
    f.x = x;
    f.y = y;
    f.f = vector<vector<char>>(y, vector<char>(x, ' '));
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(
                (i == 0 and j == 0) or
                (i == 0 and j == x-1) or
                (i == y-1 and j == 0) or
                (i == y-1 and j == x-1)
            ) f.f[i][j] = '*';
            else if(i == 0 or i == y-1) f.f[i][j] = '-'; 
            else if(j == 0 or j == x-1) f.f[i][j] = '|'; 
        }
    }
    return f;
}

void add_on_frame(Frame &f, int x, int y, vector<vector<char>> obj, string color){
    for(int i = 0; i < obj.size(); i++){
        for(int j = 0; j < obj[0].size(); j++){
            if(i + y < f.y-1 and j + x < f.x-1 and i + y >= 1 and j + x >= 1){
                f.f[i+y][j+x] = obj[i][j];
                f.colors[color].push_back(make_pair(i+y, j+x));
            }
        }   
    }
}