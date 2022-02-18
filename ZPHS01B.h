/**
# ZPHS01B Library for Winsen MH-Z19B NDIR CO2 Module

by **ShaggyDog18@gmail.com**, JULY 2020

github: https://github.com/ShaggyDog18/ZPHS01B

Arduino library for **MH-Z19B NDIR CO2 Module** by [Zhengzhou Winsen Electronics Technology Co., Ltd](www.winsen-sensor.com)

License: [GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)

MH-Z19B NDIR infrared gas module is a common type, small size sensor, using non-dispersive infrared (NDIR) principle to detect the existence of CO 2 in the air, with good selectivity, non-oxygen dependent and long life. Built-in temperature compensation; and it has UART output and PWM output.

This library features access to all module features though an abstracted class and methods to manage the module implemented in user-level functionality.

The library does not work with PWM module signal. Communicates with the module by Hardware or Software UART.

CO2 Measurement Range 0~2000ppm or 0~5000ppm. Accuracy: ±(50ppm+3%).

## Library Methods

- `ZPHS01B( Stream& serial )` - Class Constructor
- `~ZPHS01B()` - Class Destructor
- `uint16_t getPPM(void)` - read data from the module; returns value of CO2 concentration in ppm; Data are verified and valid (validate by calculating checkSum of the data received). Retunt `FALSE` i.e. ZERO value if communication or CRC error.
- `int8_t getTemp(void)` - returns module temperature in degrees Celcium. Should be called after getPPM() function; otherwise will  return a previous value. Rather inaccurate ±2*C; is used for internal compensation.
- `void setAutoCalibration( bool _autoCalib )` - toggles Auto Calibration (Automatic Baseline Correction - ABC) ON/OFF. Set `true` for Enabled/ON; `false` for Disabled/OFF (default). Refer to Auto Calibration Notes below.
- `bool getABCstatus(void)` - gets Auto Calibration ABC status (undocumented feature). Returns `true` for Enabled/ON, `false` - Disabled/OFF.
- `void calibrateZeroPoint(void)` - calibrate Zero point. During the zero point calibration, the sensor must work in stable gas environment (400ppm) for over 20 minutes.
- `bool calibrateSpanPoint( uint16_t _spanPoint )`- do `ZeroPoint` calibration before `Span` calibration. Make sure the sensor worked under a certain level co2 for over 20 minutes. Suggest using 2000ppm as span, at least 1000ppm. Default value is 2000ppm. Returns true if the requested Span value is OK.
- `bool setDetectionRange( uint16_t _detectionRange )` - sets detection range, default is 0~2000ppm. The range could be 2,000-5,000ppm. Returns `true` if the requested range value is OK.
- `uint8_t getStatus(void)` - Reads module status (undocumented feature), Returns 0 if OK; The value is available after successful getPPM() reading only; otherwise, will return previous value; to be called after getPPM().

For more details on the library use refer to the example that utilizes major library methods.

## Auto Calibration Notes

if Auto Calibration (Automatic Baseline Correction - ABC) is ON, the sensor itself performs a zero point judgment and automatic calibration procedure intelligently after a continuous operation period. The automatic calibration cycle is every 24 hours after powered on. The zero point for automatic calibration is **400ppm**.

This function is usually suitable for indoor air quality monitor such as offices and homes, not suitable for greenhouse, farm and refrigeratory where this function should be off. Please do zero calibration timely, such as manual or command calibration.

## Compatibility

The library developed for Arduino UNO, NANO, Pro Mini, ESP8266, etc.

 **If you like and use this library please consider making a small donation using [PayPal](https://paypal.me/shaggyDog18/3USD)**
 */

#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define RANGE_TOP_LIMIT 5000  // in ppm, pre-defined for the MH-Z19B, refer to datasheet

class ZPHS01B {
    public:

        /**
         * @brief Constructor for ZPHS01B class
         * @param  a Stream ({Software/Hardware}Serial) object.
         * @note The serial stream should be already initialized
         * @return  void
         */
        ZPHS01B( Stream& serial );


