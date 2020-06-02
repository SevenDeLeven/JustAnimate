/*
 * Model.cpp
 *
 *  Created on: Mar 30, 2020
 *      Author: Kyle Karnitz
 */

#include "Model.h"


#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "../render/animation/Joint.h"

#include "../tinyxml/tinyxml.h"

Model::Model(int vertexCount, GLuint vao, GLuint vbo, GLuint uvbo, GLuint nvbo) {
	this->vertexCount = vertexCount;
	this->vao = vao;
	this->vbo = vbo;
	this->uvbo = uvbo;
	this->nvbo = nvbo;
}

Model::~Model() {

}

int Model::getVertexCount() {
	return this->vertexCount;
}

void Model::bind() {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, this->nvbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 0, 0);
}

void Model::unbind() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}










Model* loadCollada(const char* filename) {
	TiXmlDocument doc(filename);
	doc.LoadFile();

	TiXmlElement* colladaBase = doc.FirstChildElement();
	TiXmlElement* geomBase = colladaBase->FirstChildElement("library_geometries");
	TiXmlElement* contrBase = colladaBase->FirstChildElement("library_controllers"); //For the Controllers
	TiXmlElement* controller = contrBase->FirstChildElement();
	TiXmlElement* skin = controller->FirstChildElement();
	TiXmlElement* model = geomBase->FirstChildElement();
	const char* modelName = model->Attribute("id");
	TiXmlElement* mesh = model->FirstChildElement();
	TiXmlElement* positions = mesh->FirstChildElement();
	float* pos;
	{
		TiXmlElement* posArray = positions->FirstChildElement("float_array");
		std::stringstream conv(posArray->Attribute("count"));
		int count = 0;
		conv >> count;
		conv = std::stringstream(posArray->GetText());
		pos = new float[count];
		for (int i = 0; i < count; i++) {
			float n;
			conv >> n;
			pos[i] = n;
		}
	}
	TiXmlElement* normals = positions->NextSiblingElement();
	float* norm;
	{
		TiXmlElement* normArray = normals->FirstChildElement("float_array");
		std::stringstream conv(normArray->Attribute("count"));
		int count = 0;
		conv >> count;
		conv = std::stringstream(normArray->GetText());
		norm = new float[count];
		for (int i = 0; i < count; i++) {
			float n;
			conv >> n;
			norm[i] = n;
		}
	}

	TiXmlElement* texCoords = normals->NextSiblingElement();
	float* tex;
	{
		TiXmlElement* texArray = texCoords->FirstChildElement("float_array");
		std::stringstream conv(texArray->Attribute("count"));
		int count = 0;
		conv >> count;
		conv = std::stringstream(texArray->GetText());
		tex = new float[count];
		for (int i = 0; i < count; i++) {
			float n;
			conv >> n;
			tex[i] = n;
		}
	}

	float* correctPos;
	float* correctNorm;
	float* correctTex;
	int vertexCount;
	{
		TiXmlElement* triangles = mesh->FirstChildElement("triangles");
		std::stringstream conv(triangles->Attribute("count"));
		conv >> vertexCount;
		vertexCount *= 3;
		conv = std::stringstream(triangles->FirstChildElement("p")->GetText());
		std::cout << triangles->FirstChildElement("p")->GetText() << std::endl;
		correctPos = new float[3*vertexCount];
		correctNorm = new float[3*vertexCount];
		correctTex = new float[2*vertexCount];
		for (int i = 0; i < vertexCount; i++) {
			int vindex;
			int nindex;
			int tindex;
			conv >> vindex >> nindex >> tindex;
			std::cout << i << ":  " << vindex << " " << nindex << " " << tindex << std::endl;
			for (int p = 0; p < 3; p++) {
				correctPos[(i*3)+p] = pos[(vindex*3)+p];
				correctNorm[(i*3)+p] = norm[(nindex*3)+p];
			}
			for (int p = 0; p < 2; p++) {
				correctTex[(i*2)+p] = tex[p+tindex];
			}
		}
	}

	std::vector<Joint*> joints;
	TiXmlElement* jointsAnim = skin->FirstChildElement("source");
	{

		TiXmlElement* nameArray = jointsAnim->FirstChildElement("Name_array");
		std::stringstream buff(nameArray->Attribute("count"));
		int jointCount;
		buff >> jointCount;
		buff = std::stringstream(nameArray->GetText());
		for (int i = 0; i < jointCount; i++) {
			int id = i;
			std::string name;
			buff >> name;
			Joint* j = new Joint(id, name.c_str());
			joints.push_back(j);
		}
	}

	TiXmlElement* bindPoses = jointsAnim->NextSiblingElement();
	{
		TiXmlElement* matrixData = bindPoses->FirstChildElement("float_array");
		std::stringstream buff(matrixData->GetText());
		for (unsigned int i = 0; i < joints.size(); i++) {
			float matrixArray[16];
			for (int t = 0; t < 16; t++) {
				buff >> matrixArray[t];
			}

			glm::mat4 invBindTransform = glm::make_mat4(matrixArray);
			joints[i]->setInverseBindTransform(invBindTransform);
		}
	}


	TiXmlElement* weightsElement = bindPoses->NextSiblingElement("source");
	TiXmlElement* vertexWeightsElement = weightsElement->NextSiblingElement("vertex_weights");
	int* correctVertexJointIds = new int[vertexCount*3];
	float* correctVertexWeights = new float[vertexCount*3];
	{
		TiXmlElement* weightsArrayElement = weightsElement->FirstChildElement("float_array");
		std::stringstream buff(weightsArrayElement->Attribute("count"));
		int weightCount;
		buff >> weightCount;
		buff = std::stringstream(weightsArrayElement->GetText());

		float indexedweights[weightCount];

		for (int i = 0; i < weightCount; i++) {
			buff >> indexedweights[i];
		}

		int vertexWeightAmounts[vertexCount];
		TiXmlElement* vcount = vertexWeightsElement->FirstChildElement("vcount");
		buff = std::stringstream(vcount->GetText());
		for (int i = 0; i < vertexCount; i++) {
			int a;
			buff >> a;
			vertexWeightAmounts[i] = a;
		}

		TiXmlElement* v = vertexWeightsElement->FirstChildElement("v");
		buff = std::stringstream(v->GetText());
		for (int i = 0; i < vertexCount; i++) {
			std::vector<int> joints;
			std::vector<float> weights;

			std::cout << vertexWeightAmounts[i] << std::endl;
			for (int j = 0; j < vertexWeightAmounts[i]; j++) {
				int jointId;
				int weightId;
				buff >> jointId >> weightId;
				joints.push_back(jointId);
				weights.push_back(indexedweights[weightId]);
			}

			for (unsigned int j = 0; j < 3-joints.size(); j++) {
				joints.push_back(0);
				weights.push_back(0);
			}

			if (joints.size() > 3) {
				int njoints[3] = {0};
				int nweights[3] = {0};
				for (int ji = 0; ji < vertexWeightAmounts[i]; ji++) {
					if (weights[ji] > nweights[0]) {
						nweights[2] = nweights[1];
						nweights[1] = nweights[0];
						nweights[0] = weights[ji];
						njoints[2] = njoints[1];
						njoints[1] = njoints[0];
						njoints[0] = joints[ji];
					} else if (weights[ji] > nweights[1]) {
						nweights[2] = nweights[1];
						nweights[1] = weights[ji];
						njoints[2] = njoints[1];
						njoints[1] = joints[ji];
					} else if (weights[ji] > nweights[2]) {
						nweights[2] = weights[ji];
						njoints[2] = joints[ji];
					}
				}
				joints = std::vector<int>();
				weights = std::vector<float>();

				float sumWeights = 0;
				for (int p = 0; p < 3; p++) {
					joints.push_back(njoints[p]);
					weights.push_back(nweights[p]);

					sumWeights += nweights[p];
				}
				for (int p = 0; p < 3; p++) {
					weights[i] /= sumWeights; //Normalize all weights so that they sum up to 1
				}

			} else {
				for (unsigned int t = 0; t < 3-joints.size(); t++) {
					joints.push_back(1);
					weights.push_back(0);
				}
			}

			for (int v = 0; v < 3; v++) {
				correctVertexJointIds[i*3+v] = joints[v];
				correctVertexWeights[i*3+v] = weights[v];
			}
		}
	}


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(float), &correctPos[0], GL_STATIC_DRAW);

	GLuint nvbo;
	glGenBuffers(1, &nvbo);
	glBindBuffer(GL_ARRAY_BUFFER, nvbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(float), &correctNorm[0], GL_STATIC_DRAW);

	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*2*sizeof(float), &correctTex[0], GL_STATIC_DRAW);

	GLuint jointvbo;
	glGenBuffers(1, &jointvbo);
	glBindBuffer(GL_ARRAY_BUFFER, jointvbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(int), &correctVertexJointIds, GL_STATIC_DRAW);

	GLuint weightvbo;
	glGenBuffers(1, &weightvbo);
	glBindBuffer(GL_ARRAY_BUFFER, weightvbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*3*sizeof(float), &correctVertexWeights, GL_STATIC_DRAW);

	delete pos;
	delete norm;
	delete tex;
	delete correctPos;
	delete correctNorm;
	delete correctTex;
	delete correctVertexJointIds;
	delete correctVertexWeights;

	Model* ret = new Model(vertexCount, vao, vbo, uvbo, nvbo);

	return ret;
}

