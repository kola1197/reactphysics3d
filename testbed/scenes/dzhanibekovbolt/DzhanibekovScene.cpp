
// Libraries
#include "DzhanibekovScene.h"
#include <cmath>

// Namespaces
using namespace openglframework;
using namespace dzhanibekovscene;

// Constructor
DzhanibekovScene::DzhanibekovScene(const std::string& name, EngineSettings& settings)
        : SceneDemo(name, settings, SCENE_RADIUS) {

    // Compute the radius and the center of the scene
    openglframework::Vector3 center(0, 5, 0);

    // Set the center of the scene
    setScenePosition(center, SCENE_RADIUS);

    // Gravity vector in the dynamics world
    rp3d::Vector3 gravity(0, rp3d::decimal(-9.81), 0);
//    rp3d::Vector3 gravity(0, 0, 0);

    rp3d::WorldSettings worldSettings;
    worldSettings.worldName = name;

    // Create the dynamics world for the physics simulation
    mPhysicsWorld = new rp3d::DynamicsWorld(gravity, worldSettings);

    //Create Drone
    createDrone();

    // Create the floor
    createFloor();

    // Get the physics engine parameters
    mEngineSettings.isGravityEnabled = getDynamicsWorld()->isGravityEnabled();
    rp3d::Vector3 gravityVector = getDynamicsWorld()->getGravity();
    mEngineSettings.gravity = openglframework::Vector3(gravityVector.x, gravityVector.y, gravityVector.z);
    mEngineSettings.isSleepingEnabled = getDynamicsWorld()->isSleepingEnabled();
    mEngineSettings.sleepLinearVelocity = getDynamicsWorld()->getSleepLinearVelocity();
    mEngineSettings.sleepAngularVelocity = getDynamicsWorld()->getSleepAngularVelocity();
    mEngineSettings.nbPositionSolverIterations = getDynamicsWorld()->getNbIterationsPositionSolver();
    mEngineSettings.nbVelocitySolverIterations = getDynamicsWorld()->getNbIterationsVelocitySolver();
    mEngineSettings.timeBeforeSleep = getDynamicsWorld()->getTimeBeforeSleep();
}

// Destructor
DzhanibekovScene::~DzhanibekovScene() {
#if 0
    // Destroy the joints
    getDynamicsWorld()->destroyJoint(mSliderJoint);
    getDynamicsWorld()->destroyJoint(mPropellerHingeJoint);
    getDynamicsWorld()->destroyJoint(mFixedJoint1);
    getDynamicsWorld()->destroyJoint(mFixedJoint2);
    for (int i = 0; i < NB_BALLSOCKETJOINT_BOXES - 1; i++) {
        getDynamicsWorld()->destroyJoint(mBallAndSocketJoints[i]);
    }

    // Destroy all the rigid bodies of the scene
    getDynamicsWorld()->destroyRigidBody(mSliderJointBottomBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mSliderJointTopBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mPropellerBox->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mFixedJointBox1->getRigidBody());
    getDynamicsWorld()->destroyRigidBody(mFixedJointBox2->getRigidBody());
    for (int i = 0; i < NB_BALLSOCKETJOINT_BOXES; i++) {
        getDynamicsWorld()->destroyRigidBody(mBallAndSocketJointChainBoxes[i]->getRigidBody());
    }

    delete mSliderJointBottomBox;
    delete mSliderJointTopBox;
    delete mPropellerBox;
    delete mFixedJointBox1;
    delete mFixedJointBox2;
    for (int i = 0; i < NB_BALLSOCKETJOINT_BOXES; i++) {
        delete mBallAndSocketJointChainBoxes[i];
    }
#endif
    // Destroy the floor
    getDynamicsWorld()->destroyRigidBody(mFloor->getRigidBody());
    delete mFloor;

    // Destroy the dynamics world
    delete getDynamicsWorld();
}

