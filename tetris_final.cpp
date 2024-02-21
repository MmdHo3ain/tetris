//-----------------------------------| Librari |-----------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iomanip>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // for_color
//-----------------------------------| Curser Handeling |--------------------------------------
void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
    if (size == 0)
    {
        size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void MoveCurser(int x, int y)
{
    COORD position = {x, y};
    SetConsoleCursorPosition(console, position);
}
//-----------------------------------| Variable Storage |--------------------------------------------------
int n = 23; // 2+n+1
int m = 12; // 1+m+1
int **Board;
int **tempUp;

int style = 1;
int difficulty_Level = 2;
int doration = 0;   //used for increasing sleep time


int score = 0;
//-----------------------------------| Structs |-----------------------------------------------------------
struct Player_Score
{
    string name;
    int score;
    int n_size;
    int m_size;
    int time;
};

struct Time
{
    int temp_total;
    int total;
    int start;
    int end;
    //int reserve;
};

Player_Score **scoreBox;


//-----------------------------------| time |------------------------------------------------------------

void time_show(int Time){

cout << Time/600;   Time = Time - (600*(Time/600));
cout << Time/60;   Time = Time - (60*(Time/60));
cout << ":";
cout << Time/10;   Time = Time - (10*(Time/10));
cout << Time;
}

//-----------------------------------| pause |----------------------------------------------------------

void howtoPlay()
{
    cout <<"USE 'W' TO ROTATE TETRIMINOS \n"
         <<"USE 'D' TO MOVE TETRIMINOS LEFT \n"
         <<"USE 'A' TO MOVE TETRIMINOS RIGHT\n"
         <<"USE 'S' TO SOFT DROP TETRIMINOS\n"
         <<"USE 'SPACE' TO HARD DROPS TETRIMINOS\n"
         <<"YOU CAN CHANGE THE GAME STYLE AND DIFFICULTY FROM SETTINGS";

}

void restart()
{
     for (int i = 2; i < n-1; i++)
    {
        for (int j = 1; j < m-1; j++)
        {
            Board[i][j]=0;
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            Board[i][j] = tempUp[i][j];
        }
    }
    score=0;
}    

bool pause_menu(Time &timeBox)
{
    while (true)
    {
        int j = 1;
        char order;
        MoveCurser(4 + (m*2),j);
        cout <<"1 _ RESUME               ";  j++;
        MoveCurser(4 + (m*2),j);
        cout <<"2 _ Restart           "; j++;
        MoveCurser(4 + (m*2),j);
        cout <<"3 _ QUIT                 ";
        order = getch();
        switch (order)
        {
        case '1':
            return 0;

            // RESUME
            break;
        case '2':
            restart();
            timeBox.start = time(0);
            break;

        case '3':
            //QUIT
            //timeBox.start = time(0);
            return 1;
            break;
        }
    }
    
}
//-----------------------------------| Game Display |----------------------------------------------------
void game_BoarderLine_1(){
    SetConsoleTextAttribute(console, 2);
    MoveCurser(0,0);
    for (int i = 0; i < n-3; i++)
    {
        MoveCurser(0,i);
        cout << "<!" ; 
        for (int i = 0; i < m-2 ; i++)
        {
        cout << " ."; Sleep(2);
        }
        cout << "!>" ;
    }

    MoveCurser(0,n-3);
    cout << "<!" ; Sleep(10);
    for (int i = 0; i < (m-2)*2 ; i++)
    {
        cout << "="; Sleep(2);
    }
    cout << "!>" ; Sleep(10);


    MoveCurser(2,n-2);
    for (int i = 0; i < m-2; i++)
    {
        cout << "\\/";
    }
}

void showGame_1(Time timeBox, float added_time = 0)
{
    for (int i = 2; i < n-1; i++)
    {
        MoveCurser(2,i-2);
        for (int j = 1; j < m-1; j++)
        {
            if(Board[i][j]!=0)
            cout <<"[]";
            else 
            cout <<" .";
        }
    }
    MoveCurser((m*2),0);
    cout << "                   ";
    MoveCurser(4+(m*2),0);
    cout << "score : " << score ;

    timeBox.end = time(0);
    timeBox.temp_total = timeBox.total ;
    timeBox.total =  timeBox.end - timeBox.start;
    
    cout << "         ";
    //time_show(timeBox.total+timeBox.reserve);
    time_show(timeBox.total);
    scoreBox[difficulty_Level][10].time = timeBox.total ;

    
    Sleep(doration+added_time);
}

void color_definer(int shapeCode){
    switch (shapeCode)
            {
            case 0:
                SetConsoleTextAttribute(console, 15);
                break;    
            case 1:
                SetConsoleTextAttribute(console, 65);
                break;
            case 2:
                SetConsoleTextAttribute(console, 96);
                break;
            case 3:
                SetConsoleTextAttribute(console, 87);
                break;
            case 4:
                SetConsoleTextAttribute(console, 191);
                break;
            case 5:
                SetConsoleTextAttribute(console, 132);
                break;
            case 6:
                SetConsoleTextAttribute(console, 149);
                break;
            case 7:
                SetConsoleTextAttribute(console, 208);
                break;
            case 9:
                SetConsoleTextAttribute(console, 112);
                break;
            default:
                break;
            }
}

void showGame_2(Time timeBox, float added_time = 0){

    for (int i = 2; i < n; i++)
    {
        MoveCurser(2,i-2);
        for (int j = 0; j < m; j++)
        {
            int displayer = Board[i][j];
            if (displayer < 0)
            {
                displayer *= -1;
            }
            color_definer(displayer);
            cout << "  ";
        }
    }
    SetConsoleTextAttribute(console, 15);
    MoveCurser(4+(m*2),0);
    cout << "score : " << score ;
    cout << "         ";

    timeBox.end = time(0);
    timeBox.total =  timeBox.end - timeBox.start;
    //time_show(timeBox.total+timeBox.reserve);
    time_show(timeBox.total);
    Sleep(doration+added_time);
}

void showGame(Time timeBox, float added_time = 0){
    switch (style)
    {
    case 1:
        showGame_1(timeBox,added_time);
        break;
    case 2:
        showGame_2(timeBox,added_time);
        break;    
    
    default:
        break;
    }
}

//-----------------------------------| Falling Movment |-------------------------------------------------
bool down_check()
{
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (Board[i][j] > 0 && Board[i + 1][j] < 0)
                return 0;
        }
    }
    return 1;
}
bool make_solid()
{
    if (down_check())
    {
        return 0;
    }
    else
    {
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = 1; j < m - 1; j++)
            {
                if (Board[i][j] > 0)
                {
                    Board[i][j] *= -1;
                }
            }
        }
        score += 40;
        return 1;
    }
}
void down_move(Time timeBox)
{
    if (down_check())
    {
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {

                if (Board[i][j] > 0)
                {
                    Board[i + 1][j] = Board[i][j];
                    Board[i][j] = 0;
                }
            }
        }
        showGame(timeBox);
    }
}
//-----------------------------------| Shape Start |-----------------------------------------------------
int shape_finder(int &x, int &y)
{
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (Board[i][j] > 0)
            {
                x = i;
                y = j;
                return Board[i][j];
            }
        }
    }
    return 0;
}

