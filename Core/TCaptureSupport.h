#ifndef TCaptureSupportH
#define TCaptureSupportH

namespace RDK {
/// ��������� ���������� ������ ��������� ������� ����������� ���
/// ������������� ������ ����������� � ��� ����� � �����������������������
struct TCaptureFrameDescription
{
/// ������ �����
int Width;

/// ������ �����
int Height;

/// �������� ������ �����
int ColorModel;

/// ��������� �������
int CaptureState;

/// ������� ������ �������
double CaptureFps;

/// ������� ���������� ������
double RealFps;

/// ��������� ����� �����
unsigned long long TimeStamp;

/// ����� �����
long long Position;
};

}
#endif
