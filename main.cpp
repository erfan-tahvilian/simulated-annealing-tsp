#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <windows.h>
#define N 31
using namespace std;

void get_distances(double[][N], string[]);
double calculate_cost(int[], double[][N]);
void generate_solution(int[]);
void simulatedAnnealing(double[][N], int[], double, double, double, int, int);
void print_table(string[], int[], double[][N]);
void print_provinces(string[]);
int Menu(string[], int[], double[][N], string, double, double, double, int, bool);
void loading();
bool isNum(string);

int main() {
    srand(time(0));
    int path[N];
    string provinces[N];
    string source_province = "Source Province", temp;
    int source;
    double distances[N][N];
    int iterations = 100;
    double T = 100;
    double T_min = 0.1;
    double alpha = 0.9;
    bool flag = false;
    get_distances(distances, provinces);

    while (1) {
        switch (Menu(provinces, path, distances, source_province, T, T_min, alpha, iterations, flag)) {
            case 1:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                print_provinces(provinces);
                cout << "\t\t\t\tPlease enter the number of the source province or \"R\" for random selection : ";
                cin >> temp;
                if (temp == "R") {
                    source = rand() % N;
                    source_province = provinces[source];
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                    flag = true;
                }
                else if (isNum(temp) && stoi(temp) > 0 && stoi(temp) < 32) {
                    source_province = provinces[stoi(temp)-1];
                    source = stoi(temp)-1;
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                    flag = true;
                }
                else {
                    system("cls");
                    cout << "\n\n\n\n\t\t\t\tThe province number is incorrect!";
                    Sleep(3000);
                }
                loading();
                break;

            case 2:
                loading();
                if (flag)
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << "\n\n\n\n\t\t\t\tPlease enter the source province first!";
                    Sleep(3000);
                    loading();
                }
                break;

            case 3:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the initial temperature value : ";
                cin >> T;
                if (flag)
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                loading();
                break;

            case 4:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the minimum temperature value : ";
                cin >> T_min;
                if (flag)
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                loading();
                break;

            case 5:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the cooling rate value : ";
                cin >> alpha;
                if (flag)
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                loading();
                break;
                
            case 6:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the number of iterations : ";
                cin >> iterations;
                if (flag)
                    simulatedAnnealing(distances, path, T, T_min, alpha, iterations, source);
                loading();
                break;

            case 7:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t*** Good Bye ***";
                Sleep(3000);
                exit(1);

            default:
                system("cls");
                cout << "\n\n\n\n\t\t\t\tPlease enter correct option!";
                Sleep(3000);

        }
    }

    return 0;
}

void get_distances(double dist[][N], string provinces[]) {
    string content[N+1][N+1];
    string line, word;
    fstream file ("distances.csv");

    if (file.is_open()) {
        int row = 0;
        while (getline(file, line)) {
            stringstream str(line);
            int col = 0;
            while (getline(str, word, ',')) {
                content[row][col] = word;
                col++;
            }
            row++;
        }
    }
    file.close();

    for (int i = 1; i < N+1; i++) {
        provinces[i-1] = content[i][0];
        for (int j = 1; j < N+1; j++)
            dist[i-1][j-1] = stod(content[i][j]);
    }

}

double calculate_cost(int path[], double dist[N][N]) {
    double cost = 0;
    for (int i = 0; i < N-1; i++) {
        cost += dist[path[i]][path[i+1]];
    }
    cost += dist[path[N-1]][path[0]];
    return cost;
}

void generate_solution(int path[]) {
    int i = 0;
    int j = 0;
    while (i == 0)
        i = rand() % N;
    while (j == 0)
        j = rand() % N;
    swap(path[i], path[j]);
}

void simulatedAnnealing(double dist[][N], int path[], double T, double T_min, double alpha, int iterations, int source) {
    for (int i = 0; i < N; i++) {
        path[i] = i;
    }
    swap(path[0],path[source]);

    while (T > T_min) {
        for (int i = 0; i < iterations; i++) {
            int new_path[N];
            for (int i = 0; i < N; i++) {
                new_path[i] = path[i];
            }
            generate_solution(new_path);
            double delta = calculate_cost(new_path, dist) - calculate_cost(path, dist);
            if (delta < 0 || (exp(-delta/T) > ((double) rand() / RAND_MAX))) {
                for (int i = 0; i < N; i++) {
                    path[i] = new_path[i];
                }
            }
        }
        T = T * alpha;
    }
}

