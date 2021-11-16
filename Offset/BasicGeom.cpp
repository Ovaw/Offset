#include <bits/stdc++.h>

#include "BasicDef.h"

// 2�{�̃x�N�g��vec0��vec1�̓���
double dot(double vec0[], double vec1[])
// double vec0[];
// double vec1[];
{
	return(vec0[X] * vec1[X] + vec0[Y] * vec1[Y] + vec0[Z] * vec1[Z]);
}

// 2�{�̃x�N�g��vec0��vec1�̊O��
void cross(double vec0[], double vec1[], double vec2[])
// double vec0[]
// double vec1[]
// double vec2[]
{
	vec2[X] = vec0[Y] * vec1[Z] - vec0[Z] * vec1[Y];
	vec2[Y] = vec0[Z] * vec1[X] - vec0[X] * vec1[Z];
	vec2[Z] = vec0[X] * vec1[Y] - vec0[Y] * vec1[X];
}

// �x�N�g���̐��K��
void normVec(double vec[])
// double vec[]; ���ӁI���̃x�N�g���͔j��I�ɕύX�����
{
	double norm;
	norm = sqrt(vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z]);
	vec[X] /= norm;
	vec[Y] /= norm;
	vec[Z] /= norm;
}

// 3���_���܂��ޕ��ʂ̒P�ʖ@���x�N�g���̌v�Z
void normal(double p0[], double p1[], double p2[], double normal[])
// double p0[], p1[], p2[]: �ʃ|���S���̎��͂̔����v���ɂȂ��3���_�̍��W
// double normal[]; �v�Z���ꂽ�@���x�N�g��
{
	unsigned int i;
	double v0[3], v1[3];

	// ��{�ƂȂ�2�̃x�N�g���𐶐�
	for (i = 0; i < 3; i++) {
		v0[i] = p2[i] - p1[i];
		v1[i] = p0[i] - p1[i];
	}

	// ���������x�N�g���̊O�ς��v�Z����
	cross(v0, v1, normal);

	// �O�ςɂ���ē���ꂽ�@���x�N�g���𐳋K��
	normVec(normal);
}

