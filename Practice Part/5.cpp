//Гоголев Михаил Александрович
#include <iostream>
#include <memory.h>
using namespace std;

struct mat4 {
	mat4() {
		memset(m, 0, sizeof(float) * 16);
		m[0] = m[5] = m[10] = m[15] = 1.0f;
	}

	float m[16];
};

struct vec3 {
	vec3(float _x, float _y, float _z, float _added) {
		x = _x;
		y = _y;
		z = _z;
		added = _added;

	}

	float x;
	float y;
	float z;
	float added;
};

vec3 multiply(mat4 matrix, vec3 vec) {
	/*
	матрица 4х4 вектор 3
	добавил еще одну переменную в вектор
	vec3(1.0f, 2.0f, 3.0f,4.0f);
	*/

	float x = matrix.m[0] * vec.x + matrix.m[1] * vec.y + matrix.m[2] * vec.z + matrix.m[3] * vec.added;
	float y = matrix.m[4] * vec.x + matrix.m[5] * vec.y + matrix.m[6] * vec.z + matrix.m[7] * vec.added;
	float z = matrix.m[8] * vec.x + matrix.m[9] * vec.y + matrix.m[10] * vec.z + matrix.m[11] * vec.added;
	float added = matrix.m[12] * vec.x + matrix.m[13] * vec.y + matrix.m[14] * vec.z + matrix.m[15] * vec.added;

	return vec3(x, y, z, added);
}

int main(int argc, char** argv) {
	mat4 matrix;

	matrix.m[0] = 2.0f;
	matrix.m[5] = 1.5f;
	matrix.m[14] = 1.5f;

	vec3 vec = vec3(1.0f, 2.0f, 3.0f, 4.0f);
	vec3 result = multiply(matrix, vec);

	cout << "x = " << result.x << " y = " << result.y << " z = " << result.z << " added = " << result.added << std::endl;


	cin.get();
	return 0;
}
