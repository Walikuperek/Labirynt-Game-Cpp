#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

//                                                                                                           \/ ZMIENNE GRACZA
/*                           PLAYER                                          */
//         ************************************************
int choice;
string Klasa_Postaci;
int LVL = 1;
int HP = 100;
int MANA = 30;
int VIGOR = 40;
int ENDURANCE = 100;

int P_DMG = 1;
//                               player_variables: "P_crit/dmg_type"
float P_crit_chance;
int P_dmg_lekki;
int P_dmg_potezny;
int P_dmg_magiczny;

int P_DMG_DEALT;

int P_atak_choice = 0; //lekki - 1, potezny - 2, magiczny - 3, rest - 4;
/*                           MONSTERS                                       */
//         ************************************************                                                  \/ ZMIENNE WROGÓW

string MonsterNazwa;
int MonsterHP, MonsterDMG; int MonsterCrit;
int M_dmg, M_dmg_mag;
int M_dmg_dealt;

/* BOSS */
//                                                                                                           \/ ZMIENNE WINDOW
float room_nr = 1;//                      ROOM NUMBERS

float room_choice;//                      PLAYERS CHOICE
//                                                                 * * * * * * * * *  DIALOGI MONSTER WINDOW * * * * * * * * *
string dialog1, dialog2, dialog3, dialog4, dialog5, dialog6, dialog7, dialog8, dialog9, dialog10;
//                                                                                                          *** FUNKCJE GRACZA

bool P_awans();
int atak_lekki();
int atak_potezny();
int atak_magiczny();
void P_rest();


void Player_Dead()
{
    system("clear");
    cout << "\nYOU ARE DEAD!";
    cout << "\n2";
    sleep(1);
    cout << "\n1";
    sleep(0.5);
    
    cout << "\n0.5";
    exit(0);
}
//                                                                                                          *** FUNKCJE WROGÓW

int M_atak();
int M_atak_magiczny();

//                           WINDOW                                                                           *** VOIDY WINDOW
//    **********************************************
void Setup();
void Display();
void displayUpdate();

//      GRA