void show_next_block_1(){
    int j = 1;
    MoveCurser(2 + (m*2),j);
    cout << "                                                            ";
    MoveCurser(4 + (m*2),j);
    for (int i = 1; i < m-1; i++)
    {
        if (tempUp[0][i]>0){
            
            cout << "[]";
        }
        else{
            cout <<"  ";
        }
    }
    cout << "                        ";
    j++;
    MoveCurser(4 + (m*2),j);
    for (int i = 1; i < m-1; i++)
    {
        if (tempUp[1][i]>0){
            cout << "[]";
        }
        else{
            cout <<"  ";
        }
    }
    cout << "                      ";
    j++;   
    MoveCurser(4 + (m*2),j);
    cout << "                          ";
    j++;
    MoveCurser(4 + (m*2),j);
    cout << "                          ";
}
void show_next_block_2(){
    int j = 1;
    MoveCurser(4 + (m*2),j);
    
    for (int i = 1; i < m-1; i++)
    {
        if (tempUp[0][i]>0){
            color_definer(tempUp[0][i]);
        }
        cout << "  ";
        color_definer(0);
    }
    cout << "    ";
    j++;
    MoveCurser(4 + (m*2),j);
    for (int i = 1; i < m-1; i++)
    {
        if (tempUp[1][i]>0){
            color_definer(tempUp[1][i]);
        }
        cout << "  ";
        color_definer(0);
    }
    cout << "    ";
    j++;
    MoveCurser(4 + (m*2),j);
    cout << "                 ";
    j++;
    MoveCurser(4 + (m*2),j);
    cout << "                  ";
}

