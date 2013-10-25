#ifndef PARAMETRICMESH_H
#define PARAMETRICMESH_H

#include <sstream>

#include "triMesh.h"

namespace my{

class ParametricMesh : public TriMesh
{
protected:
    int _imax; /*!< Parameter s max sampling step value*/
    int _jmax; /*!< Parameter t max sampling step value*/

    virtual my::Parameters _sampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument);

    virtual int _indiceOfSampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument);

    void _preSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & i_max, const int & j, const int & j_max)const throw(std::invalid_argument);
    void _preIndiceOfSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & i_max, const int & j, const int & j_max)const throw(std::invalid_argument);
    void _preSetMax(const int & max, const std::string & setter);
public:
    ParametricMesh(const std::string & name="ParametricMesh", const int & imax=0, const int & jmax=0);

    //getters and setter for max sampling values
    void setImax(const int & imax) throw(std::invalid_argument);
    void setJmax(const int & jmax) throw(std::invalid_argument);
    int imax() const;
    int jmax() const;

    /**
      * Public version of protected _indiceOfSampled.
      * I finally ended up needing the services of _indiceOfSampled outside tha class (for mesh sewing), but it was too much code to change, so added this method.
      * @see _indiceOfSampled
      */
    int indiceOfSampled(const int & m, const int & n)const;

    /**
     * adds multiple vertex using the surface parametric equation
     * the surface parameters are (s,t)
     * @param imax limit value for sampling the s parameter
     * @param jmax limit value for sampling the t parameter
     */
    void parametricVertexInsertion(const int & imax, const int & jmax,
                                   my::Parametric &coord);

    /**
     * adds multiple traingles using the surface parametric equation
     * the surface parameters are (s,t)
     * @param imax limit value for sampling the s parameter
     * @param jmax limit value for sampling the t parameter
     */
    void parametricTriangleInsertion(const int & imax, const int & jmax);
};

}

#endif // PARAMETRICMESH_H
