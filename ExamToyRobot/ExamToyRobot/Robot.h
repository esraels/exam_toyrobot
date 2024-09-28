#pragma once

#include <iostream>
#include "ConstantsData.h"
#include "Geometry.h"


namespace ExamToyRobot {

    using namespace Tools;

    class Robot {

    protected:
        Vec m_vPos;
        Vec m_vDir;

    public:
        Robot() :m_vPos(Vec::ZERO), m_vDir(Vec::UP) {}

        //---actions:
        void Place(Vec p, Vec d) {
            m_vPos = p;
            m_vDir = d;
        }

        void FaceLeft() {
            m_vDir.rotateLeft90();
        }

        void FaceRight() {
            m_vDir.rotateRight90();
        }

        void Move() {
            m_vPos += m_vDir;
        }

        const auto getPosAhead() const { return m_vPos + m_vDir; }

        const auto& getPos() const { return m_vPos; }
        const auto& getDir() const { return m_vDir; }
        
    };


}//namespace...