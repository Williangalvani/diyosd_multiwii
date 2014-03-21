#include "menu.h"
#include "variables.h"
#include <avr/pgmspace.h>
#include "output.h"

PROGMEM const unsigned char menu_intro[] = "PID:                                                                       ";
PROGMEM const unsigned char pid_items[][6] = {"ROLL", "PITCH", "YAW", "ALT", "POS", "POSR", "NAVR", "LEVEL", "MAG", "TPA"};


char left = 0;
char right = 0;
char up = 0;
char down = 0;
char more = 0;
char less = 0;

char selectedMenu = 0;
char menus_Available = 10;
char current_menu = 0;

char pid_showing = 'P';

#define INTRO_MENU 1

#define PID_MENU 2

void go_to_menu(char menu);
void menu_right();
void menu_left();
void menu_down();
void menu_up();

void pid_right()
{
    if (pid_showing == 'P')
    {
        pid_showing = 'I';
    }
    else if (pid_showing == 'I')
    {
        pid_showing = 'D';
    }
    else if (pid_showing == 'D')
    {
        pid_showing = 'P';
    }
    pid_reloaded_flag = 1;
}
void pid_left()
{
    if (pid_showing == 'P')
    {
        pid_showing = 'D';
    }
    else if (pid_showing == 'D')
    {
        pid_showing = 'I';
    }
    else if (pid_showing == 'I')
    {
        pid_showing = 'P';
    }
    pid_reloaded_flag = 1;
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
    }
}

void menu_right()
{
    switch (current_menu)
    {
    case (PID_MENU):
        pid_right();
        break;
    }
}

void menu_increase(char delta)
{
    switch (current_menu)
    {
    case PID_MENU:
        switch (pid_showing)
        {
        case 'P':
            confP[selectedMenu]+=delta;
            break;
        case 'I':
            confI[selectedMenu]+=delta;
            break;
        case 'D':
            confD[selectedMenu]+=delta;
            break;
        }
        pid_reloaded_flag = 1;
        break;
    }

}



void process_menu()
{
    if (mode_armed)
    {
        menuon = 0;
    }
    else
    {
        menuon = 1;
    }
    if (menuon)
    {
        if (current_menu == 0)
        {
            clear_menu();
            go_to_menu(PID_MENU);
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
        //////////////////////////////////////////////////////////////////////////
        if (down > 5)
        {
            down = 0;
            menu_down();
        }
        if (up > 5)
        {
            up = 0;
            menu_up();
        }
        if (left > 5)
        {
            left = 0;
            menu_left();
        }
        if (right > 5)
        {
            right = 0;
            menu_right();
        }
        if (more > 5)
        {
            more = 0;
            menu_increase(1);
        }
        if (less > 5)
        {
            less = 0;
            menu_increase(-1);
        }
        rc_updated_flag = 0;
    }

}

void go_to_menu(char menu)
{
    current_menu = menu;
    switch (current_menu)
    {
    case (INTRO_MENU):
        strcpy_P((char *)menuBuffer, (PGM_P)menu_intro);
        for (int i = 0; i < 90; i++)
        {
            menuBuffer[i] = to_index(menuBuffer[i]);
        }
        break;




    case (PID_MENU):
        customMessage = MSP_PID;
        printing_numbers = 1;
        for (int i = 0; i < 10; i++)
        {
            char current_pos = i * 10;
            strcpy_P((char *)menuBuffer + current_pos, (PGM_P)pid_items[i]);
            menuBuffer[6 + current_pos] = pid_showing;
            copy_to_buffer(confP[i], &menuBuffer[current_pos + 7], 3, AS_INTEGER);
            menuBuffer[current_pos + 7] = 3;

        }
        for (int i = 0; i < 90; i++)
        {
            menuBuffer[i] = to_index(menuBuffer[i]);
        }
        menuBuffer[7] = 3;

        for (int i = 0; i < 10; i++)
        {
            char current_pos = i * 10;
            copy_to_buffer(confP[i], &menuBuffer[current_pos + 7], 3, AS_INTEGER);

        }


        break;

    }




}