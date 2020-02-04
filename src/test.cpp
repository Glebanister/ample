#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <cassert>
#include <queue>

#include "Activity.h"
#include "EventManager.h"
#include "Window.h"
#include "Clock.h"
#include "LayeredWindowActivity.h"
#include "WindowObject.h"

class UpdatableObject
{
public:
    virtual void update() = 0;
};

int randInt(int l, int r)
{
    if (l == r)
    {
        return l;
    }
    return (rand()) % (r - l + 1) + l;
}

double randDouble()
{
    return rand() / double(RAND_MAX);
}

double randDouble(double l, double r, double acc = 10000.0)
{
    if (l == r)
    {
        return l;
    }
    return randInt(l * acc, r * acc) / acc;
}

class Particle : public UpdatableObject, public graphics::WindowObject2d
{
public:
    Particle() = delete;

    Particle(const geometry::Vector2d pos,
             double speed,
             double speedDecrease,
             double dir,
             double rad,
             double r, double g, double b, double a,
             double rSpeed = -0.01, double gSpeed = -0.01, double bSpeed = -0.01, double aSpeed = -0.01,
             double radSpeed = 0.0,
             double centration = 0.75,
             double finishAngle = M_PI_2,
             double angleSpeed = 0.0,
             double angle = 45.0)
        : graphics::WindowObject2d(pos),
          speed(speed),
          speedDecrease(speedDecrease),
          dir(dir),
          rad(rad),
          r(r), g(g), b(b), a(a),
          rSpeed(rSpeed), gSpeed(gSpeed), bSpeed(bSpeed), aSpeed(aSpeed),
          radSpeed(radSpeed),
          centration(centration),
          finishAngle(finishAngle),
          angleSpeed(angleSpeed),
          angle(angle),
          clock()
    {
    }

    void draw() override
    {
        glColor4d(r, g, b, a);

        glTranslated(pos.x, pos.y, 0);
        glRotated(angle, 0, 0, 1);

        glBegin(GL_POLYGON);
        glVertex2d(-rad / 2, -rad / 2);
        glVertex2d(rad / 2, -rad / 2);
        glVertex2d(rad / 2, rad / 2);
        glVertex2d(-rad / 2, rad / 2);
        glEnd();

        glRotated(-angle, 0, 0, 1);
        glTranslated(-pos.x, -pos.y, 0);
    }

    bool isDone()
    {
        return a <= 0.01 || rad <= 0.0001;
    }

    void update() override
    {
        pos.x += speed * SDL_cos(dir) * clock.deltaTimeMs() / 1000;
        pos.y += speed * SDL_sin(dir) * clock.deltaTimeMs() / 1000;
        if (abs(finishAngle - dir) < abs(finishAngle - dir - 2 * M_PI))
        {
            dir += (finishAngle - dir) * centration;
        }
        else
        {
            dir += (finishAngle - dir - 2 * M_PI) * centration;
        }

        r += rSpeed * clock.deltaTimeMs() / 10;
        g += gSpeed * clock.deltaTimeMs() / 10;
        b += bSpeed * clock.deltaTimeMs() / 10;
        a += aSpeed * clock.deltaTimeMs() / 10;
        rad += radSpeed * clock.deltaTimeMs() / 10;
        r = std::max(r, 0.0);
        g = std::max(g, 0.0);
        b = std::max(b, 0.0);
        a = std::max(a, 0.0);
        rad = std::max(rad, 0.0);
        angle += angleSpeed * clock.deltaTimeMs() / 10;
        if (speed >= 0)
        {
            speed += speedDecrease * clock.deltaTimeMs() / 10;
        }
    }

    void increaseDirAngle(double delta)
    {
        dir += delta;
    }

    void increaseSpeed(double delta)
    {
        speed += delta;
    }

private:
    double speed;
    double speedDecrease;
    double dir;
    double rad;
    double r, g, b, a;
    double rSpeed, gSpeed, bSpeed, aSpeed;
    double radSpeed;
    double centration;
    double finishAngle;
    double angle;
    double angleSpeed;

    os::Clock clock;
};

int randint(const int &l, const int &r)
{
    return rand() % (r - l) + l;
}

class ParticleEmitter : public UpdatableObject, public graphics::WindowObject2d
{
public:
    ParticleEmitter(double dirMin, double dirMax,
                    double speedMin, double speedMax,
                    double speedDecrMin, double speedDecrMax,
                    double radMin, double radMax,
                    double perMs,
                    double red, double green, double blue, double alpha,

                    double redSpeed = 0.0, double greenSpeed = 0.0, double blueSpeed = 0.0, double alphaSpeed = 0.0,
                    double radSpeed = 0.0,
                    double finishAngleMin = M_PI_2, double finishAngleMax = M_PI_2,
                    double centration = 0.75,
                    double rotSpeedMin = 0.0, double rotSpeedMax = 0.1)
        : dirMin(dirMin), dirMax(dirMax),
          speedMin(speedMin), speedMax(speedMax),
          speedDecrMin(speedDecrMin), speedDecrMax(speedDecrMax),
          radMin(radMin), radMax(radMax),
          perMs(perMs),
          red(red), green(green), blue(blue), alpha(alpha),

