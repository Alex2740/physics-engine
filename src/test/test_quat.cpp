#include "Quaternion.h"
#include "Matrix3.h"
#include <iostream>
#include <cmath>

int main() {
    std::cout << "-- Test Quaternion --" << std::endl;

    std::cout << "Init quaternion q1: " << std::endl;
    Quaternion q1 = Quaternion(0, 1, 0, 0);
    std::cout << q1.getString() << std::endl;

    std::cout << "with quaternion q2: " << std::endl;
    Quaternion q2 = Quaternion(0, 0, 1, 0);
    std::cout << q2.getString() << std::endl;

    std::cout << "their sum: " << std::endl;
    Quaternion tmp = q1 + q2;
    std::cout << tmp.getString() << std::endl;

    std::cout << "the rotation of q1 by q2 (q1 should be [0 (-1 0 0)])" << std::endl;
    q1.rotateByQuaternion(q2);
    std::cout << q1.getString() << std::endl;

    std::cout << "rotate q1 by q2 (second time) \n";
    std::cout << "q1 should be [0 (1 0 0)]" << std::endl;
    q1.rotateByQuaternion(q2);
    std::cout << q1.getString() << std::endl;

    std::cout << "calcul the euler angle of q1 ";
    std::cout << "(should be [-pi 0 0])" << std::endl;
    Vector3 tmpVet = q1.toEuler();
    std::cout << tmpVet.x << " " << tmpVet.y << " " << tmpVet.z << std::endl;

    // std::cout << "calculate the quaternion from euler angle" << std::endl;
    // float degToRad = M_PI / 180;
    // Vector3 euler = Vector3(45 * degToRad, 90 * degToRad, 180 * degToRad);
    // std::cout << "answer should be 0.6532815, -0.2705981, 0.6532815, 0.270598" << std::endl;
    // Quaternion q = Quaternion(euler);
    // std::cout << q << std::endl;
    Quaternion q3 = Quaternion(1, 0, 0, 1);
    q3 = Quaternion::normalize(q3);
    std::cout << "calculate the value of new quat: " << q3;
    std::cout << std::endl;
    std::cout << "(should be [ 0, 0, 0.7071068, 0.7071068 ])" << std::endl;

    Quaternion q4 = Quaternion(1, 1.5, 2, 3);
    std::cout << "calculate a new quat q4 * q4, with q4 = " << q4 << std::endl;

    std::cout << q4 * q4 << std::endl;
}