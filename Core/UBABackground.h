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

/// ������� ����� ���������� ����������� �����
class RDK_LIB_TYPE UBABackground: public UNet
{
public: // ������� � �������� ������
/// ������� �����������
UPropertyInputData<UBitmap, UBABackground> Input;

/// �������� �����������
UPropertyOutputData<UBitmap, UBABackground> Background;

///����������, ������������, ���������� �� ������ ����������� ����
ULProperty<bool, UBABackground> IsBGReady;




public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABackground(void);
virtual ~UBABackground(void);
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
class RDK_LIB_TYPE UBABackgroundAvg: public UBABackground
{
protected: // ���������
/// ������ ������� � ������
ULProperty<int, UBABackgroundAvg> HistorySize;

protected: // ��������� ����������
/// ������� ����
UBitmapVector History;

/// ������� ������ � �������
int CurrentHistoryIndex;

/// ������� �������� ������ �������
int CurrentHistorySize;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBABackgroundAvg(void);
virtual ~UBABackgroundAvg(void);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
// �������� ����� ����� ����� �������
virtual UBABackgroundAvg* New(void);

bool BCalculate(UBitmap &input, UBitmap &background);
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




/// ��������� ���� ������� ����������������� ����������� ��������
/// C ������ ��������� tempoUpdate
class RDK_LIB_TYPE UBABackgroundExponnential: public UBABackground
{
    /*protected: // ���������
    /// ������ ������� � ������
    int HistorySize;*/

    /// ������� ������ � �������
    protected:
    int CurrentHistoryIndex;

    /// ������� �������� ������ �������
    int CurrentHistorySize;

    /// ���� ����������
    ULProperty<double, UBABackgroundExponnential> tempoUpdate;

    public: // ������
    // ---------------------
    // ������������ � �����������
    // ---------------------
    UBABackgroundExponnential(void);
    virtual ~UBABackgroundExponnential(void);
    // ---------------------

    // ---------------------
    // ������ �����
    // ---------------------
    // �������� ����� ����� ����� �������
    virtual UBABackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
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

/// ��������� ���� ������� ����������������� ����������� ��������
/// C ������ ��������� tempoUpdate
/// � ������� ������� � ������������� � double �����������
/// �.� 1. ��� ���������� ���������� � ����� ������
/// 2. � double � ����������� � �����
class RDK_LIB_TYPE UBADeltaBackgroundExponnential: public UBABackground
{

    /// ������� ������ � �������
    protected:
    int CurrentHistoryIndex;

    /// ������� �������� ������ �������
    int CurrentHistorySize;

    /// ���� ����������
    ULProperty<double, UBADeltaBackgroundExponnential> tempoUpdate;

    public: // ������
    // ---------------------
    // ������������ � �����������
    // ---------------------
    UBADeltaBackgroundExponnential(void);
    virtual ~UBADeltaBackgroundExponnential(void);
    // ---------------------

    // ---------------------
    // ������ �����
    // ---------------------
    // �������� ����� ����� ����� �������
    virtual UBADeltaBackgroundExponnential* New(void);

    bool BCalculate(UBitmap &input, UBitmap &background);
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





///����������  ��������� ����
///� ����������� �� ��������������� ���� ����������� �����


class RDK_LIB_TYPE UBABackgroundSimpleAdaptive: public UBABackground
{

    /// ������� ������ � �������
    protected:
    int CurrentHistoryIndex;

    /// ������� �������� ������ �������
    int CurrentHistorySize;

    /// ���� ���������� ����
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdate;
    ///���� ���������� ��������� �����
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdateFG;
    ///���� ���������� ����
    ULProperty<double, UBABackgroundSimpleAdaptive> tempoUpdateBG;
    ///�������������� ���� ����������
    UPropertyInputData<UBitmap, UBABackgroundSimpleAdaptive> lastBinarization;
    ///�������� ����������
    ULProperty<unsigned int, UBABackgroundSimpleAdaptive> delay;
    //��������� ������������
    //ULProperty<double, UBABackgroundSimpleAdaptive,ptPubState> UpdateFGFlag;
    ///�������� ������ ����
    ULProperty<int, UBABackgroundSimpleAdaptive> modeTypes;
    ///���������� ����
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> lastInput;
    ///����� ������� ���������� ���������� ���� ���������� �������� �����
    ULProperty<double, UBABackgroundSimpleAdaptive> deltaFrames;
    ///���������� ������������ ��� ������� �������
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> updateFGFlag;
    ///�����, ��� ������� ���������� ��������� ������������
    ULProperty<unsigned int, UBABackgroundSimpleAdaptive> zeroingUpdateFlag;
    ///��� ���� ����� ����
    UPropertyOutputData<UBitmap, UBABackgroundSimpleAdaptive> output2;
    ///��������� ������ ������, ����������� �����
    ULProperty<int, UBABackgroundSimpleAdaptive> countFirstCleanBgFrame;
    ///������� ����, ��� ����
    int nCounterBG;


    public: // ������
    // ---------------------
    // ������������ � �����������
    // ---------------------
    UBABackgroundSimpleAdaptive(void);
    virtual ~UBABackgroundSimpleAdaptive(void);
    // ---------------------

    // ---------------------
    // ������ �����
    // ---------------------
    // �������� ����� ����� ����� �������
    virtual UBABackgroundSimpleAdaptive* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateSimplAdaptive(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    bool BCalculateExp(UBitmap &input, UBitmap &background);
    bool BCalculateStabilityIndicator(UBitmap &input, UBitmap &background, UBitmap &lastBinarization, UBitmap &lastInput, UBitmap &updateFGFlag);
    //���������� ���� �� ������ countFirstCleanBgFrame ������
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);

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


//------------------------------------------------------------------------
// ��� � ���������� �� �������� ������ ����� ����� � ������� ������
//------------------------------------------------------------------------




class RDK_LIB_TYPE UBABackgroundDependDiff: public UBABackground
{

    protected:

    /// ���� ���������� ����
    //ULProperty<double, UBABackgroundDependDiff> StateTempoDif;
    ///�������������� ���� ����������
    UPropertyInputData<UBitmap, UBABackgroundDependDiff> deltaImg;
    ///��������� ������ ������, ����������� �����
    ULProperty<int, UBABackgroundDependDiff> countFirstCleanBgFrame;
    ///������� ����, ��� ����
    int nCounterBG;




    public: // ������
    // ---------------------
    // ������������ � �����������
    // ---------------------
    UBABackgroundDependDiff(void);
    virtual ~UBABackgroundDependDiff(void);
    // ---------------------

    // ---------------------
    // ������ �����
    // ---------------------
    // �������� ����� ����� ����� �������
    virtual UBABackgroundDependDiff* New(void);

    //bool BCalculate1(UBitmap &input, UBitmap &background, UBitmap &lastBinarization);
    double BCalculate1(UBitmap &input, UBitmap &background, UBitmap &delta);
    //���������� ���� �� ������ countFirstCleanBgFrame ������
    bool BCalculateFirstBackground(UBitmap &input, UBitmap &background);


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

