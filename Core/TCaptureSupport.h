#ifndef TCaptureSupportH
#define TCaptureSupportH

namespace RDK {
/// Описывает актуальные данные состояния захвата необходимые для
/// декодирования данных изображения и его места в видеопоследовательности
struct TCaptureFrameDescription
{
/// Ширина кадра
int Width;

/// Высота кадра
int Height;

/// Цветовая модель кадра
int ColorModel;

/// Состояние захвата
int CaptureState;

/// Частота кадров захвата
double CaptureFps;

/// Частота отдаваемых кадров
double RealFps;

/// Временная метка кадра
unsigned long long TimeStamp;

/// Номер кадра
long long Position;
};

}
#endif