void print_table(string provinces[], int path[], double dist[][N]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[#] Path Cost Table [#]\n\n";

    int rows = N+2;
    int cols = 4;
    int width = 36;
    string data[rows][cols];
    data[0][0] = "Province Number";
    data[0][1] = "Province Name";
    data[0][2] = "Path Cost";
    data[0][3] = "Total Path Cost";
    data[rows-1][0] = to_string(N);
    data[rows-1][1] = provinces[path[0]];
    data[rows-1][2] = to_string(dist[path[N-1]][path[0]]);
    data[1][2] = to_string((double)0);

    double total_cost = 0;
    for (int i = 1; i < rows-1; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == 0)
                data[i][j] = to_string(i-1);
            else if (j == 1)
                data[i][j] = provinces[path[i-1]];
            else if (j == 2) {
                if (i != 1)
                    data[i][j] = to_string(dist[path[i-2]][path[i-1]]);
            }
            else {
                if (i != 1)
                    total_cost += dist[path[i-2]][path[i-1]];
                data[i][j] = to_string(total_cost);
            }
        }
    }
    total_cost += dist[path[N-1]][path[0]];
    data[rows-1][3] = to_string(total_cost);

    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t";
        cout << (char)186;
        for (int j = 0; j < cols; j++) {
            int padding = (width - data[i][j].length()) / 2;
            cout << right << setfill(' ') << setw(padding) << ' ';
            cout << left << setfill(' ') << setw(width - padding) << data[i][j];
            cout << (char)186;
        }
        cout << endl;
        if (i != rows - 1)
            cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    }
    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    cout << "\n\t\t\t\tFinal Cost : " << to_string(total_cost) << endl;
    cout << "\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}

void print_provinces(string provinces[]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\n\n\n\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[#] Provinces Table [#]\n\n";

    int rows = N+1;
    int cols = 2;
    int width = 36;
    string data[rows][cols];
    data[0][0] = "Province Number";
    data[0][1] = "Province Name";

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == 0)
                data[i][j] = to_string(i);
            else
                data[i][j] = provinces[i-1];
        }
    }

    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t";
        cout << (char)186;
        for (int j = 0; j < cols; j++) {
            int padding = (width - data[i][j].length()) / 2;
            cout << right << setfill(' ') << setw(padding) << ' ';
            cout << left << setfill(' ') << setw(width - padding) << data[i][j];
            cout << (char)186;
        }
        cout << endl;
        if (i != rows - 1)
            cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    }
    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    cout << "\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}


int Menu(string provinces[], int path[], double dist[][N], string source, double T, double T_min, double alpha, int iterations, bool flag) {
    system("cls");

    if (flag) {
        cout << "\n\n\n\n";
        print_table(provinces, path, dist);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    }

    int option;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    if (!flag)
        cout << "\n\n\n\n";
    cout << "\t\t\t\t[+] Menu [+]" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[1] Solve New Travelling Salesman Problem With Simulated Annealing Algorithm" << endl << endl;
    cout << "\t\t\t\t[2] Resolve Travelling Salesman Problem With Simulated Annealing Algorithm for ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "\"" << source << "\"" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[3] Change Initial Temperature => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string(T) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[4] Change Minimum Temperature => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string(T_min) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[5] Change Cooling Rate => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string(alpha) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[6] Change Number of Iterations => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << iterations << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[7] Exit" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\tPlease enter option : ";
    cin >> option;
    return option;
}

void loading() {
    system("cls");
    system("COLOR 0e");
    printf("\e[?25l");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\t\t\t\t";

    for(int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(15);
    }
    Sleep(40);
    system("cls");
}

bool isNum(string s) {
    if (s.length() == 1) {
        if (isdigit(s[0]))
            return true;
    }
    else if (s.length() == 2) {
        if (isdigit(s[0]) && isdigit(s[1]))
            return true;
    }
    return false;
}