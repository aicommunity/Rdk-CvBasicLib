//---------------------------------------------------------------------------

#ifndef CNFieldH
#define CNFieldH

#include <vector>
#include <string>
#include <list>
#include <map>
#include <cmath>
//#include "mysdk.h"
#include "CNeuron.h"

using namespace std;
using namespace RDK;

class CNLayer;
//class CNeuron;

class RDK_LIB_TYPE CNField: public UModule
{
protected: // Параметры
// Ширина поля нейронов
int WidthField;

// Высота поля нейронов
int HeightField;


//Шаг свертки
//int ConvolutionStep;

protected: // Данные
// Указатель на родительский слой
CNLayer* Owner;

public:
// Индекс этого поля
int FieldIndex;


// Нейроны
vector<vector<CNeuron> > Neurons;

protected: // Данные

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
CNField(void);
virtual ~CNField(void);
// --------------------------

// --------------------------
// Методы управления параметрами
// --------------------------
// Число нейронов поля
int GetWidthField(void) const;
int GetHeightField(void) const;
bool SetWidthField(int width);
bool SetHeightField(int height);

//Шаг свертки
//int GetConvolutionStep(void) const;
//bool SetConvolutionStep(int value);

// --------------------------

// --------------------------
// Методы управления данными
// --------------------------
// Возвращает ссылку на нейрон
CNeuron& GetNeuron(int i,int j);

// Указатель на родительский слой
CNLayer* GetOwner(void) const;
bool SetOwner(CNLayer* value);

// Принудительно задает значения выходов нейронов
bool SetOutput(vector<vector<double> > &output);
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

#endif
//---------------------------------------------------------------------------

