#include <testing/verlet/ball/colliders/circle_closed.hpp>
#include <testing/verlet/ball/colliders/circle_open.hpp>
#include <testing/verlet/ball/colliders/screen.hpp>
#include <testing/verlet/ball/colliders/line.hpp>
#include <testing/verlet/ball/ball.hpp>
#include <testing/verlet/grid.hpp>
#include <testing/verlet/menu.hpp>
#include <testing/line.hpp>

int main()
{
    ///////////////////
    //    WORKING    //
    ///////////////////

    // LineTesting::start();
    // VerletBallTesting::start();
    // OpenCircleColliderTesting::start();
    //ClosedCircleColliderTesting::start();
    // MenuTesting::start(); // fix button sensitivity
    // LineColliderTesting::start();
    ScreenColliderTesting::start();

    ////////////////////
    //    NEED FIX    //
    ////////////////////

    // 1. Fix the balls disappearing when they hit the open circle collider (sub steps maybe?)

    // GridTesting::start(); // fix all of it
    return 0;
}
