#pragma once

#include "Geometry.h"

namespace ExamToyRobot {

    using namespace Tools;

    class TableTop {
    protected:
        Rect m_rect;
    public:
        TableTop(const Vec& size = Vec::ONE) {
            setSize(size);
        };

        void setSize(Vec const& size) {
            m_rect.size = size;  
        }
        Vec getSize() {
            return m_rect.size;
        }
        
        bool isValidPos(const Point& p) {
            return m_rect.isInside(p);
        }

        const auto& getSize() const { return m_rect.size; }

    };

}//namespace...