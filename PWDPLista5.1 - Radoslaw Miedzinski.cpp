#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctime>


using namespace std;

/*
Program byl pisany na komputerze z windowsem i bardzo mozliwe ze moze nie dzialac poprawnie pod innym systemem.
Jezeli beda problemy z dzialaniem programu moge zademonstrowac jego dzialanie na zajeciach lub w formie wideo.
*/
void clc() //czyszczenie konsoli
{
    cout<<"\x1b[2J \x1b[0m \x1b[1;1H";
}
int ruch() //bierze input z klawiatury w postaci cyfry
{
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD events;
    INPUT_RECORD buffer;
    PeekConsoleInput( handle, &buffer, 1, &events );
    if(events > 0)
    {
        ReadConsoleInput(handle, &buffer, 1, &events);
        //cout<<buffer.Event.KeyEvent.wVirtualKeyCode;

        return buffer.Event.KeyEvent.wVirtualKeyCode;
    }
    return 0;
}
double time_elapsed(clock_t a,clock_t b=0)
{
    return double(b-a);
}
int menu()
{
    clc();
    cout<<"Dla optymalnej rozgrywki, zaleca sie otworzenie konsoli w trybie pelnoekranowym."<<endl;
   Sleep(4000);
    clc();

    while(1)
    {

    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;95;187;208m                                       \\\\                                                                        \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;100;187;208m     ||            ||  ||      ||   ||||||||    ||         ||  ||            ||  ||  ||||||||||    ||||||||      \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;105;187;208m     ||||        ||||   ||    ||   ||      ||   ||         ||  ||     ||     ||  ||  ||           ||      ||     \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;110;187;208m     || ||      || ||    ||  ||    ||      ||   ||         ||  ||    ||||    ||  ||  ||           ||             \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;115;187;208m     ||  ||    ||  ||     ||||     ||           ||         ||  ||   ||  ||   ||  ||  ||||||||     ||             \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;120;187;208m     ||   ||  ||   ||      ||       ||||||||    ||         ||  ||  ||    ||  ||  ||  ||           ||             \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;125;187;208m     ||    ||||    ||      ||              ||   ||         ||  || ||      || ||  ||  ||           ||             \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;130;187;208m     ||     ||     ||      ||      ||      ||   ||         ||  ||||        ||||  ||  ||           ||      ||     \x1b[0m"<<endl;
    cout<<"\x1b[38;2;100;70;50m\x1b[48;2;135;187;208m     ||            ||      ||       ||||||||    ||||||||   ||  ||            ||  ||  ||||||||||    ||||||||      \x1b[0m"<<endl;


        cout<<endl<<"\x1b[12;40H Witaj w grze Mysliwiec!"<<"\x1b[13;40H Co chcialbys zrobic?";
        cout<<"\x1b[15;40H 1. Rozpocznij gre"<<"\x1b[16;40H 2. Zasady gry"<<"\x1b[17;40H 3. Zakoncz gre"<<"\x1b[18;40H ";
        char a;
        cin>>a;
        if(a=='1'){return 1;}
        else if(a=='2'){Sleep(250);return 2;}
        else if(a=='3'){return 0;}
        else {cout<<"\x1b[18;40H Wybor niepoprawny, sprobuj ponownie";Sleep(1000);clc();}


    }
}
int pause_menu()
{
    char a;
    while(1)
    {
    cout<<"\x1b[12;40H Gra zatrzymana";
    cout<<"\x1b[13;40H 1. Wznow";
    cout<<"\x1b[14;40H 2. Wroc do menu glownego";
    cout<<"\x1b[15;40H 3. Wyjdz z gry"<<"\x1b[16;40H";
    cin>>a;
    if(a=='1'){return 0;}
    else if(a=='2'){return 2;}
    else if(a=='3'){return 1;}
    else{cout<<"\x1b[17;40H Wybor niepoprawny, sprobuj ponownie";Sleep(1000);clc();}
    }
}
void zasady()
{
    while(ruch()!=13)
    {
    cout<<"\x1b[?25l\x1b[12;40H Zasady Gry";
    cout<<"\x1b[13;40H 1. Nie pozwol wrogim jednostka przedostac przez linie obrony. Uwazaj: jezeli do tego dopuscisz lub zostaniesz trafiony przegrasz";
    cout<<"\x1b[14;40H 2. Zestrzel przeciwnikow klikajac Spacje, ale pamietaj, ilosc naboi jest ograniczona, pociski odzyskujesz po trafieniu";
    cout<<"\x1b[15;40H 3. Przeciwnicy \x1b[48;2;255;50;20m  \x1b[40m sa dosc latwi do pokonania, wystarczy tylko jeden celny strzal! Uwazaj na \x1b[48;2;220;150;50m  \x1b[40m,";
    cout<<"\x1b[16;40H    sa twardsi i wymagaja dwoch celnych trafien zanim zostana wyeliminowani";
    cout<<"\x1b[17;40H 4. Za kazdego pokonanego przeciwnika zyskasz punkt, zdobadz 30, aby zwyciezyc";
    cout<<"\x1b[19;40H    Wcisnij ENTER aby powrocic do menu glownego";
    }
}

int* spawn(int b) //generuje losowe wspolrzedne pola w konsoli
{
    srand(rand()*(time(NULL)+b));
    static int a[1];
    a[0]=1+(rand()%24);
    a[1]=40+rand()%150;
    return a;

}

class Movable //class of objects able to move
{
private:
    int x;
    int y;
    int hp=1;
public:
    void setX(int a)
    {
        x=a;
    }
    void setY(int a)
    {
        y=a;
    }
    int getxCord()
    {
        return x;
    }
    int getyCord()
    {
        return y;
    }
    int End(Movable k)
    {
        int a=k.getxCord();
        int b=k.getyCord()-2;
        if(x==a&&y>=b-1&&y<=b+1){return 0;}
        else{return 1;}
    }
    Movable Fire()
    {
        Movable shot;
        shot.setX(x);
        shot.setY(y+3);
        return shot;
    }
    void poz()
    {
        cout<<x<<" "<<y;
    }
    int getHP()
    {
        return hp;
    }
    void setHP(int a)
    {
        hp=a;
    }
};

int main()
{
    int timer=100;
    int game=1;
    int o =0;
    int c1=0;
    int c2=0;
    int c,z,n;
    int wybor;
    int points;
    int kills;
    int shots;
    int r,m,k,h;
    int pause=0;
    clock_t finish;
    double time;
    vector<Movable> e;
    vector<Movable> s;
    Movable player,etemp;
    player.setX(12);
    player.setY(4);
                //game preparation
    while(game)
        {
        game=menu();
        m=1;
        clc();

        if(game==2)
            {
                zasady();
                m=0;
            }

        player.setX(12);
        player.setY(4);
        k=10;
        h=0;
        points=0;
        kills=0;
        shots=5;
        o=0; e.clear(); s.clear(); c1=0;c2=0;pause=0;
        while(game&&m)
            {
            clock_t start = clock();
            time=time_elapsed(start,finish)/CLOCKS_PER_SEC;

            while(o<k-1) //setting all moving enemy dots
                {
                    etemp.setX(spawn(o)[0]);
                    etemp.setY(spawn(o)[1]);
                    if(o%10<=h){etemp.setHP(2);}
                    else{etemp.setHP(1);}
                    e.push_back(etemp);
                    o++;
                }



            r=ruch();
            if(r==27&&time<=-0.1)
                {
                    finish=clock();
                    if(pause==0){pause=1;}
                    else{pause=0;}
                    wybor=pause_menu();
                    if(wybor==0){pause=0;}
                    else if(wybor==1){game=0;}
                    else if(wybor==2){m=0;}

                }

            if(o==k-1)
                {
                    for(int i=0;i<e.size();i++) //drawing enemy dots
                    {   if(e[i].getHP()>1){c=220;z=150;n=50;}
                        else {c=255;z=50;n=20;}
                        cout<<"\x1b["<<e[i].getxCord()<<";"<<e[i].getyCord()<<"H\x1b[48;2;"<<c<<";"<<z<<";"<<n<<"m  \x1b[40m";
                        //e[i].poz();
                        if(e[i].getyCord()<=0)//removing enemies that cross the left boundary
                        {
                            m=0;
                            if(m==0){cout<<"\x1b[12;70H KONIEC GRY\x1b[13;70H udalo Ci sie zestrzelic: "<<kills<<" przeciwnikow.\x1b[15;70H Zdobyles: "<<points<<" puntkow."<<"\x1b[15;70H Nacisnij enter zeby kontynuowac";while(ruch()!=13);break;}
                            /*e.erase(e.begin()+i);
                            k=k+1;
                            o=o-1;*/
                        }
                    }
                }
         //menu na ESC

            if(game==0){break;}
            if(m==0){break;}


            if(pause==0)
                {

                if((r==38||r==87)&&time<=-0.1){finish=clock();player.setX(player.getxCord()-1);}
                else if((r==40||r==83)&&time<=-0.1){finish=clock();player.setX(player.getxCord()+1);}
                else if((r==39||r==68)&&time<=-0.1){finish=clock();player.setY(player.getyCord()+1);}
                else if((r==65||r==37)&&time<=-0.1){finish=clock();player.setY(player.getyCord()-1);}//player controls
                else if((r==32&&shots>0)&&time<=-0.2){finish=clock();s.push_back(player.Fire());shots+=-1;}//fire
                else if(time>=1){finish=clock();}

                if(player.getxCord()<=1){player.setX(1);}
                if(player.getyCord()<=0){player.setY(0);}
                if(player.getxCord()>=24){player.setX(24);}
                if(player.getyCord()>=180){player.setY(180);}//player position boundaries



                cout<<"\x1b["<<player.getxCord()-1<<";"<<player.getyCord()+1<<"H  \x1b[0m";
                cout<<"\x1b["<<player.getxCord()<<";"<<player.getyCord()<<"H \x1b[48;2;192;192;192m  \x1b[0m " ;
                cout<<"\x1b["<<player.getxCord()+1<<";"<<player.getyCord()+1<<"H  \x1b[0m"; //player

                for(int j=0;j<e.size();j++) //colision detector
                        {
                                m=player.End(e[j]);
                                if(m==0){cout<<"\x1b[12;70H KONIEC GRY\x1b[13;70H udalo Ci sie zestrzelic: "<<kills<<" przeciwnikow.\x1b[15;70H Zdobyles: "<<points<<" puntkow."<<"\x1b[15;70H Nacisnij enter zeby kontynuowac";while(ruch()!=13);break;}

                        }
                if(s.size()>0)
                    {
                    for(int i=0;i<s.size();i++) //drawing bolts shot
                        {
                            cout<<"\x1b["<<s[i].getxCord()<<";"<<s[i].getyCord()-1<<"H -\x1b[40m\x1b[0m";
                            if(s[i].getyCord()>=180)//removing bolts that crossed the boundary
                                {
                                    s.erase(s.begin()+i);
                                }
                        }
                    }


                cout<<"\x1b[?25l\x1b[26;0H\x1b[48;2;100;100;100m Twoja pozycja: "; player.poz();cout<<endl<<"Pozostale strzaly: "<<shots<<endl<<"Trafienia: "<<points<<endl<<"Zestrzeleni: "<<kills<<endl;
                cout<<endl<<"Poruszanie: strzalki lub WASD"<<endl<<"Strzal: Spacja"<<endl<<"Pauza: ESC"<<"\x1b[0m";




                    if(c1>=timer) //timer
                        {
                            clc();
                            c1=0;
                            c2+=2;


                            for(int i=0;i<e.size();i++)
                                {
                                    e[i].setY(e[i].getyCord()-1);
                                }
                            if(points<20){if(c2%(20-points)==0){k=k+1;if(timer>=20){timer=timer-1;}}}
                            else if(c2%1==0){k=k+1;if(timer>=20){timer=timer-1;}}

                            if(c2%30==0&&h<10){h++;}
                        }
                    if(s.size()>0&&c1%10==0)
                        {
                             //for(int i=0 ;i<s.size();i++)
                                for(int j=0;j<e.size();j++)//counting succesfull shots
                                    {
                                        //for(int j=0;j<e.size();j++)
                                        for(int i=0 ;i<s.size();i++)
                                            {
                                                if((e[j].getyCord()==s[i].getyCord()||e[j].getyCord()==s[i].getyCord()+1)&&e[j].getxCord()==s[i].getxCord())
                                                    {
                                                        if(e[j].getHP()>1){e[j].setHP(e[j].getHP()-1);}
                                                        else if(e[j].getHP()==1){e.erase(e.begin()+j);kills++;}
                                                        s.erase(s.begin()+i);
                                                        points++;
                                                        shots+=1;
                                                        if(points%2==1){k+=1;}
                                                        if(points%10==0){shots+=1;}

                                                    }
                                            }
                                    }

                                for(int i=0;i<s.size();i++)
                                    {
                                        s[i].setY(s[i].getyCord()+1);
                                    }

                        }

                    c1++;
                    }

                    if(kills>=30)
                        {
                            cout<<"\x1b[12;70H Gratulacje! Zwyciezyles.\x1b[13;70H udalo Ci sie zestrzelic: "<<kills<<" przeciwnikow.\x1b[15;70H Zdobyles: "<<points<<" puntkow."<<"\x1b[15;70H Nacisnij enter zeby kontynuowac";
                            while(ruch()!=13);
                            break;
                        }
                }

            }
    clc();
    cout<<"\x1b[12;40H Do widzenia! \x1b[24;1H";

    return 0;
}
