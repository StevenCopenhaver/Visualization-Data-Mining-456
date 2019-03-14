#include "decisionTree.h"
#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>
#include <vector>

using namespace std;

decisionTree tree;
node* root = tree.search(0);
int currentNode = 1;
void centerOnScreen();
int window_x;
int window_y;


int window_width = 1000;
int window_height = 700;
int quandrantSize = 200;
int marginX = quandrantSize / 3;
int marginY = quandrantSize / 3;
int line_width = quandrantSize / 200;
int done = false;


int xN = 1;
int yN = 1;

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

const Color ORANGE = { 0.929f, 0.490f, 0.192f, 1.0f };
const Color BLUE = { 0.357f, 0.609f, 0.835f, 1.0f };
const Color GRAY = { 0.851f, 0.851f, 0.851f, 1.0f };
const Color WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
const Color RED = { 1.0f, 0.0f, 0.0f, 1.0f };

const Color ORANGE_DISABLED = { 0.929f, 0.490f, 0.192f, 0.35f };
const Color BLUE_DISABLED = { 0.357f, 0.609f, 0.835f, 0.35f };
const Color GRAY_DISABLED = { 0.851f, 0.851f, 0.851f, 0.35f };
const Color WHITE_DISABLED = { 1.0f, 1.0f, 1.0f, 0.35f };
const Color BLACK_DISABLED = { 0.0f, 0.0f, 0.0f, 0.35f };
const Color RED_DISABLED = { 1.0f, 0.0f, 0.0f, 0.35f };


void clearBackground(Color c) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(c.r, c.g, c.b, c.a);
}

Color getClassColor(int cls) {
	switch (cls) {
	case 0:
		return GRAY;
	case 1:
		return ORANGE;
	case 2:
		return BLUE;
	case 3:
		return RED;

		// Get disabled class number + 4
	case 4:
		return GRAY_DISABLED;
	case 5:
		return ORANGE_DISABLED;
	case 6:
		return BLUE_DISABLED;
	case 7:
		return RED_DISABLED;
	default:
		return GRAY;
	}
}

void createRect(GLint x1, GLint y1, GLint x2, GLint y2, Color c) {
	glColor4f(c.r, c.g, c.b, c.a);
	glRecti(x1, y1, x2, y2);
}

int calculateQuandrantPositionX1(int qN) {
	return (marginX*qN)+(quandrantSize*(qN-1));
}

int calculateQuandrantPositionX2(int qN) {
	return (marginX*qN) + (quandrantSize*qN);
}

int calculateQuandrantPositionY1(int qN) {
	return window_height-(marginY*qN) - (quandrantSize*(qN));
	//return 500;
}

int calculateQuandrantPositionY2(int qN) {
	return window_height - (marginY*qN) - (quandrantSize*(qN - 1));
	//return 500;
}

string splitAt(int key, string str) {
	if(str[0]=='<') return str.substr(1);
	else if (str[0] == '>') return str.substr(2);
}


Color getClassColor(string cls) {
	if (cls == "begnin") return ORANGE;
	else if (cls == "malignant") return BLUE;
	return GRAY;
}
 
