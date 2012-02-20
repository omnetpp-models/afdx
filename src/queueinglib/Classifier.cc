//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#include "QueueingUtils.h"
#include "Classifier.h"
#include "Job.h"

namespace queueing {

Define_Module(Classifier);

void Classifier::initialize()
{
    dispatchField = par("dispatchField");
}

void Classifier::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job *>(msg);
    int outGateIndex =  getFieldAsLong(msg, dispatchField);

    if (outGateIndex < 0 || outGateIndex >= gateSize("out")) {
    	if (!gate("rest")->isPathOK())
    		error("cannot classify job and the 'rest' gate is not connected: %s contains %i but the out gate size is %i",dispatchField, outGateIndex, gateSize("out"));

        send(job, "rest");
    }
    else
        send(job, "out", outGateIndex);
}

}; //namespace

