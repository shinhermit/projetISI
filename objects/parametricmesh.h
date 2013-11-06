/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Specializes TriMesh for parametric surfaces
 *
 *
 */
#ifndef PARAMETRICMESH_H
#define PARAMETRICMESH_H

#include <sstream>

#include "triMesh.h"

namespace my{

/**
 * Defines the squeleton of parametric surfaces (ones based on parametric equations).
 * Specializes TriMesh.
 * Surfaces in 3D can be pametrized by two parameters, that we will name s and t.
 * The purpose of this class is to provide a sampler that allow to get a discrete surface from a continuous mathematical system of equations.
 * Sampling is considered as an application {0,..,n}x{0,..,m} -> [minS,maxS]x[minT,maxT] (natural integer to real).
 * n and m above are called imax and jmax below.
 *
 */
class ParametricMesh : public TriMesh
{
protected:
    int _imax; /*!< Parameter s max sampling step value*/
    int _jmax; /*!< Parameter t max sampling step value*/

    /**
      * Provides the actual parameters (float types values of parameters (s,t)) corresponding to the point of the surface sampled at integers m,n.
      * Sampling if considered as an application (s,t) = sample(m,n).
      * For a comprehensive explanation of sampling principle, see the ParametricMesh class description above.
      * @param m current sampling step of parameter s
      * @param n current sampling step of parameter t
      */
    virtual my::Parameters _sampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument);

    /**
      * Provides the indice of the vertex sampled at sampling steps (m,n). This indice is the number of the vertex in the mesh.
      * @see _sampled
      * @param m sampling step of parameter s
      * @param n sampling step of parameter t
      */
    virtual int _indiceOfSampled(const int & m, const int & n)const throw(std::logic_error, std::invalid_argument);

    void _preSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & i_max, const int & j, const int & j_max)const throw(std::invalid_argument);
    void _preIndiceOfSampled(const std::string & className, const std::string & sParamName, const std::string & tParamName, const std::string & sRange, const std::string & tRange, const int & i, const int & i_max, const int & j, const int & j_max)const throw(std::invalid_argument);
    void _preSetMax(const int & max, const std::string & setter);
public:
    ParametricMesh(const std::string & name="ParametricMesh", const int & imax=0, const int & jmax=0);

    /**
      * Parameter s max sampling value setter.
      * For explanation about imax and jmax, see the class description above.
      */
    void setImax(const int & imax) throw(std::invalid_argument);
    /**
      * Parameter t max sampling value setter.
      * For explanation about imax and jmax, see the class description above.
      */
    void setJmax(const int & jmax) throw(std::invalid_argument);
    /**
      * Parameter s max sampling value getter.
      * For explanation about imax and jmax, see the class description above.
      */
    int imax() const;
    /**
      * Parameter t max sampling value getter.
      * For explanation about imax and jmax, see the class description above.
      */
    int jmax() const;

    /**
      * Public version of protected _indiceOfSampled.
      * I finally ended up needing the services of _indiceOfSampled outside the class (for mesh sewing), but it was too much code to change, so added this method.
      * @see _indiceOfSampled
      */
    int indiceOfSampled(const int & m, const int & n)const;

    /**
     * adds multiple vertex using the surface parametric equation
     * the surface parameters are (s,t)
     * The method uses the protected method _sampled(const int & m, const int & n), that is abstract and must be defined by every subclass of ParametricMesh
     * @param imax limit value for sampling the s parameter
     * @param jmax limit value for sampling the t parameter
     */
    void parametricVertexInsertion(const int & imax, const int & jmax,
                                   my::Parametric &coord);

    /**
     * adds multiple traingles using the surface parametric equation
     * the surface parameters are (s,t)
     * The method uses the protected method _indiceOfSampled(const int & m, const int & n), that is abstract and must be defined by every subclass of ParametricMesh
     * @param imax limit value for sampling the s parameter
     * @param jmax limit value for sampling the t parameter
     */
    void parametricTriangleInsertion(const int & imax, const int & jmax);
};

}

#endif // PARAMETRICMESH_H
