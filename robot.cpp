#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;

void read_file(int matran[MAX_ROWS][MAX_COLS], int& rows, int& cols, int n ) {
    ifstream file("input.txt");
    file >> rows >> cols;
    if(n == 0)
    {
        cout << endl ;
    }
    for (int i = 0; i < rows; i++) {
        if(n == 0 )
        {cout << "\t\t\t\t\t\t";}
        for (int j = 0; j < cols; j++) {
            file >> matran[i][j];
            if (n == 0)
                cout<< setw(0)<<"|" << setw(3)<< matran[i][j];
            else continue;
        }
        if (n == 0)
         {   cout << "|";
            cout<<endl ;}
        else continue;
    }
    file.close();
}
void in_matran_1_robot(int matran[MAX_ROWS][MAX_COLS], bool visited[MAX_ROWS][MAX_COLS], int rows, int cols) {
    cout << "\t\t\t\t\t\tROBOT RUN:"<< endl ;
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t\t\t";
        for (int j = 0; j < cols; j++) {
            if (visited[i][j]) {
                cout << setw(0)<<"|"<< "\033[36m"<<setw(3)<< "*"<<"\033[0m";
            } else {
                cout << setw(0)<<"|"<<setw(3)<< matran[i][j];
            }
        }
        cout << "|";
        cout << endl;
    }
}

void in_matran_2robot_2(int matran[MAX_ROWS][MAX_COLS], bool visited1[MAX_ROWS][MAX_COLS], bool visited2[MAX_ROWS][MAX_COLS], int rows, int cols) {
    cout << "\t\t\t\t\t\tROBOT RUN:"<< endl ;
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t\t\t";
        for (int j = 0; j < cols; j++) {
            if (visited1[i][j]) {
                cout << setw(0)<<"|"<< "\033[36m"<<setw(3)<< "*"<<"\033[0m";
            } else {
                cout << setw(0)<<"|"<<setw(3)<< matran[i][j];
            }
        }
        cout << "|";
        cout << "   ";
        for (int j = 0; j < cols; j++) {
            if (visited2[i][j]) {
                cout << setw(0)<<"|"<< "\033[32m"<<setw(3)<< "*"<<"\033[0m";
            } else {
                cout << setw(0)<<"|"<<setw(3)<< matran[i][j];
            }
        }
        cout << "|";
        cout << endl;
    }
}

void in_1matran_2robot(int matran[MAX_ROWS][MAX_COLS], int rows, int cols, int path1[], int path_size1, int path2[], int path_size2, int x1, int y1, int x2, int y2)
{
    int matran_1 [MAX_ROWS][MAX_COLS];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matran_1[i][j] = matran[i][j];
        }
    }

    for (int i = 0; i < path_size1; i++) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                if (matran[x][y] == path1[i]) {
                   matran_1[x][y] = -1;
                }
            }
        }
    }

    for (int i = 0; i < path_size2; i++) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                if (matran[x][y] == path2[i]) {
                    matran_1[x][y] = -2;
                }
            }
        }
    }

    matran_1[x1][y1] = -1;
    matran_1[x2][y2] = -2;

    cout << "\t\t\t\t\t\tROBOT RUN:"<< endl ;
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t\t\t";
        for (int j = 0; j < cols; j++) {
            if (matran_1[i][j] == -1) {
                cout << setw(0)<<"|"<< "\033[31m"<<setw(3)<< "A"<<"\033[0m";
            } else if (matran_1[i][j] == -2) {
                cout << setw(0)<<"|"<< "\033[33m"<<setw(3)<< "B"<<"\033[0m";
            } else {
                cout  << setw(0)<<"|"<<setw(3)<< matran_1[i][j] ;
            }
        }
        cout << "|";
        cout << endl;
    }
}



