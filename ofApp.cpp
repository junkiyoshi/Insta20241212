#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float span = 1;
	ofColor color;
	vector<ofColor> color_list;
	for (int i = 0; i < 3; i++) {

		color.setHsb(ofMap(i, 0, 3, 0, 255), 255, 255);
		color_list.push_back(color);
	}

	for (int i = 0; i < color_list.size(); i++) {

		ofMesh mesh;
		auto noise_param = ofRandom(1000);

		for (float x = 10; x < ofGetWindowWidth() - 10 - span; x += span) {

			for (float y = 10; y < ofGetWindowHeight() - 10 - span; y += span) {

				if (glm::distance(glm::vec2(x, y), ofGetWindowSize() * 0.5) > 300) {

					continue;
				}

				mesh.addVertex(glm::vec3(x, y, 0));
				mesh.addVertex(glm::vec3(x + span, y, 0));
				mesh.addVertex(glm::vec3(x + span, y + span, 0));
				mesh.addVertex(glm::vec3(x, y + span, 0));

				for (int k = mesh.getNumVertices() - 4; k < mesh.getNumVertices(); k++) {

					auto noise_value = ofNoise(mesh.getVertex(k).x * 0.002, mesh.getVertex(k).y * 0.002, noise_param + ofGetFrameNum() * 0.015 + i * 0.05);
					int int_noise_value = noise_value;
					float param = noise_value - int_noise_value;
					param = abs(param - 0.5);

					auto color = ofColor(color_list[i], param < 0.125 ? ofMap(param, 0, 0.125, 255, 0) : 0);
					mesh.addColor(color);
				}

				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);
				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);
			}
		}

		mesh.draw();
	}

	/*
	int start = 83;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}