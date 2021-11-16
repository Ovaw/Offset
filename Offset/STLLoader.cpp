#include <bits/stdc++.h>

#include "BasicDef.h"

// �_�Ƃ��̌� �ꎞ�I�ȗ��p
tmp_point* point_array[3 * MAX_NUM_TRIANGLES];
unsigned int num_tmp_points;

// �_�ɐڑ�����ӂ̃��X�g�D�ꎞ�I�ȗ��p�D
tmp_edge** connecting_edge;

// �_
double point[MAX_NUM_POINTS][3];
unsigned int num_points;

// ��
unsigned int edge[MAX_NUM_EDGES][2];
unsigned int num_edges;

// �O�p�`�|���S���̒��_�Ǝ��͂̕�
unsigned int triangle[MAX_NUM_TRIANGLES][3];
unsigned int triangle_edge[MAX_NUM_TRIANGLES][3];
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

// �_�̔�r�֐�
int compare(tmp_point* point0, tmp_point* point1)
// tmp_point *point0, tmp_point *point1; ��r�Ώۂ̓_
{

	// X���W�l�Ŕ�r�D
	if (point0->coord[X] < (point1->coord[X] - (EPS)))
		return -1;
	else if (point0->coord[X] > (point1->coord[X] + (EPS)))
		return 1;

	// Y���W�l�Ŕ�r�D
	else {
		if (point0->coord[Y] > (point1->coord[Y] - (EPS)))
			return -1;
		else if (point0->coord[Y] < (point1->coord[Y] + (EPS)))
			return 1;

		// Z���W�l�Ŕ�r�D
		else {
			if (point0->coord[Z] > (point1->coord[Z] - (EPS)))
				return -1;
			else if (point0->coord[Z] < (point1->coord[Z] + (EPS)))
				return 1;
			else
				return 0; // 2�_�͓���Ƃ݂Ȃ��D
		}
	}
}

// �_��̃N�C�b�N�\�[�g�D
void quickSort(int l, int r, tmp_point* point[])
// int l, r; �\�[�g�͈͂̍����ƉE���̃C���f�b�N�X�D
// tmp_point *point[]; �\�[�g�Ώۂ̓_��D
{
	int i, j;
	tmp_point* m_p, * swap;
	if (l < r) {
		m_p = point[(l + r) / 2];
		i = l - 1;
		j = r + 1;
		while (true) {
			while (compare(point[++i], m_p) == -1) {};
			while (compare(point[--j], m_p) == 1) {};
			if (i >= j) break;
			swap = point[i]; point[i] = point[j]; point[j] = swap;
		}
		quickSort(l, i - 1, point);
		quickSort(j + 1, r, point);
	}
}