int tim_duong_di_1robot(int matran[MAX_ROWS][MAX_COLS], int x, int y, bool visited[MAX_ROWS][MAX_COLS], int rows, int cols, int giatri[], int buoc_nhay, string print) {
    if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y]) {
        cout << "\033[31m \t "<< "Toa do da ngoai bang" <<"\033[0m"<< endl ;
        return buoc_nhay;
    }
    visited[x][y] = true;
    if(print == "TH1")
    {system("cls");
    in_matran_1_robot(matran, visited, rows, cols);}

    this_thread::sleep_for(chrono::seconds(1));

    giatri[buoc_nhay++] = matran[x][y];
    int max_val = 0;
    int next_x = -1, next_y = -1;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matran[new_x][new_y] > max_val && !visited[new_x][new_y]) {
            max_val = matran[new_x][new_y];
            next_x = new_x;
            next_y = new_y;
        }
    }
    if (next_x != -1) {
        buoc_nhay = tim_duong_di_1robot(matran, next_x, next_y, visited, rows, cols, giatri, buoc_nhay, "TH1");
    }
    return buoc_nhay;
}
int tim_duong_robot1(int matran[MAX_ROWS][MAX_COLS], int x, int y, bool visited1[MAX_ROWS][MAX_COLS], bool visited2[MAX_ROWS][MAX_COLS], int rows, int cols, int giatri[], int buoc_nhay, string print) {
    if (x < 0 || x >= rows || y < 0 || y >= cols || visited1[x][y]) {
        cout << "\033[31m \t "<< "Toa do da ngoai bang" <<"\033[0m"<< endl ;
        return buoc_nhay;
    }
    visited1[x][y] = true;
    if(print == "TH1")
    {system("cls");
    in_matran_2robot_2(matran, visited1,visited2, rows, cols);}

    this_thread::sleep_for(chrono::seconds(1));

    giatri[buoc_nhay++] = matran[x][y];
    int values = 0;
    int next_x = -1, next_y = -1;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matran[new_x][new_y] > values && !visited1[new_x][new_y]) {
            values = matran[new_x][new_y];
            next_x = new_x;
            next_y = new_y;
        }
    }
    if (next_x != -1) {
        buoc_nhay = tim_duong_robot1(matran, next_x, next_y, visited1,visited2, rows, cols, giatri, buoc_nhay, "TH1");
    }
    return buoc_nhay;
}
int tim_duong_robot2(int matran[MAX_ROWS][MAX_COLS], int x, int y,bool visited1[MAX_ROWS][MAX_COLS], bool visited2[MAX_ROWS][MAX_COLS], int rows, int cols, int giatri[], int buoc_nhay, string print) {
    if (x < 0 || x >= rows || y < 0 || y >= cols || visited2[x][y]) {
        cout << "\033[31m \t "<< "Toa do da ngoai bang" <<"\033[0m"<< endl ;
        return buoc_nhay;
    }
    visited2[x][y] = true;
    if(print == "TH1")
    {system("cls");
    in_matran_2robot_2(matran, visited1, visited2, rows, cols);}

    this_thread::sleep_for(chrono::seconds(1));

    giatri[buoc_nhay++] = matran[x][y];
    int max_val = 0;
    int next_x = -1, next_y = -1;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matran[new_x][new_y] > max_val && !visited2[new_x][new_y]) {
            max_val = matran[new_x][new_y];
            next_x = new_x;
            next_y = new_y;
        }
    }
    if (next_x != -1) {
        buoc_nhay = tim_duong_robot2(matran, next_x, next_y,visited1, visited2, rows, cols, giatri, buoc_nhay, "TH1");
    }
    return buoc_nhay;
}

bool tim_duong_robot_1_2(int matran[MAX_ROWS][MAX_COLS], int x, int y, bool visited[MAX_ROWS][MAX_COLS], int rows, int cols, int& next_x, int& next_y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y]) {
        return false;
    }

    visited[x][y] = true;

    int max_val = 0;
    next_x = -1, next_y = -1;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i], new_y = y + dy[i];
        if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < cols && matran[new_x][new_y] > max_val && !visited[new_x][new_y]) {
            max_val = matran[new_x][new_y];
            next_x = new_x;
            next_y = new_y;
        }
    }
    return next_x != -1;
}

int score(int buoc_nhay, int giatri[])
{
    int scores_value = 0;
        for (int i = 0; i < buoc_nhay; i++)
        {
            scores_value += giatri[i];
        }
        return scores_value ;
}

void trung_nhau(int buoc_nhay_1, int buoc_nhay_2 , int giatri_1[], int giatri_2[] )
{
    for (int i = 0; i < buoc_nhay_1; i++)
        {
            for (int j = 0; j < buoc_nhay_2; j++)
            {
                if (giatri_1[i] == giatri_2[j])
                {
                    cout << giatri_1[i]<< " ";
                }
            }
        }
}

