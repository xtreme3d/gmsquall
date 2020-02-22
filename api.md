```cpp
double SquallInit();
double SquallFree();
double SquallPause(double pause);
double SquallSetDevice(double num);
double SquallSetHardwareAcceleration(double hw2d, double hw3d);
double SquallSetSpeakerMode(double mode);
double SquallSet3DAlgorithm(double algo);
double SquallSetBufferSize(double size);
double SquallSetListenerPosition(double x, double y, double z);
double SquallSetListenerDirection(double x, double y, double z);
double SquallSetListenerUp(double x, double y, double z);
double SquallSetListenerVelocity(double x, double y, double z);
double SquallSetVolume(double vol);
double SquallSampleCreate(char* filename, double streamed);
double SquallSamplePlay(double sample, double loop);
double SquallSamplePlay3D(double sample, double loop, double x, double y, double z, double vx, double vy, double vz);
double SquallChannelPlaying(double chan);
double SquallChannelStop(double chan);
double SquallChannelSetVolume(double chan, double vol);
double SquallChannelSetPlayPositionMs(double chan, double pos);
double SquallChannelSetLoop(double chan, double loop);
double SquallStop();
```