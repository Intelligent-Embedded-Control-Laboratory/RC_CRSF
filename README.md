# RC_CRSF

除夕夜還在工作，這麼認真的員工是不是該加薪了

## How to use

```cpp
// 2023-01-21
#include <Arduino.h>
#include <RC_CRSF.h>

#define HW_SERIAL_INTERFACE_RC_CRSF Serial1
#define HW_SERIAL_BAUD_RATE_RC_CRSF 400000

RC_CRSF CRSF;
uint16_t RC[16];

void setup()
{
    Serial.begin(115200);
    CRSF.begin(HW_SERIAL_INTERFACE_RC_CRSF, HW_SERIAL_BAUD_RATE_RC_CRSF);
}

void loop()
{
    if (CRSF.read(RC) == RC_CRSF::CRSF_OK)
    {
        for (auto &s : RC)
        {
            Serial.print(s);
            Serial.print(" ");
        }
        Serial.println();
        Serial.flush();
    }
}
```
