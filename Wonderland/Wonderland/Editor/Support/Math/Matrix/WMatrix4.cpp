///////////////////////////////////////////////////////////////////////////////
// Filename: WMatrix4.cpp
///////////////////////////////////////////////////////////////////////////////
#include "WMatrix4.h"

#include <stdio.h>
#include <string.h>

#include "..\Vector\Vector3.h"
#include "..\Matrix\WMatrix3.h"

WMatrix4::WMatrix4()
{
}

/*
WMatrix4::WMatrix4(Wfloat _m0, Wfloat _m1, Wfloat _m2, Wfloat _m3, Wfloat _m4, Wfloat _m5, Wfloat _m6, Wfloat _m7, Wfloat _m8, Wfloat _m9
	, Wfloat _m10, Wfloat _m11, Wfloat _m12, Wfloat _m13, Wfloat _m14, Wfloat _m15)
{
	v[0] = _m0, v[1] = _m1; v[2] = _m2; v[3] = _m3; v[4] = _m4; v[5] = _m5; v[6] = _m6; v[7] = _m7; v[8] = _m8; v[9] = _m9; v[10] = _m10; 
	v[11] = _m11; v[12] = _m12; v[13] = _m13; v[14] = _m14; v[15] = _m15;
}
*/

WMatrix4::WMatrix4(const WMatrix4& other)
{
	memcpy(this, &other, sizeof(WMatrix4));
}

WMatrix4::~WMatrix4()
{
}

Wvoid WMatrix4::Scale(WMatrix4& _out, const WMatrix4& _in, Wfloat _x, Wfloat _y, Wfloat _z)
{
	_out.v[0] *= _x;
	_out.v[5] *= _y;
	_out.v[10] *= _z;
}

Wvoid WMatrix4::RotationYawPitchRoll(WMatrix4& _out, const WMatrix4& _in, Wfloat _yaw, Wfloat _pitch, Wfloat _roll)
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

	_out.v[4] = (-sRoll * cYaw) + (cRoll * sPitch * sYaw);
	_out.v[5] = (cRoll * cPitch);
	_out.v[6] = (sRoll * sYaw) + (cRoll * sPitch * cYaw);

	_out.v[8] = (cPitch * sYaw);
	_out.v[9] = -sPitch;
	_out.v[10] = (cPitch * cYaw);
}

Wvoid WMatrix4::Translation(WMatrix4& _out, WMatrix4& _in, Vector3 _position)
{
	
	return;
}

//
//
//

void WMatrix4::BuildIdentity()
{
	v[0] = 1.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;

	v[4] = 0.0f;
	v[5] = 1.0f;
	v[6] = 0.0f;
	v[7] = 0.0f;

	v[8] = 0.0f;
	v[9] = 0.0f;
	v[10] = 1.0f;
	v[11] = 0.0f;

	v[12] = 0.0f;
	v[13] = 0.0f;
	v[14] = 0.0f;
	v[15] = 1.0f;
}

void WMatrix4::BuildView(Vector3 _position, Vector3 _rotation, Vector3 _lookAt, Vector3 _up)
{
	Vector3 zAxis, xAxis, yAxis;
	float length, result1, result2, result3;

	// Set the pitch, yaw and roll
	float pitch = _rotation.x * 0.0174532925f;
	float yaw = _rotation.y * 0.0174532925f;
	float roll = _rotation.z * 0.0174532925f;

	// Make the rotation matrix
	WMatrix3 rotationMatrix;
	WMatrix3::RotationYawPitchRoll(rotationMatrix, yaw, pitch, roll);

	// Transform the look at and the up vector
	WMatrix3::Transform(_lookAt, rotationMatrix);
	WMatrix3::Transform(_up, rotationMatrix);

	// Translate the rotated position to the look at position
	_lookAt.x = _position.x + _lookAt.x;
	_lookAt.y = _position.y + _lookAt.y;
	_lookAt.z = _position.z + _lookAt.z;

	// zAxis = normal(lookAt - position)
	zAxis.x = _lookAt.x - _position.x;
	zAxis.y = _lookAt.y - _position.y;
	zAxis.z = _lookAt.z - _position.z;
	length = sqrt((zAxis.x * zAxis.x) + (zAxis.y * zAxis.y) + (zAxis.z * zAxis.z));
	zAxis.x = zAxis.x / length;
	zAxis.y = zAxis.y / length;
	zAxis.z = zAxis.z / length;

	// xAxis = normal(cross(up, zAxis))
	xAxis.x = (_up.y * zAxis.z) - (_up.z * zAxis.y);
	xAxis.y = (_up.z * zAxis.x) - (_up.x * zAxis.z);
	xAxis.z = (_up.x * zAxis.y) - (_up.y * zAxis.x);
	length = sqrt((xAxis.x * xAxis.x) + (xAxis.y * xAxis.y) + (xAxis.z * xAxis.z));
	xAxis.x = xAxis.x / length;
	xAxis.y = xAxis.y / length;
	xAxis.z = xAxis.z / length;

	// yAxis = cross(zAxis, xAxis)
	yAxis.x = (zAxis.y * xAxis.z) - (zAxis.z * xAxis.y);
	yAxis.y = (zAxis.z * xAxis.x) - (zAxis.x * xAxis.z);
	yAxis.z = (zAxis.x * xAxis.y) - (zAxis.y * xAxis.x);

	// -dot(xAxis, _position)
	result1 = ((xAxis.x * _position.x) + (xAxis.y * _position.y) + (xAxis.z * _position.z)) * -1.0f;

	// -dot(yaxis, eye)
	result2 = ((yAxis.x * _position.x) + (yAxis.y * _position.y) + (yAxis.z * _position.z)) * -1.0f;

	// -dot(zaxis, eye)
	result3 = ((zAxis.x * _position.x) + (zAxis.y * _position.y) + (zAxis.z * _position.z)) * -1.0f;

	// Set the computed values in the view matrix.
	v[0] = xAxis.x;
	v[1] = yAxis.x;
	v[2] = zAxis.x;
	v[3] = 0.0f;

	v[4] = xAxis.y;
	v[5] = yAxis.y;
	v[6] = zAxis.y;
	v[7] = 0.0f;

	v[8] = xAxis.z;
	v[9] = yAxis.z;
	v[10] = zAxis.z;
	v[11] = 0.0f;

	v[12] = result1;
	v[13] = result2;
	v[14] = result3;
	v[15] = 1.0f;
}

