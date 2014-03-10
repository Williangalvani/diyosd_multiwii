

#include "gps.h"
#include "config.h"

#include "Arduino.h"

#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

#include <math.h>


unsigned char Buttonpin = Buttonpin_;



//==================================
// Decleration for GPS-variables
//==================================

// Has homeposition been set?
char homepos = 0;
// Simple way to make a little delay before the homeposition is set. (It waits for GPS-fix, waits a couple of ekstra seconds and set homeposition)
int homeposcount = 0;
// GPSfix - when '0' no satellite fix.
char GPSfix = '0';
long lats = 0;
long lons = 0;

// Used to calculate line of sight.
long losy = 0;
long losx = 0;

// Variables to store home position:
long lathome = 0;
long lonhome = 0;
long los = 1234;
// Direction home:
int arrowd;


//========================================
// Menu system
//========================================

unsigned char show_mah_km = EEPROM.read(1);
unsigned char show_decimals = EEPROM.read(2);
unsigned char altitude_offset_on = EEPROM.read(3);
unsigned char align_text = EEPROM.read(4);
//unsigned char show_plane_pos = EEPROM.read(5);

int menuon = 0;
unsigned char menupos = 0;
char move_arrow_count = 0;
unsigned char menu = 1;

unsigned int speedkm = 0;
unsigned char altitude2[10] = {1, 1, 1, 1, 1, 1};
unsigned char altituder[10] = {1, 1, 1, 1, 1, 1, 1, 1};

long altitude_offset = 0;
int altitude_negative = 0;

unsigned char landed = 1;
long altitude_num = 0;
unsigned char loadbar[] = {29, 27, 27, 27, 27, 27, 27, 27, 27, 28};
unsigned char losr[] = {1, 1, 1, 1}; // Stores LOS characters (numbers) written to screen
unsigned char arrowr[] = {3, 3, 3};
int current_num = 0;
////variables changed, to updaate on the screen
int updatedSpeed = 1;
int updatedArrow = 1;
int updatedAlt = 1;
int updatedAtt = 1;
int updatedDist = 1;
int updatedVolt = 1;
int updatedCur = 1;
int updatedSats = 1;
int updatedAnalog = 1;

void update_gps_data()
{
    SPDR = 0b00000000;
    // This is used to set homeposition.
    if (homepos == 0)
    {
        // If we have GPS-fix;
        if (GPSfix > '0')
        {
            homeposcount++;
            if (homeposcount > set_home_delay)
            {
                lathome = lats;
                lonhome = lons;
                homepos = 1;

                altitude_offset = altitude_num;

            }
        }
    }

}

/////////////////////////MULTIWII CODE

#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ANALOG               110

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MwAngle[2] = {0, 0};        // Those will hold Accelerator Angle

int16_t GPS_distanceToHome = 0;
uint8_t GPS_fix = 0;
int32_t GPS_latitude;
int32_t GPS_longitude;
int16_t GPS_altitude;
uint16_t GPS_speed = 0;
int16_t GPS_directionToHome = 0;
uint8_t GPS_numSat = 0;

//========================================
// For flight summary
//========================================
long max_los =0;
unsigned char max_losr[] = {3,3,3,3};

int max_speed =0;
unsigned char max_speedr[] = {3,3,3,3};

long kmh_total =0;
unsigned char total_distancer[] = {3,3,3,3,3};

long max_alt=0;
unsigned char max_altr[] = {3,3,3,3,3,3};

long altitude_num2=0;
int altitude_int=0;

unsigned long flight_time =0;
unsigned char last_time=0;
unsigned char flight_timer[] = {3,3,3,3,3,3};

int avg_speed =0;
unsigned char avg_speedr[] = {3,3,3,3,3,3};



unsigned char test=0;

  // Stores LOS characters (numbers) written to screen
unsigned long long_buf=0;



unsigned int mahkm =0;
unsigned char mahkmr[]={3,3,3,3,3,3};  
/////////////////////////////////////////////////////
int success = 0;

// Mode bits
uint32_t mode_armed;
uint32_t mode_stable;
uint32_t mode_horizon;
uint32_t mode_baro;
uint32_t mode_mag;
uint32_t mode_gpshome;
uint32_t mode_gpshold;
uint32_t mode_osd_switch;

int temp1;
uint16_t vbat = 0;
uint16_t powermeter = 0;
uint16_t rssi = 0;
uint16_t mwcurrent = 0;
int32_t  MwAltitude = 0;                       // This hold barometric value
static int16_t MwHeading = 0;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SERIALBUFFERSIZE 256
static uint8_t serialBuffer[SERIALBUFFERSIZE]; // this hold the imcoming string from serial O string
static uint8_t receiverIndex;
static uint8_t dataSize;
static uint8_t cmdMSP;
static uint8_t rcvChecksum;
static uint8_t readIndex;

