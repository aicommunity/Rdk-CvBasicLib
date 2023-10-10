/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBABackgroundH
#define UBABackgroundH
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

/// Базовый класс построения разнострого кадра
class RDK_LIB_TYPE UBABackground: public UNet
{
public: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBABackground> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBABackground> Background;

///Переменная, показывающая, закончился ли период накомпления фона
ULProperty<bool, UBABackground> IsBGReady;




public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackground(void);
virtual ~UBABackground(void);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool ADefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool ABuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AReset(void);

/// Выполняет расчет этого объекта
virtual bool ACalculate(void);
// --------------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};

/// Вычисляет простой разностный кадр
class RDK_LIB_TYPE UBABackgroundAvg: public UBABackground
{
protected: // Параметры
/// Размер истории в кадрах
ULProperty<int, UBABackgroundAvg> HistorySize;

protected: // Временные переменные
/// История фона
UBitmapVector History;

/// Текущий индекс в истории
int CurrentHistoryIndex;

/// Текущий реальный размер истории
int CurrentHistorySize;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBABackgroundAvg(void);
virtual ~UBABackgroundAvg(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBABackgroundAvg* New(void);

bool BCalculate(UBitmap &input, UBitmap &background);
// ---------------------

// --------------------------
// Скрытые методы управления счетом фильтров разностных кадров
// --------------------------
protected:
/// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFBgDefault(void);

/// Обеспечивает сборку внутренней структуры объекта
/// после настройки параметров
/// Автоматически вызывает метод Reset() и выставляет Ready в true
/// в случае успешной сборки
virtual bool AFBgBuild(void);

/// Сброс процесса счета без потери настроек
virtual bool AFBgReset(void);

/// Выполняет расчет этого объекта
virtual bool AFBgCalculate(void);
// --------------------------
};




/// Вычисляет кадр методом экспоненциального скользящего среднего
/// C темпом обновлени tempoUpdate
class RDK_LIB_TYPE UBABackgroundExponnential: public UBABackground
{
    /*protected: // Параметры
    /// Размер истории в кадрах
    int HistorySize;*/

    /// Текущий индекс в истории
    protected:
    int CurrentHistoryIndex;

    /// Текущий реальный размер истории
    int CurrentHistorySize;

    /// Темп обновления
    ULProperty<double, UBABackgroundExponnential> tempoUpdate;

    public: // Методы
    // ---------------------
    // Конструкторы и деструкторы
    // ---------------------
    UBABackgroundExponnential(void);
    virtual ~UBABackgroundExponnential(void);
    // ---------------------

    // ---------------------
    // Методы счета
    // ---------------------
    // Создание новой копии этого объекта
    virtual UBABackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
    // ---------------------

    // --------------------------
    // Скрытые методы управления счетом фильтров разностных кадров
    // --------------------------
    protected:
    /// Восстановление настроек по умолчанию и сброс процесса счета
    virtual bool AFBgDefault(void);

    /// Обеспечивает сборку внутренней структуры объекта
    /// после настройки параметров
    /// Автоматически вызывает метод Reset() и выставляет Ready в true
    /// в случае успешной сборки
    virtual bool AFBgBuild(void);

    /// Сброс процесса счета без потери настроек
    virtual bool AFBgReset(void);

    /// Выполняет расчет этого объекта
    virtual bool AFBgCalculate(void);
    // --------------------------
};

/// Вычисляет кадр методом экспоненциального скользящего среднего
/// C темпом обновлени tempoUpdate
/// И находит разницу в целочисленных и double вычислениях
/// Т.е 1. все ычиследния происходят в целых числах
/// 2. в double и округляются в конце
class RDK_LIB_TYPE UBADeltaBackgroundExponnential: public UBABackground
{

    /// Текущий индекс в истории
    protected:
    int CurrentHistoryIndex;

    /// Текущий реальный размер истории
    int CurrentHistorySize;

    /// Темп обновления
    ULProperty<double, UBADeltaBackgroundExponnential> tempoUpdate;

    public: // Методы
    // ---------------------
    // Конструкторы и деструкторы
    // ---------------------
    UBADeltaBackgroundExponnential(void);
    virtual ~UBADeltaBackgroundExponnential(void);
    // ---------------------

    // ---------------------
    // Методы счета
    // ---------------------
    // Создание новой копии этого объекта
    virtual UBADeltaBackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
    // ---------------------

    // --------------------------
    // Скрытые методы управления счетом фильтров разностных кадров
    // --------------------------
    protected:
    /// Восстановление настроек по умолчанию и сброс процесса счета
    virtual bool AFBgDefault(void);

    /// Обеспечивает сборку внутренней структуры объекта
    /// после настройки параметров
    /// Автоматически вызывает метод Reset() и выставляет Ready в true
    /// в случае успешной сборки
    virtual bool AFBgBuild(void);

    /// Сброс процесса счета без потери настроек
    virtual bool AFBgReset(void);

    /// Выполняет расчет этого объекта
    virtual bool AFBgCalculate(void);
    // --------------------------
};





///Адаптивное  изменение фона
///В зависимости от бинаризованного фона предыдущего кадра


class RDK_LIB_TYPE UBABackgroundSimpleAdaptive: public UBABackground
{

    /// Текущий индекс в истории
    protected:
    int CurrentHistoryIndex;

    /// Текущий реальный размер истории
    int CurrentHistorySize;

    /// Темп обновления фона
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdate;
    ///Темп обновления переднего плана
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdateFG;
    ///Темп обновления фона
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdateBG;
    ///Бинаризованный кадр предыдущий
    UPropertyInputData<UBitmap, UBABackgroundSimpleAdaptive> lastBinarization;
    ///Задержка интеграции
    ULProperty<unsigned int, UBABackgroundSimpleAdaptive> delay;
    //Индикатор стабильности
    //ULProperty<double, UBABackgroundSimpleAdaptive,ptPubState> UpdateFGFlag;
    ///Варианты работы фона
    ULProperty<int, UBABackgroundSimpleAdaptive> modeTypes;
    ///Предыдущий кадр
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> lastInput;
    ///Число которое определяет достаточно мало отличаются соседние кадры
    ULProperty<double, UBABackgroundSimpleAdaptive> deltaFrames;
    ///Индекаторы стабильности для каждого пикселя
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> updateFGFlag;
    ///Число, при котором обнуляется индикатор стабильности
    ULProperty<unsigned int, UBABackgroundSimpleAdaptive> zeroingUpdateFlag;
    ///Еще один выход фона
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> output2;
    ///количесво первых кадров, считающихся фоном
    ULProperty<int, UBABackgroundSimpleAdaptive> countFirstCleanBgFrame;
    ///счетчик того, что выше
    int nCounterBG;


    public: // Методы
    // ---------------------
    // Конструкторы и деструкторы
    // ---------------------
    UBABackgroundSimpleAdaptive(void);
    virtual ~UBABackgroundSimpleAdaptive(void);
    // ---------------------

    // ---------------------
    // Методы счета
    // ---------------------
    // Создание новой копии этого объекта
    virtual UBABackgroundSimpleAdaptive* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateSimplAdaptive(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateExp(UBitmap &input, UBitmap &background);
    bool BCalculateStabilityIndicator(UBitmap &input, UBitmap &background, UBitmap &lastBinarization, UBitmap &lastInput, UBitmap &updateFGFlag);
    //Вычисление фона по первым countFirstCleanBgFrame кадрам
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);

    // ---------------------
    // --------------------------
    // Скрытые методы управления счетом фильтров разностных кадров
    // --------------------------
    protected:
    /// Восстановление настроек по умолчанию и сброс процесса счета
    virtual bool AFBgDefault(void);

    /// Обеспечивает сборку внутренней структуры объекта
    /// после настройки параметров
    /// Автоматически вызывает метод Reset() и выставляет Ready в true
    /// в случае успешной сборки
    virtual bool AFBgBuild(void);

    /// Сброс процесса счета без потери настроек
    virtual bool AFBgReset(void);

    /// Выполняет расчет этого объекта
    virtual bool AFBgCalculate(void);
    // --------------------------
};


//------------------------------------------------------------------------
// Фон в зависимоти от текущего дельта между фоном и текущим кадром
//------------------------------------------------------------------------




class RDK_LIB_TYPE UBABackgroundDependDiff: public UBABackground
{

    protected:

    /// Темп обновления фона
    //ULProperty<double, UBABackgroundDependDiff> StateTempoDif;
    ///Бинаризованный кадр предыдущий
    UPropertyInputData<UBitmap, UBABackgroundDependDiff> deltaImg;
    ///количесво первых кадров, считающихся фоном
    ULProperty<int, UBABackgroundDependDiff> countFirstCleanBgFrame;
    ///счетчик того, что выше
    int nCounterBG;




    public: // Методы
    // ---------------------
    // Конструкторы и деструкторы
    // ---------------------
    UBABackgroundDependDiff(void);
    virtual ~UBABackgroundDependDiff(void);
    // ---------------------

    // ---------------------
    // Методы счета
    // ---------------------
    // Создание новой копии этого объекта
    virtual UBABackgroundDependDiff* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    double BCalculate1(UBitmap &input, UBitmap &background, UBitmap &delta);
    //Вычисление фона по первым countFirstCleanBgFrame кадрам
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);


    // ---------------------
    // --------------------------
    // Скрытые методы управления счетом фильтров разностных кадров
    // --------------------------
    protected:
    /// Восстановление настроек по умолчанию и сброс процесса счета
    virtual bool AFBgDefault(void);

    /// Обеспечивает сборку внутренней структуры объекта
    /// после настройки параметров
    /// Автоматически вызывает метод Reset() и выставляет Ready в true
    /// в случае успешной сборки
    virtual bool AFBgBuild(void);

    /// Сброс процесса счета без потери настроек
    virtual bool AFBgReset(void);

    /// Выполняет расчет этого объекта
    virtual bool AFBgCalculate(void);
    // --------------------------
};





}
//---------------------------------------------------------------------------
#endif

