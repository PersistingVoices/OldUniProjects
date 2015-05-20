ing UnityEngine;
using System.Collections;

public class TorqueStabilizer : MonoBehaviour {

    public float stability = 0.3f;
    public float speed = 2.0f;

    void FixedUpdate () {
        Vector3 predictedUp = Quaternion.AngleAxis(
                rigidbody.angularVelocity.magnitude * Mathf.Rad2Deg * stability / speed,
                rigidbody.angularVelocity
                ) * transform.up;

        Vector3 torqueVector = Vector3.Cross(predictedUp, Vector3.up);
        rigidbody.AddTorque(torqueVector * speed);
    }
}