int should_process_now = 0;
extern unsigned char voltager[];
int counter = 0;


void update_data();

uint8_t read8();
uint16_t read16();
uint32_t read32();

uint32_t read32()
{
    uint32_t t = read16();
    t |= (uint32_t)read16() << 16;
    return t;
}

uint16_t read16()
{
    uint16_t t = read8();
    t |= (uint16_t)read8() << 8;
    return t;
}

uint8_t read8()
{
    return serialBuffer[readIndex++];
}

// --------------------------------------------------------------------------------------
// Here are decoded received commands from MultiWii
void serialMSPCheck()
{
    readIndex = 0;
    success++;
    updatedVolt = 1;
    if (cmdMSP == MSP_RAW_GPS)
    {
        GPS_fix = (int)read8();
        if (GPS_fix != 0)
        {
            GPSfix = '1';
        }
        GPS_numSat = read8();
        lats = GPS_latitude = read32();
        lons = GPS_longitude = read32();
        GPS_altitude = read16();
        speedkm = GPS_speed = read16() / 10;
        updatedSats = 1;
        updatedAlt = 1;
        updatedSpeed = 1;
    }

    else if (cmdMSP == MSP_COMP_GPS)
    {
        los = GPS_distanceToHome = read16();
        arrowd = (int(read16()) + 22) / 45;
        if (arrowd < 0)
        {
            arrowd += 8;
        }
        updatedArrow = 1;
        updatedDist = 1;
    }
    else if (cmdMSP == MSP_ATTITUDE)
    {
        for (uint8_t i = 0; i < 2; i++)
            MwAngle[i] = (int)read16() / 10;
        MwHeading = read16();
        read16();
        updatedAtt = 1;
    }
    else if (cmdMSP == MSP_ANALOG)
    {
        vbat = read8();
        powermeter = read16();
        rssi = read16();
        mwcurrent = read16();
        updatedAnalog = 1;
    }

}

// End of decoded received commands from MultiWii
// --------------------------------------------------------------------------------------


static enum _serial_state
{
    IDLE,
    HEADER_START,
    HEADER_M,
    HEADER_ARROW,
    HEADER_SIZE,
    HEADER_CMD,
}
c_state = IDLE;

// receives whole commands from multiwii
void serialMSPreceive()
{
    char c;

    //while (UCSR0A & (1 << RXC0))
    while (Serial.available())
    {
        //c = UDR0;
        c = Serial.read();

        if (c_state == IDLE)
        {
            c_state = (c == '$') ? HEADER_START : IDLE;
        }
        else if (c_state == HEADER_START)
        {
            c_state = (c == 'M') ? HEADER_M : IDLE;
        }
        else if (c_state == HEADER_M)
        {
            c_state = (c == '>') ? HEADER_ARROW : IDLE;
        }
        else if (c_state == HEADER_ARROW)
        {
            if (c > SERIALBUFFERSIZE)
            {
                // now we are expecting the payload size
                c_state = IDLE;
            }
            else
            {
                dataSize = c;
                c_state = HEADER_SIZE;
                rcvChecksum = c;
            }
        }
        else if (c_state == HEADER_SIZE)
        {
            c_state = HEADER_CMD;
            cmdMSP = c;
            rcvChecksum ^= c;
            receiverIndex = 0;
        }
        else if (c_state == HEADER_CMD)
        {
            rcvChecksum ^= c;
            if (receiverIndex == dataSize) // received checksum byte
            {
                if (rcvChecksum == 0)
                {
                    GPSfix = '1';
                    should_process_now = 1;
                }
                else
                {
                    temp1 = rcvChecksum;
                }
                c_state = IDLE;
            }
            else
                serialBuffer[receiverIndex++] = c;
        }
    }
}



void blankserialRequest(uint8_t requestMSP)
{

    uint8_t txCheckSum;
    Serial.write('$');
    Serial.write('M');
    Serial.write('<');
    Serial.write((uint8_t)0x00);
    Serial.write(requestMSP);
    Serial.write(requestMSP);

}

void do_multiwii_communication()
{
    update_data();
    update_gps_data();
    if (should_process_now)
    {
        serialMSPCheck();
        should_process_now = 0;
    }
    else
    {
        serialMSPreceive();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void gps()
{
    if (CONTROLLER == 1)
    {
        Buttonpin = 6;
    }
    
    while (1 == 1)
    {
        do_multiwii_communication();
    }

}
