#include"KinectInit.h"

KinectInit::KinectInit():
	m_pKinectSensor(nullptr),
	m_pCoordinateMapper(nullptr),
	m_pColorFrameReader(nullptr),
	m_pBodyFrameReader(nullptr),
	m_pAudioBeamFrameReader(nullptr)
{

}

KinectInit::~KinectInit()
{

	// done with body frame reader
	SafeRelease(m_pBodyFrameReader);

	// done with color frame reader
	SafeRelease(m_pColorFrameReader);

	// done with coordinate mapper
	SafeRelease(m_pCoordinateMapper);

	if (NULL != m_pAudioBeamFrameReader)
	{
		SafeRelease(m_pAudioBeamFrameReader);
	}


	// close the Kinect Sensor
	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();
	}

	SafeRelease(m_pKinectSensor);
}

HRESULT KinectInit::InitializeDefaultSensor()
{
	HRESULT hr = S_OK;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		// Initialize Kinect and get color, body and face readers
		IColorFrameSource* pColorFrameSource = nullptr;
		IBodyFrameSource* pBodyFrameSource = nullptr;

		// Initialize the Audio
		IAudioSource* pAudioSource = nullptr;

		hr = m_pKinectSensor->Open();

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
		}

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
		}


		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_AudioSource(&pAudioSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pAudioSource->OpenReader(&m_pAudioBeamFrameReader);
		}

		
		SafeRelease(pAudioSource);
		SafeRelease(pColorFrameSource);
		SafeRelease(pBodyFrameSource);
	}

	if (!m_pKinectSensor || FAILED(hr))
	{
		exit(-5);
		return E_FAIL;
	}

	return hr;
}
