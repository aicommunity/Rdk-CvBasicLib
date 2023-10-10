/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2013.
E-mail:        alexab@ailab.ru
Url:           http://ailab.ru

This file is part of the project: RDK

File License:       New BSD License
Project License:    New BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UBABinarizationH
#define UBABinarizationH
#include "../../../Rdk/Deploy/Include/rdk.h"


namespace RDK {

/// ������� ����� ���������� ����������� �����
class RDK_LIB_TYPE UBABinarization: public UNet
{
public: // ������� � �������� ������
/// ������� �����������
UPropertyInputData<UBitmap, UBABinarization> Input;

/// �������� �����������
UPropertyOutputData<UBitmap, UBABinarization> Output;


public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarization(void);
virtual ~UBABinarization(void);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ ��������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool ABuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AReset(void);

/// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFBgDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBgBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFBgReset(void);

/// ��������� ������ ����� �������
virtual bool AFBgCalculate(void);
// --------------------------
};

/// ��������� ������� ���������� ����
class RDK_LIB_TYPE UBABinarizationSimple: public UBABinarization
{
protected: // ���������
/// ����� �� �������
ULProperty<UColorT, UBABinarizationSimple> Threshold;

protected: // ��������� ����������

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarizationSimple(void);
virtual ~UBABinarizationSimple(void);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBABinarizationSimple* New(void);

bool BCalculate(UBitmap &input, UBitmap &output);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFBgDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBgBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFBgReset(void);

/// ��������� ������ ����� �������
virtual bool AFBgCalculate(void);
// --------------------------
};



//----------------------------------------------------------------------------
///������� ���������� ���� � ���������� ������� ������
///
//----------------------------------------------------------------------------

class RDK_LIB_TYPE UBABinarizationSimpleAdaptiveThreshold: public UBABinarization
{
protected: // ���������
/// ����� �� �������
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Threshold;

///���
UPropertyInputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Background;

ULProperty<double, UBABinarizationSimpleAdaptiveThreshold> KAlpha;
ULProperty<double, UBABinarizationSimpleAdaptiveThreshold> KGamma;

///��������� ��������� �������, ��� �������� ��� ������� ����������� ������ 1
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> startThreshold;

UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> counterFG;

ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> stableBGflag;

///�������� ������ ������������
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> modeTypes;

UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> counterBG;

ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> unstableFlag;

///����� ��� ����-�� �������
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> Threshold2;
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> output2;

///����������� ��������� ����� �  �������
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> maxDinamThreshold;

///��������������� �����
UPropertyOutputData<UBitmap, UBABinarizationSimpleAdaptiveThreshold> invThreshold;

///���������� �� ����, ����� ��������� ������ �������� ����� � ����
/// �������� � ��������� 0-1, 1-2... 13-14, >14.
std::vector<double> ThresholdStats;

///��������� ������ ������, ����������� �����
ULProperty<int, UBABinarizationSimpleAdaptiveThreshold> countFirstCleanBgFrame;

///������� ��������������� ��������� ������
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> firstThTypes;

///���������� ��������� ����� �  �������
ULProperty<unsigned char, UBABinarizationSimpleAdaptiveThreshold> minDinamThreshold;

///������� ����, ��� ���� ����
int nCounter;

protected: // ��������� ����������

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarizationSimpleAdaptiveThreshold(void);
virtual ~UBABinarizationSimpleAdaptiveThreshold(void);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBABinarizationSimpleAdaptiveThreshold* New(void);

bool BCalculate0(UBitmap &Background, UBitmap &input, UBitmap &output);
bool BCalculate1(UBitmap &Background, UBitmap &input, UBitmap &Threshold, UBitmap &output, UBitmap &counterFG);
bool BCalculate2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
///������� ������
bool BCalculate3(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                 UBitmap &output, UBitmap &counterFG,UBitmap &counterBG);
///�������� ����� �� ���� countFirstCleanBgFrame ������ ��������
bool BCalculateFirstThreshold1(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
///������������ ����� �� ���� countFirstCleanBgFrame ������ ��������
bool BCalculateFirstThreshold2(UBitmap &Background, UBitmap &input, UBitmap &Threshold,
                               UBitmap &output);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFBgDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBgBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFBgReset(void);

/// ��������� ������ ����� �������
virtual bool AFBgCalculate(void);
// --------------------------
};




//----------------------------------------------------------------------------
///��������� ���� � ������� ������ ���
//----------------------------------------------------------------------------
class RDK_LIB_TYPE UBABinarizationOtsu: public UBABinarization
{
protected: // ���������
//����������� �����, ����� ����� �� ��� ��� �� ��������
ULProperty<int, UBABinarizationOtsu> minThreshold;
///���� �������� - �����
UPropertyInputData<UBitmap, UBABinarizationOtsu> Mask;


//int minThreshold;
// ����� �� �������
//ULProperty<UColorT, UBABinarizationSimple> Threshold;

protected: // ��������� ����������

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABinarizationOtsu(void);
virtual ~UBABinarizationOtsu(void);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBABinarizationOtsu* New(void);

bool BCalculate(UBitmap &input, UBitmap &output, UBitmap &mask);
// ---------------------

// --------------------------
// ������� ������ ���������� ������ �������� ���������� ������
// --------------------------
protected:
/// �������������� �������� �� ��������� � ����� �������� �����
virtual bool AFBgDefault(void);

/// ������������ ������ ���������� ��������� �������
/// ����� ��������� ����������
/// ������������� �������� ����� Reset() � ���������� Ready � true
/// � ������ �������� ������
virtual bool AFBgBuild(void);

/// ����� �������� ����� ��� ������ ��������
virtual bool AFBgReset(void);

/// ��������� ������ ����� �������
virtual bool AFBgCalculate(void);
// --------------------------
};


}
//---------------------------------------------------------------------------
#endif

