//Following-Cyborgs-2019

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm.hpp"
#include "GL/ext.hpp"
#include "GL/gtc/matrix_transform.hpp"
#include "GL/freeglut_ext.h"
#define PI 3.14159265359

using namespace std;
int gwidth = 1200;
int gheight = 600;

bool pendingTimerStop = false;

bool fillMode = true;

bool wKey = false;
bool sKey = false;
bool aKey = false;
bool dKey = false;

bool jKey = false;

bool oKey = false;
bool pKey = false;

bool lKey = false;
bool kKey = false;

bool catched[4];

bool metBot[4];

GLuint programID;

GLuint VAO[10];
GLuint VBO[10];

glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 defaultMatrix = glm::mat4(1.0f);
glm::mat4 rotMatrix = glm::mat4(1.0f);
glm::mat4 transMatrix = glm::mat4(1.0f);
glm::mat4 downMatrix = glm::mat4(1.0f);
glm::mat4 upMatrix = glm::mat4(1.0f);
glm::mat4 scaleMatrix = glm::mat4(1.0f);
glm::mat4 dirMatrix = glm::mat4(1.0f);
glm::mat4 lastDownMatrix = glm::mat4(1.0f);

glm::mat4 catchedTopMatrix = glm::mat4(1.0f);
glm::mat4 catchedBottomMatrix = glm::mat4(1.0f);

glm::mat4 jumpMatrix[5];

glm::mat4 camTransMatrix = glm::mat4(1.0f);

glm::mat4 camMatrix = glm::mat4(1.0f);

glm::mat4 camRotMatrix = glm::mat4(1.0f);
glm::mat4 camRevMatrix = glm::mat4(1.0f);
glm::mat4 camViewMatrix = glm::mat4(1.0f);
float camViewX = 0.f;
float camViewZ = 0.f;
float camViewY = 0.f;
float camDown = 0.f;

glm::mat4 roomMatrix = glm::mat4(1.0f);
glm::mat4 boxMatrix = glm::mat4(1.0f);
glm::mat4 headMatrix = glm::mat4(1.0f);
glm::mat4 noseMatrix = glm::mat4(1.0f);
glm::mat4 bodyMatrix = glm::mat4(1.0f);
glm::mat4 leftLegMatrix = glm::mat4(1.0f);
glm::mat4 rightLegMatrix = glm::mat4(1.0f);
glm::mat4 leftArmMatrix = glm::mat4(1.0f);
glm::mat4 rightArmMatrix = glm::mat4(1.0f);

float rotValue[4];
bool rotDir[4];
float botRotValue = 0.f;
bool botRotDir = true;
int viewType = 3;

float jumpValue[5];
float nowJump[5];
float openDoorValue = 0.f;

float verticalValue[4];
float horizonValue[4];
float dirValue[5];

int botDir[4];
int walkCount[4];

int catchNum[4];
int catchCnt = 0;

float botLoc[4];

float camVerticalValue = -1.1f;
float camHorizonValue = 0.f;
float myVerticalValue = 0.f;
float myHorizonValue = 0.f;
float camRotValue = 0.f;
float camRevValue = 0.f;

float viewAngle = 0.f;

float vertexData[216] =
{
		//왼
		-0.2, -0.2, 0.2, 1.0, 0.6, 0.6,
		-0.2, 0.2, 0.2, 1.0, 0.6, 0.6,
		-0.2, 0.2, -0.2, 1.0, 0.6, 0.6,

		-0.2, -0.2, -0.2, 1.0, 0.6, 0.6,
		-0.2, -0.2, 0.2, 1.0, 0.6, 0.6,
		-0.2, 0.2, -0.2, 1.0, 0.6, 0.6,
		//오른
		0.2, 0.2, -0.2, 1.0, 0.7, 0.7,
		0.2, 0.2, 0.2, 1.0, 0.7, 0.7,
		0.2, -0.2, 0.2, 1.0, 0.7, 0.7,

		0.2, -0.2, -0.2, 1.0, 0.7, 0.7,
		0.2, 0.2, -0.2, 1.0, 0.7, 0.7,
		0.2, -0.2, 0.2, 1.0, 0.7, 0.7,
		//뒤
		-0.2, -0.2, -0.2, 1.0, 0.8, 0.8,
		-0.2, 0.2, -0.2, 1.0, 0.8, 0.8,
		0.2, 0.2, -0.2, 1.0, 0.8, 0.8,

		0.2, -0.2, -0.2, 1.0, 0.8, 0.8,
		-0.2, -0.2, -0.2, 1.0, 0.8, 0.8,
		0.2, 0.2, -0.2, 1.0, 0.8, 0.8,
		//밑
		-0.2, -0.2, 0.2, 1.0, 0.9, 0.9,
		-0.2, -0.2, -0.2, 1.0, 0.9, 0.9,
		0.2, -0.2, -0.2, 1.0, 0.9, 0.9,

		0.2, -0.2, 0.2, 1.0, 0.9, 0.9,
		-0.2, -0.2, 0.2, 1.0, 0.9, 0.9,
		0.2, -0.2, -0.2, 1.0, 0.9, 0.9,
		//위
		0.2, 0.2, -0.2, 1.0, 0.4, 0.4,
		-0.2, 0.2, -0.2, 1.0, 0.4, 0.4,
		-0.2, 0.2, 0.2, 1.0, 0.4, 0.4,

		0.2, 0.2, -0.2, 1.0, 0.4, 0.4,
		-0.2, 0.2, 0.2, 1.0, 0.4, 0.4,
		0.2, 0.2, 0.2, 1.0, 0.4, 0.4,
	    //앞
		0.2, 0.2, 0.2, 1.0, 0.5, 0.5,
		-0.2, 0.2, 0.2, 1.0, 0.5, 0.5,
		-0.2, -0.2, 0.2, 1.0, 0.5, 0.5,

		0.2, 0.2, 0.2, 1.0, 0.5, 0.5,
		-0.2, -0.2, 0.2, 1.0, 0.5, 0.5,
		0.2, -0.2, 0.2, 1.0, 0.5, 0.5,
};