void show_next_block(){
    switch (style)
    {
    case 1:
        show_next_block_1();
        break;
    case 2:
        show_next_block_2();
        break;
    }
}

bool is_possible(int possiblity){
    if ((rand() % possiblity)==0)
    {return 1;}
    return 0;
}

int realRandom(int possiblity[8])
{
    while(1)
    {    
        int shapecode = rand() % 7 + 1;

        if(is_possible(possiblity[shapecode]))
        {   
            possiblity[shapecode]*=3;
            possiblity[0] ++;
            return shapecode;
        } 
    }    
}

void random_shape(int possiblity[8])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            tempUp[i][j] = 0;
        }
    }
    
    
    int shapeCode = realRandom(possiblity);
   
    int j = rand() % (m - 2 - 3) + 1;
    switch (shapeCode)
    {
    case 1: // square
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[0][j] = shapeCode;
        tempUp[0][j + 1] = shapeCode;
        break;
    case 2: //___|     alt L block
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[1][j + 2] = shapeCode;
        tempUp[0][j + 2] = shapeCode;
        break;
    case 3: // |___   L block
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[1][j + 2] = shapeCode;
        tempUp[0][j] = shapeCode;
        break;
    case 4: // straight line
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[1][j + 2] = shapeCode;
        tempUp[1][j + 3] = shapeCode;
        break;
    case 5: // --|__
        tempUp[0][j] = shapeCode;
        tempUp[0][j + 1] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[1][j + 2] = shapeCode;
        break;
    case 6: // __/--
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[0][j + 1] = shapeCode;
        tempUp[0][j + 2] = shapeCode;
        break;
    case 7: //__|__
        tempUp[1][j] = shapeCode;
        tempUp[1][j + 1] = shapeCode;
        tempUp[1][j + 2] = shapeCode;
        tempUp[0][j + 1] = shapeCode;
        break;
    default:
        break;
    }
    show_next_block();
}
void insert_shape()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            Board[i][j] = tempUp[i][j];
        }
    }
}
//-----------------------------------| Rotating |--------------------------------------------------------

