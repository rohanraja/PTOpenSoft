//
//  CanvasDataGenerator.cpp
//  2dpaint
//
//  Created by Rohan Raja on 23/03/15.
//
//

#include "CanvasDataGenerator.h"
#include "CanvasStateData.h"
#include "Line.h"
#include "CoordinateSystem.h"
#include <QtGui>

CanvasDataGenerator::CanvasDataGenerator()
{
}

CanvasDataGenerator::CanvasDataGenerator(Range prange, MathFunction pmathFunc):range(prange), mathFunc(pmathFunc)
{
}

CanvasStateData CanvasDataGenerator::changeRange(Range prange)
{
    range = prange;
    return getCanvasStateData();
}

CanvasStateData CanvasDataGenerator::getCanvasStateData()
{
    listOfPoints = range.getAllPoints(mathFunc);
    vector<Line> lines = getPlotLines();
    vector<QRect> rects;
    
    lines.push_back(range.x_axis); // X-Axis
    lines.push_back(range.y_axis); // Y-Axis
    rects.push_back(* new QRect(0,0,range.width, range.height)); //Main Box
    
    CanvasStateData csd = *new CanvasStateData(rects, lines);
    csd.width = range.width ;
    csd.height = range.height;
    
    return csd ;
}

vector<Line> CanvasDataGenerator::getPlotLines()
{
    
    vector<Line> lines ;
    
    for (int i=0; i<listOfPoints.size()-1; i++) {
        
        Point p1 = listOfPoints[i];
        Point p2 = listOfPoints[i+1];
        QPoint q1 = range.findQPoint(p1);
        QPoint q2 = range.findQPoint(p2);
        Line l = * new Line(q1,q2);
        lines.push_back(l);
        
    }
    
    return lines;
    
}



