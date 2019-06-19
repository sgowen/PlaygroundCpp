//
//  MathTest.h
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 9/7/18.
//  Copyright © 2018 Stephen Gowen. All rights reserved.
//

#ifndef MathTest_h
#define MathTest_h

#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
#include <cmath>

class MathTest
{
public:
    struct Point
    {
        double x;
        double y;
    };
    
    struct LeastSqrRegressionResult
    {
        double slope = 0; //slope of regression line
        double y_intercept = 0; //y intercept of regression line
    };
    
    static LeastSqrRegressionResult leastSqrRegression(struct Point* xyCollection, size_t dataSize, bool forceThroughZero)
    {
        LeastSqrRegressionResult ret;
        
        if (xyCollection == NULL || dataSize == 0)
        {
            printf("Empty data set!\n");
            return ret;
        }
        
        double SUMx = 0;     //sum of x values
        double SUMy = 0;     //sum of y values
        double SUMxy = 0;    //sum of x * y
        double SUMxx = 0;    //sum of x^2
        double SUMres = 0;   //sum of squared residue
        double res = 0;      //residue squared
        double slope = 0;    //slope of regression line
        double y_intercept = 0; //y intercept of regression line
        double SUM_Yres = 0; //sum of squared of the discrepancies
        double AVGy = 0;     //mean of y
        double AVGx = 0;     //mean of x
        double Yres = 0;     //squared of the discrepancies
        double Rsqr = 0;     //coefficient of determination
        
        //calculate various sums
        for (int i = 0; i < dataSize; i++)
        {
            //sum of x
            SUMx = SUMx + (xyCollection + i)->x;
            //sum of y
            SUMy = SUMy + (xyCollection + i)->y;
            //sum of squared x*y
            SUMxy = SUMxy + (xyCollection + i)->x * (xyCollection + i)->y;
            //sum of squared x
            SUMxx = SUMxx + (xyCollection + i)->x * (xyCollection + i)->x;
        }
        
        //calculate the means of x and y
        AVGy = SUMy / dataSize;
        AVGx = SUMx / dataSize;
        
        //slope or a1
        slope = (dataSize * SUMxy - SUMx * SUMy) / (dataSize * SUMxx - SUMx*SUMx);
        
        if (forceThroughZero)
        {
            slope = SUMxy / SUMxx;
        }
        else
        {
            //y itercept or a0
            y_intercept = AVGy - slope * AVGx;
        }
        
        printf("x mean(AVGx) = %0.5E\n", AVGx);
        printf("y mean(AVGy) = %0.5E\n", AVGy);
        
        printf ("\n");
        printf ("The linear equation that best fits the given data:\n");
        printf ("       y = %2.8lfx + %2.8f\n", slope, y_intercept);
        printf ("------------------------------------------------------------\n");
        printf ("   Original (x,y)   (y_i - y_avg)^2     (y_i - a_o - a_1*x_i)^2\n");
        printf ("------------------------------------------------------------\n");
        
        //calculate squared residues, their sum etc.
        for (int i = 0; i < dataSize; i++)
        {
            //current (y_i - a0 - a1 * x_i)^2
            Yres = pow(((xyCollection + i)->y - y_intercept - (slope * (xyCollection + i)->x)), 2);
            
            //sum of (y_i - a0 - a1 * x_i)^2
            SUM_Yres += Yres;
            
            //current residue squared (y_i - AVGy)^2
            res = pow((xyCollection + i)->y - AVGy, 2);
            
            //sum of squared residues
            SUMres += res;
            
            printf ("   (%0.2f %0.2f)      %0.5E         %0.5E\n", (xyCollection + i)->x, (xyCollection + i)->y, res, Yres);
        }
        
        //calculate r^2 coefficient of determination
        Rsqr = (SUMres - SUM_Yres) / SUMres;
        
        printf("--------------------------------------------------\n");
        printf("Sum of (y_i - y_avg)^2 = %0.5E\t\n", SUMres);
        printf("Sum of (y_i - a_o - a_1*x_i)^2 = %0.5E\t\n", SUM_Yres);
        printf("Standard deviation(St) = %0.5E\n", sqrt(SUMres / (dataSize - 1)));
        printf("Standard error of the estimate(Sr) = %0.5E\t\n", sqrt(SUM_Yres / (dataSize-2)));
        printf("Coefficent of determination(r^2) = %0.5E\t\n", (SUMres - SUM_Yres)/SUMres);
        printf("Correlation coefficient(r) = %0.5E\t\n", sqrt(Rsqr));
        
        ret.slope = slope;
        ret.y_intercept = y_intercept;
        
        printf("slope %f offset %f \n", slope, y_intercept);
        
        return ret;
    }
    
    static void test()
    {
        test1();
        test2();
    }
    
    static void test1()
    {
        using namespace std;
        
        int i,n;
        
        n = 6;
        double x[n], y[n], a, b;
        
        y[0] = 1.13333333;
        y[1] = 1.26666667;
        y[2] = 1.53333333;
        y[3] = 2.03333333;
        y[4] = 3.06666667;
        y[5] = 4.13333333;
        
        x[0] = 0.16666667;
        x[1] = 0.33333333;
        x[2] = 0.66666667;
        x[3] = 1.33333333;
        x[4] = 2.66666667;
        x[5] = 4.00000000;
        
        double xsum=0, x2sum=0, ysum=0, xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
        for (i=0;i<n;i++)
        {
            xsum=xsum+x[i];                        //calculate sigma(xi)
            ysum=ysum+y[i];                        //calculate sigma(yi)
            x2sum=x2sum+pow(x[i],2);                //calculate sigma(x^2i)
            xysum=xysum+x[i]*y[i];                    //calculate sigma(xi*yi)
        }
        a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope
        b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);            //calculate intercept
        double y_fit[n];                        //an array to store the new fitted values of y
        for (i=0;i<n;i++)
            y_fit[i]=a*x[i]+b;                    //to calculate y(fitted) at given x points
        cout<<"S.no"<<setw(5)<<"x"<<setw(19)<<"y(observed)"<<setw(19)<<"y(fitted)"<<endl;
        cout<<"-----------------------------------------------------------------\n";
        for (i=0;i<n;i++)
            cout<<i+1<<"."<<setw(8)<<x[i]<<setw(15)<<y[i]<<setw(18)<<y_fit[i]<<endl;//print a table of x,y(obs.) and y(fit.)
        cout<<"\nThe linear fit line is of the form:\n\n"<<a<<"x + "<<b<<endl;        //print the best fit line
    }
    
    static void test2()
    {
        std::vector<Point> points;
        Point p;
        
        p.x = 0.16666667;
        p.y = 1.13333333;
        points.push_back(p);
        
        p.x = 0.33333333;
        p.y = 1.26666667;
        points.push_back(p);
        
        p.x = 0.66666667;
        p.y = 1.53333333;
        points.push_back(p);
        
        p.x = 1.33333333;
        p.y = 2.03333333;
        points.push_back(p);
        
        p.x = 2.66666667;
        p.y = 3.06666667;
        points.push_back(p);
        
        p.x = 4.00000000;
        p.y = 4.13333333;
        points.push_back(p);
        
        leastSqrRegression(&points[0], points.size(), false);
        leastSqrRegression(&points[0], points.size(), true);
    }
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    MathTest();
    MathTest(const MathTest&);
    MathTest& operator=(const MathTest&);
};

#endif /* MathTest_h */
