#ifndef RDK_UCRPrincipalComponentAnalysis_H
#define RDK_UCRPrincipalComponentAnalysis_H
#include "../../../Rdk/Deploy/Include/rdk.h"

#define CLASS_UNDEFINED -2
#define CLASS_LOWQUAL -3

namespace RDK {
/// Компонент для сохранения результатов классификации

class RDK_LIB_TYPE UCRPrincipalComponentAnalysis: virtual public RDK::UNet
{
public: // Параметры

///Флаг переобучения, выставляется при ресете или управляющими компонентами, чтобы переобучить PCA если
/// поменялись какие-то параметры
ULProperty<bool, UCRPrincipalComponentAnalysis> RetrainFlag;

///Число выходных компонент (от 0 до TrainingData.GetCols())
ULProperty<int, UCRPrincipalComponentAnalysis> OutComponents;

protected: // Входы и выходы

/// Входная матрица со стандартизованными данными для обучения PCA
UPropertyInputData<MDMatrix<double>,UCRPrincipalComponentAnalysis, ptPubInput> TrainingData;

/// Входная строка для применения PCA, по ширине идентичная TrainingData
UPropertyInputData<MDMatrix<double>,UCRPrincipalComponentAnalysis, ptPubInput> EncodingData;


public: // Переменные состояния

/// Матрица double - результат применения PCA
UPropertyOutputData<MDMatrix<double>, UCRPrincipalComponentAnalysis, ptPubState | ptOutput> PCAResult;

/// Матрица преобразования размерности (МхМ) и вектор собственных чисел (Мх1 правый столбец) в одном флаконе
UPropertyOutputData<MDMatrix<double>, UCRPrincipalComponentAnalysis, ptPubState> PCA_X;

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRPrincipalComponentAnalysis(void);
virtual ~UCRPrincipalComponentAnalysis(void);
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
virtual UCRPrincipalComponentAnalysis* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------

virtual bool ACalculate(void);

virtual bool AReset(void);

bool TrainPCA(void);
bool ApplyPCA(void);
};

}
#endif



