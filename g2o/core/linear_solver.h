// g2o - General Graph Optimization
// Copyright (C) 2011 R. Kuemmerle, G. Grisetti, W. Burgard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef G2O_LINEAR_SOLVER_H
#define G2O_LINEAR_SOLVER_H
#include "sparse_block_matrix.h"

namespace g2o {

/**
 * \brief basic solver for Ax = b
 *
 * basic solver for Ax = b which has to reimplemented for different linear algebra libraries.
 * A is assumed to be symmetric (only upper triangular block is stored) and positive-semi-definit.
 */
template <typename MatrixType>
class LinearSolver
{
  public:
    LinearSolver() {};
    virtual ~LinearSolver() {}

    /**
     * init for operating on matrices with a different non-zero pattern like before
     */
    virtual bool init() = 0;

    /**
     * Assumes that A has the same non-zero pattern over several calls.
     * If the pattern changes call init() before.
     * solve system Ax = b, x and b have to allocated beforehand!!
     */
    virtual bool solve(const SparseBlockMatrix<MatrixType>& A, double* x, double* b) = 0;

    /**
     * Inverts the diagonal blocks of A
     * @returns false if not defined.
     */
    virtual bool solveBlocks(double**&blocks, const SparseBlockMatrix<MatrixType>& A) { (void)blocks; (void) A; return false; }


    /**
     * Inverts the a block pattern of A in spinv
     * @returns false if not defined.
     */
    virtual bool solvePattern(SparseBlockMatrix<MatrixXd>& spinv, const std::vector<std::pair<int, int> >& blockIndices, const SparseBlockMatrix<MatrixType>& A){
      (void) spinv;
      (void) blockIndices;
      (void) A;
      return false;
    }
};

} // end namespace

#endif