Model* loadOBJ(const char* filename) {
	std::FILE* file = std::fopen(filename, "r");

	std::vector< glm::vec3 > out_vertices;
	std::vector< glm::vec2 > out_uvs;
	std::vector< glm::vec3 > out_normals;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	while (true) {
		char header[128];
		std::fscanf(file, "%s", header);
		if (strcmp(header, "v") == 0) {
			glm::vec3 vert;
			std::fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
			temp_vertices.push_back(vert);
		} else if (strcmp(header, "vt") == 0) {
			glm::vec2 uv;
			std::fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		} else if (strcmp(header, "vn") == 0) {
			glm::vec3 norm;
			std::fscanf(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
			temp_normals.push_back(norm);
		} else if (strcmp(header, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vindex[3], uindex[3], nindex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vindex[0], &uindex[0], &nindex[0], &vindex[1], &uindex[1], &nindex[1], &vindex[2], &uindex[2], &nindex[2]);
			if (matches != 9) {
				std::cerr << "Could not load file " << filename << " due to face indices format mismatch" << std::endl;
				return nullptr;
			}
			vertexIndices.push_back(vindex[0]);
			vertexIndices.push_back(vindex[1]);
			vertexIndices.push_back(vindex[2]);
			uvIndices.push_back(uindex[0]);
			uvIndices.push_back(uindex[1]);
			uvIndices.push_back(uindex[2]);
			normalIndices.push_back(nindex[0]);
			normalIndices.push_back(nindex[1]);
			normalIndices.push_back(nindex[2]);
		}
	}

	for ( unsigned int i = 0; i < vertexIndices.size(); i++ ) {
		unsigned int vIndex = vertexIndices[i];
		glm::vec3 vert = temp_vertices[vIndex - 1];
		out_vertices.push_back(vert);
	}

	for ( unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uIndex - 1];
		out_uvs.push_back(uv);
	}

	for ( unsigned int i = 0; i < normalIndices.size(); i++ ) {
		unsigned int nIndex = normalIndices[i];
		glm::vec3 norm = temp_normals[nIndex - 1];
		out_normals.push_back(norm);
	}


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, out_uvs.size() * sizeof(glm::vec2), &out_uvs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint nvbo;
	glGenBuffers(1, &nvbo);
	glBindBuffer(GL_ARRAY_BUFFER, nvbo);
	glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	Model* ret = new Model(out_vertices.size(), vao, vbo, uvbo, nvbo);

	return ret;
}
