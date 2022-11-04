#include "Transform.h"

Vector3 Transform::LocalToWorld(Vector3& local, Matrix4& transform)
{
	return transform.transform(local);
}

Vector3 Transform::WorldToLocal(Vector3& world, Matrix4& transform)
{
	return transform.transformInverse(world);
}
