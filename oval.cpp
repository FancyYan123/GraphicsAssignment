#include "oval.h"
#include <math.h>

void Oval::drawSymPoint(intPoint2D first){
    if(horizontalFocus){
        glVertex2i(first.x+center.x, first.y+center.y);
        glVertex2i(-first.x+center.x, first.y+center.y);
        glVertex2i(first.x+center.x, -first.y+center.y);
        glVertex2i(-first.x+center.x, -first.y+center.y);
    }
    else{
        glVertex2i(first.y+center.x, first.x+center.y);
        glVertex2i(-first.y+center.x, first.x+center.y);
        glVertex2i(first.y+center.x, -first.x+center.y);
        glVertex2i(-first.y+center.x, -first.x+center.y);
    }
}

void Oval::setStart(int x, int y){
    start.x=x;
    start.y=y;
}

void Oval::setEnd(int x, int y){
    end.x=x;
    end.y=y;
    center.x=(start.x+end.x)/2;
    center.y=(start.y+end.y)/2;
    double dist1=fabs(start.x-end.x)/2.0;
    double dist2 = fabs(start.y-end.y)/2.0;

    longHalf = dist1>=dist2?dist1:dist2;
    shortHalf = dist1<dist2?dist1:dist2;
    horizontalFocus = dist1>=dist2?true:false;
}

void Oval::Draw(){

        intPoint2D temp(0, shortHalf);
        double p1=pow(shortHalf, 2.0)-pow(longHalf, 2.0)*shortHalf+pow(longHalf, 2.0)/4;
        glBegin(GL_POINTS);
        drawSymPoint(temp);

        //int count1=0, count2=0;
        //切记这里不能写小于等于，因为初始化的时候shortHalf和LongHalf都是0，会有死循环
        while(temp.x*shortHalf*shortHalf < temp.y*longHalf*longHalf){
           // cout<<temp.x<<" "<<temp.y<<" "<<shortHalf<<" "<<longHalf<<endl;
            if(p1<0){
                p1 = p1+2*pow(shortHalf, 2)*temp.x+3*pow(shortHalf, 2);
                temp.x += 1;
            }
            else{
                p1 = p1+2*pow(shortHalf, 2)*temp.x-2*pow(longHalf, 2)*temp.y+2*pow(longHalf, 2)+3*pow(shortHalf, 2);
                temp.x += 1;
                temp.y -= 1;
            }
            drawSymPoint(temp);
        }
        //cout<<count1<<" "<<count2<<endl;

        double p2=pow(shortHalf, 2)*pow(temp.x+0.5, 2)+pow(longHalf, 2)*pow(temp.y-1,2)-pow(shortHalf*longHalf, 2);
        while(temp.y>0){
            if(p2<=0){
                p2 = p2+2*pow(shortHalf, 2)*temp.x-2*pow(longHalf,2)*temp.y+2*pow(shortHalf, 2)+3*pow(longHalf, 2);
                temp.y-=1;
                temp.x+=1;
                //cout<<1<<endl;
            }
            else{
                p2 = p2-2*pow(longHalf, 2)*temp.y+3*pow(longHalf, 2);
                temp.y-=1;
                //cout<<2<<endl;
            }
            drawSymPoint(temp);
        }
        glEnd();

}

void Oval::move(intPoint2D start, intPoint2D end){
    int shiftX=end.x-start.x;
    int shiftY=end.y-start.y;

    center.x += shiftX;
    center.y += shiftY;
}

void Oval::zoom(intPoint2D origin, intPoint2D scale){
    double standard = sqrt((origin.x-center.x)*(origin.x-center.x)+(origin.y-center.y)*(origin.y-center.y));
    double scaled = sqrt((scale.x-center.x)*(scale.x-center.x)+(scale.y-center.y)*(scale.y-center.y));

    double s = scaled/standard;

    shortHalf *= s;
    longHalf *= s;
}

void Oval::fill(){

}

Graph2D* Oval::mouseSelect(intPoint2D click){
//    int x_max = start.x>end.x?start.x:end.x;
//    int x_min = start.x<end.x?start.x:end.x;
//    int y_max = start.y>end.y?start.y:end.y;
//    int y_min = start.y<end.y?start.y:end.y;
    int x_min, x_max, y_min, y_max;
    if(horizontalFocus){
        x_min = center.x-longHalf;
        x_max = center.x+longHalf;
        y_min = center.y-shortHalf;
        y_max = center.y+shortHalf;
    }
    else{
        x_min = center.x-shortHalf;
        x_max = center.x+shortHalf;
        y_min = center.y-longHalf;
        y_max = center.y+longHalf;
    }

    if(click.x<x_min || click.x>x_max)
        return NULL;
    if(click.y<y_min || click.y>y_max)
        return NULL;

    return this;
}

void Oval::rotate(intPoint2D start, intPoint2D end){

}
