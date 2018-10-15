#pragma once

#include <Ogre.h> //unneeded?
#include <iostream>

class DebugDrawer: public btIDebugDraw, public Ogre::FrameListener{
public:
	Ogre::SceneManager* mScnMgr;
	int debugMode;
	bool initiated = false;
	Ogre::ManualObject* myManualObject;

	DebugDrawer(Ogre::SceneManager* sceneManager){
		mScnMgr = sceneManager;
	}

	//make the manualObject
	void init(){

	}

	//draws by line->position();
	void drawLine (const btVector3& from, const btVector3& to, const btVector3& color){
		std::cout << "drawLine" << std::endl;
		//if(true){
			myManualObject =  mScnMgr->createManualObject("manual1"); 
			Ogre::SceneNode* myManualObjectNode = mScnMgr->getRootSceneNode()->createChildSceneNode("manual1_node"); 
 
			Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material","General"); 
			myManualObjectMaterial->setReceiveShadows(false); 
			myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
			myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
			/*
			//drawing
			line->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
			line->position(from.x(), from.z(), from.y());
			line->position(to.x(), to.z(), to.y());
			line->end();
			*/

			//attach in order to render
			myManualObjectNode->attachObject(myManualObject);
			initiated = true;
		//}
		myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST);
		//myManualObject->position(from.x(), from.z(), from.y());
		//myManualObject->position(to.x(), to.z(), to.y());
		myManualObject->position(0, 0, 0); 
	myManualObject->position(200, 200, 200);
	myManualObject->position(5, 5, 5);
	myManualObject->position(0, 200, 0);
	myManualObject->position(-10, -10, 0);
	myManualObject->position(20, 50, 90);
		myManualObject->position(0, 0, 0);
		myManualObject->position(10, 10, 100);
		myManualObject->end();
	}

	/*
	void drawLine (const btVector3& from, const btVector3& to, const btVector3& color){
		Ogre::ManualObject* myManualObject =  mScnMgr->createManualObject("manual1"); 
		Ogre::SceneNode* myManualObjectNode = mScnMgr->getRootSceneNode()->createChildSceneNode("manual1_node"); 
 
// NOTE: The second parameter to the create method is the resource group the material will be added to.
// If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
		Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material","General"); 
		myManualObjectMaterial->setReceiveShadows(false); 
		myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
		myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
		myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
		myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 

 
		myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST); 
		myManualObject->position(0, 0, 0); 
		myManualObject->position(200, 200, 200); 
// etc 
		myManualObject->end(); 
 
		myManualObjectNode->attachObject(myManualObject);
		
	}*/

	void drawContactPoint(const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color){}
	void reportErrorWarning(const char* warningString){}
	void draw3dText(const btVector3& location, const char* textString){}
	void setDebugMode(int debugMode){
		this->debugMode = debugMode;
	}
	int getDebugMode() const{
		return debugMode;
	}
};
