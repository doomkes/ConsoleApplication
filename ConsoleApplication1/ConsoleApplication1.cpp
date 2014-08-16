// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <fstream>

using namespace std;



class StraightMoveProfile {
	float m_accel, m_decel, m_max_speed, m_distance;
	float m_t1, m_t2, m_t3;
public:
	StraightMoveProfile();
	void SetAccel(float);		// feet per second per second
	void SetDecel(float);		// feet per second per second
	void SetMaxSpeed(float);	// feet per second
	void SetDistance(float);
	void CalcParams(void);
	float Position(float time);

};

StraightMoveProfile::StraightMoveProfile() {
	m_accel = 0.1;		// ft/s/s
	m_decel = 0.1;		// ft/s/s
	m_max_speed = 0.5;	// ft/s
	m_distance = 5;	//ft
	m_t1 = -99;			// seconds
	m_t2 = -99;			// seconds
	m_t3 = -99;			// seconds

}

void StraightMoveProfile::SetAccel (float value){
	m_accel = value;
}
void StraightMoveProfile::SetDecel(float value){
	m_decel = value;
}
void StraightMoveProfile::SetMaxSpeed(float value){
	m_max_speed = value;
}
void StraightMoveProfile::SetDistance(float value){
	m_distance = value;
}
void StraightMoveProfile::CalcParams(void){
	float accel_time, decel_time, min_dist, accel_dist, decel_dist;

	accel_time = m_max_speed / m_accel;
	decel_time = m_max_speed / m_decel;
	accel_dist = 0.5*m_accel * accel_time*accel_time;
	decel_dist = 0.5*m_decel * decel_time*decel_time;
	min_dist = accel_dist + decel_dist;
	if (min_dist > m_distance) // never gets up to speed.
		{
		m_t1 = 99;
		m_t2 = 0; // time at end of constanct velocity
		m_t3 = 99;


		}
	else
		{
		m_t1 = accel_time;
		m_t2 = (m_distance - min_dist) / m_max_speed + m_t1; // time at end of constanct velocity
		m_t3 = decel_time + m_t2;
		cout << accel_dist << "\n";
		cout << decel_dist << "\n";
		cout << m_t1 << "\n";
		cout << m_t2 << "\n";
		cout << m_t3 << "\n";
		};
}

float StraightMoveProfile::Position(float time){
	float position{};
	if (time < m_t1) position = 0.5*m_accel*time*time;
	else if (time < m_t2) position = 0.5*m_accel*m_t1*m_t1 + (time - m_t1)*m_max_speed;
	else if (time <= m_t3) position = 0.5*m_accel*m_t1*m_t1 + (m_t2 - m_t1)*m_max_speed + 0.5*m_decel*(m_t3 - m_t2)*(m_t3 - m_t2) - 0.5*m_decel*(m_t3 - time)*(m_t3 - time);
	else position = m_distance;
		
	return position;
}



int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Hello World\n";
	ofstream myfile;
	myfile.open("test.csv");

	StraightMoveProfile sm{};

	sm.CalcParams();

	float time{ 0.0 };
	for (time = 0.0; time < 16.0; time = time + 0.50)
	{
		cout << sm.Position (time) << "\n";
		myfile << sm.Position(time) << "\n";

	}

	myfile.close();
	return 0;
}
