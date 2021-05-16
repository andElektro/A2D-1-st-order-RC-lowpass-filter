#ifndef LPFILTER_H
#define LPFILTER_H

#include "cbuff.h"

/*
 * Ohmg = 2*PI*fcut/fsam //Normalized cut off frequency
 * Wg = k*tan(Ohmg/2) //Cut off frequency for difference equation.
 * k = 2/Tsam //k is removed for lowpass and highpass filters.
 * Wg = tan(PI*fcut/fsam) //Cut off frequency actually used for difference equation.
 * y[n] = Wg/(1+Wg)*x[n] + Wg/(1+Wg)*x[n-1] - (Wg-1)/(1+Wg)*y[n-1]
 */

template<typename V>
class LPfilter
{
  private:
    V fcut; //Cut off frequency
    V fsam; //Sampling frequrncy
    int SIZE = 2; //Size of array used for storing Vout.
    Cbuff<V>* x = nullptr; //Arrayobjectpointer to use as circular buffer.
    Cbuff<V>* y = nullptr;
    V yin = 0; //Input
    float xp = 0; //Parameter used for x values.
    float yp = 0; //Parameter used for y value.

  public:
    LPfilter(V& _fcut, V& _fsam);
    ~LPfilter();
    V get(V _Xin);
};

template<typename V>
LPfilter<V>::LPfilter(V& _fcut, V& _fsam)
  : fcut(_fcut), fsam(_fsam)
{
  x = new Cbuff<V> (SIZE);
  y = new Cbuff<V> (SIZE);
  float Wg = tan(PI*fcut/fsam);
  xp = Wg/(1+Wg);
  yp = (Wg-1)/(1+Wg);
}

template<typename V>
LPfilter<V>::~LPfilter()
{
  delete x;
  delete y;
}

template<typename V>
V LPfilter<V>::get(V _yin)
{
  //y[n] = Wg/(1+Wg)*x[n] + Wg/(1+Wg)*x[n-1] - (Wg-1)/(1+Wg)*y[n-1]
  y->push(xp*x->get(0)+xp*x->get(1)-yp*y->get(1));
  return y->get(0);
}

#endif
