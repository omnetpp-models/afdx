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

#include "RedundancyChecker.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(RedundancyChecker);

void RedundancyChecker::initialize()
{
	enabled = par("enabled");
	skewMax = par("skewMax");
	lastFrameReceived = simTime();
	nextSeqExpected = 0;
}

void RedundancyChecker::handleMessage(cMessage *msg)
{
	// if not enabled just pass through all frames received
	if (!enabled) {
		send(msg,"out");
		return;
	}

	// filter out redundant messages
    AFDXMessage *afdxMsg = check_and_cast<AFDXMessage *>(msg);
    int currSeqNum = afdxMsg->getSeqNum();

    // drop the frame if the seqNum is smaller than the one we are expecting
    // and the last frame was received recently (less than skewMax time ago)
    if (currSeqNum < nextSeqExpected && simTime() - lastFrameReceived <= skewMax) {
		delete msg;
		return;     // frame dropped. do not update the next expected counter
	}
	send(msg,"out");

	lastFrameReceived = simTime();
    // store the last sequence number.
	nextSeqExpected = currSeqNum + 1;
    if (nextSeqExpected > 255)
    	nextSeqExpected = 1;
}

}; // namespace afdx