// Update the physics world (take a simulation step)
void DzhanibekovScene::updatePhysics() {
    double elapsedTime = static_cast<double>(mEngineSettings.elapsedTime) - simStartTime;
//    std::cout << "elapsed time: " << elapsedTime << std::endl;
    if (elapsedTime > 15.0) {
//        mCentralSphere->getRigidBody()->setAngularVelocity(rp3d::Vector3(10, 0, 0));
//        mDroneModule->getRigidBody()->setAngularVelocity(rp3d::Vector3(10, 0, 0));
//        mRightSphere->getRigidBody()->setAngularVelocity(rp3d::Vector3(10, 0, 0));
//        mLeftSphere->getRigidBody()->setAngularVelocity(rp3d::Vector3(10, 0, 0));

//        mCentralSphere->getRigidBody()->setAngularVelocity(rp3d::Vector3(10, 0, 0));
        rp3d::Vector3 force = rp3d::Vector3(0, 0.0001, 0);
//        for (auto& droneModule : mDrone->getDroneModules()) {
//            droneModule->getPhysicsBody()->getRigidBody()->applyForceToCenterOfMass(force);
//        }
//        PhysicsObject* mDroneModule = mDrone->getDroneModules()[]->getPhysicsBody();
//        rp3d::Vector3 transformedForce = mDroneModule->getTransform().getOrientation() * force;
//        mDroneModule->getRigidBody()->applyForceToCenterOfMass(force);
        mDrone->getMotors()[MOTOR_BL]->getPhysicsBody()->getRigidBody()->applyForceToCenterOfMass(force);
        mDrone->getMotors()[MOTOR_BR]->getPhysicsBody()->getRigidBody()->applyForceToCenterOfMass(force);
        force+=force;
//#define topPosition mDroneModule->getTransform().getPosition()
//        openglframework::Vector3 point1(topPosition.x, topPosition.y, topPosition.z);
//        rp3d::Vector3 forcePositionEnd = topPosition + transformedForce;
//        openglframework::Vector3 point2(forcePositionEnd.x, forcePositionEnd.y, forcePositionEnd.z);
//        Line* forceLine = new Line(point1, point2);
//        std::vector<openglframework::Vector3> lines;
//        lines.push_back(point1);
//        lines.push_back(point2);
//        glDrawArrays(GL_LINES, 0, lines.size());
//        PhysicsObject* mBottomSphere = mDrone->getDroneModules()[2]->getPhysicsBody();
//        rp3d::Vector3 transformedBotForce = mBottomSphere->getTransform() * (-force);
        //mBottomSphere->getRigidBody()->applyForceToCenterOfMass(transformedBotForce);
    }

//    PhysicsObject* mCentralSphere = mDrone->getDroneModules()[0]->getPhysicsBody();
//    mCentralSphere->getRigidBody()->setLinearVelocity(rp3d::Vector3(0, 0, 0));

    mDrone->updatePhysics(mEngineSettings.timeStep);
    SceneDemo::updatePhysics();
}

// Reset the scene
void DzhanibekovScene::reset() {
    simStartTime = static_cast<double>(mEngineSettings.elapsedTime);

//    rp3d::Vector3 floorPosition(0, -5, 0);
//    mFloor->setTransform(rp3d::Transform(floorPosition,rp3d::Quaternion::identity()));

    // --------------- Drone --------------- //mFloor->setTransform(rp3d::Transform(floorPosition,rp3d::Quaternion::identity()));
    mDrone->reset();
    rp3d::Vector3 positionDrone(0, initialHeight, 0);
    mDrone->setTransform(rp3d::Transform(positionDrone, rp3d::Quaternion::identity()));
    mDrone->hover();
}


// Create the floor
void DzhanibekovScene::createFloor() {

    // Create the floor
    rp3d::Vector3 floorPosition(0, 0, 0);
    mFloor = new Box(FLOOR_SIZE, FLOOR_MASS, getDynamicsWorld(), mMeshFolderPath);

    // Set the box color
    mFloor->setColor(mGreyColorDemo);
    mFloor->setSleepingColor(mGreyColorDemo);

//    mFloor->setTransform(rp3d::Transform(floorPosition,rp3d::Quaternion::identity()));
    // The floor must be a static rigid body
    mFloor->getRigidBody()->setType(rp3d::BodyType::STATIC);

    // Change the material properties of the rigid body
    rp3d::Material& material = mFloor->getRigidBody()->getMaterial();
    material.setBounciness(rp3d::decimal(0.3));
    mPhysicsObjects.push_back(mFloor);
}

void DzhanibekovScene::createDrone() {
    rp3d::Vector3 positionDrone(0, initialHeight, 0);
    QuadPids quadPids(PID(0.7, 0.35, 0.35),
                      PID(0.7, 0.35, 0.35),
                      PID(0.7, 0.35, 0.35),
                      PID(0.7, 0.35, 0.35));
    double droneFrame = 0.088;
    double droneMass = 0.12;
    double motorMass = 0.01;
    double propellerRadius = 0.02;

    mDrone = new Drone(droneFrame, droneMass, propellerRadius, motorMass,
                       quadPids, getDynamicsWorld(), mMeshFolderPath);
    mDrone->setTransform(rp3d::Transform(positionDrone, rp3d::Quaternion::identity()));
    for (auto& mDroneModule : mDrone->getDroneModules()) {
        mPhysicsObjects.push_back(mDroneModule->getPhysicsBody());
    }
    mDrone->hover();
}


#include "DzhanibekovScene.h"
