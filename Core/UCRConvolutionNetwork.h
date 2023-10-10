#ifndef UCR_CONVOLUTION_NETWORK_H
#define UCR_CONVOLUTION_NETWORK_H

#include "UCRClassifier.h"
#include "UCVNetwork/CNetwork.h"

namespace RDK{
class RDK_LIB_TYPE UCRConvolutionNetwork : public UCRClassifier
{
public: // Общедоступные свойства
// Имя файла сохранения результатов работы сети
// RDK::ULProperty<string, UCRClassifier>  ResultsFileName;

protected: // Данные
// Сверточная нейронная сеть
CNetwork CVNetwork;

protected: // Данные и параметры обучения сети

protected: // Временные переменные

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRConvolutionNetwork(void);
virtual ~UCRConvolutionNetwork(void);
// --------------------------

// -----------------------------
// Методы доступа к данным модели
// -----------------------------
public:
// Доступ к сети
CNetwork& GetNetwork(void);
// Вектор выборки
//double GetSamples(int i, int j, int k) const;

// --------------------------
// Методы управления параметрами
// --------------------------
// Число слоев сети
const int& GetNetworkNumLayers(void) const;
bool SetNetworkNumLayers(const int& value);

// Шаг ядра свертки для каждого слоя
const vector<int>& GetNetworkConvStep(void) const;
bool SetNetworkConvStep(const vector<int>& value);

// Высота ядра свертки для каждого слоя
const vector<int>& GetNetworkConvHeight(void) const;
bool SetNetworkConvHeight(const vector<int>& value);

// Ширина ядра свертки для каждого слоя
const vector<int>& GetNetworkConvWidth(void) const;
bool SetNetworkConvWidth(const vector<int>& value);

// Числое полей нейронов для каждого слоя
const vector<int>& GetNetworkNumFields(void) const;
bool SetNetworkNumFields(const vector<int>& value);

// Параметр скорости обучения
const double& GetNetworkEta(void) const;
//bool SetNetworkEta(const double &value);
// Порядок весовых коэффициентов сети
const double& GetNetworkDegWeights(void) const;
bool SetNetworkDegWeights(const double& value);

// Размеры входного изображения
const int& GetInputWidth(void) const;
bool SetInputWidth(const int& value);

const int& GetInputHeight(void) const;
bool SetInputHeight(const int& value);

// --------------------------
// Методы управления данными
// --------------------------
// Преобразовывает входной вектор в матрицу входа и загружает в нулевой слой сети
bool LoadInputData(double *input, int size);

// Преобразовывает выходной слой полей нейронов сети в выходной вектор
vector<double> ConversionOutputData(int size);

//bool LoadImage(const string &file_name);
//double ScaleImage(double a, double b, double m, double n, double data);
// ------------------------
// Методы счета
// ------------------------
public:
// Загружает настройки весов из файла с именем 'name'
virtual bool AFileLoad(fstream &file);

// Сохраняет настройки весов в файл с именем 'name'
virtual bool AFileSave(fstream &file);
// ------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
virtual UCRConvolutionNetwork* New(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ACRDefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool ACRBuild(void);

// Сброс процесса счета.
virtual bool ACRReset(void);

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
// Скрытые методы обучения сети
// --------------------------
protected:
// Сброс настроек обучение в исходное состояние
virtual void AResetTraining(void);

public:
// Однократное обучение на заданном примере
virtual double Train(size_t exp_class);
// --------------------------

};


}


#endif