void Rotation_2(int &shapeMod, int i, int j)
{
    shapeMod = shapeMod % 4;
    switch (shapeMod)
    {
    case 1:
        if (Board[i][j - 1] == 0 && Board[i][j - 2] == 0 && Board[i + 2][j - 1] == 0)
        {
            Board[i][j - 1] = 2;
            Board[i][j - 2] = 2;
            Board[i + 2][j - 1] = 2;
            Board[i][j] = 0;
            Board[i + 1][j] = 0;
            Board[i + 1][j - 2] = 0;
            shapeMod++;
        }
        break;
    case 2:
        if (Board[i + 1][j] == 0 && Board[i + 2][j] == 0 && Board[i + 1][j + 2] == 0) /*check if rotate can be done*/
        {
            Board[i + 1][j] = 2;
            Board[i + 2][j] = 2;
            Board[i + 1][j + 2] = 2;
            Board[i][j] = 0;
            Board[i][j + 1] = 0;
            Board[i + 2][j + 1] = 0;
            shapeMod++;
        }
        break;
    case 3:
        if (Board[i - 1][j + 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 1][j + 2] == 0) /*check if rotate can be done*/
        {
            Board[i - 1][j + 1] = 2;
            Board[i + 1][j + 1] = 2;
            Board[i + 1][j + 2] = 2;
            Board[i][j] = 0;
            Board[i][j + 2] = 0;
            Board[i + 1][j] = 0;
            shapeMod++;
        }
        break;
    case 0:
        if (Board[i][j + 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 1][j - 1] == 0) /*check if rotate can be done*/
        {
            Board[i][j + 1] = 2;
            Board[i + 1][j + 1] = 2;
            Board[i + 1][j - 1] = 2;
            Board[i][j] = 0;
            Board[i + 2][j] = 0;
            Board[i + 2][j + 1] = 0;
            shapeMod++;
        }
        break;
    default:
        break;
    }
}
void Rotation_3(int &shapeMod, int i, int j)
{

    shapeMod = shapeMod % 4;
    switch (shapeMod)
    {
    case 1:
        if (Board[i][j + 1] == 0 && Board[i + 2][j] == 0 && Board[i + 2][j + 1] == 0)
        {
            Board[i][j + 1] = 3;
            Board[i + 2][j] = 3;
            Board[i + 2][j + 1] = 3;
            Board[i][j] = 0;
            Board[i + 1][j] = 0;
            Board[i + 1][j + 2] = 0;
            shapeMod++;
        }
        break;
    case 2:
        if (Board[i + 1][j - 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 1] == 0) /*check if rotate can be done*/
        {
            Board[i + 1][j - 1] = 3;
            Board[i + 1][j + 1] = 3;
            Board[i + 2][j + 1] = 3;
            Board[i][j] = 0;
            Board[i + 2][j] = 0;
            Board[i + 2][j - 1] = 0;
            shapeMod++;
        }
        break;
    case 3:
        if (Board[i - 1][j + 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i - 1][j + 2] == 0) /*check if rotate can be done*/
        {
            Board[i - 1][j + 1] = 3;
            Board[i + 1][j + 1] = 3;
            Board[i - 1][j + 2] = 3;
            Board[i][j] = 0;
            Board[i][j + 2] = 0;
            Board[i + 1][j + 2] = 0;
            shapeMod++;
        }
        break;
    case 0:
        if (Board[i][j - 1] == 0 && Board[i + 1][j - 1] == 0 && Board[i + 1][j + 1] == 0) /*check if rotate can be done*/
        {
            Board[i][j - 1] = 3;
            Board[i + 1][j - 1] = 3;
            Board[i + 1][j + 1] = 3;
            Board[i][j] = 0;
            Board[i][j + 1] = 0;
            Board[i + 2][j] = 0;
            shapeMod++;
        }
        break;
    default:
        break;
    }
}
void Rotation_4(int &shapeMod, int i, int j)
{
    shapeMod = shapeMod % 2;
    switch (shapeMod)
    {
    case 1: // ofoghi be amoodi
        if (Board[i - 1][j + 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 2][j + 1] == 0)
        {
            Board[i - 1][j + 1] = 4;
            Board[i + 1][j + 1] = 4;
            Board[i + 2][j + 1] = 4;
            Board[i][j] = 0;
            Board[i][j + 2] = 0;
            Board[i][j + 3] = 0;
            shapeMod++;
        }
        break;
    case 0:                                                                                   // amoodi be ofoghi  // 0 chon hamoon 2 haast
        if (Board[i + 1][j - 1] == 0 && Board[i + 1][j + 1] == 0 && Board[i + 1][j + 2] == 0) /*check if rotate can be done*/
        {
            Board[i + 1][j - 1] = 4;
            Board[i + 1][j + 1] = 4;
            Board[i + 1][j + 2] = 4;
            Board[i][j] = 0;
            Board[i + 2][j] = 0;
            Board[i + 3][j] = 0;
            shapeMod++;
        }
        break;

    default:
        break;
    }
}
void Rotation_5(int &shapeMod, int i, int j)
{
    shapeMod = shapeMod % 2;
    switch (shapeMod)
    {
    case 1:
        if (Board[i][j + 2] == 0 && Board[i + 2][j + 1] == 0)
        {
            Board[i][j + 2] = 5;
            Board[i + 2][j + 1] = 5;
            Board[i][j] = 0;
            Board[i][j + 1] = 0;
            shapeMod++;
        }
        break;
    case 0:
        if (Board[i][j - 1] == 0 && Board[i][j - 2] == 0)
        {
            Board[i][j - 1] = 5;
            Board[i][j - 2] = 5;
            Board[i][j] = 0;
            Board[i + 2][j - 1] = 0;
            shapeMod++;
        }
        break;
    default:
        break;
    }
}
void Rotation_6(int &shapeMod, int i, int j)
{
    shapeMod = shapeMod % 2;
    switch (shapeMod)
    {
    case 1:
        if (Board[i][j - 1] == 0 && Board[i + 2][j] == 0)
        {
            Board[i][j - 1] = 6;
            Board[i + 2][j] = 6;
            Board[i][j] = 0;
            Board[i][j + 1] = 0;
            shapeMod++;
        }
        break;
    case 0:
        if (Board[i][j + 1] == 0 && Board[i][j + 2] == 0)
        {
            Board[i][j + 1] = 6;
            Board[i][j + 2] = 6;
            Board[i][j] = 0;
            Board[i + 2][j + 1] = 0;
            shapeMod++;
        }
        break;
    default:
        break;
    }
}
void Rotation_7(int &shapeMod, int i, int j)
{
    shapeMod = shapeMod % 4;
    switch (shapeMod)
    {
    case 1:
        if (Board[i + 2][j] == 0)
        {
            Board[i + 2][j] = 7;
            Board[i + 1][j + 1] = 0;
            shapeMod++;
        }
        break;
    case 2:
        if (Board[i + 1][j + 1] == 0)
        {
            Board[i + 1][j + 1] = 7;
            Board[i][j] = 0;
            shapeMod++;
        }
        break;
    case 3:
        if (Board[i - 1][j + 1] == 0)
        {
            Board[i - 1][j + 1] = 7;
            Board[i][j] = 0;
            shapeMod++;
        }
        break;
    case 0:
        if (Board[i + 1][j - 1] == 0)
        {
            Board[i + 1][j - 1] = 7;
            Board[i + 2][j] = 0;
            shapeMod++;
        }
        break;
    default:
        break;
    }
}

