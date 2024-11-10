#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;
class Player {
protected:
    string name;
    char symbol;
    int level;
public:
    Player(string nam, char sym, int level):name(nam), symbol(sym), level(level) {}
    string getName() const { return name; }
    char getSymbol() const { return symbol; }
    int getLVL() const { return level; }
    void SetALL(const string& nam, const char& sym, const int& lvl) {
        this->name = nam;
        this->symbol = sym;
        this->level = lvl;
    }
    virtual string getPlayerData() const {
        return name + ": " + symbol + ", Level: " + to_string(level);
    }
    friend ostream& operator<<(ostream& output, const Player& play) {
        output << play.getPlayerData();
        return output;
    }
};
class Player1 :public Player {
    int score;
public:
    Player1():Player(" ",' ',0),score(0){}
    void SetScore(const int& scr) { this->score= scr; }
    int getScore() const { return score; }
    Player1(string name,char sym, int level,int score) :Player(name,sym,level),score(score){}
    virtual string getPlayerData() const {
        return Player::getPlayerData() + ", Score: " + to_string(score);
    }
    friend ostream& operator<<(ostream& output, const Player1& play) {
        output << play.getPlayerData();
        return output;
    }
};
class Player2 :public Player {
    int experience;
    string y_d_m;
public:
    Player2() :Player(" ", ' ', 0), experience(0), y_d_m(" "){}
    Player2(string name, char sym,int level,int exp) :Player(name, sym, level), experience(exp){}
    void SetY_D_M(const string& ydm) { this->y_d_m = ydm; }
    void SetExp(const int& exper) { this->experience = exper; }
    int getExp() const { return experience; }
    string getY_D_M() const { return y_d_m; }
    virtual string getPlayerData() const{
        return Player::getPlayerData() + ", Experience: " + to_string(experience) + " " + y_d_m;
    }
    friend ostream& operator<<(ostream& output, const Player2& play) {
        output << play.getPlayerData();
        return output;
    }
};
template <typename T, typename T2>
void setPlayerDani(T& player1, const string& name, const char& symbol, const int& level, const int& score,
    T2& player2, const string& name2, const char& symbol2, const int& level2,const int& exp) {
    player1.SetALL(name, symbol, level);
    player2.SetALL(name2, symbol2, level2);
    player1.SetScore(score);
    player2.SetExp(exp);
}
void print_pole(short krestik, short nolik, int pole[3][3]) {
    cout << "\t\tTic tac toe" << endl;
    cout << "\t\t-----------" << endl;
    for (short i = 0; i < 3; i++) {
        cout << "\t\t";
        for (short j = 0; j < 3; j++) {
            cout << "|";
            (pole[i][j] == krestik) ? cout << "X" : (pole[i][j] == nolik) ? cout << "O" : cout << " ";
            cout << "| ";
        }
        cout << endl << "\t\t-----------" << endl;
    }
}
void save_res(const Player1 &player1, const Player2& player2, double time,int win) {
    fstream file("saves.txt", ios::out | ios::app);
    string win_name;
    try {
        if (!file) {
            throw invalid_argument("Error opening file for saving results.");
            return;
        }
        (win == 1) ? win_name = player1.getName() : (win == 2) ? win_name = player2.getName() : win_name = "Draw";
        file << "Player 1: " << player1.getName() << ", Level: " << player1.getLVL() << ", Symbol: " << player1.getSymbol() << endl;
        file << "Player 2: " << player2.getName() << ", Level: " << player2.getLVL() << ", Symbol: " << player2.getSymbol() << endl;
        file << "Game Duration: " << time << " seconds" << endl;
        file << "Win: " << win_name << endl;
        file << "--------------------------------------" << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }
}
void print_results() {
    fstream file("saves.txt", ios::in);
    if (!file) {
        cerr << "Error opening file for reading results." << endl;
        return;
    }

    string line;
    cout << "\n--- Saved Game Results ---\n";
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void clean_pole(int pole[3][3]){
    for (short i = 0; i < 3; i++) {
        for (short j = 0; j < 3; j++) {
            pole[i][j] = 0;
        }   
    }
}
class Game {
    int pole[3][3] = { 0 }, first_hid = 1 + rand() % 2;
    Player1 player1;
    Player2 player2;
    string nam1, nam2;
    int lev1, lev2,score,exper, yrdymth;
    short  krestik = -1, nolik = -1;
    int vibor, klitka,again, same,win=0;
    double time;
public:
    bool Check() {
        for (short i = 0; i < 3; i++) {
            if (pole[i][0] == 1 && pole[i][1] == 1 && pole[i][2] == 1) {
                print_pole(krestik, nolik, pole);
                cout << player1.getName() << " win!" << endl;
                win = 1;
                return true;
            }
            if (pole[i][0] == 2 && pole[i][1] == 2 && pole[i][2] == 2) {
                print_pole(krestik, nolik, pole);
                cout << player2.getName() << " win!" << endl;
                win = 2;
                return true;
            }
        }
        for (short i = 0; i < 3; i++) {
            if (pole[0][i] == 1 && pole[1][i] == 1 && pole[2][i] == 1) {
                print_pole(krestik, nolik, pole);
                cout << player1.getName() << " win!" << endl;
                win = 1;
                return true;
            }
            if (pole[0][i] == 2 && pole[1][i] == 2 && pole[2][i] == 2) {
                print_pole(krestik, nolik, pole);
                cout << player2.getName() << " win!" << endl;
                win = 2;
                return true;
            }
        }
        if ((pole[0][0] == 1 && pole[1][1] == 1 && pole[2][2] == 1) || (pole[0][2] == 1 && pole[1][1] == 1 && pole[2][0] == 1)) {
            print_pole(krestik, nolik, pole);
            cout << endl << player1.getName() << " win!" << endl;
            win = 1;
            return true;
        }
        if ((pole[0][0] == 2 && pole[1][1] == 2 && pole[2][2] == 2) || (pole[0][2] == 2 && pole[1][1] == 2 && pole[2][0] == 2)) {
            print_pole(krestik, nolik, pole);
            cout << endl << player2.getName() << " win!" << endl;
            win = 2;
            return true;
        }
        int count = 0;
        for (short i = 0; i < 3; i++) {
            for (short j = 0; j < 3; j++) {
                if (pole[i][j] == 0) {
                    return false;
                }
                else {
                    count++;
                }
            }
        }
        if (count == 9) {
            print_pole(krestik, nolik, pole);
            cout << "It's a draw!" << endl;
            win = 3;
            return true;
        }
    }
    void play() {
        auto start = chrono::steady_clock::now();
        try {
            do {
                clean_pole(pole);
                cout << "Input names first and second player(with space): " << endl;
                cin >> nam1 >> nam2;
                cout << "Input level first and second player(with space): " << endl;
                cin >> lev1 >> lev2;
                cout << "Input firts player wins and second player experience with(days(1),month(2),years(3)): " << endl;
                cin >> score>>exper>> yrdymth;
                if(yrdymth>3 && yrdymth<1){ throw invalid_argument("Input from 1 to 3"); }
                (yrdymth == 1) ? player2.SetY_D_M("days") : (yrdymth == 2) ? player2.SetY_D_M("months") : player2.SetY_D_M("years");
                (first_hid == 1) ? cout << "First hid 1 player" << endl : cout << "First hid 2 player" << endl;
                cout << "Krestik(1) or nolik(2)? " << endl;
                cin >> vibor;
                if (vibor < 1 || vibor>2) throw - 1;
                if (first_hid == 1) {
                    if (vibor == 1) {
                        krestik = first_hid;
                        nolik = 2;
                    }
                    else {
                        krestik = 2;
                        nolik = first_hid;
                    }
                }
                else {
                    if (vibor == 1) {
                        krestik = first_hid;
                        nolik = 1;
                    }
                    else {
                        krestik = 1;
                        nolik = first_hid;
                    }
                }
                (first_hid == 1 && krestik == 1) ? setPlayerDani(player1, nam1, 'X', lev1,score, player2, nam2, 'O', lev2,exper) :
                    (first_hid == 1 && nolik == 1) ? setPlayerDani(player1, nam1, 'O', lev1, score, player2, nam2, 'X', lev2, exper) :
                    (first_hid == 2 && krestik == 2) ? setPlayerDani(player1, nam1, 'O', lev1, score, player2, nam2, 'X', lev2, exper) :
                    setPlayerDani(player1, nam1, 'X', lev1, score, player2, nam2, 'O', lev2, exper);
                cout<<endl << "Dani 1 player: "<<endl<<player1 << endl <<"\nDani 2 player: " << endl << player2 << endl << endl;
                do {
                    do {
                        print_pole(krestik, nolik, pole);
                        cout << endl << "Input klitinku: " << endl;
                        cin >> klitka;
                        if (cin.fail() || klitka < 1 || klitka > 9) {
                            cin.clear();
                            throw invalid_argument("Invalid position. Choose between 1 and 9.");
                        }
                        for (short i = 0; i < 3; i++) {
                            for (short j = 0; j < 3; j++) {
                                if (klitka == i * 3 + j + 1) {
                                    if (pole[i][j] == 0) {
                                        pole[i][j] = first_hid;
                                    }
                                    else {
                                        throw invalid_argument("In this klitinki already occupied");
                                    }
                                }
                            }
                        }
                        print_pole(krestik, nolik, pole);
                        (first_hid == 1) ? first_hid = 2 : first_hid = 1;
                        system("CLS");
                    } while (Check() == false);
                    auto end = chrono::steady_clock::now();
                    chrono::duration<double> elapsed = end - start; 
                    double timee = elapsed.count();
                    cout << endl << "Game's time: " << timee<<endl;
                    time = timee;
                    cout << "Playing with same players? (1)Yes (2)No";
                    cin >> same;
                    if (same < 1 || same>2) throw - 1;
                    clean_pole(pole);
                } while (same == 1);
                cout << "Do you want play again? (1)Yes (2)No";
                cin >> again;
                if (again < 1 || again>2) throw - 1;
                if (again == 2) break;
            } while (again == 1);
            int save;
            cout << endl << "Do you want save results? (1)Yes (2)No ";
            cin >> save;
            if (save < 1 || save>2) throw - 1;
            if (save == 1) {
                save_res(player1,player2, time,win);
                cout << "Results saved";
            }
            else { cout << "Results were not saved"; }
        }
        catch (int) {
            cerr << "Input 1 or 2";
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
};
int main()
{
    srand(time(NULL));
    int look_saves;
    Game game;
    game.play();
    cout << endl << "Do you want to look saved results?(1)Yes (2)No"<<endl;
    cin >> look_saves;
    if (look_saves == 1) { print_results(); }
}
