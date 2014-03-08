

#include "gps.h"
#include "config.h"

#include "Arduino.h"

#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

#include <math.h>


unsigned char Buttonpin = Buttonpin_;

// Buffer for GPS string
//char GPSbuffer[100] = {0};

int iiii = 0;


//==================================
// Decleration for GPS-variables
//==================================

// Has homeposition been set?
char homepos = 0;
// Simple way to make a little delay before the homeposition is set. (It waits for GPS-fix, waits a couple of ekstra seconds and set homeposition)
int homeposcount = 0;

// GPSfix - when '0' no satellite fix.
char GPSfix = '0';

// Used to store all the GPS positions etc...
//long lat1 = 0;
//long lat2 = 0;
long lats = 0;

//long lon1 = 0;
//long lon2 = 2;
long lons = 0;

// Used to calculate line of sight.
long losy = 0;
long losx = 0;

// Variables to store home position:
long lathome = 0;
long lonhome = 0;
long los = 1234;

// Direction home:
int homehead = 0;
int homehead_r[3] = {96, 96, 96};
int headi = 0;
int arrow = 0;
int arrowd;


unsigned char latitude_dir = 0;
unsigned char longitude_dir = 0;

float longitude_factor = 1;
int lat_deg = 90;

//========================================
// Menu system
//========================================

/*
int menuon = 0;
unsigned char menupos = 0;
unsigned char move_arrow_count =0;

unsigned char show_mah_km = show_mah_km_;
unsigned char show_decimals = show_decimals_;
unsigned char altitude_offset_on = altitude_offset_on_;
unsigned char align_text = align_text_;
unsigned char show_plane_pos = show_plane_pos_;
*/

//unsigned char Buttonpin = Buttonpin_;

int menuon = 0;
unsigned char menupos = 0;
char move_arrow_count = 0;
unsigned char menu = 1;

unsigned char show_mah_km = EEPROM.read(1);
unsigned char show_decimals = EEPROM.read(2);
unsigned char altitude_offset_on = EEPROM.read(3);
unsigned char align_text = EEPROM.read(4);
unsigned char show_plane_pos = EEPROM.read(5);

int alt_alarm = EEPROM.read(10) + (EEPROM.read(11) << 8);
int los_alarm = EEPROM.read(12) + (EEPROM.read(13) << 8);
int volt_alarm = EEPROM.read(14) + (EEPROM.read(15) << 8);
int mah_alarm = EEPROM.read(16) + (EEPROM.read(17) << 8);




//========================================
// Variables when analyzing serial data (GPS)
//========================================

// For GPS/Serial read
// bufnr counts the number of characters received. N used to when extracting
// data from GPS strings.
int bufnr = 0; // Bytes are stored in an array. bufnr "counts the characters"
int n = 0;
int count = 0;






//========================================
// Data read from GPS
//========================================
unsigned char time[14] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};;
unsigned char speedkn[10] = {1, 1, 1, 1, 1};
unsigned char speedkn2[10] = {1, 1, 1, 1, 1};
unsigned char speedkmw[5] = {1, 1, 1, 1, 1};
unsigned int speedkm = 0;
unsigned int speedkm2 = 0;
int latitude[15] = {0};
int longitude[15] = {0};

unsigned char altitude[10] = {1, 1, 1, 1, 1, 1};
unsigned char altitude2[10] = {1, 1, 1, 1, 1, 1};
unsigned char altituder[10] = {1, 1, 1, 1, 1, 1, 1, 1};
unsigned char altituder2[10] = {1, 1, 1, 1, 1, 1, 1, 1};
long altitude_offset = 0;
int altitude_negative = 0;





//========================================
// For flight summary
//========================================
long max_los = 0;
unsigned char max_losr[] = {3, 3, 3, 3};

int max_speed = 0;
unsigned char max_speedr[] = {3, 3, 3, 3};

long kmh_total = 0;
unsigned char total_distancer[] = {3, 3, 3, 3, 3};

long max_alt = 0;
unsigned char max_altr[] = {3, 3, 3, 3, 3, 3};

unsigned char landed = 1;
long altitude_num = 0;
long altitude_num2 = 0;
int altitude_int = 0;

unsigned long flight_time = 0;
unsigned char last_time = 0;
unsigned char flight_timer[] = {3, 3, 3, 3, 3, 3};

int avg_speed = 0;
unsigned char avg_speedr[] = {3, 3, 3, 3, 3, 3};

unsigned char loadbar[] = {29, 27, 27, 27, 27, 27, 27, 27, 27, 28};

unsigned char test = 0;


unsigned char losr[] = {1, 1, 1, 1}; // Stores LOS characters (numbers) written to screen
unsigned long long_buf = 0;

