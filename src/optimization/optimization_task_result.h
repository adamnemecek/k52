#ifndef OPTIMIZATION_TASK_RESULT_H
#define OPTIMIZATION_TASK_RESULT_H

#include <k52/parallel/i_task_result.h>
#include <k52/optimization/params/i_parameters.h>

#ifdef BUILD_WITH_MPI
#include <k52/parallel/mpi/i_mpi_task_result.h>
#endif

namespace k52
{
namespace optimization
{

class OptimizationTaskResult :

#ifdef BUILD_WITH_MPI
    public k52::parallel::mpi::IMpiTaskResult
#else
    public k52::parallel::ITaskResult
#endif

{
public:
    typedef boost::shared_ptr<OptimizationTaskResult> shared_ptr;

    OptimizationTaskResult(const IParameters* optimal_parameters);

#ifdef BUILD_WITH_MPI

    virtual boost::mpi::request ReceiveAsync(boost::mpi::communicator* communicator, int source);

    virtual void Send(boost::mpi::communicator* communicator);

#endif

private:
    IParameters::shared_ptr optimal_parameters_;
};

}/* namespace optimization */
}/* namespace k52 */

#endif /* OPTIMIZATION_TASK_RESULT_H */
