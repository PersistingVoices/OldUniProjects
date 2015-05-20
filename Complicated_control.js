// to be understood, DO NOT USE



var speed = 100.0;
var speedFalloffDistMin = 0.00;
var speedFalloffDistMax = 10.00;
var force = 22.00;

var predictTarget = 1.00;
var predictTargetSharpness = 3.00;
var predictThis = 0.9;
var predictThisSharpness = 3.00;

var target : Transform;

private var lastTargetPos : Vector3;
private var predictThisVel : Vector3;
private var predictTargetVel : Vector3;
private var warned = false;

function FixedUpdate () {
    // get the smooothed velocity of this and the target this frame
    predictThisVel = Vector3.Lerp(predictThisVel, rigidbody.velocity, Time.fixedDeltaTime * predictThisSharpness);
    predictTargetVel = Vector3.Lerp(predictTargetVel, (target.position - lastTargetPos) / Time.fixedDeltaTime, Time.fixedDeltaTime * predictTargetSharpness);
    lastTargetPos = target.position;

    // predict future positions for this and the target
    var predictedTarget = target.position + (predictTargetVel * predictTarget);
    var predictedPosition = transform.position + (predictThisVel * predictThis);

    // construct a velocity vector from our position to the target's, tweaking the falloff relative to distance
    var toTarget = predictedTarget - predictedPosition;
    var wantedVelocity = toTarget.normalized * Mathf.InverseLerp(-speedFalloffDistMin, speedFalloffDistMax, toTarget.magnitude) * speed;

    // safeguard against things exploding
    var explosionDanger = Mathf.Clamp01(Mathf.Pow((Vector3.Angle(wantedVelocity, rigidbody.velocity) / 180.00) * (rigidbody.velocity.magnitude / speed), 3));
    rigidbody.AddForce(-rigidbody.velocity * explosionDanger * 0.8, ForceMode.Acceleration);

    // the final force
    var usedForce = (wantedVelocity - rigidbody.velocity) * Mathf.Lerp(force, 0.0, explosionDanger);
    rigidbody.AddForce(usedForce, ForceMode.Acceleration);

    // if we are exploding, lower forces so that the simulation becomes sane
    if(explosionDanger > 0.9) {
        force = Mathf.Lerp(force, force * 0.8, Time.fixedDeltaTime * 3);
        if(!warned) Debug.Log("Forces on object `" + gameObject.name + "` are really crazy, I'm automatically lowering them");
        warned = true;
    }
}
