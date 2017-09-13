//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "MAC.h"
#include "queueinglib/IPassiveQueue.h"

namespace afdx {

Define_Module(MAC);

MAC::MAC()
{
    selectionStrategy = NULL;
    reserved = false;
    endServiceMsg = NULL;
}

MAC::~MAC()
{
    delete selectionStrategy;
    cancelAndDelete(endServiceMsg);
}


void MAC::initialize()
{
    endServiceMsg = new cMessage("end-tx");
    reserved = false;
    selectionStrategy = queueing::SelectionStrategy::create(par("fetchingAlgorithm"), this, true);
    if (!selectionStrategy)
        error("invalid selection strategy");
    max_frame_age = par("maxFrameAge");
}

bool MAC::isIdle()
{
    return !reserved;
}

void MAC::reserve()
{
    Enter_Method("reserve()");

    if (reserved)
		error("trying to reserve a server which is already reserved");

    reserved = true;
}

void MAC::handleMessage(cMessage *msg)
{
	// serviceMessage.
  	// tx end. Free up the interface and request additional frames if any
    if (msg == endServiceMsg)
    {
        ASSERT(reserved);
        reserved = false;

        // examine all input queues, and request a new frame from a non empty queue
        int k = selectionStrategy->select();
        if (k >= 0)
        {
            EV << "requesting frame from queue " << k << endl;
            cGate *gate = selectionStrategy->selectableGate(k);
            check_and_cast<queueing::IPassiveQueue *>(gate->getOwnerModule())->request(gate->getIndex());
            reserved = true;
        }

        return;
    }

    // received on ethernet in port
    if (msg->arrivedOn("eth$i")) {
    	// decapsulation
    	cPacket *cpkt = check_and_cast<cPacket *>(msg);
    	cpkt->setByteLength(cpkt->getByteLength() - 7 - 1); // decrease the size (PREAMBLE + SFD)
    	// store the current timestamp (the time of last bit received). Can be used to drop timed out frames
    	msg->setTimestamp();
		// send out to upper layers
		send(msg,"out");
		return;  // do not allow a fallback because msg->arrivedOn("in") would return now true (we already sent out the message)
	}

	// frame to be sent to ethernet out port
	if (msg->arrivedOn("in")) {
	    {
	        if (!reserved)
	            error("frame arrived but the MAC was not correctly reserved");

	        cGate *ethOutGate = gate("eth$o");
	        if (!ethOutGate->isPathOK()) {
	            EV << "dropping frame. " << getParentModule()->getFullName() << " is not connected. " << endl;
	            scheduleAt(simTime(), endServiceMsg);  // reschedule the message for now, try to get an other frame
	            delete msg;
	            return;
	        }


	        cDatarateChannel *drChan = check_and_cast<cDatarateChannel *>(ethOutGate->getTransmissionChannel());

	    if (drChan->isBusy())
	        error("trying to send out on a transmission line while the line is busy");

	        if (drChan->isDisabled()) {
	            EV << "dropping frame. Channel is disabled. " << endl;
	            scheduleAt(simTime(), endServiceMsg);  // reschedule the message for now, try to get an other frame
	            delete msg;
	            return;
	        }

	        // encapsulation
	    	cPacket *cpkt = check_and_cast<cPacket *>(msg);
	    	cpkt->addByteLength(7 + 1);  // increase length with (PREAMBLE + SFD)

	    	// reserve the transmitter and send out (start sending) the frame
	        reserved = true;
	        send(msg, ethOutGate);

	        // we have scheduled the message so we can get back the transmission finish time now
	        // check for frames that are too old
	        simtime_t frame_age = drChan->getTransmissionFinishTime() - msg->getTimestamp();
	        if (frame_age > max_frame_age) {
	            EV << "dropping frame. It is too old: " << frame_age << "s" << endl;
	            cancelAndDelete(msg);
	            scheduleAt(simTime(), endServiceMsg);  // reschedule the message for now, try to get an other frame
	            return;
	        }
	        // calculate inter-frame gap (12byte) and add it to the processing time
	        simtime_t IFG_TIME = 12 * 8 / drChan->getDatarate();
	        scheduleAt(drChan->getTransmissionFinishTime() + IFG_TIME, endServiceMsg);

	    }
	    return;
	}
}

}; // namespace afdx