float roomVertexData[216] =
{
	//앞
-0.2, -0.2, 0.2, 0.9, 0.9, 1.0,
-0.2, 0.2, 0.2, 0.9, 0.9, 1.0,
0.2, 0.2, 0.2, 0.9, 0.9, 1.0,

0.2, -0.2, 0.2, 0.9, 0.9, 1.0,
-0.2, -0.2, 0.2, 0.9, 0.9, 1.0,
0.2, 0.2, 0.2, 0.9, 0.9, 1.0,
//왼
-0.2, 0.2, -0.2, 0.7, 0.7, 1.0,
-0.2, 0.2, 0.2, 0.7, 0.7, 1.0,
-0.2, -0.2, 0.2, 0.7, 0.7, 1.0,

-0.2, 0.2, -0.2, 0.7, 0.7, 1.0,
-0.2, -0.2, 0.2, 0.7, 0.7, 1.0,
-0.2, -0.2, -0.2, 0.7, 0.7, 1.0,
//오른
0.2, -0.2, 0.2, 0.5, 0.5, 1.0,
0.2, 0.2, 0.2, 0.5, 0.5, 1.0,
0.2, 0.2, -0.2, 0.5, 0.5, 1.0,

0.2, -0.2, 0.2, 0.5, 0.5, 1.0,
0.2, 0.2, -0.2, 0.5, 0.5, 1.0,
0.2, -0.2, -0.2, 0.5, 0.5, 1.0,
//뒤
0.2, 0.2, -0.2, 0.8, 0.8, 1.0,
-0.2, 0.2, -0.2, 0.8, 0.8, 1.0,
-0.2, -0.2, -0.2, 0.8, 0.8, 1.0,

0.2, 0.2, -0.2, 0.8, 0.8, 1.0,
-0.2, -0.2, -0.2, 0.8, 0.8, 1.0,
0.2, -0.2, -0.2, 0.8, 0.8, 1.0,
//밑
0.2, -0.2, -0.2, 0.6, 0.6, 1.0,
-0.2, -0.2, -0.2, 0.6, 0.6, 1.0,
-0.2, -0.2, 0.2, 0.6, 0.6, 1.0,

0.2, -0.2, -0.2, 0.6, 0.6, 1.0,
-0.2, -0.2, 0.2, 0.6, 0.6, 1.0,
0.2, -0.2, 0.2, 0.6, 0.6, 1.0,
//위
-0.2, 0.2, 0.2, 0.6, 0.6, 1.0,
-0.2, 0.2, -0.2, 0.6, 0.6, 1.0,
0.2, 0.2, -0.2, 0.6, 0.6, 1.0,

0.2, 0.2, 0.2, 0.6, 0.6, 1.0,
-0.2, 0.2, 0.2, 0.6, 0.6, 1.0,
0.2, 0.2, -0.2, 0.6, 0.6, 1.0,
};

float rangeVertexData[366];

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, ios::in);
	if (VertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음\n", vertex_file_path);
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음\n", fragment_file_path);
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// 버텍스 쉐이더를 컴파일
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// 프래그먼트 쉐이더를 컴파일
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
	int w = gwidth;
	int h = gheight;
	*ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

void Mouse(int button, int state, int x, int y)
{
	float ox;
	float oy;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		convertDeviceXY2OpenglXY(x, y, &ox, &oy);
		cout << "x = " << ox << " y = " << oy << endl;
	}
}

