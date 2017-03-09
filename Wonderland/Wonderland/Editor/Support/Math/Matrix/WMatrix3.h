////////////////////////////////////////////////////////////////////////////////
// Filename: WMatrix3.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WMatrix3_H_
#define _WMatrix3_H_

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
// Class name: WMatrix3
////////////////////////////////////////////////////////////////////////////////
class WMatrix3
{
private:

public:
	WMatrix3();
	// WMatrix3(Wfloat _m0, Wfloat _m1, Wfloat _m2, Wfloat _m3, Wfloat _m4, Wfloat _m5, Wfloat _m6, Wfloat _m7, Wfloat _m8, Wfloat _m9
	// 	, Wfloat _m10, Wfloat _m11, Wfloat _m12, Wfloat _m13, Wfloat _m14, Wfloat _m15);
	WMatrix3(const WMatrix3&);
	~WMatrix3();

	// Base Functions
	static Wvoid Determinant(Wfloat& _out, const WMatrix3& _in);
	static Wvoid Identity(WMatrix3& _out, const WMatrix3& _in);
	static Wvoid Inverse(WMatrix3& _out, const WMatrix3& _in);
	static Wvoid LookAtLH(/**/);
	static Wvoid LookAtRH(/**/);
	static Wvoid Multiply(WMatrix3& _out, WMatrix3& _left, WMatrix3& _right);
	static Wvoid MultiplyTranspose(WMatrix3& _out, WMatrix3& _left, WMatrix3& _right);
	static Wvoid OrthoLH(/**/);
	static Wvoid OrthoRH(/**/);
	static Wvoid Reflect(WMatrix3& _in);
	static Wvoid RotationAxis(/**/);
	static Wvoid RotationQuaternion(/**/);
	static Wvoid RotationX(/**/);
	static Wvoid RotationY(/**/);
	static Wvoid RotationZ(/**/);
	static Wvoid RotationYawPitchRoll(WMatrix3& _out, Wfloat _yaw, Wfloat _pitch, Wfloat _roll);	// OK n
	static Wvoid Shadow(/**/);
	static Wvoid Transpose(WMatrix3& _out, const WMatrix3& _in);
	static Wvoid Transform(Vector3& _inout, const WMatrix3& _in);

	// Specialization Functions
	void BuildIdentity();

public:

	// Union with all types of values for this vector
	union
	{
		// For "s" pattern
		struct
		{
			Wfloat
				s1, s2, s3,
				s4, s5, s6,
				s7, s8, s9;
		};

		// For "m" pattern
		struct
		{
			Wfloat
				m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22;
		};

		// For the number pattern
		struct
		{
			Wfloat
				_01, _02, _03,
				_10, _11, _12,
				_20, _21, _22;
		};

		// For the index pattern
		struct
		{
			Wfloat m[3][3];
		};

		// Base
		Wfloat v[9];
	};

};

#endif
