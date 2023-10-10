#ifndef UCRTeacher_H
#define UCRTeacher_H

//#include "../../UNet.h"
#include "UCRClassifier.h"
#include "UCRSample.h"
#include "UCRPerseptron.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacher: public UNet
{
public: // Параметры
// Максимально допустимая ошибка обучения
RDK::ULProperty<double, UCRTeacher>  TrainEpsilon;

// Устанавливает предельное число шагов обучения
RDK::ULProperty<size_t, UCRTeacher>  TrainMaxStepsNum;

// Скорость обучения
RDK::ULProperty<double, UCRTeacher> TrainingRate;

// 0 - распознавание
// 1 - обучение
// далее - уровни обучения в зависимости от учителя
ULProperty<int,UCRTeacher> Mode;

public:
// Указатель на обучающую выборку
UPropertyInput<UCRSample,UCRTeacher> TrainSample;

// Указатель на тестовую выборку
UPropertyInput<UCRSample,UCRTeacher> TestSample;

// Указатель на выборку кроссвалидации
UPropertyInput<UCRSample,UCRTeacher> CrossValidationSample;

// Указатель на классификатор
UPropertyInput<UCRClassifier,UCRTeacher> Classifier;


public: // Переменные состояния
ULProperty<int,UCRTeacher,ptPubState> CurrentSampleIteration;

// Ошибка обучения
RDK::ULProperty<double, UCRTeacher,ptPubState>  TrainingError;

// Ошибка обучения
RDK::UPropertyOutputData<MDMatrix<double>, UCRTeacher>  MatrixTrainingError;


public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacher(void);
virtual ~UCRTeacher(void);
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
public:
// -----------------------------

protected:
// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
virtual bool SetMode(const int &value);

// Устанавливает скорость обучения сети
bool SetTrainingRate(const double &tr);

// Устанавливает максимально допустимую ошибку обучения
bool SetTrainEpsilon(const double &eps);

// Устанавливает предельное число шагов обучения
bool SetTrainMaxStepsNum(const size_t &lmaxsteps);
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
//virtual UCRTeacher* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);
virtual bool ACrDefault(void)=0;

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ABuild(void);
virtual bool ACrBuild(void)=0;

// Сброс процесса счета.
virtual bool AReset(void);
virtual bool ACrReset(void)=0;

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACalculate(void);
virtual bool ACrCalculate(void)=0;
// --------------------------

// --------------------------
// Методы обучения сети
// --------------------------
public:
// Сброс настроек обучение в исходное состояние
virtual void ResetTraining(void);
virtual void ACrResetTraining(void)=0;

// Итерация обучения
virtual void Train(void);

// Собственно выполнение алгоритма обучения
virtual double TrainStep(size_t exp_class);
virtual double ACrTrainStep(size_t exp_class)=0;

// Завершающие действия при завершении текущего обхода выборки
virtual void SampleIterationCompleteAction(void);
virtual void ACrSampleIterationCompleteAction(void)=0;
// --------------------------
};

}
#endif
