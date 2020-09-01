bool view_debug = false;

__int64 freq, start, end, diff;
void StartTiming()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&start);
}

void EndTiming()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&end);
	diff = ((end - start) * 1000000) / freq;
	unsigned int microseconds = (unsigned int)(diff & 0xffffffff);
	printf("It took %u microseconds\n", microseconds);	
}

void PrintMatrix(m4x4 m)
{
	printf("{ %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f }\n",
		m.m11, m.m12, m.m13, m.m14, m.m21, m.m22, m.m23, m.m24, m.m31, m.m32, m.m33, m.m34, m.m41, m.m42, m.m43, m.m44);
}

void PrintAnimation(Animation animation)
{
	for (size_t i = 0; i < animation.curves_length; i++)
	{
		printf("curve: %d transform: %d, property: %d, keyframe count: %d\n", i, animation.curves[0].transform_index, animation.curves[0].channel_offset, animation.curves[0].keyframes_length);
		for (size_t o = 0; o < animation.curves[0].keyframes_length; o++)
		{
			KeyFrame keyframe = animation.curves[0].keyframes[o];
			printf("keyframe: %d, frame: %.3f, value: %.3f, left handle: { %.3f, %.3f }, right handle: { %.3f, %.3f }\n", o, keyframe.frame, keyframe.value, keyframe.left_handle_x, keyframe.left_handle_y, keyframe.right_handle_x, keyframe.right_handle_y);
		}
	}
}

void PrintMesh(Mesh mesh)
{
	printf("indices: %d\n",  mesh.indices_length);
	for (int i = 0; i < mesh.indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);
	}

	printf("vertices:\n");
	for (int i = 0; i < mesh.vertices_length; i++)
	{
		printf("{ %+f, %+f, %+f }\n", mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
	}

	printf("uvs:\n");
	for (int i = 0; i < mesh.uvs_length; i++)
	{
		printf("{ %+f, %+f }\n", mesh.uvs[i].x, mesh.uvs[i].y);
	}

	printf("uv indices:\n");
	for (int i = 0; i < mesh.uv_indices_length; i += 3)
	{
		printf("{ %d, %d, %d }\n", mesh.uv_indices[i], mesh.uv_indices[i + 1], mesh.uv_indices[i + 2]);
	}

	printf("normals:\n");
	for (int i = 0; i < mesh.normals_length; i++)
	{
		printf("{ %+f, %+f, %+f }\n", mesh.normals[i].x, mesh.normals[i].y, mesh.normals[i].z);
	}

}