void rotate_move(int &shapeMod)
{
    int x;
    int y;
    switch (shape_finder(x, y))
    {
    case 1:
        // squar doesn't rotate
        break;
    case 2:
        Rotation_2(shapeMod, x, y);
        break;
    case 3:
        Rotation_3(shapeMod, x, y);
        break;
    case 4:
        Rotation_4(shapeMod, x, y);
        break;
    case 5:
        Rotation_5(shapeMod, x, y);
        break;
    case 6:
        Rotation_6(shapeMod, x, y);
        break;
    case 7:
        Rotation_7(shapeMod, x, y);
        break;

    default:
        break;
    }
}

//-----------------------------------| Movment |---------------------------------------------------------
bool right_check()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (Board[i][j] > 0 && Board[i][j + 1] < 0)
                return 0;
        }
    }
    return 1;
}
void right_move(Time timeBox)
{

    if (right_check())
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (Board[i][j] > 0)
                {
                    Board[i][j + 1] = Board[i][j];
                    Board[i][j] = 0;
                }
            }
        }

        showGame(timeBox);
    }
}
bool left_check()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (Board[i][j] > 0 && Board[i][j - 1] < 0)
                return 0;
        }
    }
    return 1;
}
void left_move(Time timeBox)
{
    if (left_check())
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (Board[i][j] > 0)
                {
                    Board[i][j - 1] = Board[i][j];
                    Board[i][j] = 0;
                }
            }
        }
        showGame(timeBox);
    }
}

bool do_move(int &shapeMod, Time timeBox)
{
    char order;
    for (int i = 0; i < m; i++)
    {

        if (_kbhit())
        {
            order = getch();
            switch (order)
            {
            case 'd':
                right_move(timeBox);
                break;
            case 'a':
                left_move(timeBox);
                break;
            case 's':
                down_move(timeBox);
                break;
            case 'w':
            case 72: 
                rotate_move(shapeMod);
                break;
            case 32:
                for (int k = 0; k < n; k++)
                {
                    down_move(timeBox);
                }
                break;
            case 'p':
                if(pause_menu(timeBox))
                {return 1;}
                break;
            default:
                break;
            }
        }
    }
    return 0;
}

void remove_line(int prime_i,Time timeBox)
{
    for (int j = 1; j < m - 1; j++)
    {
        Board[prime_i][j] = 0;
    }
    showGame(timeBox,100);
    for (int i = prime_i - 1; i > 1; i--)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (Board[i][j] < 0)
            {
                Board[i + 1][j] = Board[i][j];
                Board[i][j] = 0;
            }
        }
    }
    showGame(timeBox);
}

void remove_floor(Time timeBox)
{
    int score_multiplier = 1;
    bool can_remove;
    for (int i = n - 2; i >= 0; i--)
    {
        can_remove = 1;
        for (int j = 1; j < m - 1; j++)
        {
            if (Board[i][j] == 0)
            {
                can_remove = 0;
            }
        }
        if (can_remove)
        {
            remove_line(i, timeBox);
            score += 100 * score_multiplier;
            score_multiplier *= 2;

            i++;
        }
    }
}
//-----------------------------------| Ending |----------------------------------------------------------------------------------------------------------------
bool is_game_over()
{
    for (int j = 1; j < m - 1; j++)
    {
        if (Board[1][j] < 0)
        {
            return 1;
        }
    }
    return 0;
}

