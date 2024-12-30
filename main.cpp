#include "render.hpp"
#include "desenhos.hpp"
#include <chrono>
#include <thread>


int random_number(int n) {    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, n);
    return dis(gen);
}

typedef struct carro {
    int x;
    int y;
} Carro;

bool colidiu(Carro a, Carro b){
    if(a.x >= b.x - 4 and a.x <= b.x + 4){
        if(a.y >= b.y - 5 and a.y <= b.y + 5){
            return true;
        }
    }
    return false;
}

bool confere(vector<Carro> carros, Carro novo){
    for(auto car: carros){
        if(colidiu(car, novo)) return true;
    }
    return false;
}

bool colidiu_inv(Carro a, Carro b){
    if(a.x >= b.y - 4 and a.x <= b.y + 4){
        if(a.y >= b.x - 5 and a.y <= b.x + 5){
            return true;
        }
    }
    return false;
}

bool confere_inv(vector<Carro> carros, Carro personagem){
    for(auto car: carros){
        if(colidiu_inv(car, personagem)) return true;
    }
    return false;
}

int main() {
    int ch;         
    vector<Carro> carros;    
    
    initscr();            
    cbreak();             
    noecho();             
    keypad(stdscr, TRUE); 
    curs_set(0);          
    start_color();
    nodelay(stdscr, TRUE); 
    Carro personagem = {40, 23};    
    long long int timer = 0;
    while (true) {
        Frame f = make_empty_frame(50, 55);
        add_on_frame(f, 1, 1, estrada, "white");
        clear(); 

        if(rand() % 150 < 5){
            Carro novo;
            novo.x = random_number(43);
            novo.y = -5;
            if(!confere(carros, novo)){
                carros.push_back(novo);
            }
        }

        for(auto car: carros){
            add_on_frame(f, car.x, car.y, carro, "blue"); 
        }

        for (auto it = carros.begin(); it != carros.end(); ) {
            if (it->y > 55) {
                it = carros.erase(it); 
            } else {
                ++it; 
            }
        }

        if(timer%2 == 0){
            for(auto &car: carros){
                car.y++;
            }   
        }
        
        add_on_frame(f, personagem.y, personagem.x, carro, "green");
        print_frame(f);
        refresh(); 

        ch = getch(); 

        if (ch == KEY_UP && personagem.x > 1) {
            personagem.x--; 
        } else if (ch == KEY_DOWN && personagem.x < f.y - 2) {
            personagem.x++; 
        } else if (ch == KEY_LEFT && personagem.y > 1) {
            personagem.y--; 
        } else if (ch == KEY_RIGHT && personagem.y < f.x - 2) {
            personagem.y++; 
        } else if (ch == 'q' || ch == 'Q') {
            break; 
        }
            
        if(confere_inv(carros, personagem)){
            mvprintw(23, 20, "Game Over!");
            mvprintw(25, 18, "Press Q to exit.");
            refresh();
            while (getch() != 'q');
            break;
        }
        
        timer++;
        
    }

    endwin();
    return 0;
}
