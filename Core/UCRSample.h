// ===========================================================
// Version:        1.0.0
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2010.
E-mail:        alexab@ailab.ru
url:        http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UCRSampleH
#define UCRSampleH

#include "../../../Rdk/Deploy/Include/rdk.h"

//---------------------------------------------------------------------------
namespace RDK {

//using namespace RDK;

class RDK_LIB_TYPE UCRSample: public UNet
{
public: // Общедоступные свойства
// Тип выборки
// 0 - признаки
// 1 - сырые изображения
RDK::ULProperty<int, UCRSample> Type;

// Размер выходного вектора выборки
RDK::ULProperty<int, UCRSample> VectorSize;

// Ширина изображения выборки
RDK::ULProperty<int, UCRSample> SampleImageWidth;

// Высота изображения выборки
RDK::ULProperty<int, UCRSample> SampleImageHeight;

// Размер выборки
RDK::ULProperty<int, UCRSample,ptPubState> SampleSize;

// Список имен файлов выборки
RDK::UCLProperty<string, UCRSample> SampleFileName;

// Граничные величины входных значений данных выборки
RDK::ULProperty<double, UCRSample>  MinInputValue, MaxInputValue;

// Граничные величины выходных значений данных выборки
RDK::ULProperty<double, UCRSample>  MinOutputValue, MaxOutputValue;

// Флаг включения режима масштабирования выборки
RDK::ULProperty<bool, UCRSample>  ScaleFlag;

// Флаг отражения изображения по вертикали
RDK::ULProperty<bool, UCRSample>  ReflictionX;

// Режим работы
// 0 - Распознавание (входы объединяются в единый вектор выхода)
// 1 - Обучение (возвращается вектор выхода из обучающей базы)
// 2 - Распознавание с вручную заданных данных
RDK::ULProperty<int, UCRSample> Mode;

// Текущий элемент выборки
RDK::ULProperty<int, UCRSample,ptPubState> CurrentSample;

// Текущая итерация обхода выборки
RDK::ULProperty<int, UCRSample,ptPubState> CurrentSampleIteration;

// Число классов в выборке
RDK::ULProperty<int, UCRSample,ptPubState> NumClasses;


protected: // Данные состояний
// Массив выборки
vector<pair<RDK::UItemData,int> > SampleData;

// Массив выборки
vector<pair<RDK::UBitmap,int> > BitmapSampleData;

/// Заданные данные для подачи на выход
RDK::UItemData CurrentSampleData;

RDK::UBitmap CurrentBitmapSampleData;

public:
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UCRSample(void);
~UCRSample(void);
// --------------------------

// --------------------------
// Методы управления общедоступными свойствами
// --------------------------
// Текущий элемент выборки
bool SetCurrentSample(const int &value);

// Изменение размера выборки
bool SetSampleSize(const int &value);

// Изменение размера вектора выборки
bool SetVectorSize(const int &value);

// Имя файла выборки
bool SetSampleFileName(const string &value);
// --------------------------

// --------------------------
// Методы управления выборкой
// --------------------------
// Пополняет выборку текущим вектором входов
bool Add(int class_index);

// Пополняет выборку заданным вектором входов
bool Add(const vector<double> &data, int class_index);

// Удаляет заданный элемент вектора входов по индекссу
bool Del(size_t index);

// Очищает выборку
void Clear(void);

// Возвращает индекс класса текущего вектора обучающей выборки
int GetCurrentClassIndex(void) const;

// Возвращает массив обучающей выборки
virtual const vector<pair<RDK::UItemData,int> >& GetSampleData(void) const;
virtual const vector<pair<RDK::UBitmap,int> >& GetBitmapSampleData(void) const;

// Устанавливает как выход выборки данные изображения
virtual bool SetSampleData(const RDK::UBitmap &image);
RDK::UBitmap& GetCurrentBitmapSampleData(void);

// Загружает выборку как набор изображений по списку,
// лежащему в текстовом файле file_name
// Имена файлов должны быть вида xxxx_classindex.bmp
// Уже имеющиеся данные в выборке не будут изменены
bool LoadBitmapSample(const string &file_path);

// Загружает выборку как содержимое текстового файла
// каждая строка - один элемент выборки
// первое число в строке - индекс класса, остальные - данные вектора выборки
// разделитель: табуляция или пробел
// Уже имеющиеся данные в выборке не будут изменены
bool LoadTextSample(const string &file_name);
// --------------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
virtual UContainer* New(void);
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

// Выполняет расчет этого объекта на текущем шаге.
virtual bool ACalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif
