#ifndef UBA_REDUCE_H
#define UBA_REDUCE_H

//#include "../../../Engine/UNet.h"
//#include "../../UBitmap.h"
#include "../../../Rdk/Deploy/Include/rdk.h"

namespace RDK {

/// ������� ����� ��������������� �����������
class RDK_LIB_TYPE UBAReduce: public UNet
{
protected: // ���������
/// ����� ������� � ������ ��� ����������
int NumCols, NumRows;

public: // ������� � �������� ������
/// ������� �����������
UPropertyInputData<UBitmap, UBAReduce> Input;

/// �������� �����������
UPropertyOutputData<UBitmap, UBAReduce> Output;

protected: // ��������� ����������
UBitmap Buffer;

public: // ������
// ---------------------
// ������������ � �����������
// ---------------------
UBAReduce(void);
virtual ~UBAReduce(void);
// ---------------------

public: // ������
// ---------------------
// ������ ���������� �����������
// ---------------------
/// ����� ������ � ������� ��� ��������
const int& GetNumCols(void) const;
const int& GetNumRows(void) const;
bool SetNumCols(const int &value);
bool SetNumRows(const int &value);
// ---------------------

// ---------------------
// ������ �����
// ---------------------
/// �������� ����� ����� ����� �������
virtual UBAReduce* New(void);

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

/// ����� �������� �����.
virtual bool AReset(void);

/// ��������� ������ ����� �������
virtual bool ACalculate(void);
// --------------------------
};
}
//---------------------------------------------------------------------------

#endif