void Timer(int n)
{
	// 카메라맨 1인칭 or 3인칭 시점 선택
	if (viewType)
	{
		camViewMatrix = glm::mat4(1.0f);
		camViewMatrix = glm::translate(camViewMatrix, glm::vec3(0.f, -0.1f, -0.4f));
	}
	else
	{
		camViewMatrix = glm::mat4(1.0f);
	}

	// 카메라 Translate
	// 카메라맨의 몸의 방향도 바뀐다.
	if (wKey)
	{
		camVerticalValue += (float)cos(viewAngle * PI / 180) / 30;
		camHorizonValue -= (float)sin(viewAngle * PI / 180) / 30;
		dirValue[4] = 0.f;
	}
	else if (sKey)
	{
		camVerticalValue -= (float)cos(viewAngle * PI / 180) / 30;
		camHorizonValue += (float)sin(viewAngle * PI / 180) / 30;
		dirValue[4] = 180.f;
	}
	else if (aKey)
	{
		camHorizonValue += (float)cos(viewAngle * PI / 180) / 30;
		camVerticalValue += (float)sin(viewAngle * PI / 180) / 30;
		dirValue[4] = 90.f;
	}
	else if (dKey)
	{
		camHorizonValue -= (float)cos(viewAngle * PI / 180) / 30;
		camVerticalValue -= (float)sin(viewAngle * PI / 180) / 30;
		dirValue[4] = 270.f;
	}

	camTransMatrix = glm::mat4(1.0f);
	camTransMatrix = glm::translate(camTransMatrix, glm::vec3(camHorizonValue, 0.4f, camVerticalValue));

	// 카메라 Rotate
	if (pKey)
	{
		camRotValue += 2.f;
		viewAngle += 2.f;
		if (!aKey)
		{
			dirValue[4] = 270.f;
		}
	}
	else if (oKey)
	{
		camRotValue -= 2.f;
		viewAngle -= 2.f;
		if (!dKey)
		{
			dirValue[4] = 90.f;
		}
	}

	camRotMatrix = glm::mat4(1.0f);
	camRotMatrix = glm::rotate(camRotMatrix, glm::radians(camRotValue), glm::vec3(0.f, 1.f, 0.f));

	// 카메라 Revolve
	if (lKey)
	{
		camRevValue -= 2.f;
		dirValue[4] = 270.f;
	}
	else if (kKey)
	{
		camRevValue += 2.f;
		dirValue[4] = 90.f;
	}

	camRevMatrix = glm::mat4(1.0f);
	camRevMatrix = glm::rotate(camRevMatrix, glm::radians(camRevValue), glm::vec3(0.f, 1.f, 0.f));

	camMatrix = camRotMatrix * camTransMatrix * camRevMatrix;

	// 로봇이 걸을 경우 팔다리를 휘젓는다.
	// 걷지 않을 땐 자동으로 차렷 자세로 돌아온다.
	for (int i = 0; i < 4; i++)
	{
		if (!metBot[i] && (fabsf(verticalValue[i] - myVerticalValue) > 0.1f) || (fabsf(horizonValue[i] - myHorizonValue) > 0.1f))
		{
			if (rotDir[i])
			{
				rotValue[i] += 10.f;
				if (rotValue[i] == 60.f)
				{
					rotDir[i] = false;
				}
			}
			else if (!rotDir[i])
			{
				rotValue[i] -= 10.f;
				if (rotValue[i] == -60.f)
				{
					rotDir[i] = true;
				}
			}
		}
		else if(catched[i])
		{
			if (rotValue[i] > 0)
			{
				rotValue[i] -= 10.f;
			}
			else if (rotValue[i] < 0)
			{
				rotValue[i] += 10.f;
			}
		}
	}
	// 카메라 로봇은 어떤 이동 키가 눌렸을 때만 팔다리를 휘젓는다.
	if (aKey || wKey || sKey || dKey || pKey || oKey || lKey || kKey)
	{
		if (botRotDir)
		{
			botRotValue += 10.f;
			if (botRotValue == 60.f)
			{
				botRotDir = false;
			}
		}
		else if (!botRotDir)
		{
			botRotValue -= 10.f;
			if (botRotValue == -60.f)
			{
				botRotDir = true;
			}
		}
	}
	else
	{
		if (botRotValue > 0)
		{
			botRotValue -= 10.f;
		}
		else if (botRotValue < 0)
		{
			botRotValue += 10.f;
		}
	}

	// 난수를 이용해 로봇 자유 이동
	for (int i = 0; i < 4; i++)
	{
		if (!metBot[i] && !catched[i])
		{
			if (walkCount[i] == 0)
			{
				botDir[i] = rand() % 4;
				walkCount[i] = 50;
			}
			if (botDir[i] == 0)
			{
				if (((horizonValue[i] < -0.27f || horizonValue[i] > 0.27f)    &&    (verticalValue[i] > -1.13f)) ||
					 (horizonValue[i] >= -0.27f && horizonValue[i] <= 0.27) && (verticalValue[i] > 0.27f || (verticalValue[i] > -1.13f && verticalValue[i] < 0.25f)))
				{
					verticalValue[i] -= 0.005f;
				}
				dirValue[i] = 180.f;
			}
			else if (botDir[i] == 1)
			{
				if (((horizonValue[i] > 0.27f || horizonValue[i] < -0.27f) && (verticalValue[i] < 1.13f)) ||
					(horizonValue[i] <= 0.27f && horizonValue[i] >= -0.27) && (verticalValue[i] < -0.27f || (verticalValue[i] < 1.13f && verticalValue[i] > -0.25f)))
				{
					verticalValue[i] += 0.005f;
				}
				dirValue[i] = 0.f;
			}
			else if (botDir[i] == 2)
			{
				if (((verticalValue[i] < -0.27f || verticalValue[i] > 0.27f) && (horizonValue[i] > -1.13f)) ||
					(verticalValue[i] >= -0.27f && verticalValue[i] <= 0.27) && (horizonValue[i] > 0.27f || (horizonValue[i] > -1.13f && horizonValue[i] < 0.25f)))
				{
					horizonValue[i] -= 0.005f;
				}
				dirValue[i] = 270.f;
			}
			else if (botDir[i] == 3)
			{
				if (((verticalValue[i] > 0.27f || verticalValue[i] < -0.27f) && (horizonValue[i] < 1.13f)) ||
					(verticalValue[i] <= 0.27f && verticalValue[i] >= -0.27) && (horizonValue[i] < -0.27f || (horizonValue[i] < 1.13f && horizonValue[i] > -0.25f)))
				{
					horizonValue[i] += 0.005f;
				}
				dirValue[i] = 90.f;
			}

			walkCount[i]--;
		}
		// catched 상태일 때는 카메라맨을 따라다닌다.
		else if (catched[i])
		{
			if ((fabsf(verticalValue[i] - myVerticalValue) > 0.1f) || (fabsf(horizonValue[i] - myHorizonValue) > 0.1f))
			{
				if (verticalValue[i] > myVerticalValue - 0.07f && verticalValue[i] < myVerticalValue + 0.07f)
				{
					if (horizonValue[i] > myHorizonValue)
					{
						dirValue[i] = 270.f;
						if (((verticalValue[i] < -0.27f || verticalValue[i] > 0.27f) && (horizonValue[i] > -1.13f)) ||
							(verticalValue[i] >= -0.27f && verticalValue[i] <= 0.27) && (horizonValue[i] > 0.27f || (horizonValue[i] > -1.13f && horizonValue[i] < 0.25f)))
						{
							horizonValue[i] -= 0.005f + i * 0.005;
						}
					}
					else
					{
						dirValue[i] = 90.f;
						if (((verticalValue[i] > 0.27f || verticalValue[i] < -0.27f) && (horizonValue[i] < 1.13f)) ||
							(verticalValue[i] <= 0.27f && verticalValue[i] >= -0.27) && (horizonValue[i] < -0.27f || (horizonValue[i] < 1.13f && horizonValue[i] > -0.25f)))
						{
							horizonValue[i] += 0.005f + i * 0.005;
						}
					}
				}
				else if (horizonValue[i] > myHorizonValue - 0.07f && horizonValue[i] < myHorizonValue + 0.07f)
				{
					if (verticalValue[i] > myVerticalValue)
					{
						dirValue[i] = 180.f;
						if (((horizonValue[i] < -0.27f || horizonValue[i] > 0.27f) && (verticalValue[i] > -1.13f)) ||
							(horizonValue[i] >= -0.27f && horizonValue[i] <= 0.27) && (verticalValue[i] > 0.27f || (verticalValue[i] > -1.13f && verticalValue[i] < 0.25f)))
						{
							verticalValue[i] -= 0.005f + i * 0.005;
						}
					}
					else
					{
						dirValue[i] = 0.f;
						if (((horizonValue[i] > 0.27f || horizonValue[i] < -0.27f) && (verticalValue[i] < 1.13f)) ||
							(horizonValue[i] <= 0.27f && horizonValue[i] >= -0.27) && (verticalValue[i] < -0.27f || (verticalValue[i] < 1.13f && verticalValue[i] > -0.25f)))
						{
							verticalValue[i] += 0.005f + i * 0.005;
						}
					}
				}
				else if (verticalValue[i] > myVerticalValue && horizonValue[i] > myHorizonValue)
				{
					dirValue[i] = 225.f;
					if (((horizonValue[i] < -0.27f || horizonValue[i] > 0.27f) && (verticalValue[i] > -1.13f)) ||
						(horizonValue[i] >= -0.27f && horizonValue[i] <= 0.27) && (verticalValue[i] > 0.27f || (verticalValue[i] > -1.13f && verticalValue[i] < 0.25f)))
					{
						verticalValue[i] -= 0.005f + i * 0.005;
					}
					if (((verticalValue[i] < -0.27f || verticalValue[i] > 0.27f) && (horizonValue[i] > -1.13f)) ||
						(verticalValue[i] >= -0.27f && verticalValue[i] <= 0.27) && (horizonValue[i] > 0.27f || (horizonValue[i] > -1.13f && horizonValue[i] < 0.25f)))
					{
						horizonValue[i] -= 0.005f + i * 0.005;
					}
				}
				else if (verticalValue[i] < myVerticalValue && horizonValue[i] > myHorizonValue)
				{
					dirValue[i] = 315.f;
					if (((horizonValue[i] > 0.27f || horizonValue[i] < -0.27f) && (verticalValue[i] < 1.13f)) ||
						(horizonValue[i] <= 0.27f && horizonValue[i] >= -0.27) && (verticalValue[i] < -0.27f || (verticalValue[i] < 1.13f && verticalValue[i] > -0.25f)))
					{
						verticalValue[i] += 0.005f + i * 0.005;
					}
					if (((verticalValue[i] < -0.27f || verticalValue[i] > 0.27f) && (horizonValue[i] > -1.13f)) ||
						(verticalValue[i] >= -0.27f && verticalValue[i] <= 0.27) && (horizonValue[i] > 0.27f || (horizonValue[i] > -1.13f && horizonValue[i] < 0.25f)))
					{
						horizonValue[i] -= 0.005f + i * 0.005;
					}
				}
				else if (verticalValue[i] < myVerticalValue && horizonValue[i] < myHorizonValue)
				{
					dirValue[i] = 45.f;
					if (((horizonValue[i] > 0.27f || horizonValue[i] < -0.27f) && (verticalValue[i] < 1.13f)) ||
						(horizonValue[i] <= 0.27f && horizonValue[i] >= -0.27) && (verticalValue[i] < -0.27f || (verticalValue[i] < 1.13f && verticalValue[i] > -0.25f)))
					{
						verticalValue[i] += 0.005f + i * 0.005;
					}
					if (((verticalValue[i] > 0.27f || verticalValue[i] < -0.27f) && (horizonValue[i] < 1.13f)) ||
						(verticalValue[i] <= 0.27f && verticalValue[i] >= -0.27) && (horizonValue[i] < -0.27f || (horizonValue[i] < 1.13f && horizonValue[i] > -0.25f)))
					{
						horizonValue[i] += 0.005f + i * 0.005;
					}
				}
				else if (verticalValue[i] > myVerticalValue && horizonValue[i] < myHorizonValue)
				{
					dirValue[i] = 135.f;
					if (((horizonValue[i] < -0.27f || horizonValue[i] > 0.27f) && (verticalValue[i] > -1.13f)) ||
						(horizonValue[i] >= -0.27f && horizonValue[i] <= 0.27) && (verticalValue[i] > 0.27f || (verticalValue[i] > -1.13f && verticalValue[i] < 0.25f)))
					{
						verticalValue[i] -= 0.005f + i * 0.005;
					}
					if (((verticalValue[i] > 0.27f || verticalValue[i] < -0.27f) && (horizonValue[i] < 1.13f)) ||
						(verticalValue[i] <= 0.27f && verticalValue[i] >= -0.27) && (horizonValue[i] < -0.27f || (horizonValue[i] < 1.13f && horizonValue[i] > -0.25f)))
					{
						horizonValue[i] += 0.005f + i * 0.005;
					}
				}
			}
		}
	}

	// 로봇끼리 충돌체크 (부딪혔다면 부딪힌 두 로봇의 이동 방향을 거꾸로 바꾼다.)
	for (int i = 0; i < 4; i++)
	{
		if (((verticalValue[i] - verticalValue[(i + 1) % 4] < 0.1f && verticalValue[i] - verticalValue[(i + 1) % 4] > -0.1f) &&
			(horizonValue[i] - horizonValue[(i + 1) % 4] < 0.1f && horizonValue[i] - horizonValue[(i + 1) % 4] > -0.1f)) ||
			
			((verticalValue[i] - verticalValue[(i + 2) % 4] < 0.1f && verticalValue[i] - verticalValue[(i + 2) % 4] > -0.1f) &&
			(horizonValue[i] - horizonValue[(i + 2) % 4] < 0.1f && horizonValue[i] - horizonValue[(i + 2) % 4] > -0.1f)) ||

				((verticalValue[i] - verticalValue[(i + 3) % 4] < 0.1f && verticalValue[i] - verticalValue[(i + 3) % 4] > -0.1f) &&
			(horizonValue[i] - horizonValue[(i + 3) % 4] < 0.1f && horizonValue[i] - horizonValue[(i + 3) % 4] > -0.1f)) && !catched[i])
		{
			if (botDir[i] == 0 || botDir[i] == 2)
			{
				botDir[i]++;
			}
			else
			{
				botDir[i]--;
			}
		}
	}

	//로봇과 카메라맨의 만남 체크
	//만났다면 제자리에서 점프 1회 후 카메라맨을 따라다닌다.
	for (int i = 0; i < 4; i++)
	{
		if ((sqrt((myHorizonValue - horizonValue[i]) * (myHorizonValue - horizonValue[i]) +
			(myVerticalValue - verticalValue[i]) * (myVerticalValue - verticalValue[i]))) < 0.5f && !metBot[i] && !catched[i])
		{
			metBot[i] = true;
		}

		if (metBot[i])
		{
			jumpValue[i] -= 0.002f;
			jumpMatrix[i] = glm::translate(jumpMatrix[i], glm::vec3(0.f, jumpValue[i], 0.f));
			nowJump[i] += jumpValue[i];

			if (nowJump[i] <= 0.f)
			{
				jumpMatrix[i] = glm::mat4(1.0f);
				nowJump[i] = 0.f;
				jumpValue[i] = 0.02f;
				metBot[i] = false;
				catched[i] = true;
			}
		}
	}

	// j 점프 키 입력 이벤트
	if (jKey)
	{
		jumpValue[4] -= 0.002f;
		jumpMatrix[4] = glm::translate(jumpMatrix[4], glm::vec3(0.f, jumpValue[4], 0.f));
		nowJump[4] += jumpValue[4];

		if (nowJump[4] <= 0.f)
		{
			jumpMatrix[4] = glm::mat4(1.0f);
			nowJump[4] = 0.f;
			jumpValue[4] = 0.02f;
			jKey = false;
		}
	}

	// 카메라(나)의 정확한 위치 좌표
	myHorizonValue = -(camHorizonValue * camRevMatrix[0][0] + camVerticalValue * camRevMatrix[0][2]);
	myVerticalValue = -(camHorizonValue * camRevMatrix[2][0] + camVerticalValue * camRevMatrix[2][2]);

	glutPostRedisplay(); // 화면 재출력
	if (!pendingTimerStop)
	{
		pendingTimerStop = true;
		glutTimerFunc(40, Timer, 1); // 타이머함수 재 설정
	}
	pendingTimerStop = false;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': // 카메라 전진
		if (!wKey)
		{
			wKey = true;
		}
		break;
	case 's': // 카메라 후퇴
		if (!sKey)
		{
			sKey = true;
		}
		break;
	case 'a': // 카메라 좌로 이동
		if (!aKey)
		{
			aKey = true;
		}
		break;
	case 'd': // 카메라 우로 이동
		if (!dKey)
		{
			dKey = true;
		}
		break;

	case 'p': // 카메라 우로 자전
		if (!pKey)
		{
			pKey = true;
		}
		break;
	case 'o': // 카메라 좌로 자전
		if (!oKey)
		{
			oKey = true;
		}
		break;

	case 'l': // 카메라 우로 공전
		if (!lKey)
		{
			lKey = true;
		}
		break;
	case 'k': // 카메라 좌로 공전
		if (!kKey)
		{
			kKey = true;
		}
		break;

	case '1': // 1인칭 시점
		viewType = 1;
		break;

	case '3': // 3인칭 시점
		viewType = 3;
		break;

	case '2': // 쿼터뷰 시점
		viewType = 2;
		break;

	case 'j': // 점프
		if (!jKey)
		{
			jKey = true;
		}
		break;

	case 'f': // 와이어모드
		if (fillMode)
		{
			glPolygonMode(GLenum(GL_FRONT_AND_BACK), GLenum(GL_LINE));
			fillMode = false;
		}
		else
		{
			glPolygonMode(GLenum(GL_FRONT_AND_BACK), GLenum(GL_FILL));
			fillMode = true;
		}
		break;

	case 'q': // 프로그램 종료
		exit(0);
		break;

	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': // 카메라 전진 멈추기
		wKey = false;
		break;
	case 's': // 카메라 후퇴 멈추기
		sKey = false;
		break;
	case 'a': // 카메라 좌로 이동 멈추기
		aKey = false;
		break;
	case 'd': // 카메라 우로 이동 멈추기
		dKey = false;
		break;
	case 'p': // 카메라 우로 회전 멈추기
		pKey = false;
		break;
	case 'o': // 카메라 좌로 회전 멈추기
		oKey = false;
		break;
	case 'l': // 카메라 우로 공전
		lKey = false;
		break;
	case 'k': // 카메라 좌로 공전
		kKey = false;
		break;
	}
}

