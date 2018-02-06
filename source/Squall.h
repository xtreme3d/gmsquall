//-----------------------------------------------------------------------------
// Заголовочный файл звуковой системы "Шквал" версия 1.48
// команда     :
// разработчик : Гилязетдинов Марат (Марыч) E-Mail AT_Marat@list.net
//-----------------------------------------------------------------------------
#ifndef _SQUALL_H_INCLUDED_
#define _SQUALL_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#define IsTrue(r) (r >= 0) ? true : false
#define IsFalse(r) (r < 0) ? true : false

// список ошибок
#define  SQUALL_ERROR_NO_SOUND               -1    // в системе нет звукового устройства
#define  SQUALL_ERROR_MEMORY                 -2    // ошибка выделения памяти
#define  SQUALL_ERROR_UNINITIALIZED          -3    // класс не инициализирован
#define  SQUALL_ERROR_INVALID_PARAM          -4    // ошибка параметры не годяться
#define  SQUALL_ERROR_CREATE_WINDOW          -5    // невозможно создать скрытое окно
#define  SQUALL_ERROR_CREATE_DIRECT_SOUND    -6    // ошибка при создании DirectSound объекта
#define  SQUALL_ERROR_CREATE_THREAD          -7    // ошибка создания потока
#define  SQUALL_ERROR_SET_LISTENER_PARAM     -8    // ошибка установки параметром слушателя
#define  SQUALL_ERROR_GET_LISTENER_PARAM     -9    // ошибка получения параметров слушателя
#define  SQUALL_ERROR_NO_FREE_CHANNEL        -10   // ошибка нет свободного канала для воспроизведения
#define  SQUALL_ERROR_CREATE_CHANNEL         -11   // ошибка создания 3х мерного звукового буфера
#define  SQUALL_ERROR_CHANNEL_NOT_FOUND      -12   // ошибка создания 3х мерного звукового буфера
#define  SQUALL_ERROR_SET_CHANNEL_PARAM      -13   // ошибка заполнения звукового буфера
#define  SQUALL_ERROR_GET_CHANNEL_PARAM      -14   // ошибка установки уровня громкости канала
#define  SQUALL_ERROR_METHOD                 -15   // ошибка вызываетый метод не поддерживается
#define  SQUALL_ERROR_ALGORITHM              -16   // ошибка 3D алгоритм не поддерживаеться
#define  SQUALL_ERROR_NO_EAX                 -17   // ошибка EAX не поддерживаеться
#define  SQUALL_ERROR_EAX_VERSION            -18   // ошибка версия EAX не поддерживаеться
#define  SQUALL_ERROR_SET_EAX_PARAM          -19   // ошибка установки EAX параметров слушателя
#define  SQUALL_ERROR_GET_EAX_PARAM          -20   // ошибка получения EAX параметров слушателя
#define  SQUALL_ERROR_NO_ZOOMFX              -21   // ошибка ZOOMFX не поддерживается
#define  SQUALL_ERROR_SET_ZOOMFX_PARAM       -22   // ошибка установки ZOOMFX параметров буфера
#define  SQUALL_ERROR_GET_ZOOMFX_PARAM       -23   // ошибка получения ZOOMFX параметров буфера
#define  SQUALL_ERROR_UNKNOWN                -24   // неизвестная ошибка
#define  SQUALL_ERROR_SAMPLE_INIT            -25   // ошибка инициализации звуковых данных
#define  SQUALL_ERROR_SAMPLE_BAD             -26   // плохой семпл
#define  SQUALL_ERROR_SET_MIXER_PARAM        -27   // ошибка установки параметров микшера
#define  SQUALL_ERROR_GET_MIXER_PARAM        -28   // ошибка получения параметров микшера

// настройки слушателя
#define SQUALL_LISTENER_MODE_IMMEDIATE 0           // настройки пересчитываются немедленно
#define SQUALL_LISTENER_MODE_DEFERRED  1           // настройки пересчитываются только после вызова метода Listener_Update

// способы обработки трехмерного звука без аппаратной поддержки
#define SQUALL_ALG_3D_DEFAULT          0           // алгоритм по умолчанию
#define SQUALL_ALG_3D_OFF              1           // 2D алгоритм
#define SQUALL_ALG_3D_FULL             2           // полноценный 3D алгоритм
#define SQUALL_ALG_3D_LIGHT            3           // облегченный 3D алгоритм

// обратные вызовы для работы с файлами
typedef unsigned int (__cdecl* squall_callback_open_t)      (const char* Name);
typedef int          (__cdecl* squall_callback_read_t)      (unsigned int Handle, void* Buffer, int Size);
typedef int          (__cdecl* squall_callback_seek_t)      (unsigned int Handle, int Position, int SeekMode);
typedef void         (__cdecl* squall_callback_close_t)     (unsigned int Handle);

// обратные вызовы для работы с памятью
typedef void*        (__cdecl* squall_callback_alloc_t)     (unsigned int Size);
typedef void         (__cdecl* squall_callback_free_t)      (void* Ptr);

// обратные вызовы для вызова обработчиков
typedef void         (__cdecl* squall_callback_listener_t)     (void* UserData);
typedef int          (__cdecl* squall_callback_channel_t)      (int ChannelID, void* UserData);
typedef int          (__cdecl* squall_callback_end_channel_t)  (int ChannelID, void* UserData);

// структура для описания настроек двигателя
typedef struct squall_parameters_s
{
    void*   Window;                                // окно к которому нужно прикреплять двигатель
    int     Device;                                // номер устройства воспроизведения
    int     SampleRate;                            // частота дискретизации
    int     BitPerSample;                          // количество бит на выборку
    int     Channels;                              // максимальное количество каналов
    int     UseHW2D;                               // использование аппаратной акселерации для рассеянных каналов
    int     UseHW3D;                               // использование аппаратной акселерации для точечных каналов
    int     UseAlg;                                // используемый трехмерный алгоритм
    int     BufferSize;                            // размер вторичного буфера в миллисекундах
    int     ListenerMode;                          // промежуток времени через который будет происходить обновление
    float   DistanceFactor;                        // фактор дистанции
    float   RolloffFactor;                         // фактор удаления
    float   DopplerFactor;                         // эффект Допплера
} squall_parameters_t;

// структура описывающая параметры звука по умолчанию
typedef struct squall_sample_default_s
{
    int     SampleGroupID;                         // принадлежность семпла к группе
    int     Priority;                              // приоритет звука по умолчанию
    int     Frequency;                             // частота звука по умолчанию
    int     Volume;                                // громкость звука по умолчанию
    int     Pan;                                   // панорама звука по умолчанию
    float   MinDist;                               // минимальная граница слышимости по умолчанию
    float   MaxDist;                               // максимальная граница слышимости по умолчанию
} squall_sample_default_t;

// структура описывающая текущее состояние каналов
typedef struct squall_channels_s
{
    int     Play;                                  // количество воспроизводящихся рассеянных каналов
    int     Pause;                                 // количество стоящих в паузе рассеянных каналов
    int     Prepare;                               // количество подготовленных рассеянных каналов
    int     Play3D;                                // количество воспроизводящихся позиционных каналов
    int     Pause3D;                               // количество стоящих в паузе позиционных каналов
    int     Prepare3D;                             // количество подготовленных позиционных каналов
} squall_channels_t;

// структура описывающая параметры устройства воспроизведения
typedef struct squall_device_caps_s
{
    int     Flags;                                 // флаги определяющие свойства устройства
    int     HardwareChannels;                      // количество аппаратных каналов
    int     Hardware3DChannels;                    // количество аппаратных 3D каналов
} squall_device_caps_t;

// флаги описывающие возможности устройства воспроизведения
#define SQUALL_DEVICE_CAPS_HARDWARE    0x00000001  // устройство поддерживает аппаратное смешивание каналов
#define SQUALL_DEVICE_CAPS_HARDWARE_3D 0x00000002  // устройство поддерживает аппаратное смешивание 3D каналов
#define SQUALL_DEVICE_CAPS_EAX10       0x00000004  // устройство поддреживает EAX 1.0
#define SQUALL_DEVICE_CAPS_EAX20       0x00000008  // устройство поддерживает EAX 2.0
#define SQUALL_DEVICE_CAPS_EAX30       0x00000010  // устройство поддерживает EAX 3.0
#define SQUALL_DEVICE_CAPS_ZOOMFX      0x00000100  // устройство поддерживает ZOOMFX

