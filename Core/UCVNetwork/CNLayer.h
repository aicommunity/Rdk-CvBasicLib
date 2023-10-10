#ifndef CNLayerH
#define CNLayerH

#include <vector>
#include "CNField.h"

using namespace std;
//using namespace MySDK;

class CNetwork;


class RDK_LIB_TYPE CNLayer: public UModule
{
protected://параметры

//Число полей слоя
int NumFields;

// Флаг слоя
// 0 - сверточный слой
// 1 - субдескритизирующий слой
int LayerFlag;

// Размер окна свертки
int ConvWidth, ConvHeight;

// Шаг свертки
int ConvolutionStep;

// Размерность полей
int FieldWidth, FieldHeight;

protected: // Данные
// Указатель на слой- источник данных
CNLayer *SourceLayer;

// Указатель на сеть
CNetwork *Network;

// Поля
vector<CNField> Fields;

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
CNLayer(void);
virtual ~CNLayer(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число полей сети
int GetNumFields(void) const;
bool SetNumFields(int value);
// --------------------------
int GetLayerFlag(void) const;
bool SetLayerFlag(int value);
// --------------------------
int GetConvWidth(void) const;
int GetConvHeight(void) const;

bool SetConvWidth(int value);
bool SetConvHeight(int value);
// --------------------------
int GetConvolutionStep(void) const;
bool SetConvolutionStep(int value);
// --------------------------
int GetFieldWidth(void) const;
bool SetFieldWidth(int value);

int GetFieldHeight(void) const;
bool SetFieldHeight(int value);
// --------------------------
// Методы управления данными
// --------------------------
// Возвращает слой по индексу
CNField& GetField(int index);

// Указатель на слой- источник данных
CNLayer* GetSourceLayer(void);
bool SetSourceLayer(CNLayer *src);

// Указатель на Сеть
CNetwork* GetNetwork(void);
bool SetNetwork(CNetwork *src);
// --------------------------


// --------------------------
// Методы управления счетом
// --------------------------
// Сбрасывает веса всех нейронов в случайные значения
void ResetTrainig(void);
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
// --------------------------
};

//---------------------------------------------------------------------------
#endif
