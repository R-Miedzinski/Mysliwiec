#include<iostream>

using namespace std;

int main() {
    char c;
   // Set the terminal to raw mode
    while(1) {
        printf("stty raw");
        c = getchar();
        // terminate when "." is pressed
        printf("stty cooked");
        printf("clear");
        std::cout << c << " was pressed."<< std::endl;
        if(c == '.') {
            cout<<c;
            exit(0);
        }
    }
}