// флаги описывающие конфигурацию аккустики
#define SQUALL_SPEAKER_DEFAULT         0x00000000  // аккустика по умолчанию
#define SQUALL_SPEAKER_HEADPHONE       0x00000001  // наушники (головные телефоны)
#define SQUALL_SPEAKER_MONO            0x00000002  // моно колонка (1.0)
#define SQUALL_SPEAKER_STEREO          0x00000003  // стерео колонки (2.0)
#define SQUALL_SPEAKER_QUAD            0x00000004  // квадро колонки (4.0)
#define SQUALL_SPEAKER_SURROUND        0x00000005  // квадро система с буфером низких эффектов (4.1)
#define SQUALL_SPEAKER_5POINT1         0x00000006  // пяти канальная система с буфером низких эффектов (5.1)

// статус канала
#define SQUALL_CHANNEL_STATUS_NONE     0           // канала нет
#define SQUALL_CHANNEL_STATUS_PLAY     1           // канал в режиме воспроизведения
#define SQUALL_CHANNEL_STATUS_PAUSE    2           // канал в режиме паузы
#define SQUALL_CHANNEL_STATUS_PREPARED 3           // канал в подготовленном состоянии

// структура параметров EAX слушателя
typedef union squall_eax_listener_s
{
   // параметры EAX 1.0
   struct
   {
      unsigned long  Environment;
      float          Volume;
      float          DecayTime_sec;
      float          Damping;
   } eax1;
    
   // параметры EAX 2.0
   struct 
   {
      long           Room;
      long           RoomHF;
      float          RoomRolloffFactor;
      float          DecayTime;
      float          DecayHFRatio;
      long           Reflections;
      float          ReflectionsDelay;
      long           Reverb;
      float          ReverbDelay;
      unsigned long  Environment;
      float          EnvironmentSize;
      float          EnvironmentDiffusion;
      float          AirAbsorptionHF;
      unsigned long  Flags;
   } eax2;

   // параметры EAX 3.0
   struct
   {
      unsigned long  Environment;
      float          EnvironmentSize;
      float          EnvironmentDiffusion;
      long           Room;
      long           RoomHF;
      long           RoomLF;
      float          DecayTime;
      float          DecayHFRatio;
      float          DecayLFRatio;
      long           Reflections;
      float          ReflectionsDelay;
      float          ReflectionsPan[3];
      long           Reverb;
      float          ReverbDelay;
      float          ReverbPan[3];
      float          EchoTime;
      float          EchoDepth;
      float          ModulationTime;
      float          ModulationDepth;
      float          AirAbsorptionHF;
      float          HFReference;
      float          LFReference;
      float          RoomRolloffFactor;
      unsigned long  Flags;
   } eax3;
} squall_eax_listener_t;

// значения флагов слушателя в EAX начиная с версии 2.0
#define SQUALL_EAX_LISTENER_FLAGS_DECAYTIMESCALE          0x00000001
#define SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSSCALE        0x00000002
#define SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSDELAYSCALE   0x00000004
#define SQUALL_EAX_LISTENER_FLAGS_REVERBSCALE             0x00000008
#define SQUALL_EAX_LISTENER_FLAGS_REVERBDELAYSCALE        0x00000010
#define SQUALL_EAX_LISTENER_FLAGS_DECAYHFLIMIT            0x00000020

// значения флагов слушателя в EAX начиная версии 3.0
#define SQUALL_EAX_LISTENER_FLAGS_ECHOTIMESCALE           0x00000040
#define SQUALL_EAX_LISTENER_FLAGS_MODULATIONTIMESCALE     0x00000080

// значение флагов слушателя в EAX начиная с версии 2.0 по умолчанию
#define SQUALL_EAX_LISTENER_FLAGS_DEFAULT                 ( SQUALL_EAX_LISTENER_FLAGS_DECAYTIMESCALE          |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSSCALE        |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REFLECTIONSDELAYSCALE   |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REVERBSCALE             |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_REVERBDELAYSCALE        |   \
                                                            SQUALL_EAX_LISTENER_FLAGS_DECAYHFLIMIT    )

// номера предустановленных значений EAX окружения
#define SQUALL_EAX_OFF              -1
#define SQUALL_EAX_GENERIC           0
#define SQUALL_EAX_PADDEDCELL        1
#define SQUALL_EAX_ROOM              2
#define SQUALL_EAX_BATHROOM          3
#define SQUALL_EAX_LIVINGROOM        4
#define SQUALL_EAX_STONEROOM         5
#define SQUALL_EAX_AUDITORIUM        6
#define SQUALL_EAX_CONCERTHALL       7
#define SQUALL_EAX_CAVE              8
#define SQUALL_EAX_ARENA             9
#define SQUALL_EAX_HANGAR           10
#define SQUALL_EAX_CARPETEDHALLWAY  11
#define SQUALL_EAX_HALLWAY          12
#define SQUALL_EAX_STONECORRIDOR    13
#define SQUALL_EAX_ALLEY            14
#define SQUALL_EAX_FOREST           15
#define SQUALL_EAX_CITY             16
#define SQUALL_EAX_MOUNTAINS        17
#define SQUALL_EAX_QUARRY           18
#define SQUALL_EAX_PLAIN            19
#define SQUALL_EAX_PARKINGLOT       20
#define SQUALL_EAX_SEWERPIPE        21
#define SQUALL_EAX_UNDERWATER       22
#define SQUALL_EAX_DRUGGED          23
#define SQUALL_EAX_DIZZY            24
#define SQUALL_EAX_PSYCHOTIC        25

// Cтруктура EAX параметров канала
typedef union squall_eax_channel_s
{
    // EAX 1.0
    struct
    {
        float               Mix;
    } eax1;

    // EAX 2.0
    struct
    {
        long                Direct;
        long                DirectHF;
        long                Room;
        long                RoomHF;
        float               RoomRolloffFactor;
        long                Obstruction;
        float               ObstructionLFRatio;
        long                Occlusion;
        float               OcclusionLFRatio;
        float               OcclusionRoomRatio;
        long                OutsideVolumeHF;
        float               AirAbsorptionFactor;
        unsigned long       Flags;
    } eax2;
    
    //  EAX 3.0
    struct
    {
        long                Direct;
        long                DirectHF;
        long                Room;
        long                RoomHF;
        long                Obstruction;
        float               ObstructionLFRatio;
        long                Occlusion;
        float               OcclusionLFRatio;
        float               OcclusionRoomRatio;
        float               OcclusionDirectRatio;
        long                Exclusion;
        float               ExclusionLFRatio;
        long                OutsideVolumeHF;
        float               DopplerFactor;
        float               RolloffFactor;
        float               RoomRolloffFactor;
        float               AirAbsorptionFactor;
        unsigned long       Flags;
    } eax3;
} squall_eax_channel_t;

// значения флагов канала в EAX начиная с версии 2.0
#define SQUALL_EAX_CHANNEL_FLAGS_DIRECTHFAUTO             0x00000001
#define SQUALL_EAX_CHANNEL_FLAGS_ROOMAUTO                 0x00000002
#define SQUALL_EAX_CHANNEL_FLAGS_ROOMHFAUTO               0x00000004
#define SQUALL_EAX_CHANNEL_FLAGS_DEFAULT                  (SQUALL_EAX_CHANNEL_FLAGS_DIRECTHFAUTO |   \
                                                            SQUALL_EAX_CHANNEL_FLAGS_ROOMAUTO     |   \
                                                            SQUALL_EAX_CHANNEL_FLAGS_ROOMHFAUTO   )
// структура ZOOMFX параметров источника звука
typedef struct squall_zoomfx_channel_s
{
   float    Min[3];
   float    Max[3];
   float    Front[3];
   float    Top[3];
   long     MacroFX;
} squall_zoomfx_channel_t;

