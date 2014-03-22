#include "menu.h"
#include "variables.h"
#include <avr/pgmspace.h>
#include "output.h"

PROGMEM const unsigned char menu_intro[] = "WELCOME                                                                     ";
PROGMEM const unsigned char pid_items[][6] = {"ROLL", "PITCH", "YAW", "ALT", "POS", "POSR", "NAVR", "LEVEL", "MAG", "TPA"};

PROGMEM const unsigned char words[][7] = {"SAVE ", "RELOAD"};
PROGMEM const unsigned char menu_titles[][6] = {"PIDS ", "TPA"};


char left = 0;
char right = 0;
char up = 0;
char down = 0;
char more = 0;
char less = 0;

char upright = 0;


int current_pid_item = 0;
char selectedMenu = 0;
char menus_Available = 9;
char current_menu = 0;


#define INTRO_MENU 1

#define PID_MENU 2

#define last_menu 2

#define first_menu 1

void go_to_menu(char menu);
void menu_right();
void menu_left();
void menu_down();
void menu_up();
void update_pid_on_screen();

void save_pids()
{
    customMessage = MSP_SET_PID;
}

void change_menu(char direction)
{
    current_menu = current_menu + direction;
    if (current_menu > last_menu)
    {
        current_menu = first_menu;
    }
    else if (current_menu < first_menu)
    {
        current_menu = last_menu;
    }
    if (current_menu == PID_MENU)
    {
        customMessage = MSP_PID;
    }
    go_to_menu(current_menu);
}

void intro_left()
{
    change_menu(-1);
}

void intro_right()
{
    change_menu(1);
}

void pid_right()
{
    switch (selectedMenu)
    {
    case 0:
        change_menu(1);
        break;
    case 1:
        current_pid_item++;

        break;
    case 3:
        confP[current_pid_item]++;
        update_pid_on_screen();
        break;
    case 4:
        confI[current_pid_item]++;
        update_pid_on_screen();
        break;
    case 5:
        confD[current_pid_item]++;
        update_pid_on_screen();
        break;
    case 6:
        save_pids();
        break;

    case 2:
        current_pid_item++;
        if (current_pid_item >= 10)
        {
            current_pid_item = 0;
        }
        go_to_menu(PID_MENU);
        break;
    case 7:
        customMessage = MSP_PID;
        break;
    }
}


void pid_left()
{
    switch (selectedMenu)
    {
    case 0:
        change_menu(-1);
        break;
    case 1:
        current_pid_item--;
        break;
    case 3:
        confP[current_pid_item]--;
        update_pid_on_screen();
        break;
    case 4:
        confI[current_pid_item]--;
        update_pid_on_screen();
        break;
    case 5:
        confD[current_pid_item]--;
        update_pid_on_screen();
        break;
    case 6:
        save_pids();
        break;

    case 2:
        current_pid_item--;
        if (current_pid_item < 0)
        {
            current_pid_item = 9;
        }
        go_to_menu(PID_MENU);
        break;
    case 7:
        customMessage = MSP_PID;
        break;
    }

}

void menu_up()
{
    menu_dim[selectedMenu] = 0;
    selectedMenu--;
    if (selectedMenu < 0)
    {
        selectedMenu = menus_Available - 1;
    }
    menu_dim[selectedMenu] = 1;
}

void menu_down()
{
    menu_dim[selectedMenu] = 0;
    selectedMenu++;
    if (selectedMenu >= (menus_Available - 1))
    {
        selectedMenu = 0;
    }
    menu_dim[selectedMenu] = 1;
}

void menu_left()
{
    switch (current_menu)
    {
    case (PID_MENU):
        pid_left();
        break;
    case (INTRO_MENU):
        intro_left();
        break;
    }
}

void menu_right()
{
    switch (current_menu)
    {
    case (PID_MENU):
        pid_right();
        break;
    case (INTRO_MENU):
        intro_right();
        break;
    }
}

void menu_increase(char delta)
{


}



void process_menu()
{

    if (menuon)
    {
        if (current_menu == 0)
        {
            change_menu(1);
        }
        if (current_menu == PID_MENU && pid_reloaded_flag)
        {
            pid_reloaded_flag = 0;
            go_to_menu(PID_MENU);
        }
    }
    ///////////////////////////////left/right//////////////////////////////////
    if (rc_updated_flag)
    {
        if (rcData[0] > 1800)
        {
            right++;
            left = 0;
        }
        else if (rcData[0] < 1300)
        {
            left++;
            right = 0;
        }
        /////////////////////////////////up/down///////////////////////////////////
        if (rcData[1] > 1800)
        {
            up++;
            down = 0;
        }
        else if (rcData[1] < 1300)
        {
            down++;
            up = 0;
        }
        /////////////////////////////////increase/decrease///////////////////////////////////
        if (rcData[2] > 1800)
        {
            more++;
            less = 0;
        }
        else if (rcData[2] < 1300)
        {
            less++;
            more = 0;
        }
        if (rcData[2] < 1300 && rcData[3] < 1300)
        {
            upright++;
        }
        else
        {
            upright = 0;
        }

        if (upright > 5)
        {
            upright = 0;
            if (!mode_armed)
            {
                menuon = !menuon;
            }

        }
        if (menuon)
        {
            //////////////////////////////////////////////////////////////////////////
            if (down > 3)
            {
                down = 0;
                menu_down();
            }
            if (up > 3)
            {
                up = 0;
                menu_up();
            }
            if (left > 3)
            {
                left = 0;
                menu_left();
            }
            if (right > 3)
            {
                right = 0;
                menu_right();
            }
            if (more > 3)
            {
                more = 0;
                menu_increase(1);
            }
            if (less > 3)
            {


                less = 0;
                menu_increase(-1);
            }
        }
        rc_updated_flag = 0;
    }

}

void update_pid_on_screen()
{
    copy_to_buffer(confP[current_pid_item], &menuBuffer[30 + 7], 3, AS_INTEGER);
    copy_to_buffer(confI[current_pid_item], &menuBuffer[40 + 7], 3, AS_INTEGER);
    copy_to_buffer(confD[current_pid_item], &menuBuffer[50 + 7], 3, AS_INTEGER);
    //copy_to_buffer(current_pid_item, &menuBuffer[50 + 7], 3, AS_INTEGER);
}

void go_to_menu(char menu)
{
    current_menu = menu;
    switch (current_menu)
    {
    case (INTRO_MENU):
        printing_numbers = 0;
        strcpy_P((char *)menuBuffer, (PGM_P)menu_intro);
        for (int i = 0; i < 90; i++)
        {
            menuBuffer[i] = to_index(menuBuffer[i]);
        }
        break;


    case (PID_MENU):
        //customMessage = MSP_PID;
        printing_numbers = 1;
        strcpy_P((char *)menuBuffer, (PGM_P)menu_titles[current_menu - 2]);

        strcpy_P((char *)menuBuffer + 21, (PGM_P)pid_items[current_pid_item]);
        //strcpy_P((char *)menuBuffer + 12, (PGM_P)pid_items[current_pid_item]);
        menuBuffer[20] = 29 + 64;
        menuBuffer[26] = 28 + 64;
        menuBuffer[30 + 5] = 'P';
        menuBuffer[40 + 5] = 'I';
        menuBuffer[50 + 5] = 'D';
        strcpy_P((char *)menuBuffer + 60, (PGM_P)words[0]);
        strcpy_P((char *)menuBuffer + 70, (PGM_P)words[1]);

        for (int i = 0; i < 90; i++)
        {
            menuBuffer[i] = to_index(menuBuffer[i]);
        }

        update_pid_on_screen();

        break;

    }




}