// STL�t�@�C���̃��[�h�D
bool loadSTLFile(const char* STL_file)
// const char* STL_file; STL�t�@�C���̖��O
{
	unsigned int i, j, start, end;
	unsigned int tri_index, ver_index;
	double ref_pnt[3] = { LARGE, LARGE, LARGE };
	tmp_edge* ed, * new_ed, * next_ed;

	// �A�X�L�[�t�@�C���̓ǂݍ��݁D�ꎞ�I��point_array�Ɋi�[�����D
	if (readASCIISTLFile(STL_file))
		std::cout << "Triangles: " << num_triangles << " ";

	// �o�C�i���[�t�@�C���̓ǂݍ��݁D�ꎞ�I��point_array�Ɋi�[�����D
	else if (readBinarySTLFile(STL_file))
		std::cout << "Triangles: " << num_triangles << " ";

	// �ǂݍ��ݎ��s
	else {
		std::cout << "Cannot open file. ";
		return(false);
	}

	// ����ꂽ�_�Q���\�[�g���������W�̓_����ɂ܂Ƃ߂�
	quickSort(0, num_tmp_points - 1, point_array);

	// �\�[�g�ς݂̓_���擪����X�L�����D
	num_points = 0;
	for (i = 0; i <= num_tmp_points; i++) {

		// �Ō�̓_���Q�ƃe���g�͈قȂ�_�����������D
		if ((i == num_tmp_points)
			|| (fabs(ref_pnt[X] - (point_array[i]->coord[X])) > (EPS))
			|| (fabs(ref_pnt[Y] - (point_array[i]->coord[Y])) > (EPS))
			|| (fabs(ref_pnt[Z] - (point_array[i]->coord[Z])) > (EPS))) {

			// ������W�̓_�������������Ă���͂��D�����𓯂��_�Ƃ��ēo�^���Ȃ����D
			end = i;
			if (i > 0) {
				// �ŏ�������������D
				point[num_points][X] = ref_pnt[X];
				point[num_points][Y] = ref_pnt[Y];
				point[num_points][Z] = ref_pnt[Z];
				for (j = start; j < end; j++) {
					tri_index = point_array[j]->index / 3;
					ver_index = point_array[j]->index % 3;
					triangle[tri_index][ver_index] = num_points;
				}
				num_points++;
			}

			// �K�v�Ȃ�Q�Ɠ_���X�V����D
			if (end < num_tmp_points) {
				ref_pnt[X] = point_array[end]->coord[X];
				ref_pnt[Y] = point_array[end]->coord[Y];
				ref_pnt[Z] = point_array[end]->coord[Z];
				start = end;
			}
		}
	}

	// �ȍ~point_array�͕s�v�Ȃ̂Ń�����������D
	for (i = 0; i < num_tmp_points; i++)
		free(point_array[i]);

	// �Ō�ɕӂ�o�^����D
	num_edges = 0;

	// �e�_�ɐڑ�����ӂ̋L�^�ꏊ�̏������D
	connecting_edge = (tmp_edge**)malloc(num_points * sizeof(tmp_edge));
	for (i = 0; i < num_points; i++)
		connecting_edge[i] = NULL;

	// �e�O�p�`�̎��͂̕ӂƓo�^�ς݂̕ӂ��r�D
	for (i = 0; i < num_triangles; i++) {
		for (j = 0; j < 3; j++) {
			ed = connecting_edge[triangle[i][j]];
			while (ed != NULL) {

				// ���łɓo�^�ς݁D
				if (((ed->start == triangle[i][j])
					&& (ed->end == triangle[i][(j + 1) % 3]))
					|| ((ed->start == triangle[i][(j + 1) % 3])
						&& (ed->end == triangle[i][j])))
					goto try_next;
			}

			// ���o�^�̕ӂ����������̂ŐV���ɓo�^�D
			edge[num_edges][0] = triangle[i][j];
			edge[num_edges][1] = triangle[i][(j + 1) % 3];

			// �ӂ��O�p�`�ɂ��L�^�D
			triangle_edge[i][j] = num_edges;
			num_edges++;

			// �����ɓ_���L�^���Ă����D
			new_ed = (tmp_edge*)malloc(sizeof(tmp_edge));
			new_ed->start = triangle[i][j];
			new_ed->end = triangle[i][(j + 1) % 3];
			new_ed->next = connecting_edge[triangle[i][j]];
			connecting_edge[triangle[i][j]] = new_ed;
			new_ed = (tmp_edge*)malloc(sizeof(tmp_edge));
			new_ed->start = triangle[i][(j + 1) % 3];
			new_ed->end = triangle[i][j];
			new_ed->next = connecting_edge[triangle[i][(j + 1) % 3]];
			connecting_edge[triangle[i][(j + 1) % 3]] = new_ed;
		try_next:;
		}
	}

	// �ȍ~connecting_edge�͕s�v�Ȃ̂Ń�����������D
	for (i = 0; i < num_points; i++) {
		ed = connecting_edge[i];
		while (ed != NULL) {
			next_ed = ed->next;
			free(ed);
			ed = next_ed;
		}
	}
	free(connecting_edge);
	std::cout << "Edges: " << num_edges << " ";
	std::cout << "Point: " << num_points << std::endl;
	return(true);
}