/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SSLWORLD_H
#define SSLWORLD_H
#include "config.h"

#include "physics/pworld.h"
#include "physics/pball.h"
#include "physics/pground.h"
#include "physics/pfixedbox.h"
#include "physics/pray.h"
#include "configwidget.h"
#include "robot.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include <QUdpSocket>
#include <string>
#define WALL_COUNT 10

class RobotsFomation;
class SendingPacket {
    public:
    SendingPacket(SSL_WrapperPacket* _packet,int _t);
    SSL_WrapperPacket* packet;
    int t;
};

class SSLWorld : public QObject
{
    Q_OBJECT
private:
    int framenum;
    dReal last_dt;
    QList<SendingPacket*> sendQueue;
    char packet[200];
    char *in_buffer;  
    int lastInfraredBlue;
    int lastInfraredYellow;  
public:
    void run();
    dReal customDT;
    bool isGLEnabled;
    SSLWorld();
    virtual ~SSLWorld();
    void step(dReal dt=-1);
    SSL_WrapperPacket* generatePacket(int cam_id=0);
    void publishPacket(int cam_id = -1);
    void addFieldLinesArcs(SSL_GeometryFieldSize *field);
    Vector2f* allocVector(float x, float y);
    void addFieldLine(SSL_GeometryFieldSize *field, const std::string &name, float p1_x, float p1_y, float p2_x, float p2_y, float thickness);
    void addFieldArc(SSL_GeometryFieldSize *field, const std::string &name, float c_x, float c_y, float radius, float a1, float a2, float thickness);
    void sendVisionBuffer();
    bool visibleInCam(int id, double x, double y);
    int  robotIndex(int robot,int team);

    ConfigWidget* cfg;
    PWorld* p;
    PBall* ball;
    PGround* ground;
    PRay* ray;
    PFixedBox* walls[WALL_COUNT];
    int selected;
    bool show3DCursor;
    dReal cursor_x,cursor_y,cursor_z;
    dReal cursor_radius;
    QUdpSocket *commandSocket;
    QUdpSocket *blueStatusSocket,*yellowStatusSocket;
    bool updatedCursor;
    SimRobot* robots[MAX_ROBOT_COUNT*2];
    QTime *timer;
    int sendGeomCount;
public slots:
    void recvActions();
signals:
    void fpsChanged(int newFPS);
};

class RobotsFomation {
    public:
        dReal x[MAX_ROBOT_COUNT];
        dReal y[MAX_ROBOT_COUNT];
        RobotsFomation(int type, ConfigWidget* _cfg);
        void setAll(dReal *xx,dReal *yy);
        void loadFromFile(const QString& filename);
        void resetRobots(SimRobot** r,int team);
    private:
        ConfigWidget* cfg;
};

dReal fric(dReal f);
int robotIndex(int robot,int team);

#endif // SSLWORLD_H
