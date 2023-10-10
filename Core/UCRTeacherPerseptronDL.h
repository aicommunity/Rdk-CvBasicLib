#ifndef UCRTeacherPerseptronDL_H
#define UCRTeacherPerseptronDL_H

#include "UCRTeacher.h"

namespace RDK {

class RDK_LIB_TYPE UCRTeacherPerseptronDL: public UCRTeacher
{
public: // Параметры
// Mode
// 0 - распознавание
// 1 - Первый уровень обучения
// 2 - Второй уровень обучения

public:
// Указатель на глубоко обученный персептрон
UPropertyInput<UCRPerseptron,UCRTeacherPerseptronDL> DeepPerseptron;

public: // Переменные состояния
ULProperty<double,UCRTeacherPerseptronDL,ptPubState> dW;
ULProperty<double,UCRTeacherPerseptronDL,ptPubState> dB;
ULProperty<double,UCRTeacherPerseptronDL,ptPubState> dC;

double Temp_dW;
double Temp_dB;
double Temp_dC;

int WCount, CCount, BCount;

vector<double> x1;
vector<double> Q;
vector<double> h1;
vector<double> P;
vector<double> x2;
vector<double> Q2;

// Вектор смещений входного слоя
vector<double> Fi;


public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRTeacherPerseptronDL(void);
virtual ~UCRTeacherPerseptronDL(void);
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
virtual UCRTeacherPerseptronDL* New(void);
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

// Создание нового слоя для обучения
// Подготоваливает алгоритм к обучению этого слоя и
// возвращает индекс созданного слоя
virtual int Train1CreateLayer(void);

// Вычисляет оценку обучения этапа 1
virtual double CalcTrain1Estimation(void);
// --------------------------
};

}
#endif
