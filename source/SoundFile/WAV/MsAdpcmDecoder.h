//-----------------------------------------------------------------------------
//	Класс декодера IMA ADPCM формата от MS
//	Копонент звукового двигателя Шквал
//	команда		: AntiTank
//	разработчик	: Гилязетдинов Марат (Марыч)
//-----------------------------------------------------------------------------
#ifndef _MS_ADPCM_DECOMPRESSOR_H_INCLUDED_
#define _MS_ADPCM_DECOMPRESSOR_H_INCLUDED_

// включения
#include <windows.h>
#include "../AbstractDecoder.h"
#include "../AbstractSoundFile.h"

class CAbstractSoundFile;

//-----------------------------------------------------------------------------
// Класс для IMA ADPCM формата от MicroSoft
//-----------------------------------------------------------------------------
class CDecompressMsAdpcm : public CAbstractDecompressor {
protected:
	struct SCoef {
		short Coef1;
		short Coef2;
	};

	// структура формата для IMA ADPCM
	struct SMS_ADPCM_Format {
		WAVEFORMATEX fmt;					// стандартный формат
		WORD SamplesPerPacket;		// длинна пакета
		WORD NumCoef;				//
	};

	DWORD _channels;							// количество каналов в треке
	DWORD _samplesPerPacket;					// количество выборок в пакете
	DWORD _bytesPerPacket;					// количество байт в пакете
	DWORD _packetof;							// количество пакетов в файле
	char* _packetBuffer;						// промежуточный буфер для данных нераспакованного пакета
	short* _left;								// указатель на данные левого канала
	short* _rigth;								// указатель на данные правого канала
	DWORD _curPacket;							// смещение в файле на текущий пакет
	WORD _numCoef;
	SCoef* _coefTable;

	// распаковка пакета
	DWORD DecodeMONOPacket(void);
	DWORD DecodeSTEREOPacket(void);

public:
	// конструктор/деструктор
	CDecompressMsAdpcm(WAVEFORMATEX* pcm_format, bool& flag,
		CAbstractSoundFile* a);
	~CDecompressMsAdpcm();

	// получение моно данных из декодера
	DWORD GetMonoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// получение стерео данных из декодера
	DWORD GetStereoSamples(void* buffer, DWORD start, DWORD length, bool loop);

	// получение тишины в моно режиме
	DWORD GetMonoMute(void* buffer, DWORD length);

	// получение тишины в стерео режиме
	DWORD GetStereoMute(void* buffer, DWORD length);

	// получение количества семплов в файле
	DWORD GetSamplesInFile(void)
	{
		return _packetof * _samplesPerPacket;
	}

	// получение количества байт в треке моно режим
	DWORD GetRealMonoDataSize(void)
	{
		return GetSamplesInFile() << 1;
	}

	// получение количества байт в треке стерео режим
	DWORD GetRealStereoDataSize(void)
	{
		return GetSamplesInFile() << 2;
	}
};
#endif