void drawRoom()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(roomVertexData), roomVertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 0.5, 0.5, 0.5);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * roomMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 36);



	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * boxMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void drawBot1()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	transMatrix = glm::mat4(1.0f);
	dirMatrix = glm::mat4(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(horizonValue[0], -0.46f, verticalValue[0]));
	dirMatrix = glm::rotate(dirMatrix, glm::radians(dirValue[0]), glm::vec3(0.0f, 1.0f, 0.0f));

	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 1.0, 0.0, 0.0);

	// Head
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[0] * transMatrix * dirMatrix * headMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nose
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[0] * transMatrix * dirMatrix * noseMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Body
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[0] * transMatrix * dirMatrix * bodyMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Arm
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.025f, -0.02f, 0.f));
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.12f, 0.04f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.05f, 0.f));

	leftArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[0] * transMatrix * dirMatrix * leftArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Arm
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.025f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[0]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[0] * transMatrix * dirMatrix * rightArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Leg
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.09f, 0.f));

	leftLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[0] * transMatrix * dirMatrix * leftLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Leg
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[0]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[0] * transMatrix * dirMatrix * rightLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ! Sign
	if (metBot[0] || catched[0])
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[0] * transMatrix * dirMatrix * catchedTopMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[0] * transMatrix * dirMatrix * catchedBottomMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void drawBot2()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	transMatrix = glm::mat4(1.0f);
	dirMatrix = glm::mat4(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(horizonValue[1], -0.46f, verticalValue[1]));
	dirMatrix = glm::rotate(dirMatrix, glm::radians(dirValue[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 0.0, 0.0, 1.0);

	// Head
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[1] * transMatrix * dirMatrix * headMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nose
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[1] * transMatrix * dirMatrix * noseMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Body
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[1] * transMatrix * dirMatrix * bodyMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Arm
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.025f, -0.02f, 0.f));
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.12f, 0.04f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[1]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.05f, 0.f));

	leftArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[1] * transMatrix * dirMatrix * leftArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Arm
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.025f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[1]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[1] * transMatrix * dirMatrix * rightArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Leg
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[1]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.09f, 0.f));

	leftLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[1] * transMatrix * dirMatrix * leftLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Leg
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[1]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[1] * transMatrix * dirMatrix * rightLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ! Sign
	if (metBot[1] || catched[1])
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[1] * transMatrix * dirMatrix * catchedTopMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[1] * transMatrix * dirMatrix * catchedBottomMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void drawBot3()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	transMatrix = glm::mat4(1.0f);
	dirMatrix = glm::mat4(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(horizonValue[2], -0.46f, verticalValue[2]));
	dirMatrix = glm::rotate(dirMatrix, glm::radians(dirValue[2]), glm::vec3(0.0f, 1.0f, 0.0f));

	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 0.0, 1.0, 0.0);

	// Head
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[2] * transMatrix * dirMatrix * headMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nose
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[2] * transMatrix * dirMatrix * noseMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Body
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[2] * transMatrix * dirMatrix * bodyMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Arm
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.025f, -0.02f, 0.f));
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.12f, 0.04f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[2]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.05f, 0.f));

	leftArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[2] * transMatrix * dirMatrix * leftArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Arm
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.025f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[2]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[2] * transMatrix * dirMatrix * rightArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Leg
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[2]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.09f, 0.f));

	leftLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[2] * transMatrix * dirMatrix * leftLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Leg
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[2]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[2] * transMatrix * dirMatrix * rightLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ! Sign
	if (metBot[2] || catched[2])
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[2] * transMatrix * dirMatrix * catchedTopMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[2] * transMatrix * dirMatrix * catchedBottomMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void drawBot4()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	transMatrix = glm::mat4(1.0f);
	dirMatrix = glm::mat4(1.0f);

	transMatrix = glm::translate(transMatrix, glm::vec3(horizonValue[3], -0.46f, verticalValue[3]));
	dirMatrix = glm::rotate(dirMatrix, glm::radians(dirValue[3]), glm::vec3(0.0f, 1.0f, 0.0f));

	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 1.0, 1.0, 0.0);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 0.0, 0.0, 0.0);

	// Head
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[3] * transMatrix * dirMatrix * headMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nose
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[3] * transMatrix * dirMatrix * noseMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Body
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[3] * transMatrix * dirMatrix * bodyMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Arm
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.025f, -0.02f, 0.f));
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.12f, 0.04f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[3]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.05f, 0.f));

	leftArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[3] * transMatrix * dirMatrix * leftArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Arm
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.025f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[3]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[3] * transMatrix * dirMatrix * rightArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Leg
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(rotValue[3]), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.09f, 0.f));

	leftLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[3] * transMatrix * dirMatrix * leftLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Leg
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-rotValue[3]), glm::vec3(1.0f, 0.0f, 0.0f));

	rightLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix* jumpMatrix[3] * transMatrix * dirMatrix * rightLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ! Sign
	if (metBot[3] || catched[3])
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[3] * transMatrix * dirMatrix * catchedTopMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[3] * transMatrix * dirMatrix * catchedBottomMatrix));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void drawCamBot()
{
	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	transMatrix = glm::mat4(1.0f);
	dirMatrix = glm::mat4(1.0f);
	camRevMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, glm::vec3(-camHorizonValue, -0.46f, -camVerticalValue));

	camRevMatrix = glm::rotate(camRevMatrix, glm::radians(-camRevValue), glm::vec3(0.f, 1.f, 0.f));

	transMatrix = camRevMatrix * transMatrix;
	dirMatrix = glm::rotate(dirMatrix, glm::radians(-viewAngle + 180.f + dirValue[4]), glm::vec3(0.0f, 1.0f, 0.0f));

	//조명
	int lightPosLocation = glGetUniformLocation(programID, "lightPos"); //--- lightPos 값전달
	glUniform3f(lightPosLocation, 0.0, 15.0, 0.0);

	int lightColorLocation = glGetUniformLocation(programID, "lightColor"); //--- lightColor값전달
	glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);

	int objColorLocation = glGetUniformLocation(programID, "objectColor"); //--- object Color값전달
	glUniform3f(objColorLocation, 0.3, 0.3, 0.3);

	int viewPosLocation = glGetUniformLocation(programID, "viewPos"); //--- view Pos값전달
	glUniform3f(viewPosLocation, 0.0, 0.0, 0.0);

	// Head
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * headMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Nose
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * noseMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Body
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * bodyMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Arm
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(0.04f, 0.12f, 0.04f));

	rotMatrix = glm::rotate(rotMatrix, glm::radians(-botRotValue), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.05f, 0.f));
	downMatrix = glm::translate(downMatrix, glm::vec3(-0.025f, -0.02f, 0.f));
	leftArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * leftArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Arm
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.025f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(botRotValue), glm::vec3(1.0f, 0.0f, 0.0f));

	rightArmMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * rightArmMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Left Leg
	downMatrix = glm::mat4(1.0f);
	upMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(-0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(botRotValue), glm::vec3(1.0f, 0.0f, 0.0f));
	upMatrix = glm::translate(upMatrix, glm::vec3(0.f, -0.09f, 0.f));

	leftLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * leftLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Right Leg
	downMatrix = glm::mat4(1.0f);
	rotMatrix = glm::mat4(1.0f);

	downMatrix = glm::translate(downMatrix, glm::vec3(0.01f, -0.02f, 0.f));
	rotMatrix = glm::rotate(rotMatrix, glm::radians(-botRotValue), glm::vec3(1.0f, 0.0f, 0.0f));

	rightLegMatrix = upMatrix * rotMatrix * downMatrix * scaleMatrix;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * jumpMatrix[4] * transMatrix * dirMatrix * rightLegMatrix));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void drawRange()
{
	// Range Circle

	glUseProgram(programID);

	unsigned int modelLocation = glGetUniformLocation(programID, "transform");

	//--- VAO 객체생성및바인딩
	glGenVertexArrays(1, &VAO[0]); glBindVertexArray(VAO[0]);
	//--- vertex data 저장을위한VBO 생성및바인딩.
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//--- vertex data 데이터입력.
	glBufferData(GL_ARRAY_BUFFER, sizeof(rangeVertexData), rangeVertexData, GL_STATIC_DRAW);
	//---위치속성: 속성인덱스0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//---색상속성: 속성인덱스1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(camMatrix * transMatrix));
	glDrawArrays(GL_LINE_STRIP, 0, 61);
}

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	programID = LoadShaders("vs.glsl", "fs.glsl"); // shader 파일과 fragment 파일을 프로그램 링크

	// 객체 초기 변환
	roomMatrix = glm::scale(roomMatrix, glm::vec3(6.f, 3.f, 6.f));

	boxMatrix = glm::scale(boxMatrix, glm::vec3(1.f, 3.f, 1.f));

	headMatrix = glm::scale(headMatrix, glm::vec3(0.2f, 0.2f, 0.2f));

	noseMatrix = glm::scale(noseMatrix, glm::vec3(0.05f, 0.05f, 0.1f));
	noseMatrix = glm::translate(noseMatrix, glm::vec3(0.f, -0.2f, 0.45f));

	bodyMatrix = glm::scale(bodyMatrix, glm::vec3(0.1f, 0.15f, 0.1f));
	bodyMatrix = glm::translate(bodyMatrix, glm::vec3(0.f, -0.45f, 0.f));

	catchedTopMatrix = glm::scale(catchedTopMatrix, glm::vec3(0.025f, 0.1f, 0.025f));
	catchedTopMatrix = glm::translate(catchedTopMatrix, glm::vec3(0.f, 1.1f, 0.f));

	catchedBottomMatrix = glm::scale(catchedBottomMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
	catchedBottomMatrix = glm::translate(catchedBottomMatrix, glm::vec3(0.f, 3.0f, 0.f));

	// 변수 초기 설정
	for (int i = 0; i < 5; i++)
	{
		dirValue[i] = 0.f;
		jumpMatrix[i] = glm::mat4(1.0f);
		jumpValue[i] = 0.02f;
		nowJump[i] = 0.f;
	}
	for (int i = 0; i < 4; i++)
	{
		rotDir[i] = true;
		rotValue[i] = 0.f;
		botDir[i] = rand() % 4;
		walkCount[i] = i * 10 + 10;
		metBot[i] = false;
		catched[i] = false;
	}
	verticalValue[0] = 0.6f;
	horizonValue[0] = 0.6f;
	verticalValue[1] = -0.6f;
	horizonValue[1] = 0.6f;
	verticalValue[2] = 0.6f;
	horizonValue[2] = -0.6f;
	verticalValue[3] = -0.6f;
	horizonValue[3] = -0.6f;

	// rangeVertexData 초기화
	for (int i = 0; i < 366; i++)
	{
		if (i % 6 == 0)
		{
			rangeVertexData[i] = sin(PI / 180.0f * i) / 2.1f;
		}
		else if (i % 6 == 2)
		{
			rangeVertexData[i] = cos(PI / 180.0f * i) / 2.1f;
		}
		else if (i % 6 == 1)
		{
			rangeVertexData[i] = -0.13f;
		}
		else
		{
			rangeVertexData[i] = 0.0f;
		}
	}

	// 타이머 함수 실행
	glutTimerFunc(10, Timer, 1);
}

