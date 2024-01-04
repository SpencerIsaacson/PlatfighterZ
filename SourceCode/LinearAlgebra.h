#define m4x4_identity ((m4x4){1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1})
#define v3_right {1, 0, 0}
#define v3_forward { 0, 0, 1 }
#define v3_backward { 0, 0, -1 }
#define v3_zero { 0, 0, 0 }
#define v3_one { 1, 1, 1 }

Transform DefaultTransform()
{
	return (Transform)
	{
		.parent = -1,
		.position = v3_zero,
		.rotation = v3_zero,
		.scale = v3_one
	};
}

v3 v3_NegateVector(v3 v)
{
	return (v3){ -v.x, -v.y, -v.z };
}

m4x4 Translation(float x, float y, float z)
{
	return (m4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 };
}

m4x4 Scale(float x, float y, float z)
{
	return (m4x4){ x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1 };
}

m4x4 Rotation(float x, float y, float z)
{

	return (m4x4)
	{
		.m11 = (float)(cos(y) * cos(z) - sin(y) * sin(x) * sin(z)),
		.m12 = (float)(cos(y) * sin(z) + sin(y) * sin(x) * cos(z)),
		.m13 = (float)(-sin(y) * cos(x)),
		.m14 = 0,
		.m21 = (float)(-sin(z) * cos(x)),
		.m22 = (float)(cos(z) * cos(x)),
		.m23 = (float)(sin(x)),
		.m24 = 0,
		.m31 = (float)(sin(y) * cos(z) + cos(y) * sin(x) * sin(z)),
		.m32 = (float)(sin(z) * sin(y) - cos(y) * sin(x) * cos(z)),
		.m33 = (float)(cos(y) * cos(x)),
		.m34 = 0,
		.m41 = 0,
		.m42 = 0,
		.m43 = 0,
		.m44 = 1,
	};
}

m4x4 Perspective(float near_plane, float far_plane, float field_of_view, float width, float height) //TODO redo to match your 
{
	float aspect_ratio = height / width;
	float zoom = (float)(1 / tan(field_of_view / 2));
	float q = far_plane / (far_plane - near_plane);

	m4x4 result =
	{
		aspect_ratio * zoom, 0, 0, 0,
		0, -zoom, 0, 0,
		0, 0, q, near_plane * q,
		0, 0, 1, 0
	};

	return result;
}

v3 v3_Add(v3 a, v3 b)
{
	return (v3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

v3 v3_Subtract(v3 a, v3 b)
{
	return (v3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

v3 v3_Scale(v3 v, float s)
{
	return (v3){ v.x * s, v.y * s, v.z * s };
}

v3 v3_Divide(v3 v, float s)
{
	return (v3){ v.x / s, v.y / s, v.z / s };
}

float v3_DotProduct(v3 a, v3 b) 
{ 
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

v3 v3_CrossProduct(v3 a, v3 b)
{
	return (v3)
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};
}

float v3_Magnitude(v3 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec4 v4_Divide(Vec4 v, float s)
{
	return (Vec4){ v.x / s, v.y / s, v.z / s, v.w / s };
}


v3 v3_Normalized(v3 v)
{
	return v3_Divide(v, v3_Magnitude(v));
}

float v3_Distance(v3 a, v3 b)
{
	return v3_Magnitude(v3_Subtract(a,b));
}

v2 v2_Add(v2 a, v2 b)
{
	return (v2){ a.x + b.x, a.y + b.y };
}

v2 v2_Subtract(v2 a, v2 b)
{
	return (v2){ a.x - b.x, a.y - b.y };
}

v2 v2_Scale(v2 v, float s)
{
	return (v2){ v.x * s, v.y * s};
}

v2 v2_Divide(v2 v, float s)
{
	return (v2){ v.x / s, v.y / s};
}

float v2_DotProduct(v2 a, v2 b) 
{ 
	return a.x * b.x + a.y * b.y; 
}

float v2_Magnitude(v2 v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y);
}

v2 v2_Normalized(v2 v)
{
	return v2_Divide(v, v2_Magnitude(v));
}


float v2_Distance(v2 a, v2 b)
{
	return v2_Magnitude(v2_Subtract(a,b));
}

Transform InvertTransform(Transform t)
{
	t.position = v3_NegateVector(t.position);
	t.rotation = v3_NegateVector(t.rotation);
	t.scale.x = 1 / t.scale.x;
	t.scale.y = 1 / t.scale.y;
	t.scale.z = 1 / t.scale.z;
	return t;
}

m4x4 Concatenate(m4x4 a, m4x4 b)
{
	return (m4x4)
	{
		.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41,
		.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42,
		.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43,
		.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44,
		.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41,
		.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42,
		.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43,
		.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44,
		.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41,
		.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42,
		.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43,
		.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44,
		.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41,
		.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42,
		.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43,
		.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44,
	};
}

m4x4 GetMatrix(Transform t)
{
	m4x4 result = m4x4_identity;
	result = Concatenate(result, Scale(t.scale.x, t.scale.y, t.scale.z));
	result = Concatenate(result, Rotation(t.rotation.x, t.rotation.y, t.rotation.z));
	result = Concatenate(result, Translation(t.position.x, t.position.y, t.position.z));
	return result;
}

m4x4 WorldSpaceMatrix(int index, Transform hierarchy[])
{
	Transform t = hierarchy[index];
	m4x4 m = GetMatrix(t);
	while (t.parent != -1)
	{
		m = Concatenate(m, GetMatrix(hierarchy[t.parent]));
		t = hierarchy[t.parent];
	}

	return m;
}

v3 Transform_v3(m4x4 m, v3 v)
{
	return (v3)
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43,
	};
}

Vec4 Transform_v4(m4x4 m, Vec4 v)
{
	return (Vec4)
	{
		m.m11 * v.x + m.m21 * v.y + m.m31 * v.z + m.m41 * v.w,
		m.m12 * v.x + m.m22 * v.y + m.m32 * v.z + m.m42 * v.w,
		m.m13 * v.x + m.m23 * v.y + m.m33 * v.z + m.m43 * v.w,
		m.m14 * v.x + m.m24 * v.y + m.m34 * v.z + m.m44 * v.w,
	};
}

m4x4 Transpose(m4x4 m)
{
	return (m4x4){ m.m11, m.m21, m.m31, m.m41, m.m12, m.m22, m.m32, m.m42, m.m13, m.m23, m.m33, m.m43, m.m14, m.m24, m.m34, m.m44 };
}