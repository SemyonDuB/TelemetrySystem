#include "data_transfer.hpp"

using namespace dt::time_literals;

void setup() 
{
    Serial.begin(9600_ms);

    pinMode(2, OUTPUT); // debug light diode
    pinMode(5, OUTPUT);
}


void loop() 
{
    delay(10000_ms);

    dt::encode_msg("Hello world! How are you?\n", 20_ms, 5);
}