string robot_win (int score_robot1 ,int score_robot2)
{
    string result ;
    if ( score_robot1 > score_robot2)
        result  = "ROBOT 1 WIN";
    else if ( score_robot1 < score_robot2)
        result = "ROBOT 2 WIN";
    else
        {result = "ROBOTS TIE";}
    return result ;
}
void write_output1(string file_name, int giatri[], int buoc_nhay)
{
    ofstream file(file_name);
    file << "So buoc di cua robot: "<< buoc_nhay<< endl ;
    file << "Robot score : " << score(buoc_nhay, giatri) <<endl ;
    file << "Duong di cua robot: ";
    for (int i = 0; i < buoc_nhay; i++) {
        file << giatri[i] << " ";
    }
    file.close();
}
void write_output(string file_name, int giatri_1[], int buoc_nhay_1, int giatri_2[], int buoc_nhay_2, string n )
{
    ofstream file(file_name);
    file << "Robot 1: " << endl;
    file << "So buoc di cua robot 1: "<< buoc_nhay_1<< endl ;
    file << "Robot 1 score : " << score(buoc_nhay_1, giatri_1) <<endl ;
    file << "Duong di cua robot 1: ";
    for (int i = 0; i < buoc_nhay_1; i++) {
        file << giatri_1[i] << " ";
    }
    file << endl;
    file << "=========================" << endl ;
    file << "Robot 2: " << endl;
    file << "So buoc di cua robot 1: "<< buoc_nhay_2<< endl ;
    file << "Robot score 1: " << score(buoc_nhay_2, giatri_2) <<endl ;
    file << "Duong di cua robot 1: ";
    for (int i = 0; i < buoc_nhay_2; i++) {
        file << giatri_2[i] << " ";
    }
    file << endl;
    file << "=========================" ;

    if (n == "TH2")
    {
        file << endl ;
        file << "Cac vi tri trung nhau: " ;
        for (int i = 0; i < buoc_nhay_1; i++)
            {
                for (int j = 0; j < buoc_nhay_2; j++)
                {
                    if (giatri_1[i] == giatri_2[j])
                    {
                        file << giatri_1[i]<< " ";
                    }
                }
            }
    }

    file << endl ;
    file <<robot_win(score(buoc_nhay_1, giatri_1), score(buoc_nhay_2, giatri_2));
    file.close();
}

