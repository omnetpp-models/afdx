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

#include "IntegrityChecker.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(IntegrityChecker);

void IntegrityChecker::initialize()
{
	// on reset expectedSeqNum should be zeroed. This allows the reception of the first frame after the reset
	expectedSeqNum = 0;
}

void IntegrityChecker::handleMessage(cMessage *msg)
{
    AFDXMessage *afdxMsg = check_and_cast<AFDXMessage *>(msg);
    int currSeqNum = afdxMsg->getSeqNum();

    if (expectedSeqNum == 0 || currSeqNum == 0 || currSeqNum == expectedSeqNum || currSeqNum == expectedSeqNum + 1)
    	send(msg,"out");
    else {
    	EV << "frame with sequence number " << currSeqNum << "dropped. Expected: " << expectedSeqNum;
    	delete msg;
    }

    // store the last sequence number.
    expectedSeqNum = currSeqNum + 1;
    if (expectedSeqNum > 255)
    	expectedSeqNum = 1;
}

}; // namespace afdx