#ifndef _USRDLL
class Squall
{
   public:
#else
#define DLL_API __declspec(dllexport)
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                 Методы инициализация / освобождения
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Инициализация звуковой системы Шквал
// на входе    :  SystemParam -  указатель на структуру с параметрами
//                               звукового двигателя для инициализации.
//                               Если параметр будет равен 0 то звуковой
//                               двигатель создаст экземпляр объекта с
//                               следующими параметрами:
//                               Window         = 0     (создать свое окно)
//                               Device         = 0     (устройство по умолчанию)
//                               SampleRate     = 44100
//                               BitPerSample   = 16
//                               Channels       = 16
//                               UseHW2D        = true  (использовать)
//                               UseHW3D        = true  (использовать)
//                               UseAlg         = 0     (алгоритм по умолчанию)
//                               BufferSize     = 200
//                               ListenerMode   = 0     (немедленное применение)
//                               DistanceFactor = 1.0f
//                               RolloffFactor  = 1.0f
//                               DopplerFactor  = 1.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Init(squall_parameters_t* SystemParam);
#else
DLL_API int SQUALL_Init(squall_parameters_t* SystemParam);
#endif

//-----------------------------------------------------------------------------
// Освобождение занятых звуковой системой ресурсов
// на входе    :  *
// на выходе   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Free(void);
#else
DLL_API void SQUALL_Free(void);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                  Методы для управления двигателем
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Включение/выключение паузы всех звуковых каналов
// на входе    :  Pause -  флаг включения/выключения паузы
//                         параметр может принимать слудующие значения
//                         true  - включить паузу
//                         false - выключить паузу
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Pause(int Pause);
#else
DLL_API int SQUALL_Pause(int Pause);
#endif

//-----------------------------------------------------------------------------
// Остановка всех звуковых каналов
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Stop(void);
#else
DLL_API int SQUALL_Stop(void);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                    Методы для настройки двигателя
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Установка нового устройства воспроизведения
// на входе    :  Num   -  номер нового устройства воспроизведения, значение 
//                         параметра должно быть в пределах от 0 до значения
#ifndef _USRDLL
//                         полученного с помощью метода GetNumDevice.
#else
//                         полученного с помощью метода SQUALL_GetNumDevice.
#endif
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetDevice(int Num);
#else
DLL_API int SQUALL_SetDevice(int Num);
#endif

//-----------------------------------------------------------------------------
// Получение номера текущего устройства воспроизведения
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит номер текущего
//                устройства воспроизведения
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDevice(void);
#else
DLL_API int SQUALL_GetDevice(void);
#endif

//-----------------------------------------------------------------------------
// Включение/выключение использования аппаратной акселерации звука
// на входе    :  UseHW2D  -  флаг определяющий использование аппаратной
//                            акселерации рассеянных звуковых каналов,
//                            параметр может принимать следующие значения:
//                            true   - использовать аппаратную акселерацию
//                            false  - не использовать аппаратную акселерацию
//                UseHW3D  -  флаг определяющий использование аппаратной
//                            акселерации позиционных звуковых каналов
//                            параметр может принимать следующие значения:
//                            true   - использовать аппаратную акселерацию
//                            false  - не использовать аппаратную акселерацию
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetHardwareAcceleration(int UseHW2D, int UseHW3D);
#else
DLL_API int SQUALL_SetHardwareAcceleration(int UseHW2D, int UseHW3D);
#endif

//-----------------------------------------------------------------------------
// Получение текущих настроек использования аппаратной акселерации звука
// на входе    :  UseHW2D  -  указатель на переменную в которую нужно поместить
//                            текущее значение использования аппаратной
//                            акселерации для рассеянных звуковых каналов
//                UseHW3D  -  указатель на переменную в которую нужно поместить
//                            текущее значение использования аппаратной
//                            акселерации для позиционных звуковых каналов
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetHardwareAcceleration(int* UseHW2D, int* UseHW3D);
#else
DLL_API int SQUALL_GetHardwareAcceleration(int* UseHW2D, int* UseHW3D);
#endif

//-----------------------------------------------------------------------------
// Установка режима аккустики
// на входе    :  Mode  -  аккустическая модель, параметр может принимать
//                         следуюшие значения:
//                         SQUALL_SPEAKER_DEFAULT   - аккустика по умолчанию
//                         SQUALL_SPEAKER_HEADPHONE - наушники (головные телефоны)
//                         SQUALL_SPEAKER_MONO      - моно колонка (1.0)
//                         SQUALL_SPEAKER_STEREO    - стерео колонки (2.0)
//                         SQUALL_SPEAKER_QUAD      - квадро колонки (4.0)
//                         SQUALL_SPEAKER_SURROUND  - квадро система с буфером
//                                                    низких эффектов (4.1)
//                         SQUALL_SPEAKER_5POINT1   - пяти канальная система с
//                                                    буфером низких эффектов (5.1)
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetSpeakerMode(int Mode);
#else
DLL_API int SQUALL_SetSpeakerMode(int Mode);
#endif

//-----------------------------------------------------------------------------
//	Получение текущего режима аккустики
//	на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит номер текущего
//                режима аккустики
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetSpeakerMode(void);
#else
DLL_API int SQUALL_GetSpeakerMode(void);
#endif

//-----------------------------------------------------------------------------
// Установка алгоритма расчета трехмерного звука
// на входе    :  Algoritm -  код применяемого алгоритма расчета звука
//                            параметр может принимать следуюшие значения:
//                            SQUALL_ALG_3D_DEFAULT - алгоритм по умолчанию
//                            SQUALL_ALG_3D_OFF     - 2D алгоритм
//                            SQUALL_ALG_3D_FULL    - полноценный 3D алгоритм
//                            SQUALL_ALG_3D_LIGHT   - облегченный 3D алгоритм
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Set3DAlgorithm(int Algorithm);
#else
DLL_API int SQUALL_Set3DAlgorithm(int Algorithm);
#endif

//-----------------------------------------------------------------------------
// Получения текущего алгоритма расчета трехмерного звука
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит номер текущего
//                алгоритма расчета трехмерного звука, результат может
//                принимать слудующие значения:
//                SQUALL_ALG_3D_DEFAULT - алгоритм по умолчанию
//                SQUALL_ALG_3D_OFF     - 2D алгоритм
//                SQUALL_ALG_3D_FULL    - полноценный 3D алгоритм
//                SQUALL_ALG_3D_LIGHT   - облегченный 3D алгоритм
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Get3DAlgorithm(void);
#else
DLL_API int SQUALL_Get3DAlgorithm(void);
#endif

//-----------------------------------------------------------------------------
// Установка нового размера звукового буфера в милисекундах
// на входе    :  BufferSize  -  новый размер звукового буфера, в милисекундах
//                               параметр должен лежать в пределах от 200
//                               до 5000
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SetBufferSize(int BufferSize);
#else
DLL_API int SQUALL_SetBufferSize(int BufferSize);
#endif

//-----------------------------------------------------------------------------
// Получение текущего размера звукового буфера в милисекундах
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущий размер
//                звукового буфера в милисекундах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetBufferSize(void);
#else
DLL_API int SQUALL_GetBufferSize(void);
#endif

//-----------------------------------------------------------------------------
// Установка внешней системы работы с памятью
// на входе    :  UserAlloc   -  указатель на внешний метод выделения памяти
//                UserFree    -  указатель на внешний метод освобождения памяти
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Squall::SetMemoryCallbacks(squall_callback_alloc_t UserAlloc, squall_callback_free_t UserFree);
#else
DLL_API int SQUALL_SetMemoryCallbacks(squall_callback_alloc_t UserAlloc, squall_callback_free_t UserFree);
#endif

//-----------------------------------------------------------------------------
// Установка внешних методов для работы с файлами
// на входе    :  UserOpen    -  указатель на внешний метод открытия файлов
//                UserSeek    -  указатель на внешний метод позиционирования
//                               в открытом файле
//                UserRead    -  указатель на внешний метод чтения данных из
//                               открытого файла
//                UserClose   -  указатель на внешний метод закрытия открытого
//                               файла
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Squall::SetFileCallbacks(squall_callback_open_t UserOpen, squall_callback_seek_t UserSeek, squall_callback_read_t UserRead, squall_callback_close_t UserClose);
#else
DLL_API int SQUALL_SetFileCallbacks(squall_callback_open_t UserOpen, squall_callback_seek_t UserSeek, squall_callback_read_t UserRead, squall_callback_close_t UserClose);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//              Методы для получения информация о системе
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Получение количества устройств воспроизведения звука
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки.
//                в случае успешного вызова результат содержит количество
//                устройств воспроизведения в системе. Если в системе нет
//                устройств воспроизведения результат будет равен 0.
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetNumDevice(void);
#else
DLL_API int SQUALL_GetNumDevice(void);
#endif

//-----------------------------------------------------------------------------
// Получение имени устройства по указаному номеру
// на входе    :  Num      -  номер устройства, значение параметра должно быть
//                            в пределах от 0 до значения полученного с помощью
#ifndef _USRDLL
//                            метода GetNumDevice.
#else
//                            метода SQUALL_GetNumDevice.
#endif
//                Buffer   -  указатель на буфер куда нужно поместить имя
//                            устройства воспроизведения
//                Size     -  размер принимающего буфера в байтах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDeviceName(int Num, char* Buffer, int Size);
#else
DLL_API int SQUALL_GetDeviceName(int Num, char* Buffer, int Size);
#endif

//-----------------------------------------------------------------------------
// Получение свойств устройства воспроизведения по указаному номеру
// на входе    :  Num   -  номер устройства, значение параметра должно быть в
//                         пределах от 0 до значения полученного с помощью
#ifndef _USRDLL
//                         метода GetNumDevice.
#else
//                         метода SQUALL_GetNumDevice.
#endif
//                Caps  -  указатель на структуру в которую нужно поместить
//                         свойства устройства воспроизведения
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetDeviceCaps(int Num, squall_device_caps_t* Caps);
#else
DLL_API int SQUALL_GetDeviceCaps(int Num, squall_device_caps_t* Caps);
#endif

//-----------------------------------------------------------------------------
// Получение используемой версии EAX интерфейса
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит максимально
//                доступную версию EAX
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetEAXVersion(void);
#else
DLL_API int SQUALL_GetEAXVersion(void);
#endif

//-----------------------------------------------------------------------------
// Получение информации о каналах
// на входе    :  Info  -  указатель на структуру в которую нужно поместить
//                         информацию о состоянии каналов
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int GetChannelsInfo(squall_channels_t* Info);
#else
DLL_API int SQUALL_GetChannelsInfo(squall_channels_t* Info);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                    Методы для работы со слушателем
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Установка новых параметров слушателя
// на входе    :  Position -  указатель на структуру с новыми координатами
//                            позиции слушателя. В случае если позицию слушателя
//                            изменять не нужно, то данный параметр должен
//                            содержать 0 
//                Front    -  указатель на структуру с новым вектором 
//                            фронтального направления слушателя. В случае еслт
//                            вектор фронтального направления слушателя изменять
//                            не нужно, то данный парамерт должен содержать 0
//                Top      -  указатель на структуру с новым вектором
//                            вертикального направления слушателя. В случае если
//                            вектор вертикального направления изменять не нужно,
//                            то данный параметр должен содержать 0
//                Velocity -  указатель на структуру с новым вектором
//                            скорости перемещения слушателя. В случае если
//                            скорость перемещения слушателя изменять не нужно,
//                            то данный параметр должен содержать 0.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetParameters(float* Position, float* Front, float* Top, float* Velocity);
#else
DLL_API int SQUALL_Listener_SetParameters(float* Position, float* Front, float* Top, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Получение текущих параметров слушателя
// на входе    :  Position -  указатель на структуру в которую нужно 
//                            поместить текущие координаты слушателя. В случае
//                            если значение координат слушателя не требуется
//                            определять, то данный параметр должен содержать 0.
//                Front    -  указатель на структуру в которую нужно
//                            поместить текущий вектор фронтального 
//                            направления слушателя. В случае если вектор
//                            фронтального направления слушателя не требуется
//                            определять, то данный параметр должен содержать 0.
//                Top      -  указатель на структуру в которую нужно
//                            поместить текущий вектор вертикального 
//                            направления слушателя. В случае если вектор
//                            вертикального направления слушателя не требуется
//                            определять, то данный параметр должен содержать 0.
//                Velocity -  указатель на структуру в которую нужно
//                            поместить текущий вектор скорости перемещения
//                            слушателя. В случае если скорость перемещения
//                            слушателя не требуется определять, то данный
//                            параметр должен содержать 0.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetParameters(float* Position, float* Front, float* Top, float* Velocity);
#else
DLL_API int SQUALL_Listener_GetParameters(float* Position, float* Front, float* Top, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Установка новой скорости перемещения слушателя
// на входе    :  Velocity -  указатель на структуру с новым вектором 
//                            скорости перемещения слушателя.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetVelocity(float* Velocity);
#else
DLL_API int SQUALL_Listener_SetVelocity(float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Получение текущей скорости перемещения слушателя
// на входе    :  Velocity - указатель на структуру в которую нужно
//                           поместить текущий вектор скорости перемещения
//                           слушателя.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetVelocity(float* Velocity);
#else
DLL_API int SQUALL_Listener_GetVelocity(float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Установка новой позиции слушателя в пространстве
// на входе    :  Position -  указатель на структуру с новым вектором
//                            скорости перемещения слушателя.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetPosition(float* Position);
#else
DLL_API int SQUALL_Listener_SetPosition(float* Position);
#endif

//-----------------------------------------------------------------------------
// Получение текущей позиции слушателя в пространстве
// на входе    :  Position -  указатель на структуру в которую нужно
//                            поместить текущий вектор скорости перемещения
//                            слушателя.
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetPosition(float* Position);
#else
DLL_API int SQUALL_Listener_GetPosition(float* Position);
#endif

//-----------------------------------------------------------------------------
// Установка нового коэффициента преобразования дистанции
// на входе    :  DistanceFactor -  новый коэффициент преобразования дистанции
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetDistanceFactor(float DistanceFactor);
#else
DLL_API int SQUALL_Listener_SetDistanceFactor(float DistanceFactor);
#endif

//-----------------------------------------------------------------------------
// Получение текущего коэффициента преобразования дистанции
// на входе    :  DistanceFactor -  указатель на переменную в которую нужно
//                                  поместить текущий коэффициент 
//                                  преобразования дистанции
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetDistanceFactor(float* DistanceFactor);
#else
DLL_API int SQUALL_Listener_GetDistanceFactor(float* DistanceFactor);
#endif

//-----------------------------------------------------------------------------
// Установка нового коэффициента затухания звука в зависимости от растояния
// на входе    :  RolloffFactor  -  новый коэффициент преобразования затухания
//                                  звука,  значение параметра должно быть
//                                  в пределах от 0.1f до 10.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetRolloffFactor(float RolloffFactor);
#else
DLL_API int SQUALL_Listener_SetRolloffFactor(float RolloffFactor);
#endif

//-----------------------------------------------------------------------------
// Получение текущего коэффициента затухания звука в зависимости от растояния
// на входе    :  RolloffFactor  -  указатель на переменную в которую нужно
//                                  поместить текущий коэффициент преобразования
//                                  затухания звука
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetRolloffFactor(float* RolloffFactor);
#else
DLL_API int SQUALL_Listener_GetRolloffFactor(float* RolloffFactor);
#endif

//-----------------------------------------------------------------------------
// Установка нового коэффициента эффекта Допплера
// на входе    :  DopplerFactor  -  новый коэффициент эффекта Допплера, значение
//                                  параметра должно быть в пределах от 0.1f
//                                  до 10.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetDopplerFactor(float DopplerFactor);
#else
DLL_API int SQUALL_Listener_SetDopplerFactor(float DopplerFactor);
#endif

//-----------------------------------------------------------------------------
// Получение текущего коэффициента эффекта Допплера
// на входе    :  DopplerFactor  -  указатель на переменную в которую нужно
//                                  поместить текущий коэффициент эффекта
//                                  Допплера
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_GetDopplerFactor(float* DopplerFactor);
#else
DLL_API int SQUALL_Listener_GetDopplerFactor(float* DopplerFactor);
#endif

//-----------------------------------------------------------------------------
// Обновление трехмерных настроек
// на входе    :  *
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод имеет смысл применять только в том случае когда
//                слушатель настроен на принудительное обновление трехмерных
//                настроек. По есть при инициализации двигателя слушатель
//                переведен в режим SQUALL_LISTENER_MODE_DEFERRED
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_Update(void);
#else
DLL_API int SQUALL_Listener_Update(void);
#endif

//-----------------------------------------------------------------------------
// Установка предустановленных значения окружения
// на входе    :  Preset   -  номер предустановленного значения
//                            параметр может принимать следуюшие значения:
//                            SQUALL_EAX_OFF
//                            SQUALL_EAX_GENERIC
//                            SQUALL_EAX_PADDEDCELL
//                            SQUALL_EAX_ROOM
//                            SQUALL_EAX_BATHROOM
//                            SQUALL_EAX_LIVINGROOM
//                            SQUALL_EAX_STONEROOM
//                            SQUALL_EAX_AUDITORIUM
//                            SQUALL_EAX_CONCERTHALL
//                            SQUALL_EAX_CAVE
//                            SQUALL_EAX_ARENA
//                            SQUALL_EAX_HANGAR
//                            SQUALL_EAX_CARPETEDHALLWAY
//                            SQUALL_EAX_HALLWAY
//                            SQUALL_EAX_STONECORRIDOR
//                            SQUALL_EAX_ALLEY
//                            SQUALL_EAX_FOREST
//                            SQUALL_EAX_CITY
//                            SQUALL_EAX_MOUNTAINS
//                            SQUALL_EAX_QUARRY
//                            SQUALL_EAX_PLAIN
//                            SQUALL_EAX_PARKINGLOT
//                            SQUALL_EAX_SEWERPIPE
//                            SQUALL_EAX_UNDERWATER
//                            SQUALL_EAX_DRUGGED
//                            SQUALL_EAX_DIZZY
//                            SQUALL_EAX_PSYCHOTIC
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_SetPreset(int Preset);
#else
DLL_API int SQUALL_Listener_EAX_SetPreset(int Preset);
#endif

//-----------------------------------------------------------------------------
// Установка новых EAX параметров слушателя
// на входе    :  Version     -  номер версии EAX интерфейса
//                Properties  -  указатель на структуру с новыми EAX параметрами
//                               слушателя
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_SetProperties(int Version, squall_eax_listener_t* Properties);
#else
DLL_API int SQUALL_Listener_EAX_SetProperties(int Version, squall_eax_listener_t* Properties);
#endif

//-----------------------------------------------------------------------------
// Получение текущих EAX параметров слушателя
// на входе    :  Version     -  номер версии EAX интерфейса
//                Properties  -  указатель на структуру куда надо поместить
//                               текущие EAX параметры слушателя
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_EAX_GetProperties(int Version, squall_eax_listener_t* Properties);
#else
DLL_API int SQUALL_Listener_EAX_GetProperties(int Version, squall_eax_listener_t* Properties);
#endif

//-----------------------------------------------------------------------------
// Установка обработчика слушателя
// на входе    :  Worker      -  указатель на обработчик слушателя, в случае
//                               если параметр равен 0, предедущий обработчик
//                               будет удален.
//                Param       -  указатель на данные пользователя, в случае
//                               данных пользователя нет, то данный параметр
//                               может содержать 0
//                UpdateTime  -  промежуток времени через который нужно
//                               вызывать обработчик параметр должен лежать
//                               в пределах от 1 до 5000
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Listener_SetWorker(squall_callback_listener_t Worker, void* Param, unsigned int UpdateTime);
#else
DLL_API int SQUALL_Listener_SetWorker(squall_callback_listener_t Worker, void* Param, unsigned int UpdateTime);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                   Общие методы для работы с каналами
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Начало воспроизведения подготовленного звукового канала
// на входе    :  ChannelID   -  идентификатор подготовленного канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Start(int ChannelID);
#else
DLL_API int SQUALL_Channel_Start(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Включение/выключение паузы звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Pause       -  флаг включения/выключения паузы, параметр может
//                               принимать следующие значения:
//                               true  - включить паузу
//                               false - выключить паузу
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Pause(int ChannelID, int Pause);
#else
DLL_API int SQUALL_Channel_Pause(int ChannelID, int Pause);
#endif

//-----------------------------------------------------------------------------
// Остановка звукового канала по идентификатору
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Stop(int ChannelID);
#else
DLL_API int SQUALL_Channel_Stop(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Получение статуса звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит статус канала,
//                результат может принимать следующие значения:
//                SQUALL_CHANNEL_STATUS_NONE       -  звукового канала с таким
//                                                    идентификатором нет
//                SQUALL_CHANNEL_STATUS_PLAY       -  звуковой канал
//                                                    воспроизводится
//                SQUALL_CHANNEL_STATUS_PAUSE      -  звуковой канал находится
//                                                    в режиме паузы
//                SQUALL_CHANNEL_STATUS_PREPARED   -  звуковой канал
//                                                    подготовлен
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Status(int ChannelID);
#else
DLL_API int SQUALL_Channel_Status(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка нового уровня громкости звукового канала в процентах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Volume      -  значение уровня громкости в провентах,
//                               значение ппараметра должно быть в пределах
//                               от 0 до 100
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetVolume(int ChannelID, int Volume);
#else
DLL_API int SQUALL_Channel_SetVolume(int ChannelID, int Volume);
#endif

//-----------------------------------------------------------------------------
// Получение текущего уровня громкости звукового канала в процентах
// на входе    :  ChannelID   -  идентификатор канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущее значение
//                громкости канала в процентах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetVolume(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetVolume(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Устанока новой частоты дискретизации звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Frequency   -  новое значение частоты дискретизации, значение
//                               параметра должно быть в пределах от 100 Герц
//                               до 1000000 Герц
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFrequency(int ChannelID, int Frequency);
#else
DLL_API int SQUALL_Channel_SetFrequency(int ChannelID, int Frequency);
#endif

//-----------------------------------------------------------------------------
// Получение текущей частоты дискретизации звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущее значение
//                частоты дискретизации звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFrequency(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetFrequency(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка новой позиции воспроизведения звукового канала в семплах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Position    -  новое значение позиции воспроизведения
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPlayPosition(int ChannelID, int Position);
#else
DLL_API int SQUALL_Channel_SetPlayPosition(int ChannelID, int Position);
#endif

//-----------------------------------------------------------------------------
// Получение текущей позиции воспроизведения звукового канала в семплах
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущую позицию
//                воспроизведения
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPlayPosition(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPlayPosition(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка новой позиции воспроизведения звукового канала в миллисекундах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Position    -  новое значение позиции воспроизведения,
//                               в миллисекундах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPlayPositionMs(int ChannelID, int Position);
#else
DLL_API int SQUALL_Channel_SetPlayPositionMs(int ChannelID, int Position);
#endif

//-----------------------------------------------------------------------------
// Получение текущей позиции воспроизведения звукового канала в миллисекундах
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущую позицию
//                воспроизведения
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPlayPositionMs(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPlayPositionMs(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка обработчика звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Worker      -  указатель на обработчик звукового канала
//                Param       -  указатель на данные пользователя, в случае
//                               если данных пользователя нет, параметр может
//                               содержать 0
//                UpdateTime  -  промежуток времени в миллисекундах через
//                               который нужно вызывать обработчик, значение
//                               параметра должно быть в пределах от 1 до 5000
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetWorker(int ChannelID, squall_callback_channel_t Worker, void* Param, unsigned int UpdateTime);
#else
DLL_API int SQUALL_Channel_SetWorker(int ChannelID, squall_callback_channel_t Worker, void* Param, unsigned int UpdateTime);
#endif

//-----------------------------------------------------------------------------
// Установка обработчика окончания звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Worker      -  указатель на обработчик звукового канала
//                Param       -  указатель на данные пользователя, в случае
//                               если данных пользователя нет, параметр может
//                               содержать 0
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
int Channel_SetEndWorker(int ChannelID, squall_callback_end_channel_t Worker, void* Param);
#else
DLL_API int SQUALL_Channel_SetEndWorker(int ChannelID, squall_callback_end_channel_t Worker, void* Param);
#endif

//-----------------------------------------------------------------------------
// Установка новых границ фрагмента звукового канала в семплах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Start       -  начальная позиция фрагмента, в отсчетах
//                End         -  конечная позиция фрагмента, в отсчетах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFragment(int ChannelID, int Start, int End);
#else
DLL_API int SQUALL_Channel_SetFragment(int ChannelID, int Start, int End);
#endif

//-----------------------------------------------------------------------------
// Получение текущих границ фрагмента звукового канала в семплах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Start       -  указатель на переменную в которую нужно
//                               поместить начальную позицию фрагмента в
//                               отсчетах
//                End         -  указатель на переменную в которую нужно
//                               поместить конечную позицию фрагмента
//                               в отсчетах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFragment(int ChannelID, int* Start, int* End);
#else
DLL_API int SQUALL_Channel_GetFragment(int ChannelID, int* Start, int* End);
#endif

//-----------------------------------------------------------------------------
// Установка новых границ фрагмента звукового канала в миллисекундах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Start       -  начальная позиция фрагмента, позиция в
//                               миллисекундах
//                End         -  конечная позиция фрагмента, позиция в
//                               миллисекундах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetFragmentMs(int ChannelID, int Start, int End);
#else
DLL_API int SQUALL_Channel_SetFragmentMs(int ChannelID, int Start, int End);
#endif

//-----------------------------------------------------------------------------
// Получение текущих границ фрагмента звукового канала в миллисекундах
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Start       -  указатель на переменную в которую нужно
//                               поместить начальную позицию фрагмента
//                               в миллисекундах
//                End         -  указатель на переменную в которую нужно
//                               поместить конечную позицию фрагмента
//                               в миллисекундах
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetFragmentMs(int ChannelID, int* Start, int* End);
#else
DLL_API int SQUALL_Channel_GetFragmentMs(int ChannelID, int* Start, int* End);
#endif

//-----------------------------------------------------------------------------
// Получение продолжительности исходных звуковых данных в семплах
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит продолжительность
//                исходных данных в семплах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLength(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLength(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Получение продолжительности исходных звуковых данных в миллисекундах
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит продолжительность
//                исходных данных в милисекундах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLengthMs(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLengthMs(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка нового приоритета звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Priority    -  новый приоритет канала, значение параметра
//                               должно быть в пределах от 0 (самый низший
//                               приоритет) до 65535 (самый высший приоритет)
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPriority(int ChannelID, int Priority);
#else
DLL_API int SQUALL_Channel_SetPriority(int ChannelID, int Priority);
#endif

//-----------------------------------------------------------------------------
// Получение текущего приоритета звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит приоритет
//                звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPriority(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPriority(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Получение текущего значения флага зацикленности воспроизведения звукового
// канала
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущее значение
//                флага зацикленности воспроизведения канала, результат может
//                принимать следующие значения:
//                true  -  звуковой канал воспроизводится бесконечно
//                false -  звуковой канал воспроизводится один раз
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetLoop(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetLoop(int ChannelID);
#endif

//-----------------------------------------------------------------------------
// Установка нового значения флага зацикленности воспроизведения звукового
// канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Loop        -  флаг зацикленности канала, значение праметра
//                               может принимать следующие значения:
//                               true  -  бесконечное воспроизведение звукового
//                                        канала
//                               false -  воспроизведение звукового канала один
//                                        раз
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetLoop(int ChannelID, int Loop);
#else
DLL_API int SQUALL_Channel_SetLoop(int ChannelID, int Loop);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                Методы для работы с рассеянными каналами
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Установка новой панорамы звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Pan         -  новое значение панорамы, значение параметра
//                               должено быть в пределах от 0 (максимальное
//                               смещение стерео баланса влево) до 100
//                               (максимальное смещение стерео баланса вправо)
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с позиционными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetPan(int ChannelID, int Pan);
#else
DLL_API int SQUALL_Channel_SetPan(int ChannelID, int Pan);
#endif

//-----------------------------------------------------------------------------
// Получение текущей панорамы звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит текущее значение
//                панорамы канала
// примечание  :  данный метод не работает с позиционными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetPan(int ChannelID);
#else
DLL_API int SQUALL_Channel_GetPan(int ChannelID);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                Методы для работы с позиционными каналами
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Установка новой трехмерной позиции звукового канала в пространстве
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Position    -  указатель на структуру с новыми координатами
//                               канала в пространстве
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Set3DPosition(int ChannelID, float* Position);
#else
DLL_API int SQUALL_Channel_Set3DPosition(int ChannelID, float* Position);
#endif

//-----------------------------------------------------------------------------
// Получение текущей трехмерной позиции звукового канала в пространстве
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Position    -  указатель на структуру в которую нужно
//                               поместить текущую трехмерную позицию звукового
//                               канала в пространстве
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_Get3DPosition(int ChannelID, float* Position);
#else
DLL_API int SQUALL_Channel_Get3DPosition(int ChannelID, float* Position);
#endif

//-----------------------------------------------------------------------------
// Установка новой скорости перемещения звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Velocity    -  указатель на структуру с новым вектором
//                               скорости перемещения звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetVelocity(int ChannelID, float* Velocity);
#else
DLL_API int SQUALL_Channel_SetVelocity(int ChannelID, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Получение текущей скорости перемещения звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Velocity    -  указатель на структуру в которую нужно
//                               поместить текущее значение вектора скорости
//                               звукового канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetVelocity(int ChannelID, float* Velocity);
#else
DLL_API int SQUALL_Channel_GetVelocity(int ChannelID, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Установка нового минимального и максимального расстояния слышимости
// звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                MinDist     -  новое минимальное расстояние слышимости
//                               значение параметра должно быть в пределах
//                               от 0.01f до 1000000000.0f
//                MaxDist     -  новое максимальное расстояние слышимости
//                               значение параметра должно быть в пределах
//                               от 0.01f до 1000000000.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetMinMaxDistance(int ChannelID, float MinDist, float MaxDist);
#else
DLL_API int SQUALL_Channel_SetMinMaxDistance(int ChannelID, float MinDist, float MaxDist);
#endif

//-----------------------------------------------------------------------------
// Получение текущего минимального растояния слышимости звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                MinDist     -  указатель на переменную в которую нужно
//                               поместить текущее минимальное растояние
//                               слышимости
//                MinDist     -  указатель на переменную в которую нужно
//                               поместить текущее максимальное растояние
//                               слышимости
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetMinMaxDistance(int ChannelID, float* MinDist, float* MaxDist);
#else
DLL_API int SQUALL_Channel_GetMinMaxDistance(int ChannelID, float* MinDist, float* MaxDist);
#endif

//-----------------------------------------------------------------------------
// Установка параметров конуса распространения звукового канала
// на входе    :  ChannelID         -  идентификатор звукового канала
//                Orientation       -  указатель на струкруру с вектором
//                                     направления внутреннего и внешнего конуса,
//                                     в случае если значение вектора направления
//                                     внешнего и внутреннего конуса изменять
//                                     не нужно, то данный параметр должен
//                                     содержать 0
//                InsideConeAngle   -  угол внутреннего звукового конуса, значение
//                                     параметра должно быть в пределах от 1 до
//                                     360 градусов, в случае если значение
//                                     угла внутреннего звукового конуса изненять
//                                     не нужно, то данный параметр должен
//                                     содержать 0
//                OutsideConeAngle  -  угол внешнего звукового конуса, значение
//                                     параметра должно быть в пределах от 1 до
//                                     360 градусов, в случае если значение
//                                     угла внешнего звукового конуса изменять
//                                     не нужно, то данный параметр должен
//                                     содержать 0
//                OutsideVolume     -  уровень громкости источника за пределами
//                                     внешнего конуса, в процентах значение
//                                     праметра должно быть в пределах от 0
//                                     до 100
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_SetConeParameters(int ChannelID, float* Orientation, int InsideConeAngle, int OutsideConeAngle, int OutsideVolume);
#else
DLL_API int SQUALL_Channel_SetConeParameters(int ChannelID, float* Orientation, int InsideConeAngle, int OutsideConeAngle, int OutsideVolume);
#endif

//-----------------------------------------------------------------------------
// Получение параметров конуса распространения звукового канала
// на входе    :  ChannelID         -  идентификатор звукового канала
//                Orientation       -  указатель на струкруру в которую нужно
//                                     поместить текущий вектор направления
//                                     внешнего и внутреннего конуса, в случае
//                                     если значение вектора внутреннего
//                                     и внешнего конуса, получать не нужно,
//                                     то данный параметр должен содержать 0
//                InsideConeAngle   -  указатель на переменную в которую нужно
//                                     поместить текущее значение угола внутреннего
//                                     конуса в градусах, в случае если значение
//                                     угла внутреннего конуса получать не нужно,
//                                     то данный параметр должен содержать 0
//                OutsideConeAngle  -  указатель на переменную в которую нужно
//                                     поместить текущее значение угола внешнего
//                                     конуса в градусах, в случае если значение
//                                     угла внешнего конуса получать не нужно,
//                                     то данный параметр должен содержать 0
//                OutsideVolume     -  указатель на переменную в которую нужно
//                                     поместить текущее значение уровеня громкости
//                                     источника за пределами внешнего конуса, в
//                                     процентах, в случае если значение уровня
//                                     громкости за пределами внешего конуса
//                                     получать не нужно, то данный параметр
//                                     должен содержать 0
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_GetConeParameters(int ChannelID, float* Orientation, int* InsideConeAngle, int* OutsideConeAngle, int* OutsideVolume);
#else
DLL_API int SQUALL_Channel_GetConeParameters(int ChannelID, float* Orientation, int* InsideConeAngle, int* OutsideConeAngle, int* OutsideVolume);
#endif

//-----------------------------------------------------------------------------
// Установка новых EAX параметров звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Version     -  номер версии EAX, параметр определяет в каком
//                               формате передаются EAX параметры канала.
//                Properties  -  указатель на структуру описывающую параметры
//                               EAX канала, параметры должны быть в формате
//                               указанном параметром Version
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_EAX_SetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#else
DLL_API int SQUALL_Channel_EAX_SetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// Получение текущих EAX параметров звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Version     -  номер версии EAX, параметр определяет в каком
//                               формате получать EAX параметры канала.
//                Properties  -  указатель на структуру куда нужно поместить
//                               текущие параметры EAX канала, структура будет
//                               заполнена параметрами в формате указанном
//                               параметром Version
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_EAX_GetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#else
DLL_API int SQUALL_Channel_EAX_GetProperties(int ChannelID, int Version, squall_eax_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// Установка новых ZOOMFX параметров звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Properties  -  указатель на структуру описывающую параметры
//                               ZOOMFX канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_ZOOMFX_SetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#else
DLL_API int SQUALL_Channel_ZOOMFX_SetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#endif

//-----------------------------------------------------------------------------
// Получение текущих ZOOMFX параметров звукового канала
// на входе    :  ChannelID   -  идентификатор звукового канала
//                Properties  -  указатель на структуру куда нужно поместить
//                               текущие параметры ZOOMFX канала
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
// примечание  :  данный метод не работает с рассеянными каналами
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Channel_ZOOMFX_GetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#else
DLL_API int SQUALL_Channel_ZOOMFX_GetProperties(int ChannelID, squall_zoomfx_channel_t* Property);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                Методы для работы с группами каналов
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Включение/выключение паузы группы каналов
// на входе    :  ChannelGroupID -  идентификатор группы каналов
//                Pause          -  флаг включения/выключения паузы, параметр
//                                  может принимать слудующие значения:
//                                  true  -  включить паузу
//                                  false -  выключить паузу
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_Pause(int ChannelGroupID, int Pause);
#else
DLL_API int SQUALL_ChannelGroup_Pause(int ChannelGroupID, int Pause);
#endif

//-----------------------------------------------------------------------------
// Остановка группы каналов
// на входе    :  ChannelGroupID -  идентификатор группы каналов
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_Stop(int ChannelGroupID);
#else
DLL_API int SQUALL_ChannelGroup_Stop(int ChannelGroupID);
#endif

//-----------------------------------------------------------------------------
// Установка уровня громкости группы каналов в процентах
// на входе    :  ChannelGroupID -  идентификатор группу каналов
//                Volume         -  значение урокня громкости, значение должно
//                                  лежать в пределах от 0 до 100
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_SetVolume(int ChannelGroupID, int Volume);
#else
DLL_API int SQUALL_ChannelGroup_SetVolume(int ChannelGroupID, int Volume);
#endif

//-----------------------------------------------------------------------------
// Установка новой частоты дискретизации группы каналов
// на входе    :  ChannelGroupID -  номер группы каналов
//                Frequency      -  новое значение частоты дискретизации,
//                                  значение параметра должно быть в пределах
//                                  от 100 до 1000000 Герц
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int ChannelGroup_SetFrequency(int ChannelGroupID, int Frequency);
#else
DLL_API int SQUALL_ChannelGroup_SetFrequency(int ChannelGroupID, int Frequency);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                Методы для работы с семплами
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Создание семпла из файла
// на входе    :  FileName - указатель на имя файла
//                MemFlag  - флаг определяющий расположение файла, параметр
//                           может принимать следующие значения:
//                           true  -   размещать данные файла в памяти
//                           false -   разместить данные файла на диске
//                Default  - указатель на структуру параметров семпла по
//                           умолчанию, если параметр равен 0, загрузчик
//                           установит следующие параметры семпла по умолчанию:
//                           SampleGroupID - 0
//                           Priority      - 0
//                           Frequency     - 0
//                           Volume        - 100
//                           Pan           - 50
//                           MinDist       - 1.0f
//                           MaxDist       - 1000000000.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного семпла
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_LoadFile(char *FileName, int MemFlag, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_LoadFile(char *FileName, int MemFlag, squall_sample_default_t* Default);
#endif
//-----------------------------------------------------------------------------
// Загрузка данных в хранилище из памяти
// на входе :  MemoryPtr   - указатель на память с данными файла
//             MemorySize  - размер памяти с данными файла
//             NewMemory   - флаг определяющий способ размещения данных
//                           true -    выделить память и скопировать, то
//                                     есть двигатель выделяет память и
//                                     копирует данные указанные MemoryPtr.
//                                     После выполнения память можно удалить
//                           false -   использовать предлагаемую память, то
//                                     есть передаваемую память нельзя удалять
//             Default     - указатель на структуру параметров семпла по
//                           умолчанию, если параметр равен 0, загрузчик
//                           установит следующие параметры семпла по умолчанию:
//                           SampleGroupID - 0
//                           Priority      - 0
//                           Frequency     - 0
//                           Volume        - 100
//                           Pan           - 50
//                           MinDist       - 1.0f
//                           MaxDist       - 1000000000.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного семпла
//-----------------------------------------------------------------------------

#ifndef _USRDLL
int Sample_LoadFromMemory(void *MemoryPtr, unsigned int MemorySize, int NewMemory, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_LoadFromMemory(void *MemoryPtr, unsigned int MemorySize, int NewMemory, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// Освобождение всех семплов
// на входе    :  *
// на выходе   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Sample_UnloadAll(void);
#else
DLL_API void SQUALL_Sample_UnloadAll(void);
#endif

//-----------------------------------------------------------------------------
// Освобождение указанного семпла
// на входе    :  SampleID -  идентификатор семпла
// на выходе   :  *
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   void Sample_Unload(int SampleID);
#else
DLL_API void SQUALL_Sample_Unload(int SampleID);
#endif

//-----------------------------------------------------------------------------
// Получение продолжительности данных звукового файла в отсчетах
// на входе    :  SampleID -  идентификатор семпла
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит продолжительность
//                данных в отсчетах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileLength(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileLength(int SampleID);
#endif

//-----------------------------------------------------------------------------
// Получение продолжительности данных звукового файла в миллисекундах
// на входе    :  SampleID -  идентификатор семпла
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит продолжительность
//                данных в милисекундах
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileLengthMs(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileLengthMs(int SampleID);
#endif

//-----------------------------------------------------------------------------
// Получение частоты дискретизации данных звукового файла
// на входе    :  SampleID -  идентификатор семпла
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит частоту
//                дискретизации
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetFileFrequency(int SampleID);
#else
DLL_API int SQUALL_Sample_GetFileFrequency(int SampleID);
#endif

//-----------------------------------------------------------------------------
// Установка новых параметров семпла по умолчанию
// на входе    :  SampleID -  идентификатор семпла
//                Default  -  указатель на структуру с новыми параметрами семпла
//                            по умолчанию
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_SetDefault(int SampleID, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_SetDefault(int SampleID, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// Получение текущих параметров семпла по умолчанию
// на входе    :  SampleID -  идентификатор семпла
//                Default  -  указатель на структуру в которую нужно поместить
//                            текущие параметры семпла по умолчанию
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_GetDefault(int SampleID, squall_sample_default_t* Default);
#else
DLL_API int SQUALL_Sample_GetDefault(int SampleID, squall_sample_default_t* Default);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение рассеянного канала из указанного семпла, опираясь
// на параметры семпла по умолчанию
// на входе    :  SampleID       -  идентификатор семпла
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play(int SampleID, int Loop, int ChannelGroupID, int Start);
#else
DLL_API int SQUALL_Sample_Play(int SampleID, int Loop, int Group, int Start);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение рассеянного канала из указанного семпла, опираясь
// на параметры семпла по умолчанию
// на входе    :  SampleID       -  идентификатор семпла
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Priority       -  приоритет создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 65535
//                Volume         -  громкость создаваемого звукового канала,
//                                  в процентах, значение параметра должно
//                                  лежать в пределах от 0 до 100
//                Frequency      -  частота дискретизации звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 100 до 1000000000
//                Pan            -  панорама создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 100
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_PlayEx(int SampleID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#else
DLL_API int SQUALL_Sample_PlayEx(int SampleID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение позиционного (трехмерного) звукового канала из
// указаного семпла, опираясь на параметры семпла по умолчанию
// на входе    :  SampleID       -  идентификатор семпла
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  указатель на структуру c координатами
//                                  источника звукового канала
//                Velocity       -  указатель на вектор скорости источника
//                                  звукового канала, в случае если значение
//                                  вектора скорости устанавливать не надо,
//                                  то данный параметр должен быть равен 0
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play3D(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity);
#else
DLL_API int SQUALL_Sample_Play3D(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение позиционного (трехмерного) звукового канала из
// указаного семпла
// на входе    :  SampleID       -  идентификатор семпла
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  указатель на структуру c координатами
//                                  источника звукового канала
//                Velocity       -  указатель на вектор скорости источника
//                                  звукового канала, в случае если значение
//                                  вектора скорости устанавливать не надо,
//                                  то данный параметр должен быть равен 0
//                Priority       -  приоритет создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 65535
//                Volume         -  громкость создаваемого звукового канала,
//                                  в процентах, значение параметра должно
//                                  лежать в пределах от 0 до 100
//                Frequency      -  частота дискретизации звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 100 до 1000000000
//                MinDist        -  минимальное растояние слышимости звукового
//                                  канала, значение параметра должно быть в
//                                  пределах от 0.01f до 1000000000.0f
//                MaxDist        -  максимальное растояние слышимости звукового
//                                  канала, значение параметра должно быть в
//                                  пределах от 0.01f до 1000000000.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Play3DEx(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#else
DLL_API int SQUALL_Sample_Play3DEx(int SampleID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#endif

//-----------------------------------------------------------------------------
// Включение/выключение паузы всех каналов использующих указаный семпл
// на входе    :  SampleID -  указатель на данные звука
//                Pause    -  флаг включения/выключения паузы, параметр может
//                            принимать следующие значения:
//                            true   - включить паузу
//                            false  - выключить паузу
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Pause(int SampleID, int Pause);
#else
DLL_API int SQUALL_Sample_Pause(int SampleID, int Pause);
#endif

//-----------------------------------------------------------------------------
// Остановка всех звуковых каналов использующих указанный семпл
// на входе    :  SampleID -  идентификатор семпла
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int Sample_Stop(int SampleID);
#else
DLL_API int SQUALL_Sample_Stop(int SampleID);
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                Методы для работы с группами семплов
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Создание и воспроизведения рассеяного канала из группы семплов, опираясь
// на параметры семпла по умолчанию
// на входе    :  SampleGroupID  -  идентификатор группы семплов
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play(int SoundGroupID, int Loop, int Group, int Start);
#else
DLL_API int SQUALL_SampleGroup_Play(int SoundGroupID, int Loop, int Group, int Start);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведения рассеяного канала из группы семплов
// на входе    :  SampleGroupID  -  идентификатор группы семплов
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Priority       -  приоритет создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 65535
//                Volume         -  громкость создаваемого звукового канала,
//                                  в процентах, значение параметра должно
//                                  лежать в пределах от 0 до 100
//                Frequency      -  частота дискретизации звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 100 до 1000000000
//                Pan            -  панорама создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 100
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_PlayEx(int SoundGroupID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#else
DLL_API int SQUALL_SampleGroup_PlayEx(int SoundGroupID, int Loop, int Group, int Start, int Priority, int Volume, int Frequency, int Pan);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение позиционного (трехмерного) звукового канала из
// указаной группы семплов, опираясь на параметры семпла по умолчанию
// на входе    :  SampleGroupID  -  идентификатор группы семплов
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  указатель на структуру c координатами
//                                  источника звукового канала
//                Velocity       -  указатель на вектор скорости источника
//                                  звукового канала, в случае если значение
//                                  вектора скорости устанавливать не надо,
//                                  то данный параметр должен быть равен 0
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play3D(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity);
#else
DLL_API int SQUALL_SampleGroup_Play3D(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity);
#endif

//-----------------------------------------------------------------------------
// Создание и воспроизведение позиционного (трехмерного) звукового канала из
// указаной группы семплов
// на входе    :  SampleGroupID  -  идентификатор группы семплов
//                Loop           -  флаг зацикленности воспроизведения, параметр
//                                  может принимать следующие значения:
//                                  true  -  воспроизводить канал в цикле
//                                           бесконечно
//                                  false -  воспроизвести канал один раз
//                ChannelGroupID -  принадлежность создаваемого канала к группе
//                                  каналов, если значение параметра равно 0
//                                  значит звуковой канал не принадлежит группе
//                                  каналов.
//                Start          -  флаг запуска звука по окончанию создания
//                                  канала, параметр может принимать следующие
//                                  значения:
//                                  true  -  канал начнет воспроизводится сразу
//                                           после создания
//                                  false -  канал будет только подготовлен,
//                                           для того чтобы начать воспроизведение
#ifndef _USRDLL
//                                           нужно вызвать метод Channel_Start()
#else
//                                           нужно вызвать метод
//                                           SQUALL_Channel_Start()
#endif
//                Position       -  указатель на структуру c координатами
//                                  источника звукового канала
//                Velocity       -  указатель на вектор скорости источника
//                                  звукового канала, в случае если значение
//                                  вектора скорости устанавливать не надо,
//                                  то данный параметр должен быть равен 0
//                Priority       -  приоритет создаваемого звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 0 до 65535
//                Volume         -  громкость создаваемого звукового канала,
//                                  в процентах, значение параметра должно
//                                  лежать в пределах от 0 до 100
//                Frequency      -  частота дискретизации звукового канала,
//                                  значение параметра должно лежать в пределах
//                                  от 100 до 1000000000
//                MinDist        -  минимальное растояние слышимости звукового
//                                  канала, значение параметра должно быть в
//                                  пределах от 0.01f до 1000000000.0f
//                MaxDist        -  максимальное растояние слышимости звукового
//                                  канала, значение параметра должно быть в
//                                  пределах от 0.01f до 1000000000.0f
// на выходе   :  успешность, если возвращаемый результат больше либо равен 0,
//                вызов состоялся, иначе результат содержит код ошибки
//                в случае успешного вызова результат содержит идентификатор
//                созданного звукового канала
//-----------------------------------------------------------------------------
#ifndef _USRDLL
   int SampleGroup_Play3DEx(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
};
#else
DLL_API int SQUALL_SampleGroup_Play3DEx(int SoundGroupID, int Loop, int Group, int Start, float* Position, float* Velocity, int Priority, int Volume, int Frequency, float MinDist, float MaxDist);
#endif

#ifdef __cplusplus
}
#endif
#endif
