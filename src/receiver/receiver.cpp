#include "data_transfer.hpp"

using namespace dt::time_literals;

void setup() 
{
    Serial.begin(9600_ms);

    pinMode(2, INPUT);
}


void loop() 
{
    Serial.print(dt::decode_msg(2));
}