void drawLHelp(float pointAX, float pointAY, float pointBX, float pointBY) {
	struct { GLubyte r, g, b; } c;
	glReadPixels(pointAX+5, pointAY+5, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
	/*glColor3f(RED.r, RED.g, RED.b);
	glBegin(GL_POINTS);
	glVertex3f(pointAX + 5, pointAY + 5, 0.0f);
	glEnd();
	*/

	GLubyte colorByte = static_cast<GLubyte>(GRAY.r * 255.f);
	cout << (int)colorByte << " " << (int)c.r << "\n";
	if ((int)c.r == (int)colorByte) {
	//if(true){
		glLineWidth(line_width);
		glBegin(GL_LINES);
		// change color based off class
		struct { GLubyte r, g, b; } cb;
		glReadPixels(pointBX, pointBY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &cb);
		GLubyte O = static_cast<GLubyte>(ORANGE.r * 255.f);
		GLubyte B = static_cast<GLubyte>(BLUE.r * 255.f);
		GLubyte R = static_cast<GLubyte>(RED.r * 255.f);
		if((int) c.r == (int)O) glColor3f(ORANGE.r, ORANGE.g, ORANGE.b);
		else if ((int) c.r == (int)B) glColor3f(BLUE.r, BLUE.g, BLUE.b);
		else if ((int) c.r == (int)R) glColor3f(BLUE.r, BLUE.g, BLUE.b);
		else glColor3f(BLACK.r, BLACK.g, BLACK.b);
		glVertex3f(pointAX, pointAY, 0.0f);
		glVertex3f(pointBX, pointBY, 0.0f);
		glEnd();
		glBegin(GL_POINTS);
		glVertex3f(pointAX, pointAY, 0.0f);
		glVertex3f(pointBX, pointBY, 0.0f);
		glEnd();
	}
	else {
		struct { GLubyte r, g, b; } cb;
		glReadPixels(pointBX, pointBY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &cb);
		GLubyte colorByte = static_cast<GLubyte>(255.f);
		//cout << (int)cb.r << " " << (int)colorByte << "\n";
		if ((int)cb.r != (int)colorByte) {
			glColor3f(BLACK.r, BLACK.g, BLACK.b);
			glBegin(GL_POINTS);
			glVertex3f(pointAX, pointAY, 0.0f);
			glVertex3f(pointBX, pointBY, 0.0f);
			glEnd();
		}
	}



}

// Returns the Max double in the vector
float getMaxVec(vector<double> v) {

	return float;
}

float getRandF(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


void drawQuadrant(int kindOf) {

	vector<DataPoint> dp = tree.data;

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	
	//cout << xN << "\n";
	//cout << calculateQuandrantPositionX2(xN) << "\n";
	if (calculateQuandrantPositionX2(xN) > window_width) {
		//cout << "TEST";
		xN = 1;
		yN++;
	}

	// these will change depending on for loop for drawing rect
	int posX1 = calculateQuandrantPositionX1(xN);
	int posY1 = calculateQuandrantPositionY1(yN);
	int posX2 = calculateQuandrantPositionX2(xN);
	int posY2 = calculateQuandrantPositionY2(yN);

	//create background rec, test if disabled
	if ((kindOf == 1) || (kindOf == 3)) {
		createRect(posX1, posY1, posX2, posY2, GRAY);
	}

	// FIND MAX NUMBER ON XY
	node* tempXr = tree.search(currentNode);
	//cout << tempXr->attribute << "\n";
	vector<double> xV = dp.at(currentNode).attributes;
	string xVC = dp.at(currentNode).target;
	vector<double> xV2 = dp.at(currentNode+4).attributes;
	/*for (unsigned j = 0; j < dp.at(currentNode).attributes.size(); j++) {
		cout << "X " << dp.at(currentNode).target << " " << dp.at(currentNode).attributes.at(j) << "\n";
	}cout << "\n";*/
	currentNode++;
	node* tempXl = tree.search(currentNode);
	if (kindOf == 3) currentNode-=2;
	else currentNode++;




	//cout << "TEST " << tempX->comparison << "\n";
	/*NodeType test = tempX->right->type;
	if(test == NodeType::CLASSIFICATION) 	cout << "TEST " << "\n";
	cout << "TEST " << tempX->right->comparison << "\n";
	cout << "TEST " << tempX->right->classification << "\n";
	cout << "TEST " << tempX->right->value << "\n";
	cout << "TEST " << tempX->right->attribute << "\n";*/
	
	/*for (int i = 0; i < currentNode; i++){
		if(root->right != nullptr)
			tempX = root->right;
		else if(root->left != nullptr)
			tempX = root->left;
	}*/

	node* tempYr = tree.search(currentNode);
	//cout << tempYr->attribute << "\n";
	vector<double> yV = dp.at(currentNode).attributes;
	vector<double> yV2 = dp.at(currentNode+4).attributes;
	/*for (unsigned j = 0; j < dp.at(currentNode).attributes.size(); j++) {
		cout << "Y " << dp.at(currentNode).target << " " << dp.at(currentNode).attributes.at(j) << "\n";
	}cout << "\n";*/
	currentNode++;
	node* tempYl = tree.search(currentNode);
	currentNode++;
	//cout << tempXr->attribute << "\n";
	//cout << tempXl ->attribute << "\n";
	//cout << tempYr->attribute << "\n";
	//cout << tempYl->attribute << "\n";
	// print this out on xy
	//cout << "TEST " << tempXr->attribute << "\n";

	//cout << "TEST " << tempXr->classification << "\n";


	// TODO find max number
	// ADD FOR DISABLED
	//float maxX = atof(splitAt(2, tempXl->comparison).c_str()) * 2;
	float maxRatioX = 0.5f;
	int xRatio = (int)(((maxRatioX)*quandrantSize) + posX1);
	//cout << xRatio << "\n";

	// DRAW X axis
	if ((kindOf == 1) || (kindOf == 3)) {
		createRect(posX1, posY1, xRatio, posY2, getClassColor(tempXl->classification));
		createRect(xRatio, posY1, posX2, posY2, getClassColor(tempXr->classification));
	}

	// TODO IMPLEMEN"T HIS CODe
	// DRAW TO EVERY SPOT
	// TODO STOP FROM MOVINGING RANDOM AFTER one draw
	// TODO thicken lines
	// TODO DISABLED LINES
	// TODO another thing i forgot
	// TODO draw text
	// TODO draw text of x y axis
	


	// CALCULATE LINE OFFSET
	int posX1B;
	int posX2B;
	int posY1B;
	int posY2B;
	// DRAW LINES from every box to every possible box
	if (calculateQuandrantPositionX2(xN + 1) > window_width) {
		//cout << "TEST";
		posX1B = calculateQuandrantPositionX1(1);
		posX2B = calculateQuandrantPositionX2(1);
		posY1B = calculateQuandrantPositionY1(yN + 1);
		posY2B = calculateQuandrantPositionY2(yN + 1);
	}
	else {
		posX1B = calculateQuandrantPositionX1(xN + 1);
		posX2B = calculateQuandrantPositionX2(xN + 1);
		posY1B = calculateQuandrantPositionY1(yN);
		posY2B = calculateQuandrantPositionY2(yN);
	}

	// line coords
	float pointAX;
	float pointAY;
	float pointBX;
	float pointBY;


	  
	//float maxY = atof(splitAt(2, tempYl->comparison).c_str()) * 2;
	float maxRatioY = 0.5f;

	// NEED TO GET MAX FUNCTION
	//float maxX = 8.0f;
	float maxX = getMaxVec(xV);
	//float maxY = 8.0f;
	float maxY = getMaxVec(yV);
	//float maxX2 = 8.0f;
	float maxX2 = getMaxVec(xV2);
	//float maxY2 = 8.0f;
	float maxY2 = getMaxVec(yV2);

	int yRatio = (int)(((maxRatioY)*quandrantSize) + posY1);
	//cout << maxY << "\n";
	//cout << yRatio << "\n";
	// TODO add this if type == right tempYr->type == NodeType::RIGHT_SPLIT
	if((kindOf==0) || (kindOf == 4)) {

		pointAX = (int)(((0)*quandrantSize) + posX1);
		pointAY = (int)(((0)*quandrantSize) + posY1);
		pointBX = (int)(((0)*quandrantSize) + posX1B);
		pointBY = (int)(((0)*quandrantSize) + posY1B);


		for (unsigned i = 0; i < dp.at(currentNode).attributes.size(); i++) {
			drawLHelp(pointAX + ((xV.at(i)/maxX)*quandrantSize), pointAY + ((yV.at(i) / maxY)*quandrantSize), 
				pointBX + ((xV2.at(i) / maxX2)*quandrantSize), pointBY + ((yV2.at(i) / maxY2)*quandrantSize));
		}


		/*
		// TODO just draw a point if not N/A
		// TODO figure out how to draw multiple lines
		//DRAW x
		//DRAW yr
		// predict where to draw line pick random point there 

		drawLHelp(pointAX,
			getRandF(pointAY+((maxRatioY / 2)*quandrantSize),pointAY- ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)((((maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));

		//DRAW yl
		// predict where to draw line pick random point there 
		pointAX = (int)((((maxRatioX / 2))*quandrantSize) + posX1);
		pointAY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1);
		pointBX = (int)(((maxRatioX / 2)*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)((((maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));


		//DRAW yr
		// predict where to draw line pick random point there 
		pointAX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1);
		pointAY = (int)(((maxRatioY / 2)*quandrantSize) + posY1);
		pointBX = (int)(((maxRatioX / 2)*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)((((maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));

		//DRAW yl
		// predict where to draw line pick random point there 
		pointAX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1);
		pointAY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1);
		pointBX = (int)(((maxRatioX / 2)*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)((((maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY / 2)*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
		pointBX = (int)(((maxRatioX + (maxRatioX / 2))*quandrantSize) + posX1B);
		pointBY = (int)(((maxRatioY + (maxRatioY / 2))*quandrantSize) + posY1B);
		drawLHelp(pointAX,
			getRandF(pointAY + ((maxRatioY / 2)*quandrantSize), pointAY - ((maxRatioY / 2)*quandrantSize))
			, pointBX
			, getRandF(pointBY + ((maxRatioY / 2)*quandrantSize), pointBY - ((maxRatioY / 2)*quandrantSize)));
			*/
	}
	else {
		/*if (tree.search(i)->type == NodeType::RIGHT_SPLIT) {
			cout << "TYPE RIGHT\n";
		}else {
			cout << "TYPE LEFT\n";
		}
		if (tempYr->type == NodeType::RIGHT_SPLIT) {
			cout << "TYPE RIGHT\n";
		}
		else {
			cout << "TYPE LEFT\n";
		}*/
		if (true) { //right
			cout << "TYPE RIGHT\n";
				createRect(xRatio, yRatio, posX2, posY2, getClassColor(tempYr->classification));
				createRect(xRatio, posY1, posX2, yRatio, getClassColor(tempYl->classification));	
		}else { //left
			cout << "TYPE LEFT\n";

				createRect(posX1, yRatio, xRatio, posY2, getClassColor(tempYr->classification));
				createRect(posX1, posY1, xRatio, yRatio, getClassColor(tempYl->classification));
		}
	}
	xN++;
}



//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void){
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, window_width, 0.0, window_height);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void centerOnScreen(){
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}

void myDisplay(void){
	if (!done) {
		tree.GetData("iris.txt");
		/*vector<DataPoint> dp = tree.data;
		for (unsigned i = 0; i < dp.size(); i++) {
			for (unsigned j = 0; j < dp.at(i).attributes.size(); j++) {
				cout << dp.at(i).target << " " << dp.at(i).attributes.at(j) << "\n";
			}cout <<  "\n";
		}*/
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen
		GLsizei w = window_width;
		GLsizei h = window_height;
		glViewport(0, 0, w, h);

		int amt = 1;
		while (true) {
			if (tree.search(amt) == nullptr) break;
			amt++;
		}
		boolean odd;
		amt--;
		amt /= 2;
		if (amt % 2 == 0) {
			odd = false;
			amt /= 2;
		}
		else { // TODO CHECK ODD
			amt++;
			odd = true;
			amt /= 2;
		}

		for (int i = 0; i < amt; i++) {
			if (odd) drawQuadrant(3);
			else drawQuadrant(1);
		}
		yN = 1;
		xN = 1;
		currentNode = 1;

		for (int i = 0; i < amt; i++) {
			if (odd) drawQuadrant(4);
			else drawQuadrant(0);
		}
		yN = 1;
		xN = 1;
		currentNode = 1;

		//drawQuadrant();
		//for (int i = 0; i < 13; i++){
		//	cout << tree.search(i)->attribute << "\n";
		//}cout << "\n";


		//createRect(90, 90, 100, 100, ORANGE_DISABLED);
		/*
		glBegin(GL_POINTS);
		glVertex2i(59, 50); // draw three points
		glVertex2i(100, 130);
		glVertex2i(150, 130);
		glEnd();*/

		glFlush(); // send all output to display
		glutSwapBuffers();
	}
	done = true;
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>



void main(int argc, char** argv){
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(window_width, window_height); // set window size
	centerOnScreen();
	tree.printTree();
	glutInitWindowPosition(window_x, window_y); // set window position on screen
	glutCreateWindow(""); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop(); // go into a perpetual loop
}