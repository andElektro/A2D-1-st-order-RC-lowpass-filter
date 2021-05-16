#ifndef CBUFF_H
#define CBUFF_H

template<typename T>
class Cbuff
{
  private:
    int SIZE;
    static int writePointer;
    T arr[];

  public:
    Cbuff(int _num);
    ~Cbuff();
    void printArr() const;
    T sumArr() const;
    void push(T _val);
    T get(int _val);

  private:
    void fillArr();
};

template<typename T>
int Cbuff<T>::writePointer = 0;

template<typename T>
Cbuff<T>::Cbuff(int _num)
  : SIZE(_num)
{
  T arr[SIZE];
  fillArr();
}

template<typename T>
Cbuff<T>::~Cbuff()
{
}

template<typename T>
void Cbuff<T>::fillArr()
{
  for (int i = 0; i < SIZE; i++)
    arr[i] = 0;
}

template<typename T>
void Cbuff<T>::printArr() const
{
  for (int i = 0; i < SIZE; i++)
    Serial.println(arr[i]);
}

template<typename T>
T Cbuff<T>::sumArr() const
{
  T sum = 0;
  for (int i = 0; i < SIZE; i++)
    sum += arr[i];
  return sum;
}

template<typename T>
void Cbuff<T>::push(T _val)
{
  if (writePointer < SIZE) {
    arr[writePointer] = _val;
    writePointer++;
  }
  else {
    arr[0] = _val;
    writePointer = 1;
  }
}

template<typename T>
T Cbuff<T>::get(int _val)
{
  if (_val <= SIZE)
    return arr[_val];
  else
    return 0;
}


#endif
