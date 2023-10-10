/* ***********************************************************
@Copyright Alexsandr V. Bakhshiev, 2011.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */
#ifndef UBAObjectDetectorH
#define UBAObjectDetectorH

#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

// ������� ����� ��������������� �����������
class RDK_LIB_TYPE UBAObjectDetector
{
public:
// ��� ����������
struct Rect { int X,Y,Width,Height; };

public: // ������
// ---------------------
// ������ �����
// ---------------------
virtual bool Calculate(const UBitmap& input, Rect* objects)=0;
// ---------------------

// ---------------------
// ���������
// ---------------------
bool operator () (const UBitmap& input, Rect* objects);
// ---------------------
};

// ����� �������� � ������ ��������
// �������� ���� �� ������
// "A real-time object detecting and tracking system for outdoor night surveillance"
// Kaiqi Huang, Liangsheng Wang, Tieniu Tan, Steve Maybank
class RDK_LIB_TYPE UBANightDetector: public UBAObjectDetector
{
public: // ���������
// ����� ����������� � �������
int HistorySize;

// ������ ����� �����������
int BlockWidth, BlockHeight;

// ������� ���������� ����������� ������
double AdaptiveThresholdPercent;

// ������� ��������, ����������� ���������� �����,
// ������ �����������
double MoveDetectionPercent;

// ������
double T1;

// ����������� ���������� ����� �������
double Tr;

protected: // ������
// ������ �����
int MapWidth, MapHeight;



protected: // ����� ��������� ����������
// ������� ������� �����������
const UBitmap* Input;

// ������ �����������
int Width,Height;

// ������������ �����������
UBitmap* LocalContrastedImages;

// ������� ������ �������
int CurrentHistorySize;

// ������� ������ ���� �������
int CurrentFirstHistoryIndex;

public: // ��������� ���������� ��� ���������� ���������� ���������
// ����� ������
int NumBlocks;

// ������ ��������� ����������
double* CL;

// ������ �������
double* ML;

// ������ ���
double* SigmaL;

protected: // ��������� ���������� ��� ���������� ����� ��������� �����������
// ����� ��������� �����
int NumMaps;

// ������ �����
double* MCm;
double* ICm;

// ����������� ����������� �����
UBitmap DiffImage;

// ����������� � ������������ ���������� ��������
UBitmap MovedImage;

// ����� ������ ����� ������ ���������
double* T;
double TT;

public:
// �����������
UBHistogram Histogram;

// ����� ����������� ��������
UBRect* ContrastGrid;

// ����� ���������� ��������
UBRect* MovedGrid;



protected: // ��������� ���������� ��� ����������� ���������� ��������
NCC2D Correlation;

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UBANightDetector(void);
~UBANightDetector(void);
// --------------------------

// --------------------------
// ������ ���������� �����������
// --------------------------
// ����� ����������� � �������
int GetHistorySize(void) const;
bool SetHistorySize(int value);
// --------------------------

// --------------------------
// ������ ������� � ������
// --------------------------
// ����������� � ������������ ���������� ��������
const UBitmap& GetMovedImage(void) const;
// --------------------------

// ---------------------
// ������ �����
// ---------------------
bool Calculate(const UBitmap& input, Rect* objects);
// ---------------------

// ---------------------
// ������� ������ �����
// ---------------------
protected:
// ���������� ���������� ���������
bool CalcLocalContrasting(void);

// ���������� ����� ��������� �����������
bool CalcLocalMap(void);

// ����������� ���������� ��������
bool CalcMovedObjects(void);

// ������ ����������� ������
bool CalcAdaptiveThreshold(void);
// ---------------------
};


}

#endif