        /*
           Destructor for SD_MHZ18B class
           */
        ~ZPHS01B();

        bool read(void);
        uint16_t getPM1(void);
        uint16_t getPM2(void);
        uint16_t getPM10(void);
        uint16_t getCO2(void);
        uint16_t getVOC(void);
        uint16_t getTemp(void);
        uint16_t getHumidity(void);
        uint16_t getCH2O(void);
        uint16_t getCO(void);
        uint16_t getO3(void);
        uint16_t getNO2(void);


        /*
           Calibrates Zero point.
           During the zero point calibration, the sensor must work in stable gas environment (400ppm) for over 20 minutes.
           */
        void calibrateZeroPoint(void);


        /*
           Span Point calibration. Make sure the sensor worked under a certain level co2 for over 20 minutes. Suggest using 2000ppm as span, at least 1000ppm. Default value is 2000ppm.
           Returns true if requested Span value is OK.
           */
        bool calibrateSpanPoint( uint16_t _spanPoint = 2000 );


        /*
           Toggles Auto Calibration ON/OFF.
           Set `true` for ON; `false` for OFF (default).
           */
        void setAutoCalibration( bool _autoCalib = false );


        /*
           Get Auto Calibration (ABC) status (undocumented)
           Returns `true` for Enabled/ON, `false` - Disabled/OFF
           */
        bool getABCstatus(void);


        /*
           Sets detection range, default is 0~2000ppm.
           The range could be 2,000-5,000ppm.
           Returns `true` if requested range value is OK.
           */
        bool setDetectionRange( uint16_t _detectionRange = 2000 );


        /*
           Reads data from the module, fills in an internal data structure;
           Returns PPM value, verified and valid (validate by calculating checkSum of the data received).
           Return zero (false) if error during data read or CRC is not valid.
           */
        uint16_t getPPM(void);


        /*
           Reads module temperature
           Returns temperature value in degrees Celcium, verified and valid (validate by calculating checkSum of the data received).
           The value is available after successful getPPM() reading only; otherwise, returns previous value; to be called after getPPM() only.
           Rather inaccurate ±3*C; is used for internal compensation.
           */

        // just to ensure compatibility
#define getTemperature() getTemp()


        /*
           Reads module status - not documented, always return 0
           Returns status, verified and valid (validate by calculating checkSum of the data received).
           The value is available after successful getPPM() reading only; otherwise, will return previous value; to be called after getPPM() only.
           */
        // undocumented features


        /*
           Reads warming status - undocumented, does not work, always return warming up...
           Returns status, verified and valid (validate by calculating checkSum of the data received).
           The value is available after successful PPM reading only; otherwise, will return previous value; to be called after getPPM() only.
           */
        //bool isWarming(void);


    private:
        Stream& _serial;

#define SIZEOF_FRAME 19

        struct MHZ19Bstruct_t {  // 9 bytes -  in Initiative Upload mode
            uint8_t  header[2];
            uint8_t  pm1[2];
            uint8_t  pm2[2];  // not corrected, have to subtruct 40
            uint8_t  pm10[2];  // not corrected, have to subtruct 40
            uint8_t  co2[2];  // not corrected, have to subtruct 40
            uint8_t  voc;   // 1 bytes are reserved
            uint8_t  temperature[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  humidity[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  ch2o[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  co[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  o3[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  no2[2];  // undocumented;  `true` for ABC AutoCalibration ON; `false` - for OFF
            uint8_t  r1;
            uint8_t  r2;
            uint8_t  checkSum;
        };

        union unionFrame_t {
            MHZ19Bstruct_t MHZ19B;
            uint8_t buffer[ sizeof(MHZ19Bstruct_t) ];  // takes 10 bytes on the 16 and 32bit pltforms
        } _unionFrame;

        // read data from Serial stream
        bool _readData(void);

        // calculate check sum for command
        uint8_t _calcCmdCheckSum( const uint8_t cmd[] );

        // send command to the module, sizeof buffer is always is 4 bytes
        void _sendCmd( const uint8_t buffer[] );
};
