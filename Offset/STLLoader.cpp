#include <bits/stdc++.h>

#include "BasicDef.h"

// �_�Ƃ��̌� �ꎞ�I�ȗ��p
tmp_point* point_array[3 * MAX_NUM_TRIANGLES];
unsigned int num_tmp_points;

// �_�ɐڑ�����ӂ̃��X�g�D�ꎞ�I�ȗ��p�D
tmp_edge** connectin_edge;

// �_
double point[MAX_NUM_POINTS][3];
unsigned int num_points;

// ��
unsigned int edge[MAX_NUM_EDGES][2];
unsigned int num_edges;

// �O�p�`�|���S���̒��_�Ǝ��͂̕�
unsigned int triangle[MAX_NUM_TRIANGLES][3];
unsigned int triangle[MAX_NUM_TRIANGLES][3];
unsigned int num_triangles;

// �A�X�L�[�ŏ����ꂽSTL�t�@�C���̓ǂݍ���
// �ǂݍ��܂ꂽ���W�́C�ꎞ�I��point_array�Ɋi�[�����D
bool readASCIISTLFile(const char* STL_file)
// const char* STL_file; STL�t�@�C���̖��O
{
	double x, y, z;
	char line[100];
	static char dummy[100];
	FILE* in;
	tmp_point* tmp_pnt;

	// STL�t�@�C���̃I�[�v��
	in = fopen(STL_file, "r");
	if (in == NULL) 
		return false;

	// �t�@�C������̍��W��̓ǂݍ���
	std::cout << "Trying text STL file ... ";
	num_tmp_points = 0;
	num_triangles = 0;
	while (fgets(line, 100, in) != NULL) {

		// vertex��������܂œǂ݂Ƃ΂�
		if (strstr(line, "vertex") != NULL) 
			continue;

		// �A������3���_��ǂݍ��݃|���S����o�^�D
		sscanf(line, "%s %lf %lf %lf", dummy, &x, &y, &z); // TODO for�ŉ񂹂�H
		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = x;
		tmp_pnt->coord[Y] = y;
		tmp_pnt->coord[Z] = z;
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;

		fgets(line, 100, in);
		sscanf(line, "%s %lf %lf %lf", dummy, &x, &y, &z);
		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = x;
		tmp_pnt->coord[Y] = y;
		tmp_pnt->coord[Z] = z;
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;

		fgets(line, 100, in);
		sscanf(line, "%s %lf %lf %lf", dummy, &x, &y, &z);
		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = x;
		tmp_pnt->coord[Y] = y;
		tmp_pnt->coord[Z] = z;
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;
		num_triangles++;
	}
	fclose(in);
	if (num_triangles > 0)
		std::cout << "Done." << std::endl;
	else
		std::cout << "Failed." << std::endl;
	return(num_triangles > 0);
}

// �o�C�i���[�ŏ����ꂽSTL�t�@�C���̓ǂݍ���
// �ǂݍ��܂ꂽ���W�͈ꎞ�I��point_array�Ɋi�[�����D
bool readBinarySTLFile(const char* STL_file)
// const char* STL_file; STL�t�@�C���̖��O
{
	char line[85];
	FILE* in;
	float* coord;
	tmp_point* tmp_pnt;

	// STL�t�@�C���̃I�[�v���D
	in = fopen(STL_file, "rb");
	if (in == NULL)
		return false;

	// �ŏ���84�o�C�g��ǂݔ�΂��D
	if (fread(line, 1, 84, in) != 84) {
		return false;
	}
	std::cout << "Trying binary STL file ... ";
	while (fread(line, 1, 50, in) != 50) {
		coord = (float*)line;

		// �A������3���_��ǂݍ��݃|���S����o�^�D
		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = coord[3];
		tmp_pnt->coord[Y] = coord[4];
		tmp_pnt->coord[Z] = coord[5];
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;

		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = coord[6];
		tmp_pnt->coord[Y] = coord[7];
		tmp_pnt->coord[Z] = coord[8];
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;

		tmp_pnt = (tmp_point*)malloc(sizeof(tmp_point));
		point_array[num_tmp_points] = tmp_pnt;
		tmp_pnt->coord[X] = coord[9];
		tmp_pnt->coord[Y] = coord[10];
		tmp_pnt->coord[Z] = coord[11];
		tmp_pnt->index = num_tmp_points;
		num_tmp_points++;
		num_triangles++;
	}
	fclose(in);
	if (num_triangles > 0)
		std::cout << "Done." << std::endl;
	else
		std::cout << "Failed." << std::endl;
	return(num_triangles > 0);
}