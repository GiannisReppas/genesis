#ifndef GENESIS_UTILS_MATH_MATRIX_PCA_H_
#define GENESIS_UTILS_MATH_MATRIX_PCA_H_

/*
    Genesis - A toolkit for working with phylogenetic data.
    Copyright (C) 2014-2016 Lucas Czech

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lucas.czech@h-its.org>
    Exelixis Lab, Heidelberg Institute for Theoretical Studies
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/

/**
 * @brief
 *
 * @file
 * @ingroup utils
 */

#include "utils/math/matrix.hpp"

#include <vector>

namespace genesis {
namespace utils {

// ================================================================================================
//     Settings for Functions
// ================================================================================================

/**
 * @brief Setting for principal_component_analysis() to determine which form of standardization
 * of the data to use prior to perfoming the PCA.
 */
enum class PcaStandardization
{
    /**
     * @brief Standardize the mean and variance of the data before performing the PCA.
     *
     * Best to use when the data has widely varying scales in between the columns, i.e., if the
     * columns present data from different domains.
     * Also, see correlation_matrix().
     */
    kCorrelation,

    /**
     * @brief Standardize the mean, but not the variance of the data before performing the PCA.
     *
     * Best to use when the data has similar scales in between the columns, i.e., if the columns
     * present data from the same domain.
     * Also, see covariance_matrix().
     */
    kCovariance,

    /**
     * @brief Do not perform any standardization prior to performing the PCA.
     *
     * Not recommended.
     * Also, see sums_of_squares_and_cross_products_matrix().
     */
    kSSCP
};

// ================================================================================================
//     Structs for Storing Results
// ================================================================================================

/**
 * @brief Helper structure used for the eigenvalue decomposition in reduce_to_tridiagonal_matrix()
 * and tridiagonal_ql_algorithm(). See there for details.
 */
struct TridiagonalDecompositionData
{
    std::vector<double> eigenvalues;
    std::vector<double> intermediates;
};

struct PcaData
{
    std::vector<double> eigenvalues;
    Matrix<double>      eigenvectors;
    Matrix<double>      projection;
};

// ================================================================================================
//     Helper Functions
// ================================================================================================

/**
 * @brief Triangular decomposition of a symmetric matrix.
 *
 * This function performs an intermediate step that is usually followed by an execution of the
 * tridiagonal_ql_algorithm().
 *
 * It uses the Householder reduction of matrix a to tridiagonal form, according to
 *
 *     Martin et al., Num. Math. 11, 181-195, 1968.
 *     Ref: Smith et al., Matrix Eigensystem Routines -- EISPACK Guide
 *     Springer-Verlag, 1976, pp. 489-494.
 *     W H Press et al., Numerical Recipes in C, Cambridge U P, 1988, pp. 373-374.
 *
 * There, the function is called `tred2()`.
 *
 * This implementation was inspired by
 * https://github.com/davidhalter-archive/ardour/blob/master/libs/qm-dsp/maths/pca/pca.c
 * published under GPL 2+.
 *
 * @param data Input data matrix. Operations are performed inline, that is, the matrix is changed
 *             during execution of the function.
 */
TridiagonalDecompositionData reduce_to_tridiagonal_matrix( Matrix<double>& data );

/**
 * @brief Reduce a symmetric matrix to a symmetric tridiagonal matrix.
 *
 * Uses the data and the intermediate result after executing reduce_to_tridiagonal_matrix()
 * in order to run the algorithm. See there for details.
 *
 * Both parameters are modified during the algorithm. After it is finished,
 * `tri.eigenvalues` contains the eigenvalus and `data` the associated eigenvectors of the
 * original data.
 */
void tridiagonal_ql_algorithm( Matrix<double>& data, TridiagonalDecompositionData& tri );

// ================================================================================================
//     Principal Component Analysis
// ================================================================================================

PcaData principal_component_analysis(
    Matrix<double> const& data,
    size_t                components      = 0,
    PcaStandardization    standardization = PcaStandardization::kCorrelation
);

} // namespace utils
} // namespace genesis

#endif // include guard
