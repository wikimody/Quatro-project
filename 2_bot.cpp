//2. bot
#include <iostream>
#include <string>

using namespace std;

// funkcja sprawdzajaca wykorzystanie pionka wczesniej
int spr_wykorzystania(char postawione[17], int pionek, char pionki[16])
{
    for(int i = 0; i < 17; i++)
    {
        if(pionki[pionek] == postawione[i]) return 0;
    }
    return 1;
}

int zamiana_pionkow(char pionek)
{
	if(pionek >= '0' && pionek <= '9') pionek -= '0';
	else if(pionek >= 'A' && pionek <= 'F')pionek -= 'A' - 10;
	//jesli dostalismy pionek spoza przedzialu zwracamy po prostu 1 0 0 0 0, czyli 16 (obsluga bledu, mozna zmienic)
	else return 16;

	return (int)pionek;
}


int main(int argc, char *argv[])
{
    int plansza[4][4], postawione[17], pionki[16]; //postawione[0.. 15] - uzyte pionki, postawione[16] - pionek do postawienia
    int licznik = 0, przegrana[4][4];
    for(int i = 0; i < 16; i++)
    {
        postawione[i] = 16;
        pionki[i] = i;
    }

    // "Wizualizujemy" plansze w tablicy: plansza. Zapisujemy, które figury zostaly juz wykorzystane.
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            plansza[i][j] = zamiana_pionkow(argv[1][licznik]);
            cout << plansza[i][j] << " ";
            if(argv[1][licznik] != 'p')
                postawione[licznik] = zamiana_pionkow(argv[1][licznik]);
            licznik++;

            przegrana[i][j] = 0;
        }
        cout << endl;
    }
    postawione[licznik] = argv[1][licznik]; // pionek ktory dostalismy????????

    int pionki_do_sprawdzenia[4] = {16, 16, 16, 16}, ilosc_pionkow = 0, wygrana_x = -1, wygrana_y = -1;

    //sprawdzenie w wierszy
     for(int i = 0; i < 4; i++)
     {
        ilosc_pionkow = 0;
        for(int j = 0; j < 4; j++)//przepisywanie pionkow w wierszu, jesli wystepuja
        {
            if(plansza[i][j] != 16)
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = plansza[i][j];
                cout << pionki_do_sprawdzenia[ilosc_pionkow] << " ";
                ilosc_pionkow++;
            }
            else // gdy puste pole to mamy potencjalne pole do wygranej
            {
                wygrana_x = i;
                wygrana_y = j;
            }
        }
        cout <<  endl;


        if(ilosc_pionkow == 3) //sprawdzamy czy mozemy dostawic czwarty pionek by wygrac
        {
            pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
            if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1) break;
            //cout << "Wygrane x, y: " << wygrana_x << ", " << wygrana_y << endl;
            wygrana_x = -1, wygrana_y = -1;
        }
        else if (ilosc_pionkow == 2) //sprawdzamy czy jesli dostawimy trzeci pionek to przeciwnik bedzie mogl wygrac
        {
            pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
            if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(plansza[i][j] == 16)
                        przegrana[i][j] = -1;
                }
            }
        }

        for(int j = 0; j < 4; j++)
            pionki_do_sprawdzenia[j] = 16;
     }



    //sprawdzanie w kolumnach
    if(wygrana_x == -1 && wygrana_y == -1)
    {
        for(int j = 0; j < 4; j++)
         {
            ilosc_pionkow = 0;
            for(int i = 0; i < 4; i++)//przepisywanie pionkow w wierszu, jesli wystepuja
            {
                if(plansza[i][j] != 16)
                {
                    pionki_do_sprawdzenia[ilosc_pionkow] = plansza[i][j];
                    //cout << pionki_do_sprawdzenia[ilosc_pionkow] << " ";
                    ilosc_pionkow++;
                }
                else // gdy puste pole to mamy potencjalne pole do wygranej
                {
                    wygrana_x = i;
                    wygrana_y = j;
                }
            }
           // cout <<  endl;


            if(ilosc_pionkow == 3) //sprawdzamy czy mozemy dostawic czwarty pionek by wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1) break;
                //cout << "Wygrane x, y: " << wygrana_x << ", " << wygrana_y;
                wygrana_x = -1, wygrana_y = -1;
            }
            else if (ilosc_pionkow == 2) //sprawdzamy czy jesli dostawimy trzeci pionek to przeciwnik bedzie mogl wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1)
                {
                    for(int i = 0; i < 4; i++)
                    {
                        if(plansza[i][j] == 16)
                            przegrana[i][j] = -1;
                    }
                }
            }

            for(int i = 0; i < 4; i++)
                pionki_do_sprawdzenia[i] = 16;
         }
    }

    //sprawdzanie po skosie (lewa gora - prawa dol)
   if(wygrana_x == -1 && wygrana_y == -1)
    {
        for(int i = 0; i < 4; i++)
        {
            ilosc_pionkow = 0;
            if(plansza[i][i] != 16)
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = plansza[i][i];
                //cout << pionki_do_sprawdzenia[ilosc_pionkow] << " ";
                ilosc_pionkow++;
            }
            else // gdy puste pole to mamy potencjalne pole do wygranej
            {
                wygrana_x = i;
                wygrana_y = i;
            }
            //cout <<  endl;

            if(ilosc_pionkow == 3) //sprawdzamy czy mozemy dostawic czwarty pionek by wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1) break;
                    //cout << "Wygrane x, y: " << wygrana_x << ", " << wygrana_y << endl;
                wygrana_x = -1, wygrana_y = -1;
            }
            else if (ilosc_pionkow == 2) //sprawdzamy czy jesli dostawimy trzeci pionek to przeciwnik bedzie mogl wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        if(plansza[j][j] == 16)
                            przegrana[j][j] = -1;
                    }
                }
            }

            for(int j = 0; j < 4; j++)
                pionki_do_sprawdzenia[j] = 16;

        }
    }

    //sprawdzanie po skosie (lewa dol - prawa gora)
    if(wygrana_x == -1 && wygrana_y == -1)
    {
        for(int i = 0; i < 4; i++)
        {
            ilosc_pionkow = 0;
            if(plansza[3 - i][i] != 16)
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = plansza[3 - i][i];
               // cout << pionki_do_sprawdzenia[ilosc_pionkow] << " ";
                ilosc_pionkow++;
            }
            else // gdy puste pole to mamy potencjalne pole do wygranej
            {
                wygrana_x = 3 - i;
                wygrana_y = i;
            }
            //cout <<  endl;

            if(ilosc_pionkow == 3) //sprawdzamy czy mozemy dostawic czwarty pionek by wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1) break;
                    //cout << "Wygrane x, y: " << wygrana_x << ", " << wygrana_y << endl;
                wygrana_x = -1, wygrana_y = -1;
            }
            else if (ilosc_pionkow == 2) //sprawdzamy czy jesli dostawimy trzeci pionek to przeciwnik bedzie mogl wygrac
            {
                pionki_do_sprawdzenia[ilosc_pionkow] = postawione[16];
                if(czy_istnieje_cecha(pionki_do_sprawdzenia) == 1)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        if(plansza[3 - j][j] == 16)
                            przegrana[3 - j][j] = -1;
                    }
                }
            }

            for(int j = 0; j < 4; j++)
                pionki_do_sprawdzenia[j] = 16;

        }
    }

    if(wygrana_x == -1 && wygrana_y == -1)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(plansza[i][j] == 16 && przegrana[i][j] != -1)
                {
                    wygrana_x = i;
                    wygrana_y = j;
                    break;
                }
            }
            if(wygrana_x != -1 && wygrana_y != -1) break;
        }

        if(wygrana_x == -1 && wygrana_y == -1)//gdy nie mamy pola potencjalnie dajacemu wygrana przeciwnikowi
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(plansza[i][j] == 16)
                {
                    wygrana_x = i;
                    wygrana_y = j;
                    break;
                }
            }
            if(wygrana_x != -1 && wygrana_y != -1) break;
        }
    }



    /* cout << "Wygrane x, y: " << wygrana_x << ", " << wygrana_y << endl;
     for(int i = 0; i < 4; i ++)
     {
         for(int j = 0; j < 4; j++)
            cout << przegrana[i][j] << " ";
        cout << endl;
     }*/


    return 0;
}
