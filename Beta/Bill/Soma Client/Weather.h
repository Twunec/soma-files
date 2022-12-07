// Weather.h: interface for the CWeather class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEATHER_H__70A35A02_9521_11D4_956A_00D0B77259E8__INCLUDED_)
#define AFX_WEATHER_H__70A35A02_9521_11D4_956A_00D0B77259E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWeather  
{
private:
	short m_Year;
	short m_Month;
	short m_Day;	// �ǽð� 4�ð�
	//short m_Hour;	// �ǽð� 10��
	DWORD m_dwHourTime;
	DWORD m_dwSubTime;
	BYTE  m_Rain;	// 0: ��ȿ� 1: ��� 
	BYTE  m_Snow;
	BOOL  m_bRainStateChange;
	BYTE  m_NightState;

public:
	BOOL GetRainState();//�� ������ ���¸� TRUE RETURN
	BOOL GetRainChange(){ return m_bRainStateChange;}
	BOOL GetSnowState();
	int  GetNightState();

//	void SetWeatherInfo( short Year, short month, short day, short hour, BYTE rain );
	void SetWeatherInfo( short Year, short month, short day, DWORD dwHourTime, DWORD dwSubTime, BYTE rain, BYTE NightState );
//	short GetHour(){ return m_Hour; }
	short GetHour(){ return short(m_dwHourTime - m_dwSubTime); }
	void GetWeatherInfo(short& year, short& month, short& day, short& hour, BYTE& rain);
	CWeather();
	virtual ~CWeather();

};

#endif // !defined(AFX_WEATHER_H__70A35A02_9521_11D4_956A_00D0B77259E8__INCLUDED_)
