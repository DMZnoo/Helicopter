//
//  CylinderModel.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 5/05/20.
//

#include "CylinderModel.hpp"
CylinderModel::CylinderModel()
{
    sectorCount = 100;
}
void CylinderModel::generateUnitCircle()
{
    float sectorStep = 2*PI/sectorCount;
    float sectorAngle;
    std::vector<float> unitCircleVertices;
    for(unsigned int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i* sectorStep;
        
        
        
    }
//    std::vector<float>().swap()
};
