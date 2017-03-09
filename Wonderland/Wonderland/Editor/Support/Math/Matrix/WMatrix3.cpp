///////////////////////////////////////////////////////////////////////////////
// Filename: WMatrix3.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WMatrix3.h"
#include "..\Vector\Vector3.h"

WMatrix3::WMatrix3()
{
}

/*
WMatrix3::WMatrix3(Wfloat _m0, Wfloat _m1, Wfloat _m2, Wfloat _m3, Wfloat _m4, Wfloat _m5, Wfloat _m6, Wfloat _m7, Wfloat _m8, Wfloat _m9
	, Wfloat _m10, Wfloat _m11, Wfloat _m12, Wfloat _m13, Wfloat _m14, Wfloat _m15)
{
	v[0] = _m0, v[1] = _m1; v[2] = _m2; v[3] = _m3; v[4] = _m4; v[5] = _m5; v[6] = _m6; v[7] = _m7; v[8] = _m8; v[9] = _m9; v[10] = _m10; 
	v[11] = _m11; v[12] = _m12; v[13] = _m13; v[14] = _m14; v[15] = _m15;
}
*/

WMatrix3::WMatrix3(const WMatrix3& other)
{
}

WMatrix3::~WMatrix3()
{
}

Wvoid WMatrix3::RotationYawPitchRoll(WMatrix3& _out, Wfloat _yaw, Wfloat _pitch, Wfloat _roll)
{
	float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;

	// Get the cosine and sin of the _yaw, _pitch, and _roll.
	cYaw = cosf(_yaw);
	cPitch = cosf(_pitch);
	cRoll = cosf(_roll);

	sYaw = sinf(_yaw);
	sPitch = sinf(_pitch);
	sRoll = sinf(_roll);

	// Calculate the _yaw, _pitch, _roll rotation matrix.
	_out.v[0] = (cRoll * cYaw) + (sRoll * sPitch * sYaw);
	_out.v[1] = (sRoll * cPitch);
	_out.v[2] = (cRoll * -sYaw) + (sRoll * sPitch * cYaw);

	_out.v[3] = (-sRoll * cYaw) + (cRoll * sPitch * sYaw);
	_out.v[4] = (cRoll * cPitch);
	_out.v[5] = (sRoll * sYaw) + (cRoll * sPitch * cYaw);

	_out.v[6] = (cPitch * sYaw);
	_out.v[7] = -sPitch;
	_out.v[8] = (cPitch * cYaw);
}

Wvoid WMatrix3::Transform(Vector3& _inout, const WMatrix3& _in)
{
	float x, y, z;
	
	// Transform the vector by the 3x3 matrix.
	x = (_inout.x * _in.v[0]) + (_inout.y * _in.v[3]) + (_inout.z * _in.v[6]);
	y = (_inout.x * _in.v[1]) + (_inout.y * _in.v[4]) + (_inout.z * _in.v[7]);
	z = (_inout.x * _in.v[2]) + (_inout.y * _in.v[5]) + (_inout.z * _in.v[8]);

	// Store the result in the reference.
	_inout.x = x;
	_inout.y = y;
	_inout.z = z;
}

//
//
//

void WMatrix3::BuildIdentity()
{
	v[0] = 1.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;

	v[3] = 0.0f;
	v[4] = 1.0f;
	v[5] = 0.0f;

	v[6] = 0.0f;
	v[7] = 0.0f;
	v[8] = 1.0f;

}