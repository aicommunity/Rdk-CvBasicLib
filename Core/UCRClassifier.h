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

#ifndef UCRCLASSIFIER_H
#define UCRCLASSIFIER_H


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <ctime>

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

//using namespace MySDK;

// Оценки качества этапа распознавания
typedef double ExpectancyT;

class RDK_LIB_TYPE UCRClassifier: public UNet
{
public: // Общедоступные свойства
// Число классов
RDK::ULProperty<int, UCRClassifier>  NumClasses;

// Граничные величины входных значений классификатора
RDK::ULProperty<double, UCRClassifier>  MinInputValue, MaxInputValue;

// Граничные величины выходных значений классификатора
RDK::ULProperty<double, UCRClassifier>  MinOutputValue, MaxOutputValue;

// Желаемый выходной диапазон классификатора
RDK::ULProperty<double, UCRClassifier>  DesiredMinOutputValue, DesiredMaxOutputValue;

// Граничные величины допустимого показателя качества
RDK::UCLProperty<vector<double>, UCRClassifier>  MinQualityRate, MaxQualityRate;

// Имя файла загрузки/сохранения состояния обучения
RDK::ULProperty<string, UCRClassifier>  TrainFileName;

// Имя файла сохранения результатов работы сети
RDK::ULProperty<string, UCRClassifier>  ResultsFileName;

// Признак разрешения автоматической настройки показателя качества
// по результатам обучения
RDK::ULProperty<bool, UCRClassifier>  AutoQualityRate;

// Признак разрешения автоматического выравнивания выходов до ожидаемого максимума
// MaxOutputValue делением на максимальный элемент выхода
RDK::ULProperty<bool, UCRClassifier>  AutoAlignmentOutput;

RDK::UPropertyOutputData<MDMatrix<double>,UCRClassifier, ptPubOutput | ptState> Result;


public: // Свойства результаты вычислений
// Показатель качества <значения показателя, номер выхода классификатора>
RDK::ULProperty<pair<double,int>, UCRClassifier,ptPubState>  QualityRate;

// Смаштабированные результаты вычислений
RDK::UCLProperty<vector<double>, UCRClassifier,ptPubState>  ScaledResult;

// Вывод о успешности распознавания
RDK::ULProperty<bool, UCRClassifier,ptPubState>  IsSuccessed;

protected: // Флаги состояний
RDK::ULProperty<bool, UCRClassifier,ptPubState>  ModifiedFlag;

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRClassifier(void);
virtual ~UCRClassifier(void);
// --------------------------


// ---------------------
// Методы счета
// ---------------------
/// Создание новой копии этого объекта
virtual UCRClassifier* New(void);
// ---------------------

protected:
// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
// Устанавливает число классов
bool SetNumClasses(const int &value);

// Устанавливает граничные величины входных значений классификатора
bool SetMinInputValue(const double &value);
bool SetMaxInputValue(const double &value);

// Устанавливает граничные величины выходных значений классификатора
bool SetMinOutputValue(const double &value);
bool SetMaxOutputValue(const double &value);

// Устанавливает граничные величины допустимого показателя качества
bool SetMinQualityRate(const vector<double>& value);
bool SetMaxQualityRate(const vector<double>& value);

// Имя файла загрузки/сохранения состояния обучения
bool SetTrainFileName(const string &name);

// Имя файла сохранения результатов работы сети
bool SetResultsFileName(const string &name);
// -----------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);
virtual bool ACRDefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ABuild(void);
virtual bool ACRBuild(void);

// Сброс процесса счета.
virtual bool AReset(void);
virtual bool ACRReset(void);

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACalculate(void);
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
// Методы обучения сети
// --------------------------
public:
// Сброс настроек обучения в исходное состояние
virtual void ResetTraining(void);
// --------------------------

// ------------------------
// Методы счета
// ------------------------
public:
// Загружает настройки из файла 'name'
virtual bool FileLoad(const string &name);
virtual bool AFileLoad(fstream &file);

// Сохраняет настройки в файл 'name'
virtual bool FileSave(const string &name);
virtual bool AFileSave(fstream &file);

// Устанавливает значения входного вектора для распознавания
//virtual bool SetInput(const Real &input)=0;
// ------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
protected:
// Сброс настроек обучения в исходное состояние
virtual void AResetTraining(void);
// --------------------------
};

}
#endif


