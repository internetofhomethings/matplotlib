//----------------------------------------------------------------
//This Windows Console App links the matplotlib to thw application
//a few example plots are provided. They are selected by starting
//the application with a parameter:
//plotter     : Plots a Sinewave
//plotter 1   :
//plotter 2   : plots 3d vector object which can rotate by 
//              dragging with mouse
//----------------------------------------------------------------

#include "matplotlibcpp.h"
#include <iostream>
#include <cmath>

#define M_PI 3.14

int main(int argc, char* argv[])
{
    int plotsel;
    const char* filename = "test1.png";
    int n=0,i=0,sinamp=50;

    namespace plt = matplotlibcpp;

    std::vector<std::vector<double>> x, y, z;
    std::vector<double> a(n), b(n), c(n), w(n, 2);


    plt::backend("wxagg");

    if (argc == 2)
    {
        plotsel = atoi(argv[1]);
    }
    else
    {
        plotsel = 0;
    }
    switch(plotsel)
    {
        case 1:
            plt::plot({ 1,3,2,4 });
            plt::show();

            // Add graph title
            plt::title("Sample figure");

            // Enable legend.
            plt::legend();

            // save figure
            plt::save(filename);
            break;
        case 2:
            //
            for (double i = -5; i <= 5; i += 0.25) {
                std::vector<double> x_row, y_row, z_row;
                for (double j = -5; j <= 5; j += 0.25) {
                    x_row.push_back(i);
                    y_row.push_back(j);
                    z_row.push_back(::std::sin(::std::hypot(i, j)));
                }
                x.push_back(x_row);
                y.push_back(y_row);
                z.push_back(z_row);
             }

            plt::plot_surface(x, y, z);
            plt::show();
            //
            break;
        default:               
               n = 1500; // 500 data points
               sinamp = 50;
                std::vector<double> x(n), y(n), z(n), w(n, 2);
                
                for (int i = 0; i < n; ++i) 
                {
                    x.at(i) = i;
                    y.at(i) = sinamp*sin(2 * M_PI * i / 360.0);
                    z.at(i) = (sinamp/2) * sin(2 * M_PI * i / 1440);
                }

                plt::figure(); // declare a new figure (optional if only one is used)
                
                plt::plot(x, y); // automatic coloring: tab:blue
                plt::show(false);
                plt::plot(x, w, "r--");                 // red dashed line
                plt::plot(x, y, { {"label", "sin 1"} }); // legend label "log(x)"
                plt::plot(x, z, { {"label", "sin 2"} }); // legend label "log(x)"

                plt::xlim(0, n);    // x-axis interval: [0, n sample]
                plt::title("Sine Wave Plot"); // set a title
                plt::legend();                // enable the legend

                //plt::savefig("standard.pdf"); // save the figure
                plt::show();
                
                break;
    }

}
