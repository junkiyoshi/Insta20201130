#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofColor color_1(239);
	ofColor color_2(39);

	for (int x = -650; x <= 650; x += 650) {

		for (int y = -650; y <= 650; y += 650) {

			ofPushMatrix();
			ofTranslate(x, y);

			ofRotateY(ofGetFrameNum() * ofRandom(0.25, 1.25));
			ofRotateX(ofGetFrameNum() * ofRandom(0.25, 1.25));

			ofMesh face, frame;
			frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

			auto noise_param = ofRandom(1000);

			for (auto deg = 0; deg < 360; deg += 1) {

				auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
				int u = ofMap(ofNoise(noise_param, noise_location.x * 0.5, noise_location.y * 0.5, ofGetFrameNum() * 0.01), 0, 1, 0, 720);

				face.addVertex(this->make_point(230, 50, (u), deg));
				face.addColor(color_1);
				face.addVertex(this->make_point(230, 50, (u + 180), deg));
				face.addColor(color_2);

				frame.addVertex(this->make_point(230, 50, (u), deg));
				frame.addColor(color_2);
				frame.addVertex(this->make_point(230, 50, (u + 180), deg));
				frame.addColor(color_1);
			}

			for (auto i = 0; i < face.getVertices().size(); i += 2) {

				auto index_0 = i;
				auto index_1 = (i + 1) % face.getVertices().size();
				auto index_2 = (i + 2) % face.getVertices().size();
				auto index_3 = (i + 3) % face.getVertices().size();

				face.addIndex(index_0);
				face.addIndex(index_1);
				face.addIndex(index_2);

				face.addIndex(index_3);
				face.addIndex(index_1);
				face.addIndex(index_2);

				frame.addIndex(index_0); frame.addIndex(index_2);
				frame.addIndex(index_1); frame.addIndex(index_3);
			}

			face.draw();
			frame.drawWireframe();

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}