void Menu();
void Wprowadzenie();
void Okno_Monster();
int Okno_Menu_Walka();
void Okno_Room_Choice();
void Okno_Statystyki();
void Okno_Mapa();
//
void Game_Loop()
{
    bool player_turn = true;
    bool monster_died = false;


    while(monster_died==false)
    {
        dialog6 = Klasa_Postaci;
        Display();
        if(player_turn == true)
        {
            //MANA + UPDATE NA POCZATKU! + PROBLEM ENTERA! + ZABICIE GRACZA + 

            switch(Okno_Menu_Walka()) // Okno_Menu_Walka() <-- tam wybierasz tą zmienną
            {
                case 1:
                {
                    MonsterHP = MonsterHP - atak_lekki();
                    if(HP > 0 && MonsterHP > 0)
                    {
                        player_turn = false;
                        P_atak_choice=0;
                        
                        break;
                    }
                    else if(HP > 0 && MonsterHP <= 0){
                        P_awans();
                        monster_died = true;
                        P_atak_choice=0;
                        break;
                    }

                }
                case 2:
                {
                    MonsterHP = MonsterHP - atak_potezny();
                    if(HP > 0 && MonsterHP > 0)
                    {
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                    else if(HP > 0 && MonsterHP <= 0){
                        monster_died = true;
                        P_awans();
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                    else{
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                }
                case 3:
                {
                    MonsterHP = MonsterHP - atak_magiczny();
                    if(HP > 0 && MonsterHP > 0)
                    {
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                    else if(HP > 0 && MonsterHP <= 0){
                        monster_died = true;
                        P_awans();
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                }
                case 4:
                {
                    P_rest();
                    if(HP > 0 && MonsterHP > 0){
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                    else if(HP > 0 && MonsterHP <= 0){
                        monster_died = true;
                        P_awans();
                        player_turn = false;
                        P_atak_choice=0;
                        break;
                    }
                }
            }
        }// IF koniec
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                    MONSTER TURN                                                                                //////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else
        {
            dialog6 = MonsterNazwa.c_str();
            dialog7 = "Zadaje Tobie obrażenia: ";
            HP = HP - M_atak();
            player_turn = true;
            P_atak_choice=0;
            displayUpdate();
            if(HP <= 0 && MonsterHP > 0)
            {
                P_atak_choice=0;
                Player_Dead();
            }//PLAYER DIED * * * * * * * DEAD
            sleep(2);
        }

    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                    GAMELOOP END                                                                                //////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                    TESTY                                                                                                  //////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    cout<< "atak_lekki: " << atak_lekki() << "\n";
//
//    cout<< "atak_potezny: " << atak_potezny() << "\n";
//
//    MonsterCrit = 70;
//    MonsterDMG = 20;
//    cout<< "crit_loss TEST MONSTER: " << M_atak() << " <-- DMG CRITA \n";
//    cout<< dialog6 << endl
//        << dialog7;
//    cout<< "\n"
//        << "M_atak_magiczny: " << M_atak_magiczny() << "\n";
//    cout<< dialog6 << endl
//        << dialog7;
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                   START                                                                                                  //////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    Setup(); // <ncurses.h> begin
    Menu();
    Wprowadzenie();
//    Klasa_Postaci = "LOTR";
    room_nr = 1;
   
    do{
        if (room_nr == 1)
        {
            MonsterNazwa = "Szkielet";
            MonsterHP = 25;
            MonsterDMG = 1;
            MonsterCrit = 20;
            Display();
            Game_Loop();
            room_nr = 2;
        } // KONIEC IF(ROOM_CHOICE == 1)
        else if(room_nr == 2)
        {
            MonsterNazwa = "Ghoul";
            MonsterHP = 40;
            MonsterDMG = 2;
            MonsterCrit = 25;
            Display();
            Game_Loop();
            room_nr = 3;
        }

        else if(room_nr == 3)
        {
            MonsterNazwa = "Rotworm";
            MonsterHP = 40;
            MonsterDMG = 2;
            MonsterCrit = 25;
            Display();
            Game_Loop();
            room_nr = 4;
        }
        else if(room_nr == 4)
        {
            MonsterNazwa = "Spider";
            MonsterHP = 55;
            MonsterDMG = 3;
            MonsterCrit = 26;
        }
        else if(room_nr == 3.2)
        {
            MonsterNazwa = "Poison Spider";
            MonsterHP = 65;
            MonsterDMG = 3;
            MonsterCrit = 30;
        }
        else if(room_nr == 3.3)
        {
            MonsterNazwa = "Giant Spider";
            MonsterHP = 90;
            MonsterDMG = 3;
            MonsterCrit = 35;
        }
        else if(room_nr == 4.1)
        {
            MonsterNazwa = "Dwarf";
            MonsterHP = 90;
            MonsterDMG = 4;
            MonsterCrit = 33;
        }
        else if(room_nr == 4.2)
        {
            MonsterNazwa = "Dwarf Archer";
            MonsterHP = 95;
            MonsterDMG = 4;
            MonsterCrit = 40;
        }
        else if(room_nr == 4.3)
        {
            MonsterNazwa = "Dwarf Guard";
            MonsterHP = 120;
            MonsterDMG = 5;
            MonsterCrit = 25;
        }
        else if(room_nr == 4.4)
        {
            MonsterNazwa = "Dwarf Mage";
            MonsterHP = 100;
            MonsterDMG = 4;
            MonsterCrit = 50;
        }
        else if(room_nr == 5.1)
        {
            MonsterNazwa = "Pit Lord";
            MonsterHP = 200;
            MonsterDMG = 5;
            MonsterCrit = 33;
        }
        else if(room_nr == 5.2)
        {
            MonsterNazwa = "Pit Lord";
            MonsterHP = 270;
            MonsterDMG = 5;
            MonsterCrit = 66;
        }
        else if(room_nr == 5.3)
        {
            MonsterNazwa = "Red Dragon";
            MonsterHP = 250;
            MonsterDMG = 6;
            MonsterCrit = 45;
        }
        else if(room_nr == 5.4)
        {
            MonsterNazwa = "Behemot";
            MonsterHP = 300;
            MonsterDMG = 7;
            MonsterCrit = 45;
        }
        else if(room_nr == 5.5)
        {
            MonsterNazwa = "Reaper of Death";
            MonsterHP = 300;
            MonsterDMG = 6;
            MonsterCrit = 60;
        }
        else if(room_nr == 6)
        {
            MonsterNazwa = "BOSS";
            MonsterHP = 1000;
            MonsterDMG = 10;
            MonsterCrit = 30;
            
            Okno_Monster();
            
            if(HP > 0 && MonsterHP <= 0)
                room_nr = 7;
        }

    }while(room_nr != 7);

    system("clear");
    cout << "POKONANO BOSSA!\n";
    sleep(1);
    cout << "Gratuluje przejscia gry Labirynth\n";
    sleep(1);
    cout << "\nAutorzy: Kasper Kowalewski & Kacper Walczak\n";
    sleep(1);
    
    endwin();
    return 0;
}


//    * * * * * * * * * * * * * * * * * * * * * * *                                                                   MAIN ();


//                                                                       *** VOIDY MONSTERS

int M_atak()
{
    int crit_loss;
    crit_loss = rand() %100+1;
    if(crit_loss < MonsterCrit)
    {
        /*
           TEST crit_loss
                cout << "crit_loss: " << crit_loss << "\n";
           TEST crit_loss
        */
        M_dmg = rand() % MonsterDMG * 10+1;
        if(M_dmg< MonsterDMG * 5)
            M_dmg = MonsterDMG * 5 * 2;
        dialog6 = MonsterNazwa;
        dialog7 = "KRTYTYK NA RYJ: ";
    }
    else
    {

/*  // TEST crit_loss
        cout << "crit_loss: " << crit_loss << "\n";
//   TEST crit_loss
//*/
        M_dmg = rand() % MonsterDMG * 10+1;
        if(M_dmg< MonsterDMG * 5)
            M_dmg = MonsterDMG * 5;
        M_dmg = M_dmg;
        dialog6 = MonsterNazwa;
        dialog7 = "OBRAŻENIA: ";
    }
    M_dmg_dealt = M_dmg;
    return M_dmg_dealt;
}

int M_atak_magiczny()
{
    int shot_loss;
    shot_loss = rand() % 4+1;
    
  /* TEST SHOT_LOSS_MONSTER*/
    
//    cout << endl << "TEST Monster:shot_loss --> " << shot_loss << " <-- TEST" << endl;
    
    if     (shot_loss == 1){ dialog7 = "Monster: Flame Strike *"; M_dmg = 20 * MonsterDMG;}
    else if(shot_loss == 2){ dialog7 = "Monster: Fire Blaze *"; M_dmg = 25 * MonsterDMG;}
    else if(shot_loss == 3){ dialog7 = "Monster: Lava Bomb **"; M_dmg = 30 * MonsterDMG;}
    else if(shot_loss == 4){ dialog7 = "Monster: Fire Armageddon ***"; M_dmg = 40 * MonsterDMG;}
   
    M_dmg_dealt = M_dmg;
    
    return M_dmg_dealt;
}

//                                                                       ***   VOIDY GRACZA
int atak_lekki()
{
    int crit_loss;
    crit_loss = rand() %100+1;
    if(crit_loss < P_crit_chance)
    {
        P_dmg_lekki = rand() % P_DMG * 10+1;
        if(P_dmg_lekki< P_DMG * 5)
            P_dmg_lekki = P_DMG * 5;
        P_dmg_lekki*=2;
        
        dialog6 = Klasa_Postaci;
        dialog7 = "LEKKI CIOS KRYTYCZNY: ";
    }
    else
    {
        P_dmg_lekki = rand() % P_DMG * 10+1;
        if(P_dmg_lekki< P_DMG * 5)
            P_dmg_lekki = P_DMG * 5;
        dialog6 = Klasa_Postaci;
        dialog7 = "ZADAJESZ: ";
    }
    P_DMG_DEALT = P_dmg_lekki;

    return P_DMG_DEALT;
}

int atak_potezny()
{
    int crit_loss;
    crit_loss = rand() %100+1;
    if(crit_loss < P_crit_chance)
    {
        P_dmg_potezny = rand() % P_DMG * 25+1;
        if(P_dmg_potezny< P_DMG * 25)
            P_dmg_potezny = P_DMG * 25;
        P_dmg_potezny*=2;
        
        dialog6 = Klasa_Postaci;
        dialog7 = "POTEZNY CIOS KRYTYCZNY: ";
    }
    else
    {
        P_dmg_potezny = rand() % P_DMG * 25+1;
        if(P_dmg_potezny< P_DMG * 25)
            P_dmg_potezny = P_DMG * 25;
        dialog6 = Klasa_Postaci;
        dialog7 = "ZADAJESZ: ";
    }
    P_DMG_DEALT = P_dmg_potezny;
    return P_DMG_DEALT;
}

int atak_magiczny()
{
    int shot_loss;
    shot_loss = rand() % 4+1;
    
    MANA -= LVL * 10;
    dialog6 = Klasa_Postaci;
    if     (shot_loss == 1){ dialog7 = "* Arcane Shot *"; P_dmg_magiczny = 20 * P_DMG;}
    else if(shot_loss == 2){ dialog7 =  "* Fire Shot *"; P_dmg_magiczny = 25 * P_DMG;}
    else if(shot_loss == 3){ dialog7 = "** Fire Ball **"; P_dmg_magiczny = 30 * P_DMG;}
    else if(shot_loss == 4){ dialog7 = "*** Lava Ball ***"; P_dmg_magiczny = 40 * P_DMG;}
   
    P_DMG_DEALT = P_dmg_magiczny;
    return P_DMG_DEALT;
}

void P_rest()
{
    ENDURANCE += 50;
    MANA += LVL * 30;
    dialog6 = Klasa_Postaci;
    dialog7 = "REST: +50 ENDURANCE, MANA ++";
}

bool P_awans()
{
    
    cout << "\n"<<"\n"<<"\n"<<"\n"<<"\n"<<"\n";
    cout << "                       AWANSUJESZ NA " << LVL+1;
    if(Klasa_Postaci == "CZAROWNIK"){
        LVL++;
        MANA += 30;
        HP+=10;
        P_DMG++;
        
        sleep(2);
    }
    else if(Klasa_Postaci == "WOJOWNIK"){
        LVL++;
        MANA+=10;
        HP+=30;
        ENDURANCE+=5;
        P_DMG++;
        
        sleep(2);
    }
    else if(Klasa_Postaci == "LOTR"){
        LVL++;
        MANA+=15;
        HP+=20;
        VIGOR+=10;
        P_DMG++;
        
        sleep(2);
    }
    return true;
}


//                                                                       ##### VOIDY EKRANU #####
// * * * * * * * * * * * * * *  ** ** ** ** ** *** ****** *** ** ** ** ** * * * * * * * * * * * * * * * * * * * * * * * * * *
void Display()
{
    Okno_Statystyki();
    Okno_Mapa();
    Okno_Monster();
    Okno_Menu_Walka();
}
void displayUpdate(){
    Okno_Statystyki();
    Okno_Monster();
    Okno_Mapa();
}
void Okno_Monster()
{
    int monster_height, monster_width, monster_y0, monster_x0; // SETTINGS: * LEFT-TOP * * * WINDOW SIZE VARIABLES * * *
    monster_height = 13;
    monster_width = 58;
    monster_y0 = 0;
    monster_x0 = 0;
    
    WINDOW *monster = newwin(monster_height, monster_width, monster_y0, monster_x0);

    wrefresh(monster);
    box(monster, 0, 0);
    mvwprintw(monster, 1, 26, "MONSTER");
    
    mvwprintw(monster, 2, 3, "%s", MonsterNazwa.c_str());
    mvwprintw(monster, 3, 3, "HP: %d", MonsterHP);
    mvwprintw(monster, 4, 3, "DMG: %d", MonsterDMG);
    mvwprintw(monster, 5, 3, "CRIT: %d", MonsterCrit);
    mvwprintw(monster, 6, 3, "%s", dialog5.c_str());
    mvwprintw(monster, 7, 3, "%s", dialog6.c_str());
    
    //removing unneccessary 0 at the beggining of the game
    if(P_DMG_DEALT > 0) { mvwprintw(monster, 8, 3, "%s %d", dialog7.c_str(), P_DMG_DEALT); }
    else{ mvwprintw(monster, 8, 3, "%s", dialog7.c_str()); };
    
    mvwprintw(monster, 9, 3, "%s", dialog8.c_str());
    mvwprintw(monster, 10,3, "%s", dialog9.c_str());
    
    wrefresh(monster);
}

int Okno_Menu_Walka()
{
    int mfight_height, mfight_width, mfight_y0, mfight_x0; // SETTINGS: * LEFT-BOTTOM * * * WINDOW SIZE VARIABLES * * *
    mfight_height = 9;
    mfight_width = 58;
    mfight_y0 = 14;
    mfight_x0 = 0;
    
    WINDOW *mfight = newwin(mfight_height, mfight_width, mfight_y0, mfight_x0);
    
    wrefresh(mfight);
    mvwprintw(mfight, 1, 26, "MFIGHT");
    box(mfight, 0, 0);
    keypad(mfight, true); // TURNING ON KEYBOARD INPUT            !  ! ! ! !!!IMPORTANT!!! ! ! !  !
    
    string choices[4] = {"Lekki", "Potezny", "Magiczny", "Obrona"};
    
    int highlight = 0;
    int Mana_cost = LVL * 10;       //                              MAGIC ATTACK
    while(1)
    {
        mvwprintw(mfight, 3, 21, "FREE COST      dmg: %d", P_dmg_lekki);
        mvwprintw(mfight, 4, 21, "- 40 ENDURANCE dmg: %d", P_dmg_potezny);
        mvwprintw(mfight, 5, 21, "- %d MANA      dmg: %d", Mana_cost, P_dmg_magiczny);
        mvwprintw(mfight, 6, 21, "+50 ENDURANCE, MANA ++");
        
        //                                  MENU GRACZA, PETLA 4X SIE ZROBI I CHOICE.[I].C_STR() \POKAZE/
                                    
        for(int i = 0; i < 4; i++)
            {
                
                if(i == highlight)
                wattron(mfight, A_REVERSE);                          // A_REVERSE ZMIENIA KOLORY PRZYCISKOW MENU
                mvwprintw(mfight, i+3, 11, "%s", choices[i].c_str());// {"Lekki", "Potezny", "Magiczny", "Obrona"}
                wattroff(mfight, A_REVERSE);   //""""""""""""""""""
            }
            choice = wgetch(mfight);
            
            switch(choice)
            {
                case KEY_UP: highlight--;
                    if(highlight == -1) highlight = 0; // ZEBY NIE POJECHALO ZA WYSOKO - TOP BORDER
                    break;
                case KEY_DOWN: highlight++;
                    if(highlight == 4) highlight = 3;  // BOTTOM BORDER
                    break;
                default: break;
            }
            if(choice == 10 && highlight == 0)      // CHOICE == 10, "ENTER" KLAWISZ, POTWIERDZENIE WYBORU
            {
                
                P_atak_choice = 1;// przekierowanie, jedno z 4 SWITCH MAIN WALKA
                sleep(1);
                break;
            }
            else if(choice == 10 && highlight == 1)
            {
                P_atak_choice = 2;// przekierowanie, jedno z 4 SWITCH MAIN WALKA
                sleep(1);
                break;
            }
            else if(choice == 10 && highlight == 2)
            {
                P_atak_choice = 3;// przekierowanie, jedno z 4 SWITCH MAIN WALKA
                MANA = MANA - LVL * 10;
                sleep(1);
                break;
            }
            else if(choice == 10 && highlight == 3)
            {
                P_atak_choice = 4; // przekierowanie, jedno z 4 SWITCH MAIN WALKA
                sleep(1);
                break;
            }
               
    }
    return P_atak_choice;
}

void Okno_Room_Choice()
{
    int mfight_height, mfight_width, mfight_y0, mfight_x0;

    mfight_height = 9;
    mfight_width = 58;
    mfight_y0 = 14;
    mfight_x0 = 0;

    WINDOW *mfight = newwin(mfight_height, mfight_width, mfight_y0, mfight_x0);
    
    wrefresh(mfight);
    box(mfight, 0, 0);
    mvwprintw(mfight, 1, 23, "ROOM CHOICE");
    keypad(mfight, true);
        
    string choices[5] = {"ROOM", "ROOM", "ROOM", "ROOM", "ROOM"};
    int choice;
    int highlight = 0;
        
    while(1)
    {
        mvwprintw(mfight, 3, 13, "͹ ͹ ͹ ͹ ͹ ͹");
        mvwprintw(mfight, 4, 13, "͹ ͹ ͹ ͹ ͹ ͹");
        mvwprintw(mfight, 5, 13, "͹ ͹ ͹ ͹ ͹ ͹");
        mvwprintw(mfight, 6, 13, "͹ ͹ ͹ ͹ ͹ ͹");
        mvwprintw(mfight, 7, 13, "͹ ͹ ͹ ͹ ͹ ͹");
            
            
        for(int i = 0; i < 5; i++)
            {
                    
                if(i == highlight)
                wattron(mfight, A_REVERSE);
                mvwprintw(mfight, i+3, 3, "%s", choices[i].c_str());
                wattroff(mfight, A_REVERSE);
            }
            choice = wgetch(mfight);
                
            switch(choice)
            {
                case KEY_UP: highlight--;
                    if(highlight == -1) highlight = 0;
                        break;
                case KEY_DOWN: highlight++;
                    if(highlight == 5) highlight = 4;
                        break;
                    default: break;
            }
            if(choice == 10 && highlight == 0)
            {
                system("clear");
                mvwprintw(mfight, 1, 1, "WYBRANO PIERWSZY LOSOWY POKOJ");
                wrefresh(mfight);
                sleep(2);
                system("clear");
                break;
            }
            else if(choice == 10 && highlight == 1)
            {
                system("clear");
                mvwprintw(mfight, 1, 1, "WYBRANO DRUGI LOSOWY POKOJ");
                wrefresh(mfight);
                sleep(2);
                system("clear");
                break;
            }
            else if(choice == 10 && highlight == 2)
            {
                system("clear");
                mvwprintw(mfight, 1, 1, "WYBRANO TRZECI LOSOWY POKOJ");
                wrefresh(mfight);
                sleep(2);
                system("clear");
                break;
            }
            else if(choice == 10 && highlight == 3)
            {
                system("clear");
                mvwprintw(mfight, 1, 1, "WYBRANO CZWARTY LOSOWY POKOJ");
                wrefresh(mfight);
                sleep(2);
                system("clear");
                break;
            }
            else if(choice == 10 && highlight == 4)
            {
                system("clear");
                mvwprintw(mfight, 1, 1, "WYBRANO PIATY LOSOWY POKOJ");
                wrefresh(mfight);
                sleep(2);
                system("clear");
                break;
            }
            }
            system("clear");
    }

///////////////////////////////
void Okno_Statystyki()
{
    // ROZMIARY OKNA
    int stat_height, stat_width, stat_y0, stat_x0;
    stat_height = 11;
    stat_width = 20;
    stat_y0 = 12;
    stat_x0 = 59;
    
    WINDOW *stat = newwin(stat_height, stat_width, stat_y0, stat_x0);
    wrefresh(stat);
    box(stat, 0, 0);
    mvwprintw(stat, 1, 2, "%s", Klasa_Postaci.c_str());
    mvwprintw(stat, 2, 2, "STATYSTYKI");
    mvwprintw(stat, 4, 2, "LVL: %d", LVL);
    mvwprintw(stat, 5, 2, "HP: %d", HP);
    mvwprintw(stat, 6, 2, "MANA: %d", MANA);
    mvwprintw(stat, 7, 2, "VIGOR: %d", VIGOR);
    mvwprintw(stat, 8, 2, "ENDURANCE: %d", ENDURANCE);
    wrefresh(stat);
    

}

///////////////////////////////
void Okno_Mapa()
{ //͹ ͹ ͹ ͹ ͹ ͹
    int map_height, map_width, map_y0, map_x0;
    map_height = 11;
    map_width = 20;
    map_y0 = 0;
    map_x0 = 59;
    
    WINDOW *map = newwin(map_height, map_width, map_y0, map_x0);
    refresh();
    wrefresh(map);
    box(map, 0, 0);
    mvwprintw(map, 1, 8, "MAPA");
  
    mvwprintw(map, 2, 4, "[DUNG BOSS]");
    
    mvwprintw(map, 4, 1, "[5][5] [5] [5][5]");
    mvwprintw(map, 5, 2, "[4] [4] [4] [4]");
    mvwprintw(map, 6, 4, "[3] [3] [3]");
    mvwprintw(map, 7, 6, "[2] [2]");
    mvwprintw(map, 8, 8, "[1]");
    wrefresh(map);
}
///////////////////////////////
void Menu()
{
    
    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);   // POBIERZ MAX WARTOSCI Z URZADZENIA STDSCR - STANDARD SCREEN RESOLUTION
    
    WINDOW *menu = newwin(6, xMax -12, yMax - 8, 5); // TWORZYMY OKNO     ++++++++++++++++++>   * "menu" *
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);
    
    
    string choices_menu[2] = {"PLAY", "QUIT GAME"};
    int choice;
    int highlight = 0;
    
    while(1)
    {
        for(int i = 0; i < 2; i++)
        {
            if(i == highlight)
            {
                wattron(menu, A_REVERSE);
                //mvwprintw(*NAZWA_WINDOW, y_w_dół_od_topa, x_od_lewej_na_prawo, "coś sie wyswietli")
                mvwprintw(menu, i+1, 1, "%s", choices_menu[i].c_str());
                wattroff(menu, A_REVERSE);
            }
        }
        choice = wgetch(menu);
        
        switch(choice)
        {
            case KEY_UP: highlight--;
                if(highlight == -1) highlight = 0;
                break;
            case KEY_DOWN: highlight++;
                if(highlight == 2) highlight = 1;
                break;
            default: break;
        }
        if(choice == 10 && highlight == 0)
        {
            system("clear");
            break;
        }
        else if(choice == 10 && highlight == 1)
        {
            system("clear");
            exit(0);
        }
    }
}

//*************************************************************** HISTORIA

void Wprowadzenie()     // DO C++
{
   
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW *wybor = newwin(yMax, xMax, 0, 0);
    

    wrefresh(wybor);
    
    mvwprintw(wybor, 1, 1, "Obudziles sie, jestes bezimienny, nie pamietasz nic.");
    sleep(1);
    mvwprintw(wybor, 3, 1, "Znajdujesz sie podczas wyboru postaci");
    wrefresh(wybor);
    sleep(1);
    mvwprintw(wybor, 8, 27, "WYBIERZ KLASE POSTACI");
    wrefresh(wybor);
    sleep(0.7);
    
    keypad(wybor, true);
    string choices[3] = {"CZAROWNIK", "WOJOWNIK", "LOTRZYK"};
    int choice;
    int highlight = 0;
    
    while(1)
    {
        
        for(int i = 0; i < 3; i++)
        {
            
            if(i == highlight)
                wattron(wybor, A_REVERSE);
                mvwprintw(wybor, i+9, 27, "%s", choices[i].c_str());
                wattroff(wybor, A_REVERSE);
        }
        choice = wgetch(wybor);
        
        switch(choice)
        {
            case KEY_UP: highlight--;
                if(highlight == -1) highlight = 0;
                break;
            case KEY_DOWN: highlight++;
                if(highlight == 3) highlight = 2;
                break;
            default: break;
        }
        if(choice == 10 && highlight == 0)
        {
            system("clear");
            mvwprintw(wybor, 1, 1, "WYBRALES CZARODZIEJA");
            Klasa_Postaci = "CZARODZIEJ";
            wrefresh(wybor);
            sleep(2);
            system("clear");
            break;
        }
        else if(choice == 10 && highlight == 1)
        {
            system("clear");
            Klasa_Postaci = "WOJOWNIK";
            mvwprintw(wybor, 1, 1, "WYBRALES WOJOWNIKA");
            wrefresh(wybor);
            sleep(2);
            system("clear");
            break;
        }
        else if(choice == 10 && highlight == 2)
        {
            system("clear");
            Klasa_Postaci = "LOTR";
            mvwprintw(wybor, 1, 1, "WYBRALES LOTRZYKA");
            wrefresh(wybor);
            sleep(2);
            system("clear");
            break;
        }
    }
    system("clear");
    
}

void Setup() /* inicjowanie ncurses.h */ //              !  ! ! ! !!!IMPORTANT!!! ! ! !  !
{
    initscr();/* inicjowanie ncurses.h */
    noecho();// nie wyswietlaj na ekranie: | <-- tego jak tyka, ani nie pokazuj co się klika np. w left-top-corner 'a'
    cbreak();// CTRL+C = wyłączenie aplikacji !  ! ! ! !!!IMPORTANT!!! ! ! !  !
    refresh();//odświeżanie ekranu
    curs_set(0);// ustaw kursor na (0,0)
}