int main ()
{
    int rows , cols;
    int matran[MAX_ROWS][MAX_COLS];
    bool visited[MAX_ROWS][MAX_COLS] = {false};

    read_file( matran, rows, cols, 1);


    int options ;
    cout << "\t\t\t\t| ----------------------------------------------------- |\n";
    cout << "\t\t\t\t|    	             ABOUT THE PROGRAMMER               |\n";
    cout << "\t\t\t\t| ----------------------------------------------------- |\n";
    cout << "\t\t\t\t|"<<"\033[1;31m"<<"Name: NGUYEN VAN HUY                                   "<<"\033[0m"<<"|\n";
    cout << "\t\t\t\t|\033[1;33mStudent code: 2251120160     \033[0m                          |\n";
    cout << "\t\t\t\t|\033[1;32mClass: CN22D                  \033[0m                         |\n";
    cout << "\t\t\t\t|                                                       |\n";

    cout << "\t\t\t\t| ----------------------------------------------------- |\n";
    cout << "\t\t\t\t|    	             --$ROBOT$--     	                |\n";
    cout << "\t\t\t\t|                                                       |\n";
    cout << "\t\t\t\t| ----------------------------------------------------- |\n";
    cout << "\t\t\t\t|                    << MENU >>                         | \n";
    cout << "\t\t\t\t|                                                       |\n";
    cout << "\t\t\t\t| Choose Mode:                                          | \n";
    cout << "\t\t\t\t|                                                       |\n";
    cout << "\t\t\t\t|\033[1;33m 1. Single-player mode 		   \033[0m             |\n";
    cout << "\t\t\t\t|\033[1;31m 2. Multi-player mode                         \033[0m         | \n";
    cout << "\t\t\t\t|\033[1;32m 3. Resistance mode 	\033[0m                                |\n";
    cout << "\t\t\t\t|\033[1;34m 4. Exit. 	\033[0m                                        |\n";
    cout << "\t\t\t\t|                                                       |\n";
    cout << "\t\t\t\t| ----------------------------------------------------- |\n";
    cout << "\033[1;31m\t\t\t\t\t\t       |MATRIX|\033[0m" << endl;
    read_file( matran, rows, cols, 0 );



    while (true){
        cout << "\033[1;32m\t Nhap lua chon: \033[0m" ;
        cin >> options ;
    if(options == 1 || options == 2 || options == 3 || options == 4 ){
    switch (options)
        {
        case 1:
        {   // Robot
            cout << "\033[1;33m \t Nhap toa do bat dau cua robot (x y): \033[0m";
            int x, y;
            cin >> x >> y;

            int giatri[MAX_ROWS * MAX_COLS];
            int buoc_nhay = tim_duong_di_1robot(matran, x, y, visited, rows, cols, giatri, 0, "TH1");
            cout << "\033[1;33m \t So buoc di cua robot: \033[0m"<< buoc_nhay<< endl ;
            cout << "\033[1;33m \t Robot score : \033[0m" << score(buoc_nhay, giatri) <<endl ;
            cout << "\033[1;33m \t Duong di cua robot: \033[0m";
            for (int i = 0; i < buoc_nhay; i++)
            {
                cout << giatri[i]<< " ";
            }
            cout << endl ;
            write_output1("output.txt", giatri, buoc_nhay);
            for (int i=0;i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    visited[i][j]=false;
                }
            }
            break;

        }
        case 2 :
        {   // Robot 1
            bool visited1[MAX_ROWS][MAX_COLS] = {false};
            bool visited2[MAX_ROWS][MAX_COLS] = {false};
            cout << "\033[1;34m \t Nhap toa do bat dau cua robot 1 (x y): \033[0m";
            int x1, y1;
            cin >> x1 >> y1;

            // Robot 2
            cout << "\033[1;36m \t Nhap toa do bat dau cua robot 2 (x y): \033[0m";
            int x2, y2;
            cin >> x2 >> y2;

            int giatri_1[MAX_ROWS * MAX_COLS];
            int buoc_nhay_1 = tim_duong_robot1(matran,x1,y1 ,visited1, visited2 ,rows ,cols ,giatri_1 ,0, "TH2");





            int giatri_2[MAX_ROWS * MAX_COLS];
            int buoc_nhay_2 = tim_duong_robot2(matran,x2,y2 ,visited1, visited2 ,rows ,cols ,giatri_2 ,0, "TH2");

            cout << "\033[1;31m \t ROBOT 1:  \033[0m"<< endl ;
            cout << "\033[1;34m \t So buoc di cua robot 1: \033[0m"<< buoc_nhay_1<< endl ;
            cout << "\033[1;34m \t Robot score 1: \033[0m" << score(buoc_nhay_1, giatri_1) <<endl ;
            cout << "\033[1;34m \t Duong di cua robot 1: \033[0m";
            for (int i = 0; i < buoc_nhay_1; i++)
            {
                cout << giatri_1[i]<< " ";
            }
            cout << endl ;

            cout << "\033[1;31m \t ROBOT 2:  \033[0m"<< endl ;
            cout << "\033[1;36m \t So buoc di cua robot 2: \033[0m"<< buoc_nhay_2<< endl ;
            cout << "\033[1;36m \t Robot 2 score : \033[0m" << score(buoc_nhay_2, giatri_2) <<endl ;
            cout << "\033[1;36m \t Duong di cua robot 2: \033[0m";
            for (int i = 0; i < buoc_nhay_2; i++)
            {
                cout << giatri_2[i]<< " ";
            }
            cout << endl ;
            cout << "\033[1;31m \t ========================="<< endl;
            cout << "\033[1;31m \t Cac vi tri robot trung nhau: \033[0m" ;
            trung_nhau( buoc_nhay_1, buoc_nhay_2 ,giatri_1, giatri_2 ) ;
            cout << endl ;

            cout <<"\033[1;31m\t "<< robot_win(score(buoc_nhay_1, giatri_1), score(buoc_nhay_2, giatri_2))<<"\033[0m"<<endl;

            write_output("output.txt", giatri_1, buoc_nhay_1, giatri_2, buoc_nhay_2, "TH2");
            for (int i=0;i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    visited[i][j]=false;
                }
            }
            break;
        }
        case 3 :
        {
            // Robot 1
            cout << "\033[1;34m \t Nhap toa do bat dau cua robot 1 (x y): \033[0m";
            int x1, y1;
            cin >> x1 >> y1;

            // Robot 2
            cout << "\033[1;36m \t Nhap toa do bat dau cua robot 2 (x y): \033[0m";
            int x2, y2;
            cin >> x2 >> y2;

            int giatri_1[MAX_ROWS * MAX_COLS];
            int buoc_nhay_1=0;

            int giatri_2[MAX_ROWS * MAX_COLS];
            int buoc_nhay_2=0;

            bool robot_1_turn=true;
            int new_x1 = x1 ;
            int new_y1 = y1 ;
            int new_x2 = x2 ;
            int new_y2 = y2 ;
            giatri_1[0] =matran[x1][y1];

            while(true)
            {
                if(robot_1_turn)
                {
                    int next_x,next_y;

                    if(tim_duong_robot_1_2(matran,new_x1,new_y1 ,visited ,rows ,cols ,next_x ,next_y))
                    {
                        new_x1=next_x;
                        new_y1=next_y;

                        giatri_1[buoc_nhay_1++]=matran[new_x1][new_y1];

                        system("cls");
                        in_1matran_2robot(matran, rows, cols, giatri_1, buoc_nhay_1, giatri_2, buoc_nhay_2, x1, y1, x2, y2);

                        this_thread::sleep_for(chrono::seconds(1));

                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    int next_x,next_y;

                    if(tim_duong_robot_1_2(matran,new_x2,new_y2 ,visited ,rows ,cols ,next_x ,next_y))
                    {
                        new_x2=next_x;
                        new_y2=next_y;

                        giatri_2[buoc_nhay_2++]=matran[new_x2][new_y2];

                        system("cls");
                        in_1matran_2robot(matran, rows, cols, giatri_1, buoc_nhay_1, giatri_2, buoc_nhay_2, x1, y1, x2, y2);
                        this_thread::sleep_for(chrono::seconds(1));

                    }
                    else
                    {
                        break;
                    }
                }
                robot_1_turn=!robot_1_turn;
            }

            cout << "\033[1;31m \t ROBOT 1:  \033[0m"<< endl ;
            cout << "\033[1;34m \t So buoc di cua robot 1: \033[0m"<< buoc_nhay_1<< endl ;
            cout<<"\033[1;34m \t Robot 1 score: \033[0m"<<score(buoc_nhay_1,giatri_1)<<endl;
            cout << "\033[1;34m \t Duong di cua robot 1: \033[0m"<<matran[x1][y1]<<" ";
            for (int i = 0; i < buoc_nhay_1; i++)
                {
                    cout << giatri_1[i]<< " ";
                }
            cout << endl ;
            cout << "\033[1;31m \t ROBOT 2:  \033[0m"<< endl ;
            cout << "\033[1;36m \t So buoc di cua robot 2: \033[0m"<< buoc_nhay_2<< endl ;
            cout << "\033[1;36m \t Robot 2 score : \033[0m" << score(buoc_nhay_2,giatri_2) <<endl ;
            cout << "\033[1;36m \t Duong di cua robot 2: \033[0m"<<matran[x2][y2]<<" ";
            for (int i = 0; i < buoc_nhay_2; i++)
            {
                cout << giatri_2[i]<< " ";
            }
            cout << endl ;
            cout << "\033[1;31m \t ========================="<< endl;
            cout <<"\033[1;31m \t "<< robot_win(score(buoc_nhay_1,giatri_1),score(buoc_nhay_2,giatri_2))<<"\033[0m"<<endl;
            write_output("output.txt", giatri_1, buoc_nhay_1, giatri_2, buoc_nhay_2, "TH3");
            for (int i=0;i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    visited[i][j]=false;
                }
            }
            break ;
        }
        case 4 :{
            return 0 ; }
        }
    }
         else {
                cout<<"\033[1;31m \t Lua chon khong hop le!\n \033[0m";
                continue;
            }
            cout << "\033[1;31m \t ========================="<< endl;
    }
    return 0 ;

}