unsigned char arrowr[] = {3, 3, 3};
int current_num = 0;

unsigned int mahkm = 0;
unsigned char mahkmr[] = {3, 3, 3, 3, 3, 3};

// Stores current characters (numbers) written to screen

/*
void update_menu()
{
    if (CONTROLLER == 1 | Usebutton == 1)
    {
        if (digitalRead(Buttonpin) == LOW)
        {

            GPSbuffer[0] = ((alt_alarm / 1000) + 3) << 3;
            GPSbuffer[1] = ((alt_alarm % 1000 / 100) + 3) << 3;
            GPSbuffer[2] = ((alt_alarm % 1000 % 100 / 10) + 3) << 3;
            GPSbuffer[3] = ((alt_alarm % 1000 % 100 % 10) + 3) << 3;

            GPSbuffer[4] = ((los_alarm / 1000) + 3) << 3;
            GPSbuffer[5] = ((los_alarm % 1000 / 100) + 3) << 3;
            GPSbuffer[6] = ((los_alarm % 1000 % 100 / 10) + 3) << 3;
            GPSbuffer[7] = ((los_alarm % 1000 % 100 % 10) + 3) << 3;

            GPSbuffer[8] = ((volt_alarm / 1000) + 3) << 3;
            GPSbuffer[9] = ((volt_alarm % 1000 / 100) + 3) << 3;
            GPSbuffer[10] = ((volt_alarm % 1000 % 100 / 10) + 3) << 3;
            GPSbuffer[11] = ((volt_alarm % 1000 % 100 % 10) + 3) << 3;

            GPSbuffer[12] = ((mah_alarm / 1000) + 3) << 3;
            GPSbuffer[13] = ((mah_alarm % 1000 / 100) + 3) << 3;
            GPSbuffer[14] = ((mah_alarm % 1000 % 100 / 10) + 3) << 3;
            GPSbuffer[15] = ((mah_alarm % 1000 % 100 % 10) + 3) << 3;

            menuon = 0;

            while (menuon == 1)
            {


                if (digitalRead(Buttonpin) == LOW)
                {
                    move_arrow_count = -25;
                    while (digitalRead(Buttonpin) == LOW)
                    {
                        if (move_arrow_count > -15)
                        {
                            break;
                        }
                    }

                    if (menupos == 7 & menu == 1)
                    {
                        menuon = 0;

                        // Show_mah_km
                        EEPROM.write(1, show_mah_km);

                        // Show decimals
                        EEPROM.write(2, show_decimals);

                        // Altitude offset
                        EEPROM.write(3, altitude_offset_on);

                        // Align text
                        EEPROM.write(4, align_text);

                        // Show plane pos
                        EEPROM.write(5, show_plane_pos);

                        // Alt alarm
                        EEPROM.write(10, (unsigned char) alt_alarm);
                        EEPROM.write(11, (unsigned char) (alt_alarm >> 8));

                        EEPROM.write(12, (unsigned char) los_alarm);
                        EEPROM.write(13, (unsigned char) (los_alarm >> 8));

                        EEPROM.write(14, (unsigned char) volt_alarm);
                        EEPROM.write(15, (unsigned char) (volt_alarm >> 8));

                        EEPROM.write(16, (unsigned char) mah_alarm);
                        EEPROM.write(17, (unsigned char) (mah_alarm >> 8));


                    }

                    if (menupos == 6 & menu == 1)
                    {
                        menu = 2;

                    }

                    else if (menupos == 1 & menu == 1)
                    {
                        if (show_mah_km == 1)
                        {
                            show_mah_km = 0;
                        }
                        else
                        {
                            show_mah_km = 1;
                        }

                    }


                    else if (menupos == 2 & menu == 1)
                    {
                        if (show_decimals == 1)
                        {
                            show_decimals = 0;
                        }
                        else
                        {
                            show_decimals = 1;
                        }

                    }

                    else if (menupos == 3 & menu == 1)
                    {
                        if (altitude_offset_on == 1)
                        {
                            altitude_offset_on  = 0;
                        }
                        else
                        {
                            altitude_offset_on = 1;
                        }

                    }


                    else if (menupos == 4 & menu == 1)
                    {
                        align_text++;

                        if (align_text > 40)
                        {
                            align_text = 2;
                        }

                    }


                    else if (menupos == 5 & menu == 1)
                    {
                        if (show_plane_pos == 1)
                        {
                            show_plane_pos  = 0;
                        }
                        else
                        {
                            show_plane_pos = 1;
                        }

                    }




                    else if (menupos == 1 & menu == 2)
                    {
                        alt_alarm = alt_alarm + 50;

                        if (alt_alarm > 2500)
                        {

                            alt_alarm = 0;
                        }

                        GPSbuffer[0] = ((alt_alarm / 1000) + 3) << 3;
                        GPSbuffer[1] = ((alt_alarm % 1000 / 100) + 3) << 3;
                        GPSbuffer[2] = ((alt_alarm % 1000 % 100 / 10) + 3) << 3;
                        GPSbuffer[3] = ((alt_alarm % 1000 % 100 % 10) + 3) << 3;

                    }


                    else if (menupos == 2 & menu == 2)
                    {
                        los_alarm = los_alarm + 50;

                        if (los_alarm > 2500)
                        {

                            los_alarm = 0;
                        }
                        GPSbuffer[4] = ((los_alarm / 1000) + 3) << 3;
                        GPSbuffer[5] = ((los_alarm % 1000 / 100) + 3) << 3;
                        GPSbuffer[6] = ((los_alarm % 1000 % 100 / 10) + 3) << 3;
                        GPSbuffer[7] = ((los_alarm % 1000 % 100 % 10) + 3) << 3;

                    }


                    else if (menupos == 3 & menu == 2)
                    {
                        volt_alarm = volt_alarm + 1;

                        if (volt_alarm > 200)
                        {

                            volt_alarm = 0;
                        }
                        GPSbuffer[8] = ((volt_alarm / 1000) + 3) << 3;
                        GPSbuffer[9] = ((volt_alarm % 1000 / 100) + 3) << 3;
                        GPSbuffer[10] = ((volt_alarm % 1000 % 100 / 10) + 3) << 3;
                        GPSbuffer[11] = ((volt_alarm % 1000 % 100 % 10) + 3) << 3;

                    }

                    else if (menupos == 4 & menu == 2)
                    {
                        mah_alarm = mah_alarm + 100;

                        if (mah_alarm > 5000)
                        {

                            mah_alarm = 500;
                        }
                        GPSbuffer[12] = ((mah_alarm / 1000) + 3) << 3;
                        GPSbuffer[13] = ((mah_alarm % 1000 / 100) + 3) << 3;
                        GPSbuffer[14] = ((mah_alarm % 1000 % 100 / 10) + 3) << 3;
                        GPSbuffer[15] = ((mah_alarm % 1000 % 100 % 10) + 3) << 3;

                    }

                    else if (menupos == 5 & menu == 2)
                    {
                        menu = 1;
                    }
                }
            }
        }
    }
}
*/

