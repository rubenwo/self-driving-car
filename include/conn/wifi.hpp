#pragma once
#include <WiFi.h>

#include "helper.hpp"

class WifiController
{

public:
    WifiController(const std::string &ssid, const std::string &password) : ssid(ssid), password(password)
    {
        wifiServer = new WiFiServer(80);
        WiFi.begin(ssid.c_str(), password.c_str());
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
        // Opening a new connection was about 40% faster than keeping a connection open.
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
    std::string ssid, password;
    WiFiServer *wifiServer;
};