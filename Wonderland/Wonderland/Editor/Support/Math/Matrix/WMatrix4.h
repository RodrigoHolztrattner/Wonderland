////////////////////////////////////////////////////////////////////////////////
// Filename: WMatrix4.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WMatrix4_H_
#define _WMatrix4_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <math.h>
#include "..\Primitive\Primitives.h"

/////////////
// DEFINES //
/////////////

// Pre declarations
class Vector3;

////////////////////////////////////////////////////////////////////////////////
// Class name: WMatrix4
////////////////////////////////////////////////////////////////////////////////
class WMatrix4
{
private:

public:
	WMatrix4();
	// WMatrix4(Wfloat _m0, Wfloat _m1, Wfloat _m2, Wfloat _m3, Wfloat _m4, Wfloat _m5, Wfloat _m6, Wfloat _m7, Wfloat _m8, Wfloat _m9
	// 	, Wfloat _m10, Wfloat _m11, Wfloat _m12, Wfloat _m13, Wfloat _m14, Wfloat _m15);
	WMatrix4(const WMatrix4&);
	~WMatrix4();

	// Base Functions
	static Wvoid Determinant(Wfloat& _out, const WMatrix4& _in);
	static Wvoid Identity(WMatrix4& _out, const WMatrix4& _in);
	static Wvoid Inverse(WMatrix4& _out, const WMatrix4& _in);
	static Wvoid LookAtLH(/**/);
	static Wvoid LookAtRH(/**/);
	static Wvoid Multiply(WMatrix4& _out, WMatrix4& _left, WMatrix4& _right);
	static Wvoid MultiplyTranspose(WMatrix4& _out, WMatrix4& _left, WMatrix4& _right);
	static Wvoid OrthoLH(/**/);
	static Wvoid OrthoRH(/**/);
	static Wvoid Scale(WMatrix4& _out, const WMatrix4& _in, Wfloat _x, Wfloat _y, Wfloat _z);
	static Wvoid Reflect(WMatrix4& _in);
	static Wvoid RotationAxis(/**/);
	static Wvoid RotationQuaternion(/**/);
	static Wvoid RotationX(/**/);
	static Wvoid RotationY(/**/);
	static Wvoid RotationZ(/**/);
	static Wvoid RotationYawPitchRoll(WMatrix4& _out, const WMatrix4& _in, Wfloat _yaw, Wfloat _pitch, Wfloat _roll);
	static Wvoid Shadow(/**/);
	static Wvoid Translation(WMatrix4& _out, WMatrix4& _in, Vector3 _position);
	static Wvoid Transpose(WMatrix4& _out, const WMatrix4& _in);

	// Specialization Functions
	void BuildIdentity();
	void BuildView(Vector3 _position, Vector3 _rotation, Vector3 _lookAt, Vector3 _up);												// OK - N
	void BuildPerspective(float _fieldOfView, float _screenAspect, float _screenNear, float _screenDepth);
	void BuildOrtho(float _fieldOfView, float _width, float _height, float _screenNear, float _screenDepth);
	void BuildTransform(Vector3 _position, Vector3 _rotation, Vector3 _size);

public:

	// Union with all types of values for this vector
	union
	{
		// For "s" pattern
		struct
		{
			Wfloat
				s1, s2, s3, s4,
				s5, s6, s7, s8,
				s9, s10, s11, s12,
				s13, s14, s15, s16;
		};

		// For "m" pattern
		struct
		{
			Wfloat
				m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
		};

		// For the number pattern
		struct
		{
			Wfloat
				_01, _02, _03, _04,
				_10, _11, _12, _13,
				_20, _21, _22, _23,
				_30, _31, _32, _33;
		};

		// For the index pattern
		struct
		{
			Wfloat m[4][4];
		};

		// Base
		Wfloat v[16];
	};

};

#endif