GLvoid onDisplay() // 콜백 함수: 출력
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 채울 배경색을 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //설정된 색으로 배경 칠하기

	unsigned int projectionLocation = glGetUniformLocation(programID, "projectionTransform");

	if (viewType == 3)
	{
		projection = glm::perspective(glm::radians(45.0f), (float)gwidth / (float)gheight, 0.1f, 100.0f);
		projection = glm::translate(projection, glm::vec3(0.f, -0.1f - nowJump[4], -0.8f));
	}
	else if(viewType == 1)
	{
		projection = glm::perspective(glm::radians(45.0f), (float)gwidth / (float)gheight, 0.1f, 100.0f);
		projection = glm::translate(projection, glm::vec3(0.f, -nowJump[4], 0.f));
	}
	else if (viewType == 2)
	{
		projection = glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -100.f, 100.f);
		projection = glm::translate(projection, glm::vec3(0.f, -1.f, 0.f));
		projection = glm::rotate(projection, glm::radians(50.f), glm::vec3(1.f, 0.f, 0.f));
		projection = glm::rotate(projection, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
		projection = glm::translate(projection, glm::vec3(0.7f, 0.f, -0.7f));
	}
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	drawRoom();
	drawBot1();
	drawBot2();
	drawBot3();
	drawBot4();

	drawCamBot();
	drawRange();

	glutSwapBuffers();
}

GLvoid onReshape(int w, int h) // 콜백 함수: 다시 그리기
{
	gwidth = w;
	gheight = h;
	glViewport(0, 0, w, h);
}

int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(30, 0); // 윈도우의 위치 지정
	glutInitWindowSize(gwidth, gheight); // 윈도우의 크기 지정
	glutCreateWindow("로보트야 따라와"); // 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		cerr << "Unable to initialize GLEW" << endl;
		exit(-1);
	}
	else {
		cout << "GLEW Initialized\n";
	}

	Init();

	glutDisplayFunc(onDisplay); // 출력 함수의 지정
	glutReshapeFunc(onReshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);

	srand((unsigned int)time(NULL));

	glutMainLoop(); // 이벤트 처리 시작
}
