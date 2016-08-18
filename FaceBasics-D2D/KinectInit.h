#pragma once

#include"stdafx.h"

class KinectInit
{
protected:


public:

	KinectInit();

	~KinectInit();

	HRESULT InitializeDefaultSensor();

	IKinectSensor*         m_pKinectSensor;

	// Coordinate mapper
	ICoordinateMapper*     m_pCoordinateMapper;

	// Color reader
	IColorFrameReader*     m_pColorFrameReader;

	// Body reader
	IBodyFrameReader*      m_pBodyFrameReader;

	IAudioBeamFrameReader*  m_pAudioBeamFrameReader;

};
