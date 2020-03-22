/*
                       BACKLOG
                       GRA LABIRYNT I POTWORY
                      "KAPI" && "CYCU"

1. ROZUMIENIE GRY: zwyczajne pokemony ale w podziemiach:


podglad okna ktore mamy widziec caly czas
 ___________________________________________________________________________________
|                                                                                   |
|  POTWÓR    OPIS SYTUACJI                                 MAPA ODWIEDZONYCH POKOI  |
|                                                                                   |
|                                                                                   |
|                                                                                   |
|                                                          STATY                    |
|                                                          HP                       |
|  WALKA/OPIS                                              MANA                     |
|  WYBOR OPCJI WALKI/FABULY                                VIGOR/ENDURANCE          |
|___________________________________________________________________________________|

Budzimy się w cholera wie czym. Bezimienny. Przezyj albo zgin.
*** 3 *** KLASY POSTACI {"CZARODZIEJ", "ŁOTR", "WOJOWNIK"};

_______
GRAFIKA:         CMD TERMINAL   80x24 (x,y)
   
musze stworzyc:
///////////////////////////////
void Okno_Potwor();
void Okno_Opis_Sytuacji();

///////////////////////////////
void Okno_Walka_Opis();

///////////////////////////////
void Okno_Walka_Menu_Player();
void Okno_Fabula_Menu_Player();

///////////////////////////////
void Okno_Statystyki();

///////////////////////////////
void Okno_Mapa();



|KSZTAŁT|::|BUDOWA|

int main()
{
   menu();  // <- ten void menu() JUZ JEST GOTOWY "Play", "Quit game"
   
   zawieramy tutaj *historie* i aktywujemy poszczegolne voidy
}


void WALKA_TUROWA [KSZTALT PROPONOWANY]
{
 1. widzisz_wroga();
       //mozesz walczyc albo znalezc sposob ucieczki[losowo z kilku opcji | szansa 50/50 zabija ciebie]
       //void widzisz_wroga() w pliku klasy Player.cpp
    
    do{
 2. Wybor ataku Player / Wytrzymalość REGEN;

 3. Losowanie ataku potwora np. Szkielet 10-19
    }while(hp_Enemy_Skeleton < 0 || HP < 0);

 3' void loot(); //Monsters.h/Monsters.cpp
 }



*******************
Standard zmiennych:
*******************
   statystyki GRACZA DUZA LITERA - np. int HP, MANA, VIGOR, ENDURANCE;
   staty mobow mala litera - np. int hp_Enemy_Warewolf;
   nazwy postaci oraz /class/ - Zawsze Z Duzej_Litery - Player, Enemy_Warewolf;
   

/ class / KLASY / :
   Player - gracz  / tutaj zapisujemy jego:
       Pkt. Stat_lvl_0:
                      1 HP = {100, +20/lvl},
                      1 MANA - zwiekszac bedziemy mane co pkt tego atrybutu, magiczne ataki[CZAROWNIK],
                      1 ENDURANCE - silne ataki[WOJOWNIK],
                      1 VIGOR - szybkie ataki[ŁOTR]
                        
                       void mechaniki()
                       {

                          Player::
                          """"""""
************************* RUCH BOHATERA PODCZAS WALKI  **********************************
                           void widzisz_wroga(); //inicjacja walki
                           void atak_lekki();
                           void atak_potezny();
                           void atak_magiczny();
                           void obrona_tarcza();
                           void obrona_bronia();
                           void obrona_magiczna();
                           
 ************************* RUCH BOHATERA PODCZAS FABULY *********************************
                           void otworz drzwi();
                           void idz_lewo();
                           void idz_prawo();
                           void podnies_przedmiot();

                       }



 //////////////////////////////////// PRZECIWNICY \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
                                                  //CALOSC
Przeciwnicy proponowani: // spis  e.g.    \\class// w dwoch plikach Creatures.h *(statystyki, spis tresci void)*
                 np.    // class Ghoul {}; \\                       Creatures.cpp *(ciala void spisanych ^^ ^^)*
class Monster
       {
       void atak_lekki();
       void atak_potezny();
       void atak_magiczny();
       void obrona_tarcza();
       void obrona_bronia();
       void obrona_magiczna();
                       
       void loot(); //od razu po walce sciaga dane z class i losuje
       };

class  Enemy_Szkielet, Enemy_Ghoul, Enemy_Warewolf, Enemy_Spider, Enemy_Giant_Spider,
       Enemy_Dwarf, Enemy_Dwarf_Archer, Enemy_Dwarf_Guard, Enemy_Dwarf_Mage
      
       

klasa poczatkowa do ktorej sie bedziemy odwolywac to Monster:: - ma wszystkie ataki i obrony ktorych bedziemy uzywac
                                                                  'wiec wydaje mi sie, ze tak moze byc najlatwiej';
       
    "dzieki temu mozemy zrobic np. jakis_obiek->obrona_magiczna(); TO JEST KAPI ROZDUPIERDOL TOTALNY Z TYM TERAZ"

 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/////////////////////////////////////////////////

    