void start(int possiblity[8])
{   
    if (style==1)
    game_BoarderLine_1();


    for (int i = 0; i < 8; i++)
    {
        possiblity[i]=1;
    }

    
    score = 0;

    



    for (int i = 0; i < n; i++)
    {
        Board[i][0] = -9; // har do zele amodi ro -9 karde
        Board[i][m - 1] = -9;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            Board[i][j] = 0; // baghiyeye deraye ha ro barabar 0 gharar mide
        }
    }
    for (int j = 0; j < m; j++)
    {
        Board[n - 1][j] = -9;
    } // satr akhar -9 mishe
    random_shape(possiblity);
    insert_shape();
    random_shape(possiblity);
}
//-----------------------------------| Leader Board |-----------------------------------------------------------------------------------------
void sortScores(int k)
{
    Player_Score temp;
    int i, j;
    bool swapped;
    for (i = 0; i < 10; i++)
    {
        swapped = false;
        for (j = 0; j < 11 - i - 1; j++)
        {
            if (scoreBox[k][j].score < scoreBox[k][j + 1].score)
            {
                temp.name = scoreBox[k][j].name;
                temp.m_size = scoreBox[k][j].m_size;
                temp.n_size = scoreBox[k][j].n_size;
                temp.score = scoreBox[k][j].score;
                temp.time = scoreBox[k][j].time;
                ///////////////
                scoreBox[k][j].name = scoreBox[k][j + 1].name;
                scoreBox[k][j].m_size = scoreBox[k][j + 1].m_size;
                scoreBox[k][j].n_size = scoreBox[k][j + 1].n_size;
                scoreBox[k][j].score = scoreBox[k][j + 1].score;
                scoreBox[k][j].time = scoreBox[k][j + 1].time;
                //////////////
                scoreBox[k][j + 1].name = temp.name;
                scoreBox[k][j + 1].m_size = temp.m_size;
                scoreBox[k][j + 1].n_size = temp.n_size;
                scoreBox[k][j + 1].score = temp.score;
                scoreBox[k][j + 1].time = temp.time;
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

void show_scoreBoard(int k)
{
    system("cls");
    cout << setw(10) << "name" << " "
         << setw(10) << "score" << " "
         << "size" 
         << "time";   
        cout << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << setw(10) << scoreBox[k][i].name << " "
             << setw(10) << scoreBox[k][i].score << " "
             << scoreBox[k][i].m_size << "*"
             << scoreBox[k][i].n_size << " " ;
        time_show(scoreBox[k][i].time);     
        cout << endl;
    }
}
//-----------------------------------| Setting |-----------------------------------------------------------------------------------------

void selected_choice(int optionNum, int order){
    SetConsoleTextAttribute(console,15);
    if(optionNum==order){
        SetConsoleTextAttribute(console,112);
    }    
}

int show_setting(){
    int userPointer = 1 ;
    
    while(true){
        system("cls");
        cout << "SETTING" << endl ;
        selected_choice(1,userPointer);    
        cout << "Style" << endl;
        selected_choice(2,userPointer);   
        cout  << "Size" << endl;
        selected_choice(3,userPointer);   
        cout << "Difficulty Level" << endl;
        SetConsoleTextAttribute(console,15);
        char order = getch();
        switch (order)
        {
        case 'w':
            if(userPointer>1)
            userPointer--;
            break;
        case 's':
            if(userPointer<3)
            userPointer++;
            break;
        case '\r':
            system("cls");
            return userPointer;
            break;
        default:
            break;
        }
    }
}
int show_styleSetting(){
    int userPointer = 1 ;
    
    while(true){
        system("cls");
        cout << "choose your style" << endl ;
        selected_choice(1,userPointer);    
        cout << "classic 1984" << endl;
        selected_choice(2,userPointer);   
        cout  << "classic colored" << endl;
        SetConsoleTextAttribute(console,15);
        char order = getch();
        switch (order)
        {
        case 'w':
            if(userPointer>1)
            userPointer--;
            break;
        case 's':
            if(userPointer<2)
            userPointer++;
            break;
        case '\r':
            system("cls");
            return userPointer;
            break;
        default:
            break;
        }
    }
}
int show_difficulty_level_Setting(){
    int userPointer = 0 ;
    
    while(true){
        system("cls");
        cout << "choose Difficulty" << endl ;
        selected_choice(0,userPointer);    
        cout << "NOOB :D" << endl;
        selected_choice(1,userPointer);   
        cout  << "EASY" << endl;
        selected_choice(2,userPointer);   
        cout  << "NORMAL" << endl;
        selected_choice(3,userPointer);   
        cout  << "HARD " << endl;
        SetConsoleTextAttribute(console,15);
        char order = getch();
        switch (order)
        {
        case 'w':
            if(userPointer>0)
            userPointer--;
            break;
        case 's':
            if(userPointer<3)
            userPointer++;
            break;
        case '\r':
            system("cls");
            return userPointer;
            break;
        default:
            break;
        }
    }
}


void setting(){
    while(1){
        system("cls");
        switch (show_setting())
        {
        case 1:
            style = show_styleSetting();
            break;
        case 2:
            cout << "Enter hight : " << endl ;
                cin >> n ;
                n += 3;
                cout << "Enter wighth : " << endl ;
                cin >> m ;
                m += 2;
            break;   
        case 3:
            difficulty_Level = show_difficulty_level_Setting();
            break;     
        default:
            break;
        }    
        cout << "setting applied"<< endl;
            Sleep(1500);
            system("cls");
            return;
    }
}
void difficulty_adjustment(int &fps){
     switch (difficulty_Level)
    {
    case 3:
        fps = 10;
        if(style==1){
            doration=5;
        }
        break;    
    case 2:
        fps = 10;
        if(style==1){
            doration=5;
        }
        break;
    case 1:
        fps = 20;
        if(style==1){
            doration=4;
        }
        break;
    case 0:
        fps = 30;
        if(style==1){
            doration=1;
        }
        break;    
    default:
        break;
    }
}
//-----------------------------------| File Handeling |-----------------------------------------------------
void readTopScores()
{
    fstream myScoreFile;
    myScoreFile.open("LeaderBoard.txt", ios::in);
    if (myScoreFile.fail())
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                scoreBox[i][j].name = "-";
                scoreBox[i][j].score = 0;
                scoreBox[i][j].n_size = 0;
                scoreBox[i][j].m_size = 0;
                scoreBox[i][j].time = 0;
            }
        }    
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            int j = 0;
            while (myScoreFile >> scoreBox[i][j].name >> scoreBox[i][j].score >> scoreBox[i][j].n_size >> scoreBox[i][j].m_size >> scoreBox[i][j].time && j<10)
            {
                j++;
            }

        }
    }
}

