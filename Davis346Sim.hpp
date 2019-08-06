/*
   Platform-indpendent simulator for iniVation DAVIS346 Dynamic Vision Sensor

   Copyright(C) 2019 Simon D.Levy

   MIT License
*/

#pragma once

class Davis346 {

    public:
        
        // Simplified AER event structure, based on
        // https://github.com/SensorsINI/jaer/blob/master/src/net/sf/jaer/event/BasicEvent.java
        typedef struct {

            uint32_t timestamp; // us
            uint16_t x;
            uint16_t y;


        } event_t;

        Davis346(void)
        {
        }

        ~Davis346(void)
        {
        }

}; 
