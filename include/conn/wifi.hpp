#pragma once
#include <WiFi.h>

#include "helper.hpp"

class WifiController
{

public:
    WifiController()
    {
        wifiServer = new WiFiServer(80);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to the WiFi network");
        Serial.println(WiFi.localIP());

        wifiServer->begin();
    }

    Driving_Input_Values get_input()
    {
        WiFiClient client = wifiServer->available();

        if (client)
        {
            while (client.connected())
            {
                if (client.available() > 0)
                {
                    auto data = client.readStringUntil('\n');
#if LOGGING
                    Serial.println("Received package");
#endif
                    int ch0, ch1, ch2, ch3, ch4, ch5;
                    sscanf(data.c_str(), "CH0:%dCH1:%dCH2:%dCH3:%dCH4:%dCH5:%d", &ch0, &ch1, &ch2, &ch3, &ch4, &ch5);
                    values = {ch0, ch1, ch2, ch3, ch4, ch5};
                    client.println("OK");
                    client.flush();
                    client.stop();
                }
            }
#if LOGGING
            Serial.println("Client disconnected");
#endif
        }
        return values;
    }

private:
    Driving_Input_Values values;
    const char *ssid = "";
    const char *password = "";
    WiFiServer *wifiServer;
};