void update_gps_data()
{
    SPDR = 0b00000000;

    //===================================================

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

                max_los = 0;
                max_speed = 0;
                kmh_total = 0;
                max_alt = 0;
                flight_time = 0;
                altitude_offset = altitude_num;

            }
        }
    }

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//to multiwii developpers/committers : do not add new MSP messages without a proper argumentation/agreement on the forum
#define MSP_IDENT                100   //out message         multitype + multiwii version + protocol version + capability variable
#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_IMU              102   //out message         9 DOF
#define MSP_SERVO                103   //out message         8 servos
#define MSP_MOTOR                104   //out message         8 motors
#define MSP_RC                   105   //out message         8 rc chan and more
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_ANALOG               110   //out message         vbat, powermetersum, rssi if available on RX
#define MSP_RC_TUNING            111   //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112   //out message         P I D coeff (9 are used currently)
#define MSP_BOX                  113   //out message         BOX setup (number is dependant of your setup)
#define MSP_MISC                 114   //out message         powermeter trig
#define MSP_MOTOR_PINS           115   //out message         which pins are in use for motors & servos, for GUI 
#define MSP_BOXNAMES             116   //out message         the aux switch names
#define MSP_PIDNAMES             117   //out message         the PID names
#define MSP_WP                   118   //out message         get a WP, WP# is in the payload, returns (WP#, lat, lon, alt, flags) WP#0-home, WP#16-poshold
#define MSP_BOXIDS               119   //out message         get the permanent IDs associated to BOXes

#define MSP_SET_RAW_RC           200   //in message          8 rc chan
#define MSP_SET_RAW_GPS          201   //in message          fix, numsat, lat, lon, alt, speed
#define MSP_SET_PID              202   //in message          P I D coeff (9 are used currently)
#define MSP_SET_BOX              203   //in message          BOX setup (number is dependant of your setup)
#define MSP_SET_RC_TUNING        204   //in message          rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION      205   //in message          no param
#define MSP_MAG_CALIBRATION      206   //in message          no param
#define MSP_SET_MISC             207   //in message          powermeter trig + 8 free for future use
#define MSP_RESET_CONF           208   //in message          no param
#define MSP_SET_WP               209   //in message          sets a given WP (WP#,lat, lon, alt, flags)
#define MSP_SELECT_SETTING       210   //in message          Select Setting Number (0-2)
#define MSP_SET_HEAD             211   //in message          define a new heading hold direction

