#ifndef LPFILTER_H
#define LPFILTER_H

#include "cbuff.h"

/*
    Vout[n]=(T/(T+R*C))*Vin[n] + ((R*C)/(T+R*C))*Vout[n-1]
    T = sampling time

    f-3dB=1/(2*pi*R*C)
    f-3dB = cut off frequency

    R*C=1/(2*pi*f-3dB)
*/

template<typename V>
class LPfilter
{
  private:
    V fcut; //Cut off frequency
    V T; //Sampling time
    V RC; //Constant representing resistor and capacitor in first order LP filter
    int SIZE = 2; //Size of array used for storing Vout.
    Cbuff<V>* Vout = nullptr; //Arrayobjectpointer to use as circular buffer of Vout.
    V Vin = 0; //Input
    V P1; //T/(T+RC)
    V P2; //(RC)/(T+RC)

  public:
    LPfilter(V& _fcut, V& _T);
    ~LPfilter();
    V get(V _Vin);
};

template<typename V>
LPfilter<V>::LPfilter(V& _fcut, V& _T)
  : fcut(_fcut), T(_T)
{
  RC = 1 / (2 * PI * fcut);
  P1 = T / (T + RC);
  P2 = RC / (T + RC);
  Vout = new Cbuff<V> (SIZE);
}

template<typename V>
LPfilter<V>::~LPfilter()
{
  delete Vout;
}

template<typename V>
V LPfilter<V>::get(V _Vin)
{
  //Vout[n]=(T/(T+R*C))*Vin[n] + ((R*C)/(T+R*C))*Vout[n-1]
  Vout->push(P1 * _Vin + P2 * Vout->get(1));
  return Vout->get(0);
}

#endif
