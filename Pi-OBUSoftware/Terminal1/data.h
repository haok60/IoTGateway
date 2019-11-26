#ifndef DATA_H
#define DATA_H
#include "QString"

class DATA
{
public:
    DATA();
    static QString temp;
    static QString hump;
    static double temp_t;
    static double hump_t;
    static QString gps;
    static QString mac;
    static QString Ip;
    static QString lat;
    static QString lng;
    static QString str;
    static QString img;
    static QString time;
    static QString lux;
    static double lux_t;
    static QString mois;
    static int mois_t;
    static int mois_t2;
    static QString dust;
    static int warningDust;
    static double time_P;
    static double time_L;
	static bool onPump;
    static bool onLight;
};

#endif // DATA_H
