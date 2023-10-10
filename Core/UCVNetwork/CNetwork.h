#ifndef CNETWORK_H
#define CNETWORK_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

//#include "mysdk.h"
#include "CNLayer.h"

using namespace std;
using namespace RDK;

//class CNLayer;

class RDK_LIB_TYPE CNetwork: public UModule
{
protected: // Параметры
// Число слоев сети
int NumLayers;

// Вектор шагов свертки
vector<int> NetworkConvolutionStep;

// Вектор высот ядра свертки
vector<int> NetworkConvHeight;

// Вектор ширин ядра свертки
vector<int> NetworkConvWidth;

// Вектор количества полей в каждом слое
vector<int> NetworkNumFields;

// Размеры входного изображения
int InputWidth,InputHeight;

// Размер окна свертки
//int ConvWidth, ConvHeight; //а надо ли? есть в CNeuron.h

// Число классов
int NumOutputs;

//Параметр скорости обучения
double Eta;

//Столбец желаемого отклика
vector<double> trueOtklik;

//Средняя энергия ошибки
double Error;

// Порядок весов
double DegWeights;

protected: // Данные
// Входное изображение
UBitmap InputImage;

// Слои
vector<CNLayer> Layers;

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
CNetwork(void);
virtual ~CNetwork(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число слоев сети
const int& GetNumLayers(void) const;
bool SetNumLayers(const int& value);

const vector<int>& GetNetworkConvStep(void) const;
bool SetNetworkConvStep(const vector<int>& value);

const vector<int>& GetNetworkConvHeight(void) const;
bool SetNetworkConvHeight(const vector<int>& value);

const vector<int>& GetNetworkConvWidth(void) const;
bool SetNetworkConvWidth(const vector<int>& value);

const vector<int>& GetNetworkNumFields(void) const;
bool SetNetworkNumFields(const vector<int>& value);

// Размеры входного изображения
const int& GetInputWidth(void) const;
bool SetInputWidth(const int &value);

const int& GetInputHeight(void) const;
bool SetInputHeight(const int &value);

// Скорость обучения
const double& GetEta(void) const;
bool SetEta(const double& value);

//Средняя энергия ошибки
const double& GetError(void) const;
bool SetError(double value);

// Порядок весов
const double& GetDegWeights(void) const;
bool SetDegWeights(double value);
// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
// Возвращает слой по индексу
CNLayer& GetLayer(int index);
// --------------------------

// --------------------------
// Методы управления счетом
// --------------------------
//bool SetInputImage(const UBitmap &input);

bool SetFieldOutput(int layer, int field, vector<vector<double> > &output);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ABuild(void);

// Сброс процесса счета.
virtual bool AReset(void);

// Выполняет расчет этого объекта
virtual bool ACalculate(void);

public:
//Обучение
double ATrain(int exp_class);

void ResetTraining(void);
// --------------------------
};

#endif
