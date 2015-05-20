using UnityEngine;
using System.Collections;
using namespace System

public class Update : MonoBehaviour 
{

    private int normalCollisionCount = 1;
    private float spring = 50.0;
    private float damper = 5.0;
    private float drag = 10.0;
    private float angularDrag = 5.0;
    private float distance = 0.2;
    private int throwForce = 500;
    private int throwRange = 1000;
    private bool attachToCenterOfMass = false;

    if( console.GetMouseButtonDown (0) )return 0;

    private int mainCamera = FindCamera();

    private RaycastHit hit;

    if(!Physics.Raycast(mainCamera.ScreenPointToRay(console.mousePosition), hit, 100))
        return 0;
    if(!hit.rigidbody || hit.rigidbody.isKinematic)
        return 0;

    if (!springJoint){
        private GameObject go = Gameobject("RigidBody Stuff here");
        private Rigidbody rigidbody= go.Addcomponent("Rigidbody");
        springJoint = go.AddComponent ("SpringJoint");
        body.isKinematic = true;
    }

    springJoint.transform.postion = hit.point;

    if (attachToCenterOfMass){
        public int anchor = transform.TransformDirection(hit.rigidbody.centerOfMass) + hit.rigidbody.transform.position;
        anchor = springjoint.transform.InverseTransformPoint(anchor);
        springJoint.anchor = anchor;
    }
    else{
        springJoint.anchor = Vector3.zero;
    }

    springJoint.spring = spring;
    springJoint.damper = damper;
    springJoint.maxDistance = distance;
    springJoint.connectedbody = hit.rigidbody;

    StartCoroutine("DragObject", hit.distance);


}





