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
	printf("It took %u microseconds", microseconds);	
}

void Printv2(v2 v)
{
	printf("{ %+f, %+f }\n", v.x, v.y);
}

void Printv3(v3 v)
{
	printf("{ %+f, %+f, %+f }\n", v.x, v.y, v.z);
}

void PrintMatrix(m4x4 m)
{
	printf("{ %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f }\n",
		m.m11, m.m12, m.m13, m.m14, m.m21, m.m22, m.m23, m.m24, m.m31, m.m32, m.m33, m.m34, m.m41, m.m42, m.m43, m.m44);
}

void PrintAnimation(Animation animation)
{
	for (int i = 0; i < animation.curves_count; i++)
	{
		printf("curve: %d transform: %d, property: %d, keyframe count: %d\n", i, animation.curves[0].transform_index, animation.curves[0].channel_offset, animation.curves[0].keyframes_count);
		for (int o = 0; o < animation.curves[0].keyframes_count; o++)
		{
			KeyFrame keyframe = animation.curves[0].keyframes[o];
			printf("keyframe: %d, frame: %.3f, value: %.3f, left handle: { %.3f, %.3f }, right handle: { %.3f, %.3f }\n", o, keyframe.frame, keyframe.value, keyframe.left_handle_x, keyframe.left_handle_y, keyframe.right_handle_x, keyframe.right_handle_y);
		}
	}
}

void PrintMesh(Mesh mesh)
{
	printf("vertices: %d\n", mesh.vertices_count);
	for (int i = 0; i < mesh.vertices_count; i++)
		Printv3(mesh.vertices[i]);

	printf("indices: %d\n",  mesh.indices_count);
	for (int i = 0; i < mesh.indices_count; i += 3)
		printf("{ %d, %d, %d }\n", mesh.indices[i], mesh.indices[i + 1], mesh.indices[i + 2]);

	printf("uvs: %d\n", mesh.uvs_count);
	for (int i = 0; i < mesh.uvs_count; i++)
		Printv2(mesh.uvs[i]);

	printf("uv indices: %d\n", mesh.uv_indices_count);
	for (int i = 0; i < mesh.uv_indices_count; i += 3)
		printf("%d: { %d, %d, %d }\n", i, mesh.uv_indices[i], mesh.uv_indices[i+1], mesh.uv_indices[i+2]);

	printf("normals: %d\n", mesh.normals_count);
	for (int i = 0; i < mesh.normals_count; i++)
		Printv3(mesh.normals[i]);
}

#if GAME
void PrintIndexedMesh(int mesh_address)
{
	IndexedMesh* mesh = (IndexedMesh*)(&mesh_arena[mesh_address]);

	v3* vertices = (v3*) &((*mesh).data[(*mesh).vertices_offset]);
	printf("vertices: %d\n", (*mesh).vertices_count);
	for (int i = 0; i < (*mesh).vertices_count; ++i)
		Printv3(vertices[i]);
	
	
	int* indices = (int*) &((*mesh).data[(*mesh).indices_offset]);
	printf("indices: %d\n", (*mesh).indices_count);
	for (int i = 0; i < (*mesh).indices_count; i += 3)
		printf("%d: { %d, %d, %d }\n", i, indices[i], indices[i + 1], indices[i + 2]);


	v2* uvs = (v2*) &((*mesh).data[(*mesh).uvs_offset]);
	printf("uvs: %d\n", (*mesh).uvs_count);
	for (int i = 0; i < (*mesh).uvs_count; i++)
		Printv2(uvs[i]);


	int* uv_indices = (int*) &((*mesh).data[(*mesh).uv_indices_offset]);
	printf("uv indices: %d\n", (*mesh).uv_indices_count);
	for (int i = 0; i < (*mesh).uv_indices_count; i += 3)
		printf("%d: { %d, %d, %d }\n", i, uv_indices[i], uv_indices[i+1], uv_indices[i+2]);


	v3* normals = (v3*) &((*mesh).data[(*mesh).normals_offset]);
	printf("normals: %d\n", (*mesh).normals_count);
	for (int i = 0; i < (*mesh).normals_count; i++)
		Printv3(normals[i]);	
}
#endif