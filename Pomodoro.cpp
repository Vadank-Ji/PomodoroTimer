//#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <curses.h>
//#include <unistd.h>

using namespace std;

class pomodoro{
protected:
    int min;
    float min1;
    int count;
public:
    pomodoro(){}
    pomodoro(int min){
        if (min > 50 || min < 1)
            printw ( "\nTimer shouldn't be more than 50 mins or less than 25 mins! RETRY!\n");

        else{
            this -> min = min;
            min1 = ((float)min/(double)25.0)*5.0;
            if (min<25){
                min1 = 1;
            }

            count=0;
        }
    }
    void timerP(){

        // Stores time as seconds
        time_t t = time(NULL);
        // converts into standard form
        tm* timeinfo = localtime(&t);

        int x = t;
        int s = 1;
        int m = 1;

        bool paused = false;
        int ch;

        //clear();
        move(6,0);
        printw("Study Timer Started! Press SPACE to pause/resume, ENTER to stop.\n");
        refresh();
        nodelay(stdscr, TRUE);
        while (true){
            ch = getch();  // check if a key was pressed
            if (ch == ' ') {
                paused = !paused;
                //clear();
                move(8, 0);
                if (paused) {

                    printw("PAUSED - Press SPACE to resume\n");
                    int y, x;
                    move(8, 0);
                }
                else {
                    printw("RESUMED - Timer running...\n");
                    x = time(NULL) - (s-1);
                    int y, x;
                    getyx(stdscr, y, x);
                    move(8, 0); // move cursor to row 8, column 0 (or wherever you want the timer)
                    clrtoeol(); // clear the rest of the line
                    printw ("%d:",s/60 );
                    if (s-(s/60)*60 <= 9){
                        printw("0");
                    }
                    printw ("%d",s-(s/60)*60 );
                    getyx(stdscr, y, x);  // Get current cursor position
                    move(y-6, x - 4);       // Move back 3 columns
                    printw("");        // Overwrite with spaces
                    move(y-6, x - 4);       // Move back again to update text
                    refresh();
                }
                refresh();
            }
            if (ch == '\n' || ch == 10 || ch == KEY_ENTER) {
                break;
            }
            if (!paused) {
                t= time(NULL);
                // asctime converts into string;
                //cout << "The local time is " << asctime(timeinfo)<< endl;

                if (t == x+s){
                    int y, x;
                    getyx(stdscr, y, x);
                    //move(y,x); // timer display
                    move(8, 0); // move cursor to row 8, column 0 (or wherever you want the timer)
                    clrtoeol(); // clear the rest of the line
                    printw ("%d:",s/60 );
                    if (s-(s/60)*60 <= 9){
                        printw("0");
                        }
                    printw ("%d",s-(s/60)*60 );
                    getyx(stdscr, y, x);  // Get current cursor position
                    move(y-6, x - 4);       // Move back 3 columns
                    printw("");        // Overwrite with spaces
                    move(y-6, x - 4);       // Move back again to update text
                    refresh();

                    //printw("\n");
                    //refresh();
                    s++;
                    //count++;
                }
                if (t == x+min*60){
                    break;
                }
                refresh();
            }

        }
        count++;
    }


    float reTime(){
        float x = min1;
        return x;
    }

    void timerB(){
        time_t t = time(NULL);
        // converts into standard form
        tm* timeinfo = localtime(&t);
        int x = t;
        int s = 1;
        int m = 1;
        int ch;
        bool paused = false;

        clear();
        printw("Break Timer Started! Press SPACE to pause/resume, ENTER to stop.\n");
        refresh();
        nodelay(stdscr, TRUE);

        while (true){

            ch = getch();  // check if a key was pressed

            if (ch == ' ') {
                paused = !paused;
                clear();
                if (paused) {
                    printw("PAUSED - Press SPACE to resume\n");
                } else {
                    printw("RESUMED - Timer running...\n");
                }
                refresh();
            }
            if (ch == '\n' || ch == 10 || ch == KEY_ENTER) {
                break;
            }
            if (!paused) {
                t= time(NULL);
                // asctime converts into string;
                //cout << "The local time is " << asctime(timeinfo)<< endl;

                if (t == x+s){
                    move(2, 0);
                    printw ("%d:",s/60 );
                    if (s-(s/60)*60 <= 9){
                        printw("0");
                    }
                    printw ("%d",s-(s/60)*60 );
                    int y, x;
                    getyx(stdscr, y, x);  // Get current cursor position
                    move(y, x - 4);       // Move back 3 columns
                    printw("");        // Overwrite with spaces
                    move(y, x - 4);       // Move back again to update text
                    refresh();

                    //printw("\n");
                    //refresh();
                    s++;
                }
                if (t == x+min*60){
                    break;
                }
            }

        }
        if (count == 4){
            min1 = min;
        }
    }
    string currentT(){
        time_t t = time(NULL);
        tm* timeinfo = localtime(&t);
        //asctime converts into string;
        return asctime(timeinfo);
    }
};

void sPomo(int n, pomodoro p){
    static const int n0 = n;
        if (n!=0){

            printw("\nStarting Timer now:\n");
            p.timerP();
            printw("\nStarting Break now:\n");
            refresh();
            //p.timerB();
            //clear();
            printw("Pomodoro-%d ended at: %s\n", n0-n+1, p.currentT().c_str());
            refresh();
            sPomo(n-1, p);
        }
        else{
            return;
            }
}

void startpomo(){

    cbreak();
    nodelay(stdscr, TRUE);
    initscr();

    //stores time as seconds
    pomodoro pomo;
    int Ptime;
    bool n = true;

    do{
        
        clear();  // Clear the whole screen each loop to avoid repeated prompts
        printw("Enter setup time (1 to 50): ");
        refresh();
        flushinp(); // clear leftover junk input
      
    }
    while (scanw("%d", &Ptime) != 1 || (Ptime > 50 || Ptime < 1));

    int p;

    do{
        //clear();
        printw("Enter No or pomodoros:");
        refresh();
        flushinp();
        }
    while (scanw("%d", &p)!=1);

   // printw("%d\n", Ptime+1);

    refresh();
    pomo = pomodoro(Ptime);
    refresh();
    printw("\nThe break time has been set accordingly:\n");
    printw( "ie. %f\n", pomo.reTime());
    refresh();
    
    }
int main(){
    startpomo();
    return 0;
}
