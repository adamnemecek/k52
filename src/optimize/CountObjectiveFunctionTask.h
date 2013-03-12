/*
 * CountObjectiveFunctionTask.h
 *
 *  Created on: Mar 11, 2012
 *      Author: feanor
 */

#ifndef COUNTOBJECTIVEFUNCTIONTASK_H_
#define COUNTOBJECTIVEFUNCTIONTASK_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include <optimize/ParametersLocalStorage.h>
#include <optimize/IObjectiveFunction.h>

#ifdef BUILD_WITH_MPI
#include <parallel/mpi/IMpiTask.h>
#include <parallel/mpi/IMpiTaskResult.h>
#endif

class CountObjectiveFunctionTask
#ifdef BUILD_WITH_MPI
	: public k52::parallel::mpi::IMpiTask
#endif
{
public:
	typedef boost::shared_ptr<CountObjectiveFunctionTask> shared_ptr;

	CountObjectiveFunctionTask();

	CountObjectiveFunctionTask(const IParameters* parameters,
			const IObjectiveFunction* functionToOptimize);

	#ifdef BUILD_WITH_MPI

	virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr performMpi() const;

	virtual k52::parallel::mpi::IMpiTaskResult::shared_ptr createEmptyResult() const;

	virtual CountObjectiveFunctionTask* clone() const;

	virtual void send(boost::mpi::communicator* communicator, int target) const;

	virtual void receive(boost::mpi::communicator* communicator);

	#endif

private:

	//TODO are functors thread-safe not to copy locally them?
	const IObjectiveFunction* _functionToOptimize;
	const IParameters*  _parameters;
};

#endif /* COUNTOBJECTIVEFUNCTIONTASK_H_ */