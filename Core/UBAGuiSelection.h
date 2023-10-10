#ifndef UBAGuiSelectionH
#define UBAGuiSelectionH

#include "../../../Rdk/Deploy/Include/rdk.h"


struct RDK_LIB_TYPE StateTMouse
{
 int Previous, Current;
};

namespace RDK {


//Класс состояния мыши
class RDK_LIB_TYPE UMouse
{
public: // Параметры
int X_mouse, Y_mouse;

// количество нажатий мыши
int NumClickes;

StateTMouse LeftClickMouse, RightClickMouse;

public:
UMouse(void);
virtual ~UMouse(void);

// ---------------------
// Методы управления параметрами
// ---------------------
bool SetDecartMouse(int x, int y);
int GetX_Mouse(void);
int GetY_Mouse(void);
// ---------------------

// ---------------------
//методы управления кнопками мыши(on/off)
// ---------------------
//значение может быть либо 0, либо 1
//1 - кнопка нажата
//0 - кнопка не нажата
bool SetModeLCMouse(int click);
bool SetModeRCMouse(int click);

StateTMouse GetModeLCMouse(void);
StateTMouse GetModeRCMouse(void);
// ---------------------
};

/// Класс выделения области изображения пользователем.
class RDK_LIB_TYPE UBAGuiSelection: public UNet
{
protected: // Входные и выходные данные
/// Входное изображение
UPropertyInputData<UBitmap, UBAGuiSelection> Input;

/// Выходное изображение
UPropertyOutputData<UBitmap, UBAGuiSelection> Output;

public: // Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UBAGuiSelection(void);
virtual ~UBAGuiSelection(void);
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

// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFCDefault(void)=0;

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool AFCBuild(void)=0;

// Сброс процесса счета.
virtual bool AFCReset(void)=0;

// Выполняет расчет этого объекта
virtual bool AFCCalculate(void)=0;
// --------------------------
};

class RDK_LIB_TYPE UBAGuiSelectionRect: public UBAGuiSelection
{
protected: // Параметры
UGraphics Graphics;
public:
UMouse MouseState;

int CurrentX, CurrentY, PreviousX, PreviousY, IWidth, IHeight, TIWidth, TIHeight;

public: // Методы
// ---------------------
// Конструкторы и деструкторы
// ---------------------
UBAGuiSelectionRect(void);
virtual ~UBAGuiSelectionRect(void);
// ---------------------

// ---------------------
// Методы счета
// ---------------------
// Создание новой копии этого объекта
virtual UBAGuiSelectionRect* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);

// Находим параметры входного изображения
bool SetImageParams(int width , int height);
int GetIWidth(void);
int GetIHeight(void);

//Находим параметры области, где у нас находится изображение
bool SetTImageParamsWH(int wight, int height);
int GetTIWidth(void);
int GetTIHeight(void);

// Методы управления параметрами
bool SetDecartPrevious(int x, int y);
bool SetDecartCurrent(int x, int y);

int GetRectangleXCurr(void);
int GetRectangleYCurr(void);
int GetRectangleXPrev(void);
int GetRectangleYPrev(void);

bool SetDecartFromMousUse(void);
// ---------------------


// --------------------------
// Скрытые методы управления счетом трекинга
// --------------------------
protected:
// Восстановление настроек по умолчанию и сброс процесса счета
virtual bool AFCDefault(void);

// Обеспечивает сборку внутренней структуры объекта
// после настройки параметров
// Автоматически вызывает метод Reset() и выставляет Ready в true
// в случае успешной сборки
virtual bool AFCBuild(void);

// Сброс процесса счета.
virtual bool AFCReset(void);

// Выполняет расчет этого объекта
virtual bool AFCCalculate(void);
// --------------------------
};

}
//---------------------------------------------------------------------------
#endif