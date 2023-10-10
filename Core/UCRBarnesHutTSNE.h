#ifndef RDK_UCRBarnesHutTSNE_H
#define RDK_UCRBarnesHutTSNE_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#include <thread>


namespace RDK {
/// Компонент для сохранения результатов классификации

class RDK_LIB_TYPE UCRBarnesHutTSNE: virtual public RDK::UNet
{
protected: // Параметры

///Флаг переобучения, выставляется при ресете или управляющими компонентами, чтобы переобучить метод, если
/// поменялись какие-то параметры
/// Метод учится долго, так что переключать нужно с умом
ULProperty<bool, UCRBarnesHutTSNE> RetrainFlag;

///Число выходных компонент (от 0 до TrainingData.GetCols())
ULProperty<int, UCRBarnesHutTSNE> NumOutCoords;

/// Соответствующий параметр описан в статье
/// Не более чем число точек/3 согласно коду
ULProperty<double, UCRBarnesHutTSNE> Perplexity;

/// Соответствующий параметр описан в статье
ULProperty<double, UCRBarnesHutTSNE> Theta;

/// Максимальное число итераций метода подбора положений точек
ULProperty<int, UCRBarnesHutTSNE> MaxIterations;

/// Задать число инициализации ГСЧ для полной повторяемости эксперимента
/// Оставьте равным -1 для случайной инициализации
ULProperty<int, UCRBarnesHutTSNE> RandomSeed;


/// Задать число инициализации ГСЧ для полной повторяемости эксперимента
/// Оставьте равным -1 для случайной инициализации
ULProperty<int, UCRBarnesHutTSNE, ptPubState> CalcActive;
protected: // Входы и выходы

/// Входные вектора заданного размера
UPropertyInputData<MDMatrix<double>,UCRBarnesHutTSNE, ptPubInput> InputComponents;

/// Выходные вектора (все) после применения t-SNE
UPropertyOutputData<MDMatrix<double>,UCRBarnesHutTSNE, ptPubOutput> OutputComponents;


protected: // Переменные состояния

/// Матрица double - результат применения PCA
//UPropertyOutputData<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState | ptOutput> ...;

/// Матрица преобразования размерности (МхМ) и вектор собственных чисел (Мх1 правый столбец) в одном флаконе
//UPropertyOutputData<MDMatrix<double>, UCRBarnesHutTSNE, ptPubState> ...;

protected: // Временные переменные

bool TSNECalcInProcess;
float CalcProgress;

int N, D, no_dims, max_iter, rand_seed;
double perplexity, theta, *data;

int* landmarks;
double* Y;
double* costs;

std::thread *m_thread;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRBarnesHutTSNE(void);
virtual ~UCRBarnesHutTSNE(void);
// --------------------------

// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------


// ---------------------
// Методы управления переменными состояния
// ---------------------
// ---------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
virtual UCRBarnesHutTSNE* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------

virtual bool ACalculate(void);

virtual bool AReset(void);

bool RunTSNECalculation();
void TSNECalculationThread();
void UpdateCalculationState();

};

}
#endif