void WMatrix4::BuildPerspective(float _fieldOfView, float _screenAspect, float _screenNear, float _screenDepth)
{
	v[0] = 1.0f / (_screenAspect * tan(_fieldOfView * 0.5f));
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;

	v[4] = 0.0f;
	v[5] = 1.0f / tan(_fieldOfView * 0.5f);
	v[6] = 0.0f;
	v[7] = 0.0f;

	v[8] = 0.0f;
	v[9] = 0.0f;
	v[10] = _screenDepth / (_screenDepth - _screenNear);
	v[11] = 1.0f;

	v[12] = 0.0f;
	v[13] = 0.0f;
	v[14] = (-_screenNear * _screenDepth) / (_screenDepth - _screenNear);
	v[15] = 0.0f;
}

void WMatrix4::BuildOrtho(float _fieldOfView, float _width, float _height, float _screenNear, float _screenDepth)
{
	v[0] = 2.0f / _width;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;

	v[4] = 0.0f;
	v[5] = -2.0f / _height;
	v[6] = 0.0f;
	v[7] = 0.0f;

	v[8] = 0.0f;
	v[9] = 0.0f;
	v[10] = 2.0f / (_screenDepth - _screenNear); 	
	v[11] = 0.0f;

	/*
	
	orthomatrix[3].x = -(right+left)/(right-left);
	orthomatrix[3].y = -(top+bottom)/(top-bottom);
	orthomatrix[3].z = -(Zfar+Znear)/(Zfar-Znear);
	
	*/
	// right = _width
	// left = 0
	// top = 0
	// bottom = _height

	v[12] = -1;
	v[13] = 1;
	v[14] = (_screenNear + _screenDepth) / (_screenNear - _screenDepth);
	v[15] = 1.0f;
}

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

void WMatrix4::BuildTransform(Vector3 _position, Vector3 _rotation, Vector3 _size)
{
	glm::mat4 scale = glm::mat4();;
	glm::mat4 rotation = glm::mat4();;
	glm::mat4 translation = glm::mat4();;
	glm::mat4 transform;

	//
	//
	//
	
	
	scale = glm::scale(scale, glm::vec3(_size.x, _size.y, _size.z));
	rotation = glm::eulerAngleYXZ(_rotation.x / 180.0f * glm::pi<float>(), _rotation.y / 180.0f * glm::pi<float>(), _rotation.z / 180.0f * glm::pi<float>());
	translation = glm::translate(translation, glm::vec3(_position.x, _position.y, _position.z));

	transform = translation * rotation * scale;
	
	float* matrixResult = ((float*)glm::value_ptr(transform));

	v[0] = matrixResult[0];
	v[1] = matrixResult[1];
	v[2] = matrixResult[2];
	v[3] = matrixResult[3];

	v[4] = matrixResult[4];
	v[5] = matrixResult[5];
	v[6] = matrixResult[6];
	v[7] = matrixResult[7];

	v[8] = matrixResult[8];
	v[9] = matrixResult[9];
	v[10] = matrixResult[10];
	v[11] = matrixResult[11];

	v[12] = matrixResult[12];
	v[13] = matrixResult[13];
	v[14] = matrixResult[14];
	v[15] = matrixResult[15];
}