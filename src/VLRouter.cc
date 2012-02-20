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

#include "VLRouter.h"
#include "AFDXMessage_m.h"

namespace afdx {

Define_Module(VLRouter);

void VLRouter::initialize()
{
	// TODO - Generated method body
}

void VLRouter::handleMessage(cMessage *msg)
{
    AFDXMessage *afdxMsg = check_and_cast<AFDXMessage *>(msg);

	int vlId = afdxMsg->getVirtualLinkId();
	// send a copy on each gate but the last, and the original on the last gate
	for (int i=0; i<gateSize("out"); i++)
	{
		// TODO this is just a fake routing table that routes to the vlId-1 and vlID+1 port
	    // a correct routing algorithm should be implemented here possibly reading the
	    // rules from an external file
		if (vlId + 1 == i || vlId -1 == i)
			send((cMessage *)afdxMsg->dup(), "out", i);
	}
	delete afdxMsg;
}

}; // namespace afdx

