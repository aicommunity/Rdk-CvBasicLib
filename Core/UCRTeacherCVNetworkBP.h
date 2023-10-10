#ifndef UCR_TEACHER_CVNETWORK_BP_H
#define UCR_TEACHER_CVNETWORK_BP_H

#include "UCRTeacher.h"
#include "UCRConvolutionNetwork.h"

namespace RDK{

class RDK_LIB_TYPE UCRTeacherCVNetworkBP : public UCRTeacher
{
public: // Параметры
// Момент сети
//DK::ULProperty<double, UCRTeacherPerseptronBP> Moment;

public:
// Указатель на сверточную сеть
UPropertyInput<UCRConvolutionNetwork,UCRTeacherCVNetworkBP> Network;

//UPropertyOutputData<MDMatrix<double>,UCRConvolutionNetwork, ptPubOutput | ptState> TrainErrorResult;
//UEPtr<UCRConvolutionNetwork> Network;

public: // Переменные состояния

protected: // Данные
// Флаг состояния обучения в зависимости от значения TrainingError
// 1 - обучение завершено
// 0 - обучение не завершено
int TrainingEndingFlag;

// Ошибки первого и второго рода
double Err1, Err2;

// Процент правильного принятия решения
double SuccessRecognition;

// Условие завершения обучения (костыль)
int TrainingUsl;

public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherCVNetworkBP(void);
virtual ~UCRTeacherCVNetworkBP(void);
// --------------------------

// -----------------------------
// Методы доступа к данным
// -----------------------------
public:
// -----------------------------
//bool SetTrainingEndingFlag(const int &value);
virtual const int& GetTrainingEndingFlag(void) const;

// Доступ к ошибкам первого и второго рода
virtual const double& GetErr1(void) const;
virtual const double& GetErr2(void) const;

// Процент правильного принятия решения
const double& GetSuccessRecognition(void) const;

protected:
// -----------------------------
// Методы управления общедоступными свойствами
// -----------------------------
//bool SetMode(const int &value);

// Устанавливает момент сети
//bool SetMoment(const double &m);
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
virtual UCRTeacherCVNetworkBP* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ACrDefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ACrBuild(void);

// Сброс процесса счета.
virtual bool ACrReset(void);

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACrCalculate(void);
// --------------------------

// --------------------------
// Методы обучения сети
// --------------------------
public:
// Сброс настроек обучение в исходное состояние
virtual void ACrResetTraining(void);

// Собственно выполнение алгоритма обучения
virtual double ACrTrainStep(size_t exp_class);

// Завершающие действия при завершении текущего обхода выборки
virtual void ACrSampleIterationCompleteAction(void);
// --------------------------


};



}


#endif