void writeTopScores()
{
    ofstream writerScore("LeaderBoard.txt");
    for (int i = 0; i < 4; i++)
    {
        for (int j=0; j < 10; j++) {
            writerScore
                << scoreBox[i][j].name << " "
                << scoreBox[i][j].score << " "
                << scoreBox[i][j].n_size << " "
                << scoreBox[i][j].m_size << " "
                << scoreBox[i][j].time << " \n";
                
        }
        writerScore << "temp 0 0 0 0\n";
    }
}
//-----------------------------------| Main |----------------------------------------------------------------------------------------------------------
void game_run(int possiblity[8],Time timeBox)
{
    int fps ;

    difficulty_adjustment(fps);
   
    MoveCurser(0, 0);
    int shapeMode = 1;
    int fps_shadow = fps;

    timeBox.start = time(0);
    
    while (true)
    {
        if (make_solid())
        {

            if (is_game_over())
            {
                // ending ceremony
                system("cls");
                cout<<"▒█▀▀█ ░█▀▀█ ▒█▀▄▀█ ▒█▀▀▀ 　 ▒█▀▀▀█ ▒█░░▒█ ▒█▀▀▀ ▒█▀▀█\n"; 
                cout<<"▒█░▄▄ ▒█▄▄█ ▒█▒█▒█ ▒█▀▀▀ 　 ▒█░░▒█ ░▒█▒█░ ▒█▀▀▀ ▒█▄▄▀\n"; 
                cout<<"▒█▄▄█ ▒█░▒█ ▒█░░▒█ ▒█▄▄▄ 　 ▒█▄▄▄█ ░░▀▄▀░ ▒█▄▄▄ ▒█░▒█\n";
                Sleep(3000);

                return;
            }
            else
            {
                remove_floor(timeBox);
                insert_shape();
                shapeMode = 1;
                random_shape(possiblity);
                fps = fps_shadow;

                if(possiblity[0]>100){
                    for (int i = 0; i < 8; i++)
                    {
                        possiblity[i]=1;
                    }
                }
            }
        }
        down_move(timeBox);
        if (difficulty_Level==3&&fps>1){
            fps --;
        }
        if (down_check())
        {
            for (int k = 0; k < fps; k++)
            {
                showGame(timeBox);
                if(do_move(shapeMode,timeBox))
                {return;}
                showGame(timeBox);
            }
        }
        else
        {
            for (int k = 0; k < fps/2; k++)
            {
                showGame(timeBox);
                if(do_move(shapeMode,timeBox))
                {return;}
                showGame(timeBox);
            }
        }   
    }
}

