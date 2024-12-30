#ifndef RENDER_HPP
#define RENDER_HPP

#include <bits/stdc++.h>
#include <ncurses.h>
#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;

typedef struct frame {
    int x;
    int y;
    vector<vector<char>> f;
    map<string, vector<pair<int, int>>> colors;
} Frame;

void print_frame(Frame f);

Frame make_empty_frame(int x, int y);

void add_on_frame(Frame &f, int x, int y, vector<vector<char>> obj, string color);

#endif