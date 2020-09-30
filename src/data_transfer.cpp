/**
 * @file data_transfer.cpp
 * @brief Implementation of data transfer functions and classes.
 */

#include "data_transfer.hpp"


unsigned long dt::operator "" _ms(unsigned long long time) { return time; }


bool dt::data_reader::read_data(int signal_pin, int sig_duration)
{
    this->sig_duration = sig_duration;

    if(signal == true)
        return trans_signal_to_bool(true, signal_pin);
    else 
        return trans_signal_to_bool(false, signal_pin);

}


bool dt::data_reader::trans_signal_to_bool(bool state, int signal_pin)
{
    unsigned long long time = millis();
    
    while(signal == state && 
          (millis() - time) <= sig_duration + 2)
    {
        signal = !static_cast<bool>(digitalRead(signal_pin));
    }

    return state;
}


String dt::decode_msg(int sig_duration, int read_pin)
{
    auto &dr = dt::data_reader::instance();

    // if data == 0b10 == STX
    if(dr.read_data(read_pin, sig_duration) == true &&
       dr.read_data(read_pin, sig_duration) == false)
    {
        String msg;

        while(true)
        {
            byte data = 0b00000000;

            for(int i = 7; i >= 0; --i)
            {
                if(dr.read_data(read_pin, sig_duration) == true)
                    bitSet(data, i);
            }

            if(data <= 0b00000100 || data == 0b11111111)
                return msg;
            else
                msg += static_cast<char>(data);
        }
    }

    return String();
}


void dt::encode_msg(String msg, int sig_duration, int write_pin)
{
    char STX = char(2);
    char EOT = char(4);

    // Send start of text (STX) - ascii symbol
    if(msg != String(STX) &&
       msg != String(EOT))
        encode_msg(String(char(2)), sig_duration, write_pin);

    // Itterate each symbol in the message
    for(int index_ch = 0; index_ch < msg.length(); ++index_ch)
    {
        byte ch = static_cast<byte>(msg[index_ch]);

        const int num_bits = 8;
        // Iterate each bit and write it in the pin
        for(int index_bit = num_bits - 1; index_bit >= 0; --index_bit)
        {
            if(bitRead(ch, index_bit) == 1)
            {
                digitalWrite(write_pin, HIGH);
                delay(sig_duration);
            }
            else
            {
                digitalWrite(write_pin, LOW);
                delay(sig_duration);
            }
        }
    }

    // Send end of transmission (EOT)
    if(msg != String(EOT) &&
       msg != String(STX))
        encode_msg(String(EOT), sig_duration, write_pin);
}
