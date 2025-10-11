// ===========================================================
// Version:        3.0.3
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2002.
E-mail:        alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: RDK

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */

#ifndef UCRCLASSIFIER_H
#define UCRCLASSIFIER_H


#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <ctime>

#include "../../../Rdk/Deploy/Include/rdk.h"
#include "../../../Rdk/Core/Engine/ModernSmartPointers.h"
#include "../../../Rdk/Core/Engine/ModernContainers.h"
#include "../../../Rdk/Core/System/ModernChrono.h"
#include "../../../Rdk/Core/System/ModernMutex.h"

namespace RDK {

//using namespace MySDK;

// ������ �������� ����� �������������
typedef double ExpectancyT;

class RDK_LIB_TYPE UCRClassifier: public UNet
{
public: // ������������� ��������
// ����� �������
RDK::ULProperty<int, UCRClassifier>  NumClasses;

// ��������� �������� ������� �������� ��������������
RDK::ULProperty<double, UCRClassifier>  MinInputValue, MaxInputValue;

// ��������� �������� �������� �������� ��������������
RDK::ULProperty<double, UCRClassifier>  MinOutputValue, MaxOutputValue;

// �������� �������� �������� ��������������
RDK::ULProperty<double, UCRClassifier>  DesiredMinOutputValue, DesiredMaxOutputValue;

// ��������� �������� ����������� ���������� ��������
RDK::UCLProperty<vector<double>, UCRClassifier>  MinQualityRate, MaxQualityRate;

// ��� ����� ��������/���������� ��������� ��������
RDK::ULProperty<string, UCRClassifier>  TrainFileName;

// ��� ����� ���������� ����������� ������ ����
RDK::ULProperty<string, UCRClassifier>  ResultsFileName;

// ������� ���������� �������������� ��������� ���������� ��������
// �� ����������� ��������
RDK::ULProperty<bool, UCRClassifier>  AutoQualityRate;

// ������� ���������� ��������������� ������������ ������� �� ���������� ���������
// MaxOutputValue �������� �� ������������ ������� ������
RDK::ULProperty<bool, UCRClassifier>  AutoAlignmentOutput;

RDK::UPropertyOutputData<MDMatrix<double>,UCRClassifier, ptPubOutput | ptState> Result;


public: // �������� ���������� ����������
// ���������� �������� <�������� ����������, ����� ������ ��������������>
RDK::ULProperty<pair<double,int>, UCRClassifier,ptPubState>  QualityRate;

// ���������������� ���������� ����������
RDK::UCLProperty<vector<double>, UCRClassifier,ptPubState>  ScaledResult;

// ����� � ���������� �������������
RDK::ULProperty<bool, UCRClassifier,ptPubState>  IsSuccessed;

protected: // ����� ���������
RDK::ULProperty<bool, UCRClassifier,ptPubState>  ModifiedFlag;

protected: // ��������� ����������

public: // ������
// --------------------------
// ������������ � �����������
// --------------------------
UCRClassifier(void);
virtual ~UCRClassifier(void);
// --------------------------


// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UCRClassifier* New(void);
// ---------------------

protected:
// -----------------------------
// ������ ���������� �������������� ����������
// -----------------------------
// ������������� ����� �������
bool SetNumClasses(const int &value);

// ������������� ��������� �������� ������� �������� ��������������
bool SetMinInputValue(const double &value);
bool SetMaxInputValue(const double &value);

// ������������� ��������� �������� �������� �������� ��������������
bool SetMinOutputValue(const double &value);
bool SetMaxOutputValue(const double &value);

// ������������� ��������� �������� ����������� ���������� ��������
bool SetMinQualityRate(const vector<double>& value);
bool SetMaxQualityRate(const vector<double>& value);

// ��� ����� ��������/���������� ��������� ��������
bool SetTrainFileName(const string &name);

// ��� ����� ���������� ����������� ������ ����
bool SetResultsFileName(const string &name);
// -----------------------------

// --------------------------
// ������� ������ ���������� ������
// --------------------------
protected:
// �������������� �������� �� ��������� � ����� �������� �����
virtual bool ADefault(void);
virtual bool ACRDefault(void);

// ������������ ������ ���������� ��������� �������
// ����� ��������� ����������
// ������������� �������� ����� Reset() � ���������� Ready � true
// � ������ �������� ������
virtual bool ABuild(void);
virtual bool ACRBuild(void);

// ����� �������� �����.
virtual bool AReset(void);
virtual bool ACRReset(void);

// ��������� ������ ����� ������� �� ������� ����.
virtual bool ACalculate(void);
virtual bool ACRCalculate(void);
// --------------------------

// --------------------------
// ������ �������� ����
// --------------------------
public:
// ����� �������� �������� � �������� ���������
virtual void ResetTraining(void);
// --------------------------

// ------------------------
// ������ �����
// ------------------------
public:
// ��������� ��������� �� ����� 'name'
virtual bool FileLoad(const string &name);
virtual bool AFileLoad(fstream &file);

// ��������� ��������� � ���� 'name'
virtual bool FileSave(const string &name);
virtual bool AFileSave(fstream &file);

// ������������� �������� �������� ������� ��� �������������
//virtual bool SetInput(const Real &input)=0;
// ------------------------

// --------------------------
// ������� ������ �������� ����
// --------------------------
protected:
// ����� �������� �������� � �������� ���������
virtual void AResetTraining(void);
// --------------------------

// --------------------------
// Modern C++20 methods
// --------------------------
// Move semantics
UCRClassifier(const UCRClassifier&) = default;
UCRClassifier(UCRClassifier&&) noexcept = default;
UCRClassifier& operator=(const UCRClassifier&) = default;
UCRClassifier& operator=(UCRClassifier&&) noexcept = default;

// Modern classification operations
void OptimizeClassificationPerformance();
bool IsClassifierValid() const;
void ReserveClassificationMemory(size_t features_count, size_t classes_count);
TimePoint GetLastClassificationTime() const;
void SetLastClassificationTime(TimePoint time);

// Modern machine learning operations
template<typename T>
void ReserveFeatureBuffer(std::vector<T>& buffer, size_t features_count);

template<typename T>
void MoveFeatureBuffer(std::vector<T>& target, std::vector<T>&& source);

// Advanced machine learning algorithms
void UpdateClassificationParameters(const std::vector<double>& parameters);
void CalculateFeatureImportance(const std::vector<double>& feature_weights);
void OptimizeClassificationThreshold(double threshold_value);
void ProcessBatchClassification(const std::vector<std::vector<double>>& feature_batch);
// --------------------------
};

}
#endif


