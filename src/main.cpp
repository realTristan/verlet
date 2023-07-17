#include <testing/verlet/ball/colliders/circle_closed.hpp>
#include <testing/verlet/ball/colliders/circle_open.hpp>
#include <testing/verlet/ball/colliders/screen.hpp>
#include <testing/verlet/ball/colliders/line.hpp>
#include <testing/verlet/ball/ball.hpp>
#include <testing/verlet/fluid.hpp>
#include <testing/verlet/grid.hpp>
#include <testing/verlet/menu.hpp>
#include <testing/line.hpp>

int main()
{   
    // Note: a lot of the physics is off because SFML sucks and 
    // somehow causes the physics equations (very basic) to not work properly? Like? wtf?
    // And their circles are messed up so getting a ball to collide with the exact edge of a circle is
    // just not possible. I'm not sure if it's just my code or if it's SFML but I'm pretty sure it's SFML.

    ///////////////////
    //    WORKING    //
    ///////////////////

    // LineTesting::start();
    // VerletBallTesting::start();
    // OpenCircleColliderTesting::start();
    ClosedCircleColliderTesting::start();
    // MenuTesting::start(); // (fix button sensitivity)
    // LineColliderTesting::start();
    // FluidTesting::start();

    ////////////////////
    //    NEED FIX    //
    ////////////////////

    // 1. Fix the balls disappearing when they hit the open circle collider (sub steps maybe?)

    // GridTesting::start(); // (doesn't even start lol)
    // ScreenColliderTesting::start(); // (fix the physics)
    return 0;
}
