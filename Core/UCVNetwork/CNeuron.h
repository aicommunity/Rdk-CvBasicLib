#ifndef CNEURON_H
#define CNEURON_H

#include <vector>
//#include "mysdk.h"
#include "../../../../Rdk/Deploy/Include/rdk.h"

using namespace std;
using namespace RDK;

class CNField;
class CNetwork;

struct RDK_LIB_TYPE CNeuronCoord
{
 int field, x, y;
};

class RDK_LIB_TYPE CNeuron: public UModule
{
friend class CNField;
friend class CNetwork;
protected: // Параметры
// Параметры функции активации
double ActA, ActB;

// Число полей источников данных
int NumSourceField;

// Координаты рецептивной зоны
int X, Y, Width, Height; //width и height константы - ядро свертки



protected: // Данные
// Указатель на родительскую сеть
CNetwork* NetworkOwner;

// Указатель на поле-источник данных
vector<CNField*> SourceField;

// Выход нейрона
double Output;

// Вход нейрона
double Input;

// Веса
vector<vector<vector<double> > > Weights;

public:
// Предыдущие веса
vector<vector<vector<double> > > PrevWeights;

// Дельта нейрона
//vector<vector<vector<double> > > Delta;
double Delta;

// Массив индексов нейронов, подключенных входами к выходу этого нейрона
vector<CNeuronCoord> ConnectedNeurons;

public: // Методы

// --------------------------
// Конструкторы и деструкторы
// --------------------------
CNeuron(void);
virtual ~CNeuron(void);
// --------------------------


// --------------------------
// Методы управления параметрами
// --------------------------
// Число слоев источников данных
int GetNumSourceField(void) const;
bool SetNumSourceField(int value);

// Координаты рецептивной зоны
int GetX(void) const;
bool SetX(int value);
int GetY(void) const;
bool SetY(int value);
int GetWidth(void) const;
bool SetWidth(int value);
int GetHeight(void) const;
bool SetHeight(int value);
// --------------------------


// Функция активации
double ActivationFunc(double x);

// Производная функции активации по аргументу
double dActivationFunc(double x);

// Выход нейрона
double GetOutput(void) const;
bool SetOutput(double value);

//Вход нейрона
double GetInput(void) const;
bool SetInput(double value);

// Возвращает выход нейрона, подключенного к этому по заданному входу
double GetInputData(int field, int x, int y) const;

// Сбрасывает веса нейрона в случайные значения
void ResetTrainig(void);

//Принудительное назначение весов
bool SetWeights(vector<vector<vector<double> > > weights);

// Доступ к массиву весов
vector<vector<vector<double> > >& GetWeights(void);

// Возвращает число нейронов подключенных входами к выходу этого нейрона
size_t GetNumConnectedNeurons(void) const;

// Возвращает нейрон подключенный входами к выходу этого нейрона
CNeuronCoord& GetConnectedNeuron(size_t index);

// --------------------------
// Методы управления данными
// --------------------------
// Указатель на родительскую сеть
CNetwork* GetNetworkOwner(void) const;
bool SetNetworkOwner(CNetwork* value);

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
