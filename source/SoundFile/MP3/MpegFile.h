//-----------------------------------------------------------------------------
//	Класс для работы с данными Mp3 файлов
//	Копонент звукового двигателя Шквал
//	команда		: AntiTank
//	разработчик	: Гилязетдинов Марат (Марыч)
//-----------------------------------------------------------------------------
#ifndef _MPEG_FILE_H_INCLUDED_
#define _MPEG_FILE_H_INCLUDED_

#include <windows.h>
#include "../AbstractSoundFile.h"

//class CAbstractSoundFile;
//-----------------------------------------------------------------------------
// Класс для работы с данными Mp3 файлов
//-----------------------------------------------------------------------------
class CMpegFile : public CAbstractSoundFile {
public:
	// конструктор/деструктор
	CMpegFile(CReader* reader_ptr);
	~CMpegFile();

	// получение указателя на формат данных
	WAVEFORMATEX* GetFmt(void)
	{
		return 0;
	}
};

#endif