void newgame()
{
    Board = new int *[n]; // declareation of main board
    for (int k = 0; k < n; k++)
    {
        Board[k] = new int[m];
    }
    tempUp = new int *[2]; // declareation of a small arr to create shapes
    for (int k = 0; k < m; k++)
    {
        tempUp[k] = new int[m];
    }

    int *possiblity;
    possiblity = new int[8];

    cout << "enter your name :";
    cin >> scoreBox[difficulty_Level][10].name;
    score = 0;                             // tamoom nashode
    scoreBox[difficulty_Level][10].n_size = n - 3;
    scoreBox[difficulty_Level][10].m_size = m - 2;

    system("cls");
    Time timeBox;
    // timeBox.total=0;
    // timeBox.reserve=0;

    start(possiblity);
   
    game_run(possiblity,timeBox);
    SetConsoleTextAttribute(console, 15);
    scoreBox[difficulty_Level][10].score = score ;
    
    sortScores(difficulty_Level);

}
int show_menu(){

    int userPointer = 1 ;
    while(true){
        system("cls");
        selected_choice(1,userPointer);
        cout << "New Game" << endl;
        selected_choice(2,userPointer);   
        cout  << "How To Play" << endl;
        selected_choice(3,userPointer);   
        cout << "Score board" << endl;
        selected_choice(4,userPointer);   
        cout << "setting" << endl;
        selected_choice(5,userPointer);   
        cout << "Exit" << endl;
        SetConsoleTextAttribute(console,15);
        char order = getch();
        switch (order)
        {
        case 'w':
        case 72:
            if(userPointer>1)
            userPointer--;
            else
            userPointer = 5;
            break;
        case 's':
            if(userPointer<5)
            userPointer++;
            else
            userPointer = 1;
            break;
        case '\r':
            system("cls");
            return userPointer;
            break;
        default:
            break;
        }
    }
}

int scoreBoard_menu(){
    int userPointer = 0 ;
    
    while(true){
        system("cls");
        cout << "Choose Difficulty Level" << endl ;
        selected_choice(0,userPointer);    
        cout << "NOOB :D" << endl;
        selected_choice(1,userPointer);   
        cout  << "EASY" << endl;
        selected_choice(2,userPointer);   
        cout  << "NORMAL" << endl;
        selected_choice(3,userPointer);   
        cout  << "HARD " << endl;
        SetConsoleTextAttribute(console,15);
        char order = getch();
        switch (order)
        {
        case 'w':
            if(userPointer>0)
            userPointer--;
            break;
        case 's':
            if(userPointer<3)
            userPointer++;
            break;
        case '\r':
            system("cls");
            return userPointer;
            break;
        default:
            break;
        }
    }
}

void menu()
{
    while (true)
    {
        system("cls");
        switch (show_menu())
        {
        case 1:
            newgame();
            break;
        case 2:
            howtoPlay();
            getch();
            break;
        case 3:

            show_scoreBoard(scoreBoard_menu());
            cout << endl
                 << "press enter.";
            getch();
            break;
        case 4:
            setting();
            break;
        case 5:
            return;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------
int main()
{

    scoreBox = new Player_Score *[4];
    for (int k = 0; k < n; k++)
    {
        scoreBox[k] = new Player_Score [11];
    }

   
    srand(time(0)); // using time as seed for rand()
    setcursor(0, 0);
    //-------------------------------------------------------------------------------------------------------------------------------------------
    readTopScores();
    menu();
    
    //---------------------------------------------------------------------------------------------------------------------------------------------
    writeTopScores();

}
