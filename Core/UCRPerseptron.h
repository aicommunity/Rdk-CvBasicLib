// ===========================================================
// Version:        3.0.3
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UCRPERSEPTRON_H
#define UCRPERSEPTRON_H

#include "UCRClassifier.h"

namespace RDK {

class RDK_LIB_TYPE UCRPerseptron: public UCRClassifier
{
public: // Общедоступные свойства
// Число слоев сети
RDK::ULProperty<int,UCRPerseptron> NumLayers;

// Число входов сети
RDK::UCLProperty<vector<int>, UCRPerseptron> NumLayerInputs;

// Автоопределение размера слоев
RDK::ULProperty<bool,UCRPerseptron> AutoSetLayerInputs;

// Режим работы перспетрона
// 0 - обычный
// 1 - режим глубокого обучения
RDK::ULProperty<int,UCRPerseptron> Mode;

/// Параметр сигмоида
RDK::ULProperty<double,UCRPerseptron> Alpha;

/// Путь к бинарному файлу, содержащему информацию о весах
RDK::ULProperty<std::string, UCRPerseptron> NameBin;

public: // Данные модели
// Матрицы весовых коэффициентов слоев
vector<vector<vector<double> > > Weights;

// Вектор входов сети
RDK::UCLProperty<vector<double>,UCRPerseptron,ptPubState> Inputs;

// Вектор выходов слоев сети
RDK::UCLProperty<vector<vector<double> >,UCRPerseptron,ptPubState> Outputs;


public: // Временные переменные
vector<vector<vector<double> > > dWeights;

public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRPerseptron(void);
~UCRPerseptron(void);
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
public:
double GetWeight(int layer, int col, int row);

double GetInputs(int row);
double GetOutputs(int layer, int row);
// -----------------------------

protected:
// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
// Устанавливает число слоев сети
bool SetNumLayers(const int &num);

// Устанавливает число входов всех скрытых слоев
bool SetNumLayerInputs(const vector<int> &numinputs);

// Автоопределение размера слоев
bool SetAutoSetLayerInputs(const bool &value);
// -----------------------------

// ------------------------
// Методы счета
// ------------------------
public:
// Загружает настройки из файла 'name'
virtual bool AFileLoad(fstream &file);

// Сохраняет настройки в файл 'name'
virtual bool AFileSave(fstream &file);
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
virtual UCRPerseptron* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ACRDefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ACRBuild(void);

// Сброс процесса счета.
virtual bool ACRReset(void);

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
public:
// Сброс настроек обучения в исходное состояние
virtual void AResetTraining(void);

// Сброс настроек обучения выбранного слоя в исходное состояние
virtual void LayerResetTraining(size_t index);
// --------------------------

// ------------------------
// Скрытые методы счета
// ------------------------
public:
// Устанавливает значения входного вектора для распознавания
virtual bool SetInput(const vector<double> &input);

public:
// Производит расчет заданного слоя
void CalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights);

void ReverseCalcLayer(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<vector<double> > &prev_weights);

void ReverseCalcLayer0(vector<double> &in_x, vector<double> &out_q,
						vector<vector<double> > &weights, vector<double> &fi);

// Производит расчет всей сети
void CalcNetwork(vector<double> &inputs);

// Производит расчет всей сети
void CalcDeepNetwork(vector<double> &inputs);

double Sigmoid(double x);
// ------------------------
};

}
#endif


