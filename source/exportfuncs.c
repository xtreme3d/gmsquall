#include "Squall.h"

#define SqExport extern "C" __declspec(dllexport)

SqExport double SquallInit()
{
    if (SQUALL_Init(0) < 0)
        return 0.0;
    else
        return 1.0;
}

SqExport double SquallFree()
{
    SQUALL_Free();
    return 1.0;
}

SqExport double SquallPause(double pause)
{
    return SQUALL_Pause(int(pause));
}

SqExport double SquallSetDevice(double num)
{
    return SQUALL_SetDevice(int(num));
}

SqExport double SquallSetHardwareAcceleration(double hw2d, double hw3d)
{
    return SQUALL_SetHardwareAcceleration(int(hw2d), int(hw3d));
}

SqExport double SquallSetSpeakerMode(double mode)
{
    return SQUALL_SetSpeakerMode(int(mode));
}

SqExport double SquallSet3DAlgorithm(double algo)
{
    return SQUALL_Set3DAlgorithm(int(algo));
}

SqExport double SquallSetBufferSize(double size)
{
    return SQUALL_SetBufferSize(int(size));
}

SqExport double SquallSetListenerPosition(double x, double y, double z)
{
	float vec[3];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
    return SQUALL_Listener_SetPosition(vec);
}

SqExport double SquallSetListenerDirection(double x, double y, double z)
{
	float vec[3];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
    return SQUALL_Listener_SetParameters(0, vec, 0, 0);
}

SqExport double SquallSetListenerUp(double x, double y, double z)
{
	float vec[3];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
    return SQUALL_Listener_SetParameters(0, 0, vec, 0);
}

SqExport double SquallSetListenerVelocity(double x, double y, double z)
{
	float vec[3];
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
    return SQUALL_Listener_SetVelocity(vec);
}

SqExport double SquallSetVolume(double vol)
{
    return SQUALL_ChannelGroup_SetVolume(1, int(vol));
}

SqExport double SquallSampleCreate(char* filename, double streamed)
{
    return SQUALL_Sample_LoadFile(filename, !int(streamed), 0);
}

SqExport double SquallSamplePlay(double sample, double loop)
{
    return SQUALL_Sample_Play(int(sample), int(loop), 1, 1);
}

SqExport double SquallSamplePlay3D(double sample, double loop, double x, double y, double z, double vx, double vy, double vz)
{
	float pvec[3];
	pvec[0] = x;
	pvec[1] = y;
	pvec[2] = z;
	float vvec[3];
	vvec[0] = x;
	vvec[1] = y;
	vvec[2] = z;
    return SQUALL_Sample_Play3D(int(sample), int(loop), 0, 1, pvec, vvec);
}

SqExport double SquallChannelPlaying(double chan)
{
    return SQUALL_Channel_Status(int(chan)) == SQUALL_CHANNEL_STATUS_PLAY;
}

SqExport double SquallChannelStop(double chan)
{
    return SQUALL_Channel_Stop(int(chan));
}

SqExport double SquallChannelSetVolume(double chan, double vol)
{
    return SQUALL_Channel_SetVolume(int(chan), int(vol));
}

