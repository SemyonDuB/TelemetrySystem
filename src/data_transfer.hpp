/**
 * @file data_transfer.hpp
 * @brief Functions and classes definition.
 */

#pragma once

#include <Arduino.h>


/** 
 * A namespace for data transfer functions and classes.
 */
namespace dt // dt means data transfer
{

    
    namespace time_literals
    {
        /**
         * @fn unsigned long operator "" _ms(unsigned long long time)
         * @brief A function for specifying time in milliseconds.
         */
        unsigned long operator "" _ms(unsigned long long time);
    }

    using namespace dt::time_literals;


    /**
     * @brief Read data/signals from sensor.
     *
     * Read data/signals from sender sensor and
     * translate it into bool. Also is the singleton class.
     */

    class data_reader
    {
    public:

        /**
         * One initialization for performance purposes.
         */
        static data_reader& instance()
        {
            static data_reader inst;
            return inst;
        }

        /**
         * @brief Read data from signal pin.
         *
         * Read data from signal pin and
         * translate it into bool by specific
         * time duration.
         *
         * @param signal_pin just pin where we get this signals.
         * @param sig_duration is how long lasts signal.
         */
        bool read_data(int signal_pin, int sig_duration = 20_ms);

    private:
        data_reader() = default;

        bool signal = false;
        int sig_duration = 20_ms;

        bool trans_signal_to_bool(bool state, int signal_pin);
    };


    /** 
     * Encode msg and send it to the receiver sensor.
     *
     * @param msg is the char sequence.
     * @param sig_duration is how long should be lasts signal.
     * @param write_to_pin is a power supply to the sensor.
     */
    void encode_msg(String msg, int sig_duration = 20_ms, 
                    int write_pin = 5);

    /** 
     * Decode msg by specific time duration from sensor.
     *
     * @param msg is the char sequence.
     * @param sig_duration is how long should be lasts signal.
     * @param read_pin is a pin where we get signals.
     */
    String decode_msg(int sig_duration = 20_ms, int read_pin = 2);
}// namespace dt
