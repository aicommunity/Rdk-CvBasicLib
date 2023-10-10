#ifndef UCRTeacherPerseptronBP_H
#define UCRTeacherPerseptronBP_H

#include "UCRTeacher.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacherPerseptronBP: public UCRTeacher
{
public: // Параметры
// Момент сети
RDK::ULProperty<double, UCRTeacherPerseptronBP> Moment;

public:
// Указатель на персептрон
UPropertyInput<UCRPerseptron,UCRTeacherPerseptronBP> Perseptron;

public: // Переменные состояния


public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherPerseptronBP(void);
virtual ~UCRTeacherPerseptronBP(void);
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
bool SetMode(const int &value);

// Устанавливает момент сети
bool SetMoment(const double &m);
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
virtual UCRTeacherPerseptronBP* New(void);
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
