#ifndef GSLAM_H
#define GSLAM_H

#include <Eigen/Dense>
#include <vector>
#include <utility>
#include "ros/ros.h"

using namespace std;

namespace gslam {

    typedef Eigen::MatrixXd Matrix;
    typedef Eigen::MatrixXi MatrixI;
    typedef Eigen::VectorXd Vector;

    class gSLAM{

        public:

            // GIANT TODO: Currently setup in such a way that we get giant problems with regards to NEW / DELETE; REWRITE THIS

            /***
             * Global Input Variable documentation:
             *
             *  - Each row in a matrix is another timestep T
             *
             *  - Control is a matrix in which rows designate timesteps and the columns: dX, dY, dRotation
             */


            /*****************************************
             *  CON- / De- structors Declarations
             *****************************************/

            gSLAM();
            ~gSLAM();

            /*****************************************
             *  Method Declarations
             *****************************************/


            /****
             * Given the control and measurements from 0:t; updates the internal slam representation and returns an estimated pose
             *     See Table 10, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
             */

            Vector* graphslam(Matrix* control, Matrix* measurements);



            /*****************************************
             *  GRAPH SLAM HIGH LEVEL METHODS
             *****************************************/


            /****
             * Initializes the GSLam algorithm; given input from start till t and returns the estimated mean poses from 0:t
             *      - input: delta Speed & delta Rotation per row
             *     See Table 1, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
             */

            Matrix* /* allPreviousMu */ initialize(Matrix& control);


            /****
             * Constructs the omega matrix and xi; given input, measurements, correspondence and estimated mean poses from 0:t
             *      See Table 2, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
             */

            pair<Matrix* /* omega */, Vector* /* xi */> linearize(Matrix* input, Matrix* measurements, MatrixI* correspondence, Matrix* estimatedPoses);


            /****
              * Reduces the vector and matrix given, by removing the features
              *     reducedOmega    : v
              *     reducedXi       : v
              *
              *     See Table 3, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
              */

            pair<Matrix* /* reducedOmega */, Vector* /* reducedXi */ > reduce(Matrix* omega, Vector* xi);


            /****
             * Computes the mean and covariance of all poses in the robot path, and the mean location estimate of all features.
             *      mu      : a vector containing the mean location estimate of all features
             *      sigma   : inverted reducedOmega
             *
             *     See Table 4, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
             */

            pair<Vector* /* mu */, Matrix* /* sigma */> solve(Matrix* reducedOmega, Vector* reducedXi, Matrix* omega, Vector* xi);


            /****
             * Returns how likely feature A corresponds to feature B
             *      See Table 9, Thrun-Montemerlo, 2006, 'The GraphSLAM Algorithm with Applications to Large-Scale Mapping of Urban Structures'
             */

            double /* Pi_a_b */ correspondenceTest(Matrix* omega, Vector* xi, Matrix* sigma, int featureIdxA, int featureIdxB);


            /*****************************************
             *  GRAPH SLAM LOW LEVEL UTILITY METHODS
             *****************************************/

            /****
             * Returns a matrix initialized with unique index for each correspondence(timeStep, featureIndex)
             */
            MatrixI* /* correspondence */ createCorrespondence(Matrix* input, Matrix* measurements);

                /* Variable Declarations */

            // Correspondence threshold for feature correspondence test
            static double CHI;
    };

}

using namespace gslam;

int main(int argc, char **argv){
    //ros::init(argc, argv, "graphSlam");  // Initiate new ROS node named "fastSlam"
    //ros::NodeHandle n;
    gSLAM gslam;

    Matrix control = Matrix::Random(12,3);
    Matrix* c = gslam.initialize(control);

    cout << "Control matrix is: \n" << control << endl;
    cout << "After initialization the matrix is: \n" << *c << endl;
}


#endif // GSLAM_H
