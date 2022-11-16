#include "Quaternion.h"
#include <iostream>

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

}