          redSpeed(redSpeed), greenSpeed(greenSpeed), blueSpeed(blueSpeed), alphaSpeed(alphaSpeed),
          radSpeed(radSpeed),
          finishAngleMin(finishAngleMin), finishAngleMax(finishAngleMax),
          centration(centration),
          rotSpeedMin(rotSpeedMin), rotSpeedMax(rotSpeedMax)
    {
    }

    void activate()
    {
        active = true;
    }

    void stop()
    {
        active = false;
    }

    void update() override
    {
        std::vector<Particle *> newParticles;
        if (active)
        {
            double cnt = os::Clock::deltaTimeMs() * perMs;
            int news = cnt;
            for (int i = 0; i < news; i++)
            {
                double speed = randDouble(speedMin, speedMax);
                double speedDecr = randDouble(speedDecrMin, speedDecrMax);
                double dir = randDouble(dirMin, dirMax);
                double radius = randDouble(radMin, radMax);
                double finishAngle = randDouble(finishAngleMin, finishAngleMax);
                double rotation = randDouble(rotSpeedMin, rotSpeedMax);
                newParticles.push_back(new Particle(pos,
                                                    speed, speedDecr, dir,
                                                    radius, red, green, blue, alpha,
                                                    redSpeed, greenSpeed, blueSpeed, alphaSpeed,
                                                    radSpeed,
                                                    centration,
                                                    finishAngle,
                                                    rotation));
            }
        }
        for (auto particle : particles)
        {
            if (!particle->isDone())
            {
                newParticles.push_back(particle);
            }
            else
            {
                delete particle;
            }
        }
        particles = newParticles;
        for (auto particle : particles)
        {
            particle->update();
        }
    }

    void draw() override
    {
        for (int i = particles.size() - 1; i > -1; i--)
        {
            particles[i]->draw();
        }
    }

    ~ParticleEmitter()
    {
        for (auto particle : particles)
        {
            delete particle;
        }
    }

private:
    double dirMin, dirMax;
    double speedMin, speedMax;
    double speedDecrMin, speedDecrMax;
    double radMin, radMax;
    double perMs;
    double red, green, blue, alpha;

    double redSpeed = 0.0, greenSpeed = 0.0, blueSpeed = 0.0, alphaSpeed = 0.0;
    double radSpeed = 0.0;
    double finishAngleMin = M_PI_2, finishAngleMax = M_PI_2;
    double centration = 0.75;
    double rotSpeedMin = 0.0, rotSpeedMax = 0.1;

    bool active = false;

    std::vector<Particle *> particles = {};
};

class EmmitterMover : public control::EventHandler
{
public:
    EmmitterMover(ParticleEmitter *em)
        : em(em) {}

    void handleEvent(const control::Event &ev) override
    {
        ev.motion.x;
    }

private:
    ParticleEmitter *em;
    os::Window *win;
};

class Object2dUpdater : public activity::LogicBlock
{
public:
    void onUpdate() override
    {
        for (auto obj : this->objects)
        {
            obj->update();
        }
    }

    void addObject(UpdatableObject *object)
    {
        objects.push_back(object);
    }

private:
    std::vector<UpdatableObject *> objects;
};

class TimeSlower : public control::KeyHandlerSingleDown
{
public:
    TimeSlower(double cf)
        : cf(cf), clock() {}

    void onKeyDown() override
    {
        clock.multiplyTimeFlow(cf);
    }

    void onKeyUp() override
    {
        clock.resetTimeFlow();
    }

private:
    double cf;
    os::Clock clock;
};

class Activator : public control::KeyHandlerSingleDown
{
public:
    Activator(ParticleEmitter *em)
        : em(em) {}

    void onKeyDown() override
    {
        em->activate();
    }

    void onKeyUp() override
    {
        em->stop();
    }

private:
    ParticleEmitter *em;
};

int main()
{
    os::Window window("Particles",
                      0, 0,
                      1920, 1080,
                      os::winpos::UNDEFINED_POS,
                      os::winmode::RESIZABLE);

    auto activity = graphics::LayeredWindowActivity(&window);

    auto layer = graphics::Layer2d(window.getWidth(), window.getHeight());
    auto system = ParticleEmitter(-M_PI, M_PI,                    // direction min/max
                                  200, 600,                       // speed min/max
                                  -2, -1,                         // speed decrease min/max
                                  3, 30,                          // radius min/max
                                  1,                              // particles per ms
                                  0.1, 0.8, 0.8, 0.9,             // rgba
                                  -0.002, -0.002, -0.002, -0.001, // color changing speed
                                  -0.0001,                        // radius changing speed
                                  3 * M_PI_2, 3 * M_PI_2,         // finish angle min/max
                                  -0.0,                           // centration
                                  15.0, 15.0                      // rotation speed min/max
    );
    layer.addObject(&system);
    activity.addLayer(&layer);
    auto updater = Object2dUpdater();
    updater.addObject(&system);
    activity.addLogicBlock(&updater);

    auto timeSlower = TimeSlower(0.1);
    activity.eventManager->addKeyHandler(control::keysym::SPACE, &timeSlower);

    auto activator = Activator(&system);
    activity.eventManager->addKeyHandler(control::keysym::KEY_b, &activator);

    activity.start();

    return 0;
}
