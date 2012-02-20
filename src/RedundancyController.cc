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

#include "RedundancyController.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(RedundancyController);

void RedundancyController::initialize()
{
	copyToLinkA = par("copyToLinkA");
	copyToLinkB = par("copyToLinkB");
	seqNum = 0;
}

void RedundancyController::handleMessage(cMessage *msg)
{
    AFDXMessage *afdxMsg = check_and_cast<AFDXMessage *>(msg);
    afdxMsg->setSeqNum(seqNum);

	if (copyToLinkA) {
	    afdxMsg->setInterfaceId(1);     // set to 1 for interface A
	    send((cMessage *)afdxMsg, "outA");

	    if ( copyToLinkB ) {
			AFDXMessage *afdxMsg2 = check_and_cast<AFDXMessage *>(msg->dup());
			afdxMsg2->setInterfaceId(2);    // set to 2 for interface B
			send((cMessage *)afdxMsg2, "outB");
	    }
	} else if (copyToLinkB ) {
	    afdxMsg->setInterfaceId(2);     // set to 2 for interface B
	    send((cMessage *)afdxMsg, "outB");
	} else
		error("redundancy controller has no enabled output");


	if ( ++seqNum > 255 )  // increase / wrap around the sequence number according to the specification
		seqNum = 1;
}

}; // namespace afdx