#define MSP_BIND                 240   //in message          no param

#define MSP_EEPROM_WRITE         250   //in message          no param

#define MSP_DEBUGMSG             253   //out message         debug string buffer
#define MSP_DEBUG                254   //out message         debug1,debug2,debug3,debug4
// End of imported defines from Multiwii Serial Protocol MultiWii_shared svn r1333

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MwAngle[2] = {0, 0};        // Those will hold Accelerator Angle
static uint16_t MwRcData[8] =   // This hold receiver pulse signal
{
    1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500
} ;

uint16_t  MwSensorPresent = 0;
uint32_t  MwSensorActive = 0;
uint8_t MwVersion = 0;
uint8_t MwVBat = 0;
int16_t MwVario = 0;
uint8_t armed = 0;
uint8_t previousarmedstatus = 0; // for statistics after disarming
int16_t GPS_distanceToHome = 0;
uint8_t GPS_fix = 0;
int32_t GPS_latitude;
int32_t GPS_longitude;
int16_t GPS_altitude;
uint16_t GPS_speed = 0;
int16_t GPS_directionToHome = 0;
uint8_t GPS_numSat = 0;
int16_t I2CError = 0;
uint16_t cycleTime = 0;
uint16_t MWpMeterSum = 0;
uint16_t MwRssi = 0;
uint16_t MWAmperage = 0;
int success = 0;


#define PIDITEMS 10

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

static uint8_t P8[PIDITEMS], I8[PIDITEMS], D8[PIDITEMS];

static uint8_t rcRate8, rcExpo8;
static uint8_t rollPitchRate;
static uint8_t yawRate;
static uint8_t dynThrPID;
static uint8_t thrMid8;
static uint8_t thrExpo8;


static uint16_t  MwAccSmooth[3] = {0, 0, 0};   // Those will hold Accelerator data
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
    if (cmdMSP == MSP_RAW_GPS)
    {
        GPS_fix = read8();
        if (GPS_fix != 0)
        {
            GPSfix = '1';
        }
        GPS_numSat = read8();
        lats = GPS_latitude = read32();
        lons = GPS_longitude = read32();
        altitude_num = GPS_altitude = read16();
        speedkm = GPS_speed = read16()/10;
    }

    else if (cmdMSP == MSP_COMP_GPS)
    {
        los = GPS_distanceToHome = read16();
        arrowd = (int(read16()) + 22) / 45;
        if (arrowd < 0)
        {
            arrowd += 8;
        }
    }
    else if (cmdMSP == MSP_ATTITUDE)
    {
        for (uint8_t i = 0; i < 2; i++)
            MwAngle[i] = read16();
        MwHeading = read16();
        read16();
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

int should_process_now = 0;
extern unsigned char voltager[];

void serialMSPreceive()
{
    uint8_t c;

    while (Serial.available() > 0)
    {
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
    /*if (requestMSP == MSP_OSD && fontMode)
    {
        fontSerialRequest();
        return;
    }*/
    Serial.write('$');
    Serial.write('M');
    Serial.write('<');
    Serial.write((uint8_t)0x00);
    Serial.write(requestMSP);
    Serial.write(requestMSP);
}
/*
void fontSerialRequest()
{
    int16_t cindex = getNextCharToRequest();
    uint8_t txCheckSum;
    uint8_t txSize;
    Serial.write('$');
    Serial.write('M');
    Serial.write('<');
    txCheckSum = 0;
    txSize = 3;
    Serial.write(txSize);
    txCheckSum ^= txSize;
    Serial.write(MSP_OSD);
    txCheckSum ^= MSP_OSD;
    Serial.write(OSD_GET_FONT);
    txCheckSum ^= OSD_GET_FONT;
    Serial.write(cindex);
    txCheckSum ^= cindex;
    Serial.write(cindex >> 8);
    txCheckSum ^= cindex >> 8;
    Serial.write(txCheckSum);
}*/


int counter = 0;
void do_multiwii_communication()
{
    counter++;
    if (counter >= 100)
    {
        counter = 0;
    }
    if (counter == 0)
    {
        blankserialRequest(MSP_ATTITUDE);
    }
    if (counter == 50 )
    {
        //Serial.println(Serial.available());
        blankserialRequest(MSP_RAW_GPS);
    }
    if (counter == 70)
    {
        update_gps_data();
    }

    delay(10);
    //Serial.println(loopcount);
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

    //update_menu();

    while (1 == 1)
    {
        do_multiwii_communication();
        //do_serial_communication();
    }

}
