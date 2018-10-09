#pragma once

#include <btBulletDynamicsCommon.h>

namespace Util {
class GenericObject;
}

namespace Physics {
struct CollisionContext {
    bool hit;

    const btCollisionObject *body;
    const btCollisionObject *lastBody;

    Util::GenericObject *obj;

    float dist;
    float velNormal;

    btVector3 point;
    btVector3 normal;
    btVector3 velocity;

    CollisionContext() { reset(); }

    void reset() {
        hit = false;

        body = nullptr;

        obj = nullptr;

        dist = 0.f;
        velNormal = 0.f;

        point.setZero();
        normal.setZero();
        velocity.setZero();
    }
};

struct BulletContactCallback : public btCollisionWorld::ContactResultCallback {
    BulletContactCallback(btRigidBody &tgtBody, CollisionContext &context)
        : btCollisionWorld::ContactResultCallback(), body(tgtBody),
          ctxt(context) {}

    btRigidBody &body;
    CollisionContext &ctxt;

    virtual bool needsCollision(btBroadphaseProxy *proxy) const {
        if (!btCollisionWorld::ContactResultCallback::needsCollision(proxy)) {
            return false;
        }

        return body.checkCollideWithOverride(
            static_cast<btCollisionObject *>(proxy->m_clientObject));
    }

    virtual btScalar addSingleResult(btManifoldPoint &cp,
                                     const btCollisionObjectWrapper *colObjWrap0,
                                     int partId0, int index0,
                                     const btCollisionObjectWrapper *colObjWrap1,
                                     int partId1, int index1) {
        auto *colObj0 = colObjWrap0->getCollisionObject();
        auto *colObj1 = colObjWrap1->getCollisionObject();

        ctxt.hit = true;
        ctxt.lastBody = ctxt.body;

        if (colObj0 == &body) {
            ctxt.point = cp.m_localPointA;
            ctxt.body = colObj1;
        } else {
            assert(colObj1 == &body &&
                   "Collision is invalid - body doesn't match either object");
            ctxt.point = cp.m_localPointB;
            ctxt.body = colObj0;
        }

        ctxt.obj =
            static_cast<Util::GenericObject *>(ctxt.body->getUserPointer());
        ctxt.normal = cp.m_normalWorldOnB;
        ctxt.velocity = body.getLinearVelocity();
        ctxt.velNormal = ctxt.normal.dot(ctxt.velocity);

        return 0;
    